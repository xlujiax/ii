open Cil
open Pretty
open Hashtbl

let calls = Hashtbl.create 32;;

class doFunCallClass = object(self)
  inherit nopCilVisitor

  method vstmt sd =
    (* If statement contains function call, increment external hash*)
    ignore (warn "Statement");
    (* Hashtbl.add calls "1" "2"; *)
    Hashtbl.add calls "asdf" 1;
    SkipChildren
end

let reportFunCall () =
  ignore (warn "Reporting");;

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
