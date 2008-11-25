type 'a btree = Leaf of 'a | Node of 'a btree * 'a * 'a btree;;

let rec bfnum' i = function
  | [] -> []
  | Leaf _ :: rest -> bfnum' (i + 1) rest @ [Leaf i]
  | Node (left, _, right) :: rest ->
      let right' :: left' :: rest' = bfnum' (i + 1) (rest @ [left] @ [right]) in
	rest' @ [Node (left', i, right')];;

let bfnum tree = let [root] = (bfnum' 1 [tree]) in root;;

let ex = Node (Node (Leaf 'a', 'b', Leaf 'c'), 'd', Leaf 'e');;
let ex2 = Node (Node (Leaf 'c', 'b', Leaf 'd') , 'a' , Node (Leaf 'f', 'e' , Leaf 'g'));;

let res = Node (Node (Leaf 4, 2, Leaf 5), 1, Leaf 3);;
