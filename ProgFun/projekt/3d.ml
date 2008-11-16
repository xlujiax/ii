let parse_model filename =
  Parser.main Lexer.next (Lexing.from_channel (open_in filename));;

let print_model = function
    Model.Vertex (a,b,c) -> Printf.printf "v: %f %f %f\n" a b c
  | Model.Face (a,b,c) -> Printf.printf "f: %d %d %d\n" a b c;;

let run () =
  try
    List.iter print_model (parse_model (Sys.argv.(1)))
  with
    | Invalid_argument _ -> print_string ("Usage: "^(Sys.argv.(0))^" <model.obj>\n")
    | Sys_error _ -> print_string ("File \""^(Sys.argv.(1))^"\" does not exist.\n")
;;
  

run ();;

