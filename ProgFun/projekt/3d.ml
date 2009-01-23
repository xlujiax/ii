open Model;;

exception Break;; (* symulacja break loop z C *)

let int (f : float) = int_of_float f;;
let float (i : int) = float_of_int i;;

let identity x = x;;

let (|>) x f = f x;;

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

(* projekcja trójwymiarowych trójkątów na dwuwymiarową płaszczyznę ekranu *)
let flatten_vertex (x, y, z) =
  (screen_width *. projection_d *. x /. z,
   screen_height *. projection_d *. y /. z);;

let flatten_tri (a, b, c) =
  (flatten_vertex a,
   flatten_vertex b,
   flatten_vertex c);;

let flatten_model model = List.map flatten_tri model;;

(*
  algorytm malarza, który jest zastosowany w moim silniku
  wymaga, aby trójkąty znajdujące się dalej zostały narysowane pierwsze
*)

let avg_z ((_,_,z1), (_,_,z2), (_,_,z3)) =
  (z1 +. z2 +. z3) /. 3.;;

let sort_z tris =
  Sort.list (fun a b -> avg_z a < avg_z b) tris;;

let render_tri (v1,v2,v3) =
  Graphics.draw_poly (Array.map (fun (x,y) ->
				   (int x, int y)) [| v1; v2; v3 |]);;

(* algorytm malarza *)
let render_world tris =
  tris
  |>  sort_z
  |>  flatten_model
  |>  List.iter render_tri;;

(*
  zbiór czysto funkcyjnych funkcji poruszających modelem
  to funkcje typu (model -> model); nie modyfikują współrzędnych tylko tworzą nową kopię modelu
*)

(* model to lista trójkątów, to pomocnicza funkcja aplikująca przekształcenie do każdego wierzchołka każdego trójkąta *)
let transform vertex_transformation model =
  List.map (fun (v1, v2, v3) -> (vertex_transformation v1,
				 vertex_transformation v2,
				 vertex_transformation v3)) model;;

let move (vx, vy, vz) model =
  transform (fun (x, y, z) ->
	       (x +. vx, y +. vy, z +. vz)) model;;

(* ruch wzdłuż współrzędnej x *)
let move_left delta = move (-.delta, 0.0, 0.0);;
let move_right delta = move (delta, 0.0, 0.0);;

(* ruch wzdłuż współrzędnej y *)
let move_up delta = move (0.0, delta, 0.0);;
let move_down delta = move (0.0, -.delta, 0.0);;

(* ruch wzdłuż współrzędnej z *)
let move_closer delta = move (0.0, 0.0, delta);;
let move_further delta = move (0.0, 0.0, -.delta);;

(* obroty wg stałych osi *)
let rotate_x angle model =
  transform (fun (x, y, z) ->
	       (x, y *. (cos angle) -. z *. (sin angle), y *. (cos angle) -. z *. (sin angle))) model;;

let rotate_y angle model =
  transform (fun (x, y, z) ->
	       (x *. (cos angle) +. z *. (sin angle), y, z *. (cos angle) -. x *. (sin angle))) model;;

let rotate_z angle model =
  transform (fun (x, y, z) ->
	       (x *. (cos angle) -. y *. (sin angle), x *. (sin angle) +. y *. (cos angle), z)) model;;

(*
  główna pętla renderująca
  napisana czysto funkcyjnie, za pomocą rekurencji ogonowej
*)
let rec rendering_loop model =
  Graphics.auto_synchronize false;
  Graphics.clear_graph ();
  
  Graphics.set_color (Graphics.rgb 0 0 0);
  render_world model;

  Graphics.auto_synchronize true;
  
  (*
    transformation ma typ funkcji częsciowo zaaplikowanej;
    rendering_loop jest wywoływane rekurencyjnie z argumentem - transformowanym modelem;
    osobiście uważam, że to najładniejszy fragment tego silnika; czegoś takiego nie da się napisać w C
  *)
  let transformation =
    match Graphics.read_key () with (* read_key czeka na naciśnięcie klawisza *)
      | 'q' -> raise Break (* wyjście z pętli renderującej *)
      | 'd' -> move_right 0.1
      | 'a' -> move_left 0.1
      | 'w' -> move_up 0.1
      | 's' -> move_down 0.1
      | 'r' -> move_closer 0.1
      | 'f' -> move_further 0.1
      | 'y' -> rotate_y 0.1
      | 'h' -> rotate_y (-.0.1)
      | 'g' -> rotate_z 0.1
      | 'j' -> rotate_z (-.0.1)
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
      rendering_loop model
    with Break -> ()
    
let path_to_model () =
  if (Array.length Sys.argv) <> 2 then
    failwith "aby uruchomic program, nalezy podac jako argument sciezke do pliku modelu: 3d.e /path/to/model.obj\n"
  else
    Sys.argv.(1);;

(* punkt startowy programu *)
let () =
  run (path_to_model ());;
