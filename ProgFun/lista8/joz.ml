#print_length 13;;

type 'a lnode = {item: 'a; mutable next: 'a lnode};;

let mk_circular_list e =
  let rec x = {item=e; next=x}
  in x;;

let insert_tail e l =
  let x = {item=e; next=l.next}
  in l.next <- x;;

let first ln = (ln.next).item;;

let next ln = ln.next;;

let elim_head l = l.next <- (l.next).next;;

(* zwraca liste cykliczna z n elementami ponumerowana od 1 do n*)
let clist_1_n n =
  let cycle = mk_circular_list 1 in
    for i = n downto 2 do
      insert_tail i cycle;
    done;
    cycle;;

let rotate ln = ln := next !ln;;
let nrotate ln m =
  for j = 1 to m do
    rotate ln;
  done;;

let joz n m =
  let cycle = ref (clist_1_n n) in
    let acc = ref [] in
      for i = 1 to n do
	nrotate cycle m;
	acc := first !cycle :: !acc;
	elim_head !cycle;
      done;
      !acc;;

