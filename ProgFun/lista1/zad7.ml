(* 1 *)
let tl stream = fun n -> stream (n + 1)
let hd stream = stream 0

(* 3 *)
let map f stream = fun n -> f (stream n)

(* 2 *)
let add ratio = map ((+) ratio)

(* 4 *)
let map2 f s1 s2 = fun n -> f (s1 n) (s2 n)

(* 5 *)
let replace every pattern stream =
  fun n ->
    if n mod every = 0 then
      pattern
    else
      stream n

(* 6 *)
let take every stream =
  fun n -> stream (n * every)

(* 7 *)
let fold a f stream =
  fun n ->
    let p = ref a
    in
      for i = 0 to n do
	p := f (!p) (stream i)
      done;
      !p

(* 8 *)
let rec tabulate ?(s=0) e stream =
    if s == e then []
    else (stream s) :: tabulate ~s:(s + 1) e stream

let table = tabulate

(* 8 - wersja tail-recursive *)
let rec tabulate' ?(s=0) ?(acc=[]) e stream =
    if s == e then acc
    else tabulate' ~s:(s) ~acc:(stream e :: acc) (e - 1) stream
      
let table' = tabulate'
  
(* przykladowe strumienie *)
let naturals n = n
let positive_naturals n = n + 1
let evens n = 2 * n
let odds n = 2 * n + 1
let rec fibs n = match n with
    0 -> 1
  | 1 -> 1
  | _ -> fibs (n - 1) + fibs (n - 2)

let naive_is_prime n =
  let rec aux div = match div with
      0 -> true
    | 1 -> true
    | _ -> (n mod div <> 0) && (aux (div - 1))
  in aux (n - 1)

let naive_next_prime n =
  let p = ref (n + 1) in
    while (not (naive_is_prime (!p))) do
      p := (!p) + 1;
    done;
    !p
     
let primes n =
  let p = ref 0 in
    for i = 0 to n do
      p := naive_next_prime !p;
    done;
    !p

(* testy *)
let test () =
  (* 1 *)
  1 = hd primes &&
  [ 1;  2;  3;  4;  5;  6;  7;  8;  9; 10] = table 10 (tl naturals) &&
  (* 2 *)
  [ 4;  5;  6;  7;  8;  9; 10; 11; 12; 13] = table 10 (add 4 naturals) &&
  (* 3 *)
  [ 0;  5; 10; 15; 20; 25; 30; 35; 40; 45] = table 10 (map ( ( * ) 5) naturals) &&
  (* 4 *)
  [ 1;  5;  9; 13; 17; 21; 25; 29; 33; 37] = table 10 (map2 (+) evens odds) &&
  (* 5 *)
  [ 0;  1;  0;  3;  0;  5;  0;  7;  0;  9] = table 10 (replace 2 0 naturals) &&
  (* 6 *)
  [ 0;  3;  6;  9; 12; 15; 18; 21; 24; 27] = table 10 (take 3 naturals) &&
  (* 7 *)
  [ 1;  3;  6; 10; 15; 21; 28; 36; 45; 55] = table 10 (fold 0 (+) positive_naturals) &&
  (* 8 *)
  [10; 11; 12; 13; 14; 15; 16; 17; 18; 19] = table ~s:10 20 naturals &&
  (* przykladowe strumienie *)
  [ 1;  2;  3;  5;  7; 11; 13; 17; 19; 23] = table 10 primes &&
  [ 1;  1;  2;  3;  5;  8; 13; 21; 34; 55] = table 10 fibs
