let rec drop n lst = match (n, lst) with
    (0, _) -> lst
  | (_, []) -> []
  | (_, x::xs) -> drop (n - 1) xs

let rec take n lst = match (n, lst) with
  | (0, _)  | (_, []) -> []
  | (_, x::xs) -> x :: take (n - 1) xs

let rec length lst = match lst with
    [] -> 0
  | x::xs -> 1 + length xs

let rec nth n lst = match (n, lst) with
    (0, x::xs) -> x
  | (_,[]) -> failwith "out of bounds"
  | (_, x::xs) -> nth (n - 1) xs

let div n lst =
  (take n lst, nth n lst, drop (n + 1) lst)

let concat x xs = x :: xs
let pull n lst = let bef, el, aft = div n lst in (el, bef @ aft)

let rec permutations ?(n=0) lst = match lst with
  |   [] -> [[]]
  | _ when n = length lst -> []
  | _ ->
      let (choosen, rest) = pull n lst
      in (permutations ~n:(n + 1) lst) @ (List.map (concat choosen) (permutations rest))
