(* autor: Maciej Pacut *)

open Model;;
open Math;;
open Transformations;;

exception Break;; (* symulacja break loop z C *)

let identity x = x;;

let (|>) x f = f x;;

type color = float * float * float;;

let (screen_width, screen_height) = (600., 600.);;
let projection_d = 1.0;;

(*
  pomocnicza funkcja parsująca;
  specyfika modeli w formacie .OBJ polega na tym,
  że nie są w nim bezpośrednio zapisywane współrzędne wierzchołków każdego trójkąta;
  na początku pliku jest lista wierzchołków a następnie współrzędne trójkątów
  brane są przez indeksowanie tej listy;
  ta funkcja zamienia indeksy współrzędnych na współrzędne
*)
let indices_to_coordinates model =
  let indexed_vertices = Array.of_list model.vertices
  in List.map (fun (ind1 ,ind2, ind3) -> (indexed_vertices.(ind1 - 1),
					  indexed_vertices.(ind2 - 1),
					  indexed_vertices.(ind3 - 1))) model.tris;;

(* parsowanie modeli za pomocą ocamlyacc i ocamllex *)
let parse_model filename =
  let model = Parser.main Lexer.next
    (Lexing.from_channel (open_in filename))
  in indices_to_coordinates model;;

(* projekcja modelu na dwuwymiarową płaszczyznę ekranu *)
let flatten_vertex (x, y, z) =
  (screen_width *. projection_d *. x /. z +. (screen_width /. 2.0),
   screen_height *. projection_d *. y /. z +. (screen_height /. 2.0));;

let flatten_tri (a, b, c) =
  (flatten_vertex a,
   flatten_vertex b,
   flatten_vertex c);;

(* oświetlenie *)
type light = Ambient of color | Directed of vector * float;;

(* lista wszystkich świateł oświetlających model *)
let lights = [
  Ambient (0.2, 0.2, 0.2);
  Directed ((0.5, 0.5, 0.5), 0.5);
];;

let lighten lights (v1, v2, v3) =
  let values = List.map (function
			   | Ambient (r, g, b) -> (r, g, b)
			   | Directed (direction, brightness) ->
			       let diff =
			         (dot_product (normal_vector v1 v2 v3) direction) *. brightness
			       in (positive diff, positive diff, positive diff)) lights in
  let (r, g, b) = List.fold_right (fun (ax, ay, az) (bx, by, bz) -> (ax +. bx, ay +. by, az +. bz)) values (0.0, 0.0, 0.0)
  in Graphics.rgb
       (int (r *. 255.0))
       (int (g *. 255.0))
       (int (b *. 255.0));;

(*
  algorytm malarza, który jest zastosowany w moim silniku
  wymaga, aby trójkąty znajdujące się dalej zostały narysowane pierwsze
*)

let avg_z ((_,_,z1), (_,_,z2), (_,_,z3)) =
  (z1 +. z2 +. z3) /. 3.;;

let sort_z tris =
  Sort.list (fun a b -> avg_z a < avg_z b) tris;;

let visible (v1,v2,v3) =
  let vector_of_view = (0.0,0.0,1.0) in
  let diff =
    (dot_product (normal_vector v1 v2 v3) vector_of_view)
  in diff < 1.0;;

let render_tri (v1,v2,v3) =
  Graphics.set_color (lighten lights (v1,v2,v3));
  let f1, f2, f3 = flatten_tri (v1, v2, v3)
  in Graphics.fill_poly (Array.map (fun (x,y) ->
				      (int x, int y)) [| f1; f2; f3 |]);;

let render_world tris =
  tris
	     |> List.filter visible
	     |> sort_z
	     |> List.iter render_tri;;

(*
  główna pętla renderująca
  napisana czysto funkcyjnie, za pomocą rekurencji ogonowej
*)
let rec rendering_loop model =
  Graphics.auto_synchronize false;
  Graphics.clear_graph ();
  
  render_world model;

  Graphics.auto_synchronize true;
  
  (*
    transformation ma typ funkcji częsciowo zaaplikowanej;
    rendering_loop jest wywoływane rekurencyjnie z argumentem - transformowanym modelem;
    osobiście uważam, że to najładniejszy fragment tego programu; czegoś takiego nie da się napisać w C
  *)
  let transformation =
    match Graphics.read_key () with (* read_key wstrzymuje pętlę do czasu naciśnięcia klawisza *)
      | 'x' -> raise Break (* wyjście z pętli renderującej *)
      | 'd' -> move_right 0.1
      | 'a' -> move_left 0.1
      | 'w' -> move_up 0.1
      | 's' -> move_down 0.1
      | 'r' -> move_closer 0.1
      | 'f' -> move_further 0.1
      | 'q' -> rotate_y 0.01
      | 'e' -> rotate_y (-.0.01)
      | _   -> identity (* przypadkowe naciśnięcie innego klawisza nie zmienia stanu *)
  in
    rendering_loop (transformation model);;

let init_args =
  Printf.sprintf " %dx%d" (int screen_width) (int screen_height);;

(* tworzy okno, parsuje model i wchodzi do pętli renderującej *)
let run model_name =
  Graphics.open_graph init_args;
  Graphics.set_window_title "3d rendering engine";
  let model = parse_model model_name in
    try
      rendering_loop (move_further 1.0 model) (* oddalam na początku model, żeby kamera nie była wewnątrz *)
    with Break -> ()
      
let path_to_model () =
  if (Array.length Sys.argv) <> 2 then
    failwith "aby uruchomic program, nalezy podac jako argument sciezke do pliku modelu: 3d.e /path/to/model.obj\n"
  else
    Sys.argv.(1);;

(* punkt startowy programu *)
let () =
  run (path_to_model ());;
