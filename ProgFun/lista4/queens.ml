(*
  BFS daje takie same rozwiązania w tej samej kolejności co DFS dla problemu n hetmanów, gdyż wszystkie rozwiązania są na jednej głębokości (n)
*)

type 'a llist = LNil | LCons of 'a * (unit -> 'a llist);;

let rec ltake = function
     (0, xq) -> []
  | (n, LNil) -> []
  | (n, LCons(x,xf)) -> x::ltake(n-1, xf())
;;

let rec lfilter pred = function
    LNil -> LNil
  | LCons(x,xf) when pred x -> LCons (x, function () -> lfilter pred (xf()))
  | LCons(_,xf)             -> lfilter pred (xf())

let breadthFirst next x =
  let rec bfs = function
      [] -> LNil
    | (h::t) -> LCons (h, function () -> bfs (t @ next h)) (* jedyna modyfikacja; było (next h @ t) *)
  in bfs [x];;

let isQueenSafe oldqs newq =
  let rec nodiag = function
      (i, []) -> true
    | (i, q::qt) -> abs(newq-q)<>i && nodiag(i+1,qt)
  in not(List.mem newq oldqs) && nodiag(1,oldqs);;

let rec fromTo  a b =
  if a>b then []
  else a::(fromTo (a+1) b);;

let nextQueen n qs =
  List.map (function h -> h::qs)
    (List.filter (isQueenSafe qs) (fromTo 1 n));;

let isSolution n qs = List.length qs = n;;

let breadthQueen n = lfilter (isSolution n)
  (breadthFirst (nextQueen n) []);;

(*
  repl:
  ltake (10,breadthQueen 8);;
*)
