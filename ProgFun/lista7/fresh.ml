type action = Reset of int | Fresh of string;;

let closure =
  let memoized = ref 0 in
    function
      | Fresh prefix ->
	  memoized := !memoized + 1;
	  prefix ^ (string_of_int !memoized);
      | Reset n -> memoized := n;
	  "reset";;

let fresh prefix = closure (Fresh prefix);;
let reset n = ignore (closure (Reset n));;
	  

