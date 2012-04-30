open Cil
open Pretty
open Hashtbl

exception FunCallError of string;;

let calls = Hashtbl.create 32;;


let init_calls fname =
  if not (Hashtbl.mem calls fname) then
    Hashtbl.add calls fname 0
  else
    raise (FunCallError "Multiple declarations of the same function");;

let inc_calls fname = 
  if Hashtbl.mem calls fname then
    let count = Hashtbl.find calls fname
    in
    Hashtbl.replace calls fname (count + 1);
  else
    init_calls fname;;
(*    raise (FunCallError "Function call uninitialized");; *)



class doFunCallClass = object(self)
  inherit nopCilVisitor

  method vinst id =
    match id with
      | Call (lval_opt, e, elist, location) ->
	Pretty.fprint stdout 80 (d_instr () id);
	print_string "\n";
	Pretty.fprint stdout 80 (d_exp () e);
	print_string "\n";
	inc_calls (Pretty.sprint 80 (d_exp () e));
	SkipChildren;
      | _ -> DoChildren;
end

class doFunCollectClass = object(self)
  inherit nopCilVisitor

  method vfunc fd =
    init_calls fd.svar.vname;
    SkipChildren;
end



let reportFunCall () =
  print_string "Report function call count:";
  print_newline ();
  Hashtbl.iter (fun fname count ->
    print_string fname;
    print_string " = ";
    print_int count;
    print_newline ();
  ) calls;;

let feature : featureDescr =
  { fd_enabled     = ref false
  ; fd_name        = "FunCall"
  ; fd_description = "Function Call Analysis."
  ; fd_extraopt    = []
  ; fd_doit        =
      (fun file ->
        Cfg.computeFileCFG file;
        visitCilFile (new doFunCollectClass) file;
        visitCilFile (new doFunCallClass) file;

        reportFunCall ();
      )
  ; fd_post_check  = false
  }
