let parse_model filename =
  Parser.main Lexer.token (Lexing.from_channel (open_in filename));;

let print_model = function
    Model.Vertex (a,b,c) -> Printf.printf "v: %f %f %f\n" a b c
  | Model.Face (a,b,c) -> Printf.printf "f: %d %d %d\n" a b c;;

let run () =
  if Array.length Sys.argv <= 1 then
    print_string ("Usage: "^(Sys.argv.(0))^" <model.obj>\n")
  else
    List.iter print_model (parse_model (Sys.argv.(1)));;

run ();;

