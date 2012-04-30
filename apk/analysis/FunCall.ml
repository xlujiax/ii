open Cil
open Pretty
open Hashtbl

exception FunCallError of string;;

let calls = Hashtbl.create 32;;

let inc_calls fname = 
  if Hashtbl.mem calls fname then
    let count = Hashtbl.find calls fname
    in
    Hashtbl.replace calls fname (count + 1);
  else
    raise (FunCallError "Function call uninitialized");;

let init_calls fname =
  if not (Hashtbl.mem calls fname) then
    Hashtbl.add calls fname 0
  else
    raise (FunCallError "Multiple declarations of the same function");;



class doFunCallClass = object(self)
  inherit nopCilVisitor

  method vstmt sd =
    ignore (warn "Statement");
    inc_calls "foo";
    DoChildren;
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
