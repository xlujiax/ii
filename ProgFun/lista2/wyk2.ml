(*
wyklad 2 - zadania kontrolne
*)

let rec fib n = match n with
    0 -> 0
  | 1 -> 1
  | _ -> fib (n - 1) + fib (n - 2)

let rec fib2 ?(acc1=1) ?(acc2=0) n : int =
  if n = 1 then
    acc1 + acc2
  else
    fib2 (n - 1) ~acc1:(acc2) ~acc2:(acc1 + acc2)

(* 3 *)
let rec a_to_b a = a_to_b a
(* 4 *)
let [_;_;x;_;_] = [-2;-1;0;1;2]
let [_;(x,_)] = [(1,2);(0,1)]
(* 5 *)
let rec initsegment (a, b) = match (a, b) with
    ([], _) -> true
  | (x::xs, y::ys) -> x = y && initsegment (xs, ys)
(* 6 *)
let rec replace_nth (lst, n, pattern) = match (lst, n) with
    ([], _) -> failwith "lista krotsza niz n"
  | (x::xs, 0) -> pattern :: xs
  | (x::xs, _) -> x :: replace_nth (xs, n - 1, pattern)
(* 7 a *)
let rec take n lst = match (n, lst) with
    (_, []) -> []
  | (0, _) -> []
  | (_, x::xs) -> x :: (take (n - 1) xs)
      
let rec drop n lst = match (n, lst) with
    (0, xs) -> xs
  | (_, x::xs) -> drop (n - 1) xs

let split lst =
  let lstlen = List.length lst
  in
  let rec aux n =
    if n == lstlen then []
    else (take n lst, drop n lst) :: aux (n + 1) 
  in
    aux 0
(* 7b *)
let insert i lst =
  let lstlen = List.length lst
  in
  let rec aux n =
    if n == lstlen then [lst @ [i]]
    else ((take n lst) @ [i] @ (drop n lst)) :: aux (n + 1) 
  in
    aux 0

let insert2 i lol = List.flatten (List.map (insert i) lol)

(* 7d *)
