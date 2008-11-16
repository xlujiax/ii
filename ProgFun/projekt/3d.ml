open Model;;

let parse_model filename = Parser.main Lexer.next (Lexing.from_channel (open_in filename));;

let model_to_world model =
  let v = Array.of_list model.vertices
  in List.map (fun (a,b,c)
	      -> (v.(a-1), v.(b-1), v.(c-1))) model.tris
;;

let flatten_vertex d = function (x, y, z) -> (600. *. d *. x /. z, 600. *. d *. y /. z);;
let flatten_tri d (a, b, c) = (flatten_vertex d a, flatten_vertex d b, flatten_vertex d c);;

let render_tri (v1,v2,v3) =
  Graphics.draw_poly (Array.map (fun (x,y) -> (int_of_float x, int_of_float y)) [| v1; v2; v3 |])
;;
  
let render_world world = List.iter (fun tri -> render_tri (flatten_tri 1. tri)) world;;


let rec loop world =
  Graphics.auto_synchronize false;
  Graphics.clear_graph ();
  
  Graphics.set_color (Graphics.rgb 0 0 0);
  render_world world;

  Graphics.auto_synchronize true;
  let status = Graphics.wait_next_event [Graphics.Poll; Graphics.Key_pressed] in
    if (not status.Graphics.keypressed) then loop world
;;

let init () =
  Graphics.open_graph " 600x600";
  Graphics.set_window_title "3d rendering engine";
  let filename = Sys.argv.(1)
  in let model = parse_model filename
  in let world = model_to_world model
  in loop world
;;

let () =
  init ();;



