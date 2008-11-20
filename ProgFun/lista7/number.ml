type 'a btree = Leaf of 'a | Node of 'a btree * 'a * 'a btree;;

let example = Node (Node (Leaf 'a', 'b', Leaf 'c'), 'd', Leaf 'e');;

let rec ref_tree = function
  | Leaf _ -> Leaf (ref 0)
  | Node (left, _, right) -> Node (ref_tree left, ref 0, ref_tree right)

let bfs tree =
  let rec aux = function
    | [] -> []
    | ((Leaf _) as actual) :: rest -> actual :: aux (rest)
    | (Node (left, _, right) as actual) :: rest -> actual :: aux (rest @ [left] @ [right])
  in aux [tree];;

let number_lst lst =
  let counter = ref 1 in
  List.iter (function
	       | Leaf slot ->         slot := !counter; incr counter
	       | Node (_, slot, _) -> slot := !counter; incr counter) lst;;


let rec map_tree f = function
  | Leaf slot -> Leaf (f slot)
  | Node (left, slot, right) -> Node (map_tree f left, f slot, map_tree f right);;

let rec number_tree tree =
  let rt = ref_tree tree in
    number_lst (bfs rt);
    map_tree (fun slot -> !slot) rt;;
