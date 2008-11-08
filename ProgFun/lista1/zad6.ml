let compose f g = fun x -> f (g x)
let id x = x

let rec iterate f n =
  if n = 1 then id
  else compose f (iterate f (n - 1))

let mul x y = iterate ((+) x) y x
let pow x y = iterate (( * ) x) y x
