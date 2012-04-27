open Cil
open Pretty
open Hashtbl

let calls = Hashtbl.create 32;;

let inc_calls fname = 
  if Hashtbl.mem calls fname then
    let count = Hashtbl.find calls fname
    in
    Hashtbl.replace calls fname (count + 1);
  else
    Hashtbl.add calls fname 1;;

class doFunCallClass = object(self)
  inherit nopCilVisitor

  method vstmt sd =
    ignore (warn "Statement");
    inc_calls "foo";
    SkipChildren;
end

let reportFunCall () =
  print_string "Reporting...";
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
	let funCall = new doFunCallClass in
        visitCilFile funCall file;
        reportFunCall ();
      )
  ; fd_post_check  = false
  }
