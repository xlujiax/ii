open Model;;

type world = vertex3d list;;

let parse_model filename = Parser.main Lexer.next (Lexing.from_channel (open_in filename));;

let print_model model =
  List.iter (fun (x,y,z) -> Printf.printf "vertex: %f %f %f\n" x y z) model.vertices;
  List.iter (fun (a,b,c) -> Printf.printf "face: %d %d %d\n" a b c) model.tris
;;

let model_to_world model =
  let v = Array.of_list model.vertices
  in List.map (fun (a,b,c)
	      -> (v.(a-1), v.(b-1), v.(c-1))) model.tris
;;

let print_vertex (x,y,z) = Printf.printf "[%.2f,%.2f,%.2f]" x y z;;
let print_tri3d (v1,v2,v3) =
  print_vertex v1;
  Printf.printf ", ";
  print_vertex v2;
  Printf.printf ", ";
  print_vertex v3;
  Printf.printf "\n"
;;
  
let print_world world = List.iter print_tri3d world;;

let run () =
  let filename = Sys.argv.(1)
  in let model = parse_model filename
  in let world = model_to_world model
  in print_world world
;;
  

run ();;

