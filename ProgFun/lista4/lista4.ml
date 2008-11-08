type formula =
    Var of char
  | Impl of formula*formula
  | And of formula*formula
  | Or of formula*formula
  | Not of formula

let v1 = [('p', true);
	  ('q', false);
	  ('r', true)]

let rec eval v f = match f with
  | Var p -> List.assoc p v
  | Impl (fi, psi) -> not (eval v fi) || (eval v psi)
  | And (fi, psi) -> (eval v fi) && (eval v psi)
  | Or (fi, psi) -> (eval v fi) || (eval v psi)
  | Not fi -> not (eval v fi)

let f1 = And ((Or ((Var 'p'),(Var 'q'))),(Impl ((Var 'p'),(Not (Var 'q')))))

let uniq lst =
  let unique_set = Hashtbl.create (List.length lst) in
    List.iter (fun x -> Hashtbl.replace unique_set x ()) lst;
    Hashtbl.fold (fun x () xs -> x :: xs) unique_set []

let vars f =
  let rec aux f = match f with
    | Var p -> [p]
    | Impl (fi, psi) -> (aux fi) @ (aux psi)
    | And (fi, psi) -> (aux fi) @ (aux psi)
    | Or (fi, psi) -> (aux fi) @ (aux psi)
    | Not fi -> (aux fi)
  in uniq (aux f)

let concat x xs = x :: xs
let rec sublists lst = match lst with
    [] -> [[]]
  | x::xs -> (List.map (concat x) (sublists xs)) @ (sublists xs)

let to_assocs v vs =
  let aux lst =
    List.map (fun p -> (p, List.mem p lst)) v
  in List.map aux vs

let all_values f =
  let v = vars f
  in to_assocs v (sublists v)

type tautology = Yes | No of (char * bool) list

let taut f =
  try
    No (List.find (fun v -> not (eval v f)) (all_values f))
  with Not_found -> Yes

let rec clausule v = match v with
    [(p, b)] ->
      if b = true then
	Var p
      else
	Not (Var p)
  | (p, b)::xs ->
      if b = true then
	And (Var p, clausule xs)
      else
	And (Not (Var p), clausule xs)

let rec alternate lst = match lst with
    [f] -> f
  | f::fs -> Or (f, alternate fs)

let dnf f =
  let truths = List.filter (fun v -> eval v f) (all_values f)
  in let rows = List.map clausule truths
  in alternate rows
