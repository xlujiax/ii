open Model;;

let (screen_width, screen_height) = (600., 600.);;
let projection_d = 1.;;

let indices_to_coordinates model =
  let v = Array.of_list model.vertices
  in List.map (fun (a,b,c)
	      -> (v.(a-1), v.(b-1), v.(c-1))) model.tris;;

let parse_model filename =
  let model = Parser.main Lexer.next (Lexing.from_channel (open_in filename))
  in indices_to_coordinates model;;

let flatten_vertex = function (x, y, z) -> (screen_width *. projection_d *. x /. z, screen_height *. projection_d *. y /. z);;
let flatten_tri (a, b, c) = (flatten_vertex a, flatten_vertex b, flatten_vertex c);;
let flatten_model model = List.map flatten_tri model;;

let avg_z ((_,_,z1), (_,_,z2), (_,_,z3)) =
  (z1 +. z2 +. z3) /. 3.;;

let sort_z tris =
  Sort.list (fun a b -> avg_z a < avg_z b) tris;;

let render_tri (v1,v2,v3) =
  Graphics.draw_poly (Array.map (fun (x,y) ->
				   (int_of_float x, int_of_float y)) [| v1; v2; v3 |]);;

let render_world tris =
  List.iter render_tri (flatten_model (sort_z tris));;


let rec loop model =
  Graphics.auto_synchronize false;
  Graphics.clear_graph ();
  
  Graphics.set_color (Graphics.rgb 0 0 0);
  render_world model;

  Graphics.auto_synchronize true;
  let status = Graphics.wait_next_event [Graphics.Poll; Graphics.Key_pressed] in
    if (not status.Graphics.keypressed) then loop model
;;

let init_args = Printf.sprintf " %dx%d" (int_of_float screen_width) (int_of_float screen_height);;

let init () =
  Graphics.open_graph init_args;
  Graphics.set_window_title "3d rendering engine";
  let filename = Sys.argv.(1)
  in let model = parse_model filename
  in loop model;;

let () =
  init ();;
