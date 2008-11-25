let rec pal' = function
  | (xs, []) -> (true, xs)
  | (_::xs, [y]) -> (true, xs) (* nieparzysta dlugosc listy; pomijamy srodkowy element *)
  | (x::xs, _::_::ys) ->
      let (before, r::rs) = pal' (xs, ys) in
	(before && r = x, rs);;
let pal lst = let (boolean, _) = pal' (lst, lst) in boolean;;
