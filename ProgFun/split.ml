let rec split' = function
  | (xs, []) -> ([], xs)
  | (xs, [y]) -> ([], xs)
  | (x::xs, y1::y2::ys) -> let a, b = split' (xs, ys) in x :: a, b;;
let split lst = split' (lst, lst);;

let ex1 = [1;2;3;4;5];;
let ex2 = [1;2;3;4;5;6];;
let ex3 = [1;2;3;4;5;6;7];;
