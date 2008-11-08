open List

let m1 = [[1;2;3];
	  [4;5;6];
	  [7;8;9]]

let m2 = [[2;0];
	  [4;5]]

let v1 = [1;2]

let iv = [[1;2;3];
	  [4;5;6;0];
	  [7;8;9]]
  
let valid m =
  let dim = length m
  in for_all (fun l -> length l = dim) m

let nth_col n m =
  map (fun l -> nth l n) m

let transpose m =
  let dim = length m
  in let rec aux n =
      if n = dim then []
      else (nth_col n m) :: aux (n + 1)
  in aux 0

let rec zip a b = match (a,b) with
    (_, []) -> []
  | ([], _) -> []
  | (x::xs, y::ys) -> (x, y) :: zip xs ys

let curry f = fun (x, y) -> f x y
      
let rec zipf f a b = map (curry f) (zip a b)

let mult_vec v m = map (fun row ->
			  fold_right (+)
			    (zipf ( * ) v row) 0) (transpose m)

let mult_mat a b = map (fun vec -> mult_vec vec a) b
