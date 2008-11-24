let ex1 = [1;2;3;4;5;6;7;8;9];;
let ex2 = [1;2;3;4;5;6;7;8];;
let pal1 = [1;2;3;4;5;4;3;2;1];;
let pal2 = [1;2;3;4;4;3;2;1];;

let l1 = [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18];;
let l2 = [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19];;
let l3 = [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20];;
let l4 = [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21];;

let p1 = [1;2;3;4;5;6;7;8;9;10;11;10;9;8;7;6;5;4;3;2;1];;
let p2 = [1;2;3;4;5;6;7;8;9;10;11;11;10;9;8;7;6;5;4;3;2;1];;
let p3 = [1;2;3;4;5;6;7;8;9;10;11;12;11;10;9;8;7;6;5;4;3;2;1];;
let p4 = [1;2;3;4;5;6;7;8;9;10;11;12;12;11;10;9;8;7;6;5;4;3;2;1];;


let rec pal' = function
  | (xs, []) -> (true, xs)
  | (x::xs, [y]) -> (true, xs) (* nieparzysta dlugosc listy; pomijamy srodkowy element *)
  | (x::xs, y1::y2::ys) ->
      let (before, r::rs) = pal' (xs, ys) in
	(before && r = x, rs);;
let pal lst = let (boolean, _) = pal' (lst, lst) in boolean;;

let test () =
  pal ex1 = false &&
  pal ex2 = false &&
  pal pal1 = true &&
  pal pal2 = true &&
  pal p1 = true &&
  pal p2 = true &&
  pal p3 = true &&
  pal p4 = true &&
  pal l1 = false &&
  pal l2 = false &&
  pal l3 = false &&
  pal l4 = false;;

let correct = test ();;
