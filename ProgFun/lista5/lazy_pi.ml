type 'a llist = LNil | LCons of 'a * (('a llist) Lazy.t)

let rec ltake n lst = match (n, lst) with
  | (0, _) -> LNil
  | (n, LNil) -> LNil
  | (n, LCons (x, xs)) -> LCons (x , lazy (ltake (n - 1) (Lazy.force xs)))

let rec ldrop n lst = match (n, lst) with
  | (0, lst) -> lst
  | (n, LNil) -> LNil
  | (n, LCons (_, xs)) -> ldrop (n - 1) (Lazy.force xs)

let rec lshow = function
  | LNil -> []
  | LCons (x, xs) -> x :: lshow (Lazy.force xs)

let rec lnth n lst = match (n, lst) with
  | (_, LNil) -> failwith "lnth"
  | (0, LCons (x, _)) -> x
  | (n, LCons (_, xs)) -> lnth (n - 1) (Lazy.force xs)

let rec lfold f i lst = match lst with
  | LNil -> i
  | LCons (x, xs) -> f x (lfold f i (Lazy.force xs))

let lsum_int = lfold (+) 0
let lsum_float = lfold (+.) 0.

let rec lmap f = function
  | LNil -> LNil
  | LCons(x, xs) -> LCons(f x, lazy (lmap f (Lazy.force xs)))

let rec lmap2 f s1 s2 = match (s1, s2) with
  | (LNil, _) -> LNil
  | (_, LNil) -> LNil
  | (LCons(x,xs), LCons(y,ys)) ->
      LCons(f x y, lazy (lmap2 f (Lazy.force xs) (Lazy.force ys)))

let lmap3 f s1 s2 s3 =
  lmap (fun (a, (b, c)) -> f a b c)
    (lmap2 (fun a b -> (a, b)) s1 (lmap2 (fun a b -> (a, b)) s2 s3))

let rec lfilter f = function
  | LNil -> LNil
  | LCons(x, xs) ->
      if f x then
	LCons(x, lazy (lfilter f (Lazy.force xs)))
      else
	lfilter f (Lazy.force xs)

let rec liter f x = LCons(x, lazy (liter f (f x)))

let rec naturals_from n = LCons (n, lazy (naturals_from (n + 1)))
let naturals = naturals_from 1
let odds = lfilter (fun n -> n mod 2 <> 0) naturals
let minus_one_pow_k = liter (fun n -> n * (-1) ) 1

(* zad 1 *)
let leibnitz =
  lmap (fun n -> 4. /. (float_of_int n)) (lmap2 ( * ) minus_one_pow_k odds)

let leibnitz_sums = lmap (fun n -> lsum_float (ltake n leibnitz)) naturals

(* uzycie: lnth 100 leibnitz_sums *)

(* zad 2 *)
let ltriples f s = lmap3 f s (ldrop 1 s) (ldrop 2 s)
let eulers_transform x y z = z -. (y-.z)*.(y-.z)/.(x-.2.*.y+.z)

let eulers_leibnitz_sums = ltriples eulers_transform leibnitz_sums
(* uzycie: lnth 100 eulers_leibnitz_sums *)

(* lazy nie jest funkcja bo funkcja musi wartosciowac swoje argumenty przed wywolaniem. lazy to makro ktore opakowywuje swoj parametr w [.. fun () -> ..] *)
