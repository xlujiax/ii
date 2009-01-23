open Model;;

let int (f : float) = int_of_float f;;
let float (i : int) = float_of_int i;;

let (|>) x f = f x;;

let (screen_width, screen_height) = (600., 600.);;
let projection_d = 1.;;

(*
  pomocnicza funkcja parsująca;
  specyfika modeli w formacie .OBJ polega na tym,
  że nie są w nim bezpośrednio zapisywane współrzędne wierzchołków każdego trójkąta;
  na początku pliku jest lista wierzchołków a następnie współrzędne trójkątów
  brane są przez indeksowanie tej listy
*)
let indices_to_coordinates model =
  let v = Array.of_list model.vertices
  in List.map (fun (a,b,c)
	      -> (v.(a-1), v.(b-1), v.(c-1))) model.tris;;

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
  wymaga, aby trójkąty znajdujące się dalej zostały naryswoane pierwsze
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
  to funkcje typu (model -> model); nie modyfikują współrzędnych
*)

let move_left model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1 -. delta, y1, z1),
				   (x2 -. delta, y2, z2),
				   (x3 -. delta, y3, z3))) model;;

let move_right model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1 +. delta, y1, z1),
				   (x2 +. delta, y2, z2),
				   (x3 +. delta, y3, z3))) model;;

let move_up model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1, y1 +. delta, z1),
				   (x2, y2 +. delta, z2),
				   (x3, y3 +. delta, z3))) model;;

let move_down model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1, y1 -. delta, z1),
				   (x2, y2 -. delta, z2),
				   (x3, y3 -. delta, z3))) model;;

let move_closer model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1, y1, z1 +. delta),
				   (x2, y2, z2 +. delta),
				   (x3, y3, z3 +. delta))) model;;

let move_further model delta =
  List.map (fun ((x1, y1, z1),
		 (x2, y2, z2),
		 (x3, y3, z3)) -> ((x1, y1, z1 -. delta),
				   (x2, y2, z2 -. delta),
				   (x3, y3, z3 -. delta))) model;;

(*
  główna pętla renderująca
  napisana czysto funkcyjnie, za pomocą rekurencji ogonowej
*)
let rec loop model =
  Graphics.auto_synchronize false;
  Graphics.clear_graph ();
  
  Graphics.set_color (Graphics.rgb 0 0 0);
  render_world model;

  Graphics.auto_synchronize true;
  
  if Graphics.key_pressed () then
       begin
	 let key = Graphics.read_key () in
	   if key = 'q' then
	     print_string "Nacisnieto q - wyjscie z programu\n"
	   else if key = 'd' then
	     loop (move_right model 0.1)
	   else if key = 'a' then
	     loop (move_left model 0.1)
	   else if key = 'w' then
	     loop (move_up model 0.1)
	   else if key = 's' then
	     loop (move_down model 0.1)
	   else if key = 'r' then
	     loop (move_closer model 0.1)
	   else if key = 'f' then
	     loop (move_further model 0.1)
	   else
	     loop model
       end
   else
       loop model
;;

let init_args =
  Printf.sprintf " %dx%d" (int screen_width) (int screen_height);;

(* tworzy okno, parsuje model i wchodzi do pętli renderującej *)
let run model_name =
  Graphics.open_graph init_args;
  Graphics.set_window_title "3d rendering engine";
  let model = parse_model model_name in
    loop model;;
    
let path_to_model () =
  if (Array.length Sys.argv) <> 2 then
    failwith "aby uruchomic program, nalezy podac jako argument sciezke do pliku modelu: 3d.e /path/to/model.obj\n"
  else
    Sys.argv.(1);;

(* punkt startowy programu *)
let () =
  run (path_to_model ());;
