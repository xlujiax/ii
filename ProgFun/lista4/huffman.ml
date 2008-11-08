type huffman_tree = Leaf of float * char | Node of float * huffman_tree * huffman_tree

let probability = function
  | Leaf (p, _) -> p
  | Node (p, _, _) -> p

let tree assoc =
  let pred = (fun a b -> (probability a) < (probability b))
  in let leafs_lst = List.map (fun (p, c) -> Leaf (p, c)) assoc
  in let sorted = Sort.list pred leafs_lst
  in let rec aux lst = match lst with
    | a::b::rest ->
	let pa = probability a and
	    pb = probability b
	in
	if pa < pb then
	  aux (Sort.merge pred [Node ((pa +. pb),a,b)] rest)
	else
	  aux (Sort.merge pred [Node ((pa +. pb),b,a)] rest)
    | [x] -> [x]
    | [] -> []
  in List.hd (aux sorted)

let rec dfs ?(path=[]) = function
  | Leaf (_, c) -> [(path, c)]
  | Node (_, l, r) -> (dfs ~path:('0'::path) l) @ (dfs ~path:('1'::path) r)

let ex = [(0.1, 'a'); (0.2, 'b'); (0.3, 'c'); (0.24, 'd'); (0.16, 'e')]

let codes assoc = dfs (tree assoc)
let encode c assoc = fst (List.find (fun (_, a) -> a = c) (codes assoc))
let decode path assoc = snd (List.find (fun (p, _) -> p = path) (codes assoc))
