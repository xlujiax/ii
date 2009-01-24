open Model;;

exception Break;; (* symulacja break loop z C *)

let int (f : float) = int_of_float f;;
let float (i : int) = float_of_int i;;

let identity x = x;;

let (|>) x f = f x;;

type vector = float * float * float;;
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
  (screen_width *. projection_d *. x /. z,
   screen_height *. projection_d *. y /. z);;

let flatten_tri (a, b, c) =
  (flatten_vertex a,
   flatten_vertex b,
   flatten_vertex c);;

(* oświetlenie *)
type light = Ambient of color | Directed of vector * float;;

(* lista wszystkich świateł oświetlających model *)
let lights = [
  Ambient (0.2, 0.2, 0.2);
  Directed ((-1.0, 0.0, 0.0), 0.5);
];;

let normalize (x, y, z) =
  let len = sqrt (x *. x +. y *. y +. z *. z) in
    (x /. len, y /. len, z/. len);;

let dot_product (x1, y1, z1) (x2, y2, z2) =
  let (nx2, ny2, nz2) = normalize (x2, y2, z2) in
    x1 *. nx2 +. y1 *. ny2 +. z1 *. nz2;;

let cross_product (x1, y1, z1) (x2, y2, z2) =
  (y1 *. z2 -. y2 *. z1,
   -.x1 *. z2 +. x2 *. z1,
   x1 *. y2 -. x2 *. y1);;

let mul_vector_by_scalar (x, y, z) s =
  (x *. s, y *. s, z *. s);;
    
let normal_vector (x1, y1, z1) (x2, y2, z2) (x3, y3, z3) =
  let a = (x1 -. x2, y1 -. y2, z1 -. z2)
  and b = (x2 -. x3, y2 -. y3, z2 -. z3) in
    normalize (cross_product a b);;

let absf x = if x >= 0.0 then x else -.x;;

let lighten lights (v1, v2, v3) =
  let values = List.map (function
			   | Ambient (r, g, b) -> (r, g, b)
			   | Directed (direction, brightness) ->
			       let diff =
			         (dot_product (normal_vector v1 v2 v3) direction) *. brightness
			       in (absf diff, absf diff, absf diff)) lights in
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

let render_tri (v1,v2,v3) =
  Graphics.set_color (lighten lights (v1,v2,v3));
  let f1, f2, f3 = flatten_tri (v1, v2, v3)
  in Graphics.fill_poly (Array.map (fun (x,y) ->
				   (int x, int y)) [| f1; f2; f3 |]);;

let render_world tris =
  tris
  |>  sort_z
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

let sum lst = List.fold_right (+.) lst 0.0;;
let average lst = (sum lst) /. (float (List.length lst));;

let average_position model =
  let x_coords = List.map (fun ((x1,_,_),(x2,_,_),(x3,_,_)) -> (x1 +. x2 +. x3) /. 3.0) model (* liczy średnie z 3 wierzchołków trójkąta *)
  and y_coords = List.map (fun ((_,y1,_),(_,y2,_),(_,y3,_)) -> (y1 +. y2 +. y3) /. 3.0) model
  and z_coords = List.map (fun ((_,_,z1),(_,_,z2),(_,_,z3)) -> (z1 +. z2 +. z3) /. 3.0) model
  in (average x_coords,
      average y_coords,
      average z_coords);;
   

(*
  obroty wg stałych osi
  funkcje rotujące przesuwają model do punktu 0,0,0
  następnie wykonują obrót i przywaracają do punktu początkowego;
  w przeciwnym przypadku model nie obracał się wg własnego środka, ale wokół punktu 0,0,0
*)

let rotate_x angle model =
  let (cx, cy, cz) = (average_position model) in
    transform (fun (x, y, z) ->
		 let (dx, dy, dz) = (cx -. x, cy -. y, cz -. z)
		 in (x,
		     dy *. (cos angle) -. dz *. (sin angle) +. cy,
		     dy *. (sin angle) +. dz *. (cos angle) +. cz)) model;;

let rotate_y angle model =
  let (cx, cy, cz) = (average_position model) in
    transform (fun (x, y, z) ->
		 let (dx, dy, dz) = (cx -. x, cy -. y, cz -. z)
		 in (dx *. (cos angle) +. dz *. (sin angle) +. cx,
		     y,
		     dz *. (cos angle) -. dx *. (sin angle) +. cz)) model;;

let rotate_z angle model =
  let (cx, cy, cz) = (average_position model) in
    transform (fun (x, y, z) ->
		 let (dx, dy, dz) = (cx -. x, cy -. y, cz -. z)
		 in (dx *. (cos angle) -. dy *. (sin angle) +. cx,
		     dx *. (sin angle) +. dy *. (cos angle) +. cy,
		     z)) model;;

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
      | 'q' -> rotate_x 0.01
      | 'e' -> rotate_x (-.0.01)
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
