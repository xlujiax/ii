let (|>) x f = f x;;

type 'a maybe = Just of 'a | Nothing;;

let read_file f =
  let rec loop accum_ref =
    let l = input_line f in
      accum_ref := l :: (!accum_ref);
      loop accum_ref
  in
  let accum_ref = ref [] in
    try
      loop accum_ref
    with
	End_of_file -> !accum_ref
;;

let parse_grade = function
  | "" -> Nothing
  | str -> Just (int_of_string str);;

let parse_line line =
  let read name surname index grade =
    (name, surname, index, parse_grade grade)
  in
    Scanf.sscanf line "%s %s %s %s" read;;

let rm_colons line =
  for i = 0 to (String.length line) - 1 do
    if line.[i] = ':' then
      line.[i] <- ' '
  done;
  line;;

let database () =
  "studenci.db"
  |> open_in
  |> read_file
  |> List.map rm_colons
  |> List.map parse_line;;

(* 1 *)

let grade_cmp (_,_,_,a) (_,_,_,b) = match a, b with
  | Nothing, Nothing -> 0
  | Just _, Nothing -> -1
  | Nothing, Just _ -> 1
  | Just a, Just b when a < b -> -1
  | Just a, Just b -> 1;;

let sort_grade = List.sort grade_cmp;;

let surname_cmp (_,a,_,_) (_,b,_,_) = String.compare a b;;

let sort_surname = List.sort surname_cmp;;

(* 2 *)
let non_empty = List.filter (function (_,_,_, Just _) -> true
			     | (_,_,_, Nothing) -> false);;

(* 3 *)
let sum db =
  db
  |> non_empty
  |> List.map (function (_,_,_, Just x) -> x)
  |> List.fold_left (+) 0
  |> float_of_int;;

let avg db =
  (sum db) /. (float_of_int (List.length db));;

(* 4 *)
let pprint =
  List.iter (function
		 (a,b,c,Nothing) -> print_endline (Printf.sprintf "%10s %10s %s -" a b c)
	       | (a,b,c,Just x) -> print_endline (Printf.sprintf "%10s %10s %s %d" a b c x))
