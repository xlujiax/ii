open Model;;

let parse_model filename =
    Parser.main Lexer.next (Lexing.from_channel (open_in filename))
;;

let print_model model =
  List.iter (fun (x,y,z) -> Printf.printf "vertex: %f %f %f\n" x y z) model.vertices;
  List.iter (fun (a,b,c) -> Printf.printf "face: %d %d %d\n" a b c) model.tris
;;
(*
let model_to_world model =
  let v = vertices model
  and f = faces model
  in let get_vertex_3d index = let Model.Vertex (x,y,z) = v.(index-1) in (x,y,z)
  in List.map (fun Model.Face (a,b,c)
		 -> (get_vertex3d(a), get_vertex3d(b), get_vertex3d(c))) faces
;;

let print_vertex (x,y,z) = Printf.printf "[%f,%f,%f]" x y z;;
let print_tri3d (v1,v2,v3) =
  print_vertex v1;
  Printf.printf ", ";
  print_vertex v2;
  Printf.printf ", ";
  print_vertex v3;
  Printf.printf "\n"
;;
  
let print_world world = List.iter print_tri3d world;;
*)
let run () =
  try
    let filename = Sys.argv.(1)
    in print_model (parse_model filename)
  with
    | Invalid_argument _ -> print_string ("Usage: "^(Sys.argv.(0))^" <model.obj>\n")
    | Sys_error _ -> print_string ("File \""^(Sys.argv.(1))^"\" does not exist.\n")
;;
  

run ();;

