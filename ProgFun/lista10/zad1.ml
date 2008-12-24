#load "graphics.cma";;

class virtual drawable =
object (self)

  method virtual vertices : (int * int) array 
  method virtual color : Graphics.color

  method draw = (Graphics.set_color (self#color); 
                 Graphics.fill_poly (self#vertices))

end;;

class polygon (pvs : (int * int) array) =
object
  inherit drawable
  val vs = pvs
  val col = Graphics.rgb 100 100 100
  method vertices = vs
  method color = col
  method change_color new_col = {< col = new_col >}
end;;

class rectangle (x,y) w h =
object
  inherit polygon [|(x,y);(x + w, y);(x + w, y + h);(x, y + h)|]
end;;

class square (x,y) a =
object
  inherit rectangle (x,y) a a
end;;

class ['a] collection =
object (self)
  val objs : 'a list = []
  method get_lst = objs
  method add x = {< objs = x :: self#get_lst >}
  method draw_all = List.iter (fun obj -> obj#draw) objs
end;;

let tri = new polygon [|(100,100); (100,200); (200,200)|];;
let r = new rectangle (300, 100) 50 25;;
let s = new square (300, 300) 50;;

let init () =
  Graphics.open_graph " 640x640";
  let c = new collection in
  let c = c#add s in
  let c = c#add (tri#change_color (Graphics.rgb 0 0 200)) in
  let c = c#add r in
  let c = c#add s in
    c#draw_all;
  let _ = Graphics.read_key () in Graphics.close_graph();;
