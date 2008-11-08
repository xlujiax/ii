let rec rev lst = match lst with
    [] -> []
  | x::xs -> (rev xs) @ [x]

let rec rev' ?(acc=[]) lst = match lst with
    [] -> acc
  | x::xs -> rev' xs ~acc:(x :: acc)

let rec maprev' f ?(acc=[]) lst = match lst with
    [] -> acc
  | x::xs -> maprev' f xs ~acc:(f x :: acc)

let rec map f lst = match lst with
    [] -> []
  | x::xs -> (f x) :: (map f xs)

let revmap f lst = rev' (map f lst)
