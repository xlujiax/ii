let rec drop n lst = match (n, lst) with
    (0, _) -> lst
  | (_, []) -> []
  | (_, x::xs) -> drop (n - 1) xs

let rec take n lst = match (n, lst) with
    (0, _) -> []
  | (_, []) -> []
  | (_, x::xs) -> x :: take (n - 1) xs

let rec length lst = match lst with
    [] -> 0
  | x::xs -> 1 + length xs

let rec merge cmp a b = match (a,b) with
    ([], _) -> b
  | (_, []) -> a
  | (x::xs, y::ys) ->
      if cmp x y then
	x :: (merge cmp xs (y::ys))
      else
	y :: (merge cmp (x::xs) ys)

(* tail -rec *)
let rec merge' ?(acc=[]) cmp a b = match (a,b) with
    ([], _) -> acc @ b
  | (_, []) -> acc @ a
  | (x::xs, y::ys) ->
      if cmp x y then
	(merge' ~acc:(acc @ [x]) cmp xs (y::ys))
      else
	(merge' ~acc:(acc @ [y]) cmp (x::xs) ys)

let div lst =
  let len = length lst
  in ((take (len / 2) lst), (drop (len / 2) lst))

let rec mergesort cmp lst = match lst with
    [] -> []
  | [a] -> [a]
  | _ -> let (a, b) = div lst
    in
      merge' cmp (mergesort cmp a) (mergesort cmp b)
