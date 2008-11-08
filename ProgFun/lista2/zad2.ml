let rec a n = match n with
    0 -> 1
  | 1 -> 2
  | _ -> 2 * (a (n-2)) - (a (n-1)) + 1

let rec a' ?(acc_min_2=1) ?(acc_min_1=2) ?(i=0) n =
  let acc_actual = 2 * acc_min_2 - acc_min_1 + 1
  in
  if i = n then acc_min_2
  else a' ~acc_min_1:acc_actual ~acc_min_2:acc_min_1 ~i:(i + 1) n
