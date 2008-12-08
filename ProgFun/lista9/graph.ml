module type VERTEX =
sig
  type t
  type label

  val equal : t -> t -> bool
  val create : label -> t
  val get_label : t -> label
end;;

module Vertex : VERTEX with type label = int =
struct
  type label = int
  type t = { lab : label }

  let equal { lab = l1 } { lab = l2 } = l1 = l2
  let create l = { lab = l }
  let get_label { lab = l } = l
end;;

module type EDGE =
sig
  type t
  type label

  type vertex

  val equal : t -> t -> bool
  val create : label -> vertex -> vertex -> t
  val get_label : t -> label
  val get_start : t -> vertex
  val get_end : t -> vertex
end;;

module Edge (V : VERTEX) : (EDGE with type vertex = V.t and type label = int) =
struct
  type vertex = V.t
  type label = int
  type t = { lab : label; a : vertex; b : vertex }

  let equal { a = a1; b = b1 } { a = a2; b = b2 } = V.equal a1 a2 && V.equal b1 b2
  let get_label { lab = l } = l
  let create l a b = { lab = l; a = a; b = b }
  let get_start { a = start } = start
  let get_end { b = en } = en
end;;

module XEdge = Edge(Vertex);;

module type GRAPH =
sig 
  type t

  module V : VERTEX
  type vertex = V.t

  module E : EDGE with type vertex = vertex
  type edge = E.t
      
  (* funkcje wyszukiwania *)
  val mem_v : t -> vertex -> bool
  val mem_e : t -> edge -> bool
  val mem_e_v : t -> vertex -> vertex -> bool
  (*val find_e : t -> vertex -> vertex -> edge*)
  val succ : t -> vertex -> vertex list
  val pred : t -> vertex -> vertex list
  (*val succ_e : t -> vertex -> edge list
  val pred_e : t -> vertex -> edge list*)

  (* funkcje modyfikacji *) 
  val empty : t
  val add_e : t -> edge -> t
  val add_v : t -> vertex -> t
  val rem_e : t -> edge -> t
  val rem_v : t -> vertex -> t

  (* iteratory *)
  val fold_v : (vertex -> 'a -> 'a) -> t -> 'a -> 'a
  val fold_e : (edge -> 'a -> 'a) -> t -> 'a -> 'a

  val dfs : t -> vertex -> vertex list
end;;

module Graph (VER : VERTEX) (EDG : EDGE with type vertex = VER.t and type label = int) : (GRAPH with module V = VER and module E = EDG) =
struct
  module V = VER
  module E = EDG
    
  type edge = EDG.t
  type vertex = VER.t

  type t = { edges : edge list; vertices : vertex list }

  (* funkcje wyszukiwania *)
  let mem_v g v = List.exists (V.equal v) g.vertices
  let mem_e g e = List.exists (E.equal e) g.edges
  let mem_e_v g vstart vend = let e = E.create 789 vstart vend in mem_e g e
  (*let find_e : t -> vertex -> vertex -> edge*)
  let succ g v = List.filter (mem_e_v g v) g.vertices
  let pred g v = List.filter (fun v2 -> mem_e_v g v v2) g.vertices
  (* let succ_e : t -> vertex -> edge list
  let pred_e : t -> vertex -> edge list*)

  (* funkcje modyfikacji *) 
  let empty = { edges = []; vertices = [] }
  let add_v g v = { edges = g.edges; vertices = v :: g.vertices }
  let add_e g e = { edges = e :: g.edges; vertices = g.vertices }
  let rem_v g v = { edges = g.edges; vertices = List.filter (fun v2 -> not (V.equal v v2)) g.vertices }
  let rem_e g e = { edges = List.filter (fun e2 -> not (E.equal e e2)) g.edges; vertices = g.vertices }

  (* iteratory *)
  let fold_v f g i = List.fold_right f g.vertices i
  let fold_e f g i = List.fold_right f g.edges i

  let dfs g vstart =
    let visited = ref []
    in let rec aux actual =
      if List.exists (V.equal actual) !visited then
	[]
      else begin
	visited := vstart :: !visited;
	List.flatten (List.map aux (succ g vstart))
      end
    in aux vstart;
      !visited
end;;

module XGraph = Graph(Vertex) (XEdge);;

let a = Vertex.create 5;;
let b = Vertex.create 6;;
let e = XEdge.create 56 a b;;
let g = XGraph.empty;;
let g = XGraph.add_v g a;;
let g = XGraph.add_v g b;;
let g = XGraph.add_e g e;;
