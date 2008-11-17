type 'a btree = Leaf | Node of 'a btree * 'a * 'a btree;;
type 'a array = int * 'a btree;;

let ahiext (max, tree) el =
  let rec aux k t = match k, t with
    | (_, Leaf)
    | (1, _) -> Node (Leaf, el, Leaf)
    | (_, Node (left, actual, right)) ->
	if k mod 2 = 0 then
	  Node (aux (k / 2) left, actual, right)
	else
	  Node (left, actual, aux (k / 2) right)
  in (max + 1, aux (max + 1) tree);;

let asub (_, tree) k =
  let rec aux k t = match k, t with
    | (_, Leaf) -> failwith "index out of bounds"
    | (1, Node (_, el, _)) -> el
    | (_, Node (left, _, right)) ->
	if k mod 2 = 0 then
	  aux (k / 2) left
	else
	  aux (k / 2) right
  in aux k tree;;

let aupdate (max, tree) k new_el =
  let rec aux k t = match k, t with
    | (_, Leaf) -> failwith "index out of bounds"
    | (1, Node (left, _, right)) -> Node (left, new_el, right)
    | (_, Node (left, el, right)) ->
	if k mod 2 = 0 then
	  Node (aux (k / 2) left, el, right)
	else
	  Node (left, el, aux (k / 2) right)
  in (max, aux k tree);;

let ahirem (max, tree) =
  let rec aux k t = match k, t with
    | (_, Leaf) -> failwith "index out of bounds"
    | (1, Node (left, _, right)) -> Leaf
    | (_, Node (left, el, right)) ->
	if k mod 2 = 0 then
	  Node (aux (k / 2) left, el, right)
	else
	  Node (left, el, aux (k / 2) right)
  in (max - 1, aux max tree);;

let aempty = (0, Leaf);;

let x = aempty;;
let x = ahiext x 3;;
let x = ahiext x 4;;
let x = ahiext x 5;;
let x = ahiext x 6;;
let x = ahiext x 7;;
let x = ahiext x 8;;
let x = ahiext x 9;;

let y = aupdate x 4 99;;
let y = aupdate y 5 100;;
let y = aupdate y 6 101;;

let z = ahirem x;;
let z = ahirem z;;
