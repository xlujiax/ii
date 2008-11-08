type 'a list = Nil | Cons of int * 'a list

(* aux *)
let rec cons_of_list lst = match lst with
    [] -> Nil
  | x::xs -> Cons (x, cons_of_list xs)

let construct data lst = Cons (data, lst)

let rec append a b = match (a, b) with
    (Nil, b) -> b
  | (Cons (x, xs), b) -> construct x (append xs b)

let rec rev lst = match lst with
    Nil -> Nil
  | Cons (x, xs) -> append (rev xs) (Cons (x, Nil))

let rec drop n lst = match (n,lst) with
    (0, xs) -> xs
  | (n, Cons (x, xs)) -> drop (n - 1) xs

(* 1 *)
let hd lst = match lst with
    Nil -> failwith "hd of empty list"
  | Cons (data, _) -> data

let tl lst = match lst with
    Nil -> failwith "hd of empty list"
  | Cons (_, tail) -> tail

(* 3 *)
let rec map f lst = match lst with
    Nil -> Nil
  | Cons (x, xs) -> construct (f x) (map f xs)

(* 4 *)
let rec map2 f a b = match (a,b) with
    (Nil, _) -> Nil
  | (_, Nil) -> Nil
  | (Cons (x, xs), Cons (y, ys)) -> construct (f x y) (map2 f xs ys)

(* 2 *)
let add ratio = map ((+) ratio)

(* 5 *)
let replace n s lst =
  let rec aux act lst = match lst with
      Nil -> Nil
    | Cons (x, xs) ->
	if (act mod n) = 0 then
	  construct s (aux (act - 1) xs)
	else
	  construct x (aux (act - 1) xs)
  in
    aux 0 lst

(* 6 *)
let take n lst =
  let rec aux act lst = match lst with
      Nil -> Nil
    | Cons (x, xs) ->
	if (act mod n) = 0 then
	  construct x (aux (act - 1) xs)
	else
	  aux (act - 1) xs
  in
    aux 0 lst

(* 7 - aux *)
let rec fold_left f i lst = match lst with
    Nil -> i
  | Cons (x, xs) -> f (fold_left f i xs) x

(* 7 *)
let fold f i lst = fold_left f i (rev lst)

(* 8 - recursive insert *)
let tabulate ?(s=0) e lst =
  let sz = e - s + 1
  in let arr = Array.make sz 0
  in let rec ins n lst2 = match (n, lst2) with
      (_, Nil) -> ()
    | (_, Cons (x, xs)) ->
	if n < sz then begin
	  arr.(n) <- x;
	  ins (n + 1) xs;
	end
  in
    ins 0 (drop s lst);
    arr

(* 8 - iterative insert *)
let tabulate' ?(s=0) e lst =
  let sz = e - s + 1
  in let arr = Array.make sz 0
  in let rlst = ref (drop s lst)
  in
    for i = 0 to sz - 1 do
      if Nil <> !rlst then begin
	arr.(i) <- hd !rlst;
	rlst := tl !rlst;
      end;
    done;
    arr

(* przykladowe strumienie: *)
let verbose = Cons (1, Cons (2, Cons (3, Cons (4, Cons (5, Nil)))))
let onefive = cons_of_list [1;2;3;4;5]
let zeroten = cons_of_list [0;1;2;3;4;5;6;7;8;9;10]
let oneten = cons_of_list [1;2;3;4;5;6;7;8;9;10]
let fourfive = cons_of_list [4;5]
let sixseven = cons_of_list [6;7]
let teens = cons_of_list [12;15]
let teens2 = cons_of_list [10;12]

(* testy: *)
let test () =
  verbose = onefive &&
  4 = hd fourfive &&
  oneten = (tl zeroten) &&
  sixseven = (add 2 fourfive) &&
  teens = (map (( * ) 3) fourfive) &&
  teens2 = (map2 (+) fourfive sixseven) &&
  120 = (fold ( * ) 1 onefive) &&
  zeroten = (take 1 zeroten) &&
  [| 4;5;6;7;8 |] = (tabulate ~s:4 8 zeroten)
  
