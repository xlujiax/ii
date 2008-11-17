type 'a btree = Leaf of 'a | Node of 'a btree * 'a btree;;

let rec dfs = function
  | Leaf x -> [x]
  | Node (left, right) -> (dfs left) @ (dfs right);;

let fringe = dfs;;
let samefringe_naive t1 t2 = (fringe t1) = (fringe t2);;

let t1 = Node (Node (Leaf 1, Leaf 2), Leaf 3);;
let t2 = Node (Leaf 1, Node (Leaf 2, Leaf 3));;

type 'a 'b continuations = Cont of ('a 'b continuations * 'b) lazy_t list;;

let rec leftmost ?(cont=[]) = function
  | Leaf x -> (cont, x)
  | Node (left, right) -> leftmost ~cont:(Cont ((lazy (leftmost right)) :: cont)) left;;

let rec next = function
  | suspended::conts1 -> let (conts2, res) = (Lazy.force suspended) in (conts1 @ conts2, res)
  | [] -> failwith "next failed";;

let samefringe t1 t2 = 
  let l1 = leftmost t1 in
  let l2 = leftmost t2 in
  let rec aux (c1, n1) (c2, n2) = match (c1, c2) with
    | ([], []) -> true
    | ([], _) -> false
    | (_, []) -> false
    | _ -> n1 = n2 && aux (next c1) (next c2)
  in aux l1 l2

