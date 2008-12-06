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
  type t = { lab : label; mutable visited : bool }

  let equal { lab = l1 } { lab = l2 } = l1 = l2
  let create l = { lab = l; visited = false }
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
end;;

module Edge (V : VERTEX) : (EDGE with type vertex = V.t and type label = int) =
struct
  type vertex = V.t
  type label = int
  type t = { lab : label; a : vertex; b : vertex }

  let equal { lab = l1 } { lab = l2 } = l1 = l2
  let get_label { lab = l } = l
  let create l a b = { lab = l; a = a; b = b }
end;;

module XEdge = Edge(Vertex);;

module type GRAPH =
sig
  type t

  module V : VERTEX
  type vertex = V.t

  module E : EDGE with type vertex = vertex
  type edge = E.t

  val empty : t
  val add_e : t -> edge -> t
  val add_v : t -> vertex -> t
end;;

module Graph (VER : VERTEX) (EDG : EDGE with type vertex = VER.t) : (GRAPH) =
struct
  module V = VER
  module E = EDG
    
  type edge = EDG.t
  type vertex = VER.t

  type t = { edges : edge list; vertices : vertex list }

  let empty = { edges = []; vertices = [] }
  let add_v g v = { edges = g.edges; vertices = v :: g.vertices }
  let add_e g e = { edges = e :: g.edges; vertices = g.vertices }
end;;

module XGraph = Graph(Vertex) (XEdge);;

let a = Vertex.create 5;;
let b = Vertex.create 6;;
let e = XEdge.create 56 a b;;
let g = XGraph.empty;;
