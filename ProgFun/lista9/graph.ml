module type VERTEX =
sig
  type t
  type label

  val equal : t -> t -> bool
  val create : label -> t
  val get_label : t -> label
end;;

module Vertex : (VERTEX with type label = int) =
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
  val label : t -> label
end;;


module Edge : (EDGE with type label = int and type vertex = Vertex.t) =
struct
  type vertex = Vertex.t
  type label = int
  type t = { lab : label; a : vertex; b : vertex }

  let equal { lab = l1 } { lab = l2 } = l1 = l2
  let label { lab = l } = l
  let create l a b = { lab = l; a = a; b = b }
end;;
