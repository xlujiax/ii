type 'a llist = LNil | LCons of 'a * (unit -> 'a llist);;

let lhd = function
    LNil -> failwith "lhd"
  | LCons (x, _) -> x

let ltl = function
    LNil -> failwith "ltl"
  | LCons (_, xf) -> xf()

let rec ltake = function
    (0, xq) -> []
  | (n, LNil) -> []
  | (n, LCons(x,xf)) -> x::ltake(n-1, xf())

let rec lnth = function
    (0, LCons(x,_)) -> x
  | (n, LCons(x,xf)) -> lnth(n-1, xf())

let rec lsum = function
    (0, LCons(x,_)) -> 0.
  | (n, LCons(x,xf)) -> x +. lsum(n-1, xf())

let rec toLazyList = function
    [] -> LNil
  | h::t -> LCons(h, function () -> toLazyList t);;


let rec lfrom k = LCons (k, function () -> lfrom (k+1));;

let rec (@@) ll1 ll2 =
  match ll1 with
      LNil -> ll2
    | LCons(x, xf) -> LCons(x, function () -> (xf()) @@ ll2);;

let rec lmap f = function
    LNil -> LNil
  | LCons(x,xf) -> LCons(f x, function () -> lmap f (xf()) )

let rec lmap2 f = function
    (LNil, _) -> LNil
  | (_, LNil) -> LNil
  | (LCons(x,xf), LCons(y,yf)) -> LCons(f x y, function () -> lmap2 f ((xf()),(yf())) )

let lzip f s1 s2 = lmap2 f (s1, s2)

let rec liter f x = LCons(x, function () -> liter f (f x));;

let rec lfilter pred = function
    LNil -> LNil
  | LCons(x,xf) -> if pred x
    then LCons(x, function () -> lfilter pred (xf()) )
    else lfilter pred (xf())
  let primes =
    let rec sieve = function
        LCons(p,nf) -> LCons(p, function () -> sieve (sift p (nf() )))
      | LNil -> failwith "Impossible! Internal error."
    and sift p = lfilter (function n -> n mod p <> 0)
    in sieve (lfrom 2)

  let change_sign x = x * (-1);;

let naturals = lfrom 1
let odds = lfilter (fun n -> n mod 2 <> 0) naturals
let minus_one_pow_k = liter (fun n ->  n * (-1) ) 1

(* zad1 *)
let leibnitz = lmap (fun n -> 4. /. (float_of_int n)) (lmap2 ( * ) (minus_one_pow_k,odds))

(* zad2 *)
let lmap3 f s1 s2 s3 =
  lmap (fun (a, (b, c)) -> f a b c)
    (lmap2 (fun a b -> (a, b)) (s1,(lmap2 (fun a b -> (a, b)) (s2,s3))))

let ltris f s = lmap3 f s (ltl s) (ltl (ltl s))
let lfloat = lmap (fun x -> float_of_int x)
let eulers_transform x y z = z -. (y-.z)*.(y-.z)/.(x-.2.*.y+.z)

let rec euler = LCons (1., fun () -> LCons (2., fun () -> LCons (4., fun () -> ltris eulers_transform euler)))
let rec fibs = LCons(1, fun () -> LCons(1, fun () -> lzip (+) fibs (ltl fibs)))

let sum n s = List.fold_right (+.) (ltake (n,s)) 0.;;

let leibnitz_sum = lmap (fun n -> lsum (n,leibnitz)) naturals
