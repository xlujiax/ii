let concat x xs = x :: xs
let rec sublists lst = match lst with
    [] -> [[]]
  | x::xs -> (List.map (concat x) (sublists xs)) @ (sublists xs)
