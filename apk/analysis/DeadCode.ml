
open Cil
open Pretty

(* ========================================================================= *)
(*                             DEFINICJA PRZEPŁYWU                           *)
(* ========================================================================= *)

module DeadCodeFlow = struct (* : ForwardsTransfer *)
  let name  = "Dead code"
  let debug = ref false

        (* KRATA *)
  type t = bool

  let copy a = a

        (* Tu będą zapisane wyniki analizy *)
  let stmtStartData = Inthash.create 32

  let pretty () a =
    if a then text "alive"
    else text "dead"

        (* ELEMENT NAJMNIEJSZY *)
  let computeFirstPredecessor stmt _ = false
        (* SUPREMUM *)
        (* Zwraca None jeśli się nic nie zmieniło, lub Some wynik *)
  let combinePredecessors stmt ~old:old nw =
    if old = nw then None
    else Some (old || nw)

        (* PRZEJŚCIE PRZEZ INSTRUKCJE *)
  let doInstr _ _ = Dataflow.Default
  let doStmt _ _ = Dataflow.SDefault
  let doGuard _ _ = Dataflow.GDefault
  let filterStmt _ = true
end

module DeadCode = Dataflow.ForwardsDataFlow(DeadCodeFlow)

(* ========================================================================= *)
(*                           ANALIZA MARTWEGO KODU                           *)
(* ========================================================================= *)

let computeDeadCode fd =
        (* Weź wszystkie polecenia *)
  let all_stmts = fst (Dataflow.find_stmts fd) in
        (* Zacznij od elementu najmniejszego *)
  List.iter (fun s -> Inthash.add DeadCodeFlow.stmtStartData s.sid false) all_stmts;
        (* Dla pierwszego polecenia ustaw wartość true (kod żywy) *)
  begin match fd.sbody.bstmts with
    | [] -> ()
    | s::_ -> Inthash.add DeadCodeFlow.stmtStartData s.sid true
  end;
        (* Wykonaj analizę *)
  DeadCode.compute (all_stmts)

















(* ========================================================================= *)
(*                               ODWIEDZAJĄCY                                *)
(* ========================================================================= *)

class doFeatureClass = object(self)
  inherit nopCilVisitor

  method vfunc fd =
    computeDeadCode fd;
    SkipChildren
end


















(* ========================================================================= *)
(*                           ODWIEDZAJĄCY Z PRZESTROGĄ                       *)
(* ========================================================================= *)

class warnDeadCodeClass = object(self)
  inherit nopCilVisitor

  method vstmt sd =
    if Inthash.find DeadCodeFlow.stmtStartData sd.sid then
      DoChildren
    else begin
      ignore (warn "Dead code detected!");
      SkipChildren
    end
end













(* ========================================================================= *)
(*                                 OPIS ANALIZY                              *)
(* ========================================================================= *)

let feature : featureDescr =
  { fd_enabled     = ref false
  ; fd_name        = "DeadCode"
  ; fd_description = "Dead Code Analysis."
  ; fd_extraopt    = []
  ; fd_doit        =
      (fun file ->
                        (* WAŻNE!!! *)
                        (* Obliczyć graf przepływu przed przystąpieniem do analizy!!! *)
        Cfg.computeFileCFG file;
        visitCilFile (new doFeatureClass) file;
        visitCilFile (new warnDeadCodeClass) file;
      )
  ; fd_post_check  = false
  }
