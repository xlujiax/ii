let memo =
  let memoized = Hashtbl.create 100 in
    fun f n ->
      if Hashtbl.mem memoized n then
	Hashtbl.find memoized n
      else
	let fn = f n in
	  Hashtbl.add memoized n fn;
	  fn;;

let memo_fib =
  let memoized = Hashtbl.create 100 in
  let rec fib = function
    | 0 | 1 -> 1
    | n ->
	if Hashtbl.mem memoized n then
	  Hashtbl.find memoized n
	else
	  let fn = fib (n - 1) + fib (n - 2) in
	    Hashtbl.add memoized n fn;
	    fn
  in fib;;

let rec fib = function
  | 0 | 1 -> 1
  | n -> (fib (n - 1)) + (fib (n - 2));;

let rec fib_memo = function
  | 0 | 1 -> 1
  | n -> (memo fib_memo (n - 1)) + (memo fib_memo (n - 2));;
