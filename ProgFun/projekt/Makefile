all: main.e
clean:
	rm -f *.cm* lexer.ml parser.ml 3d.e

model.cmi: model.mli
	ocamlc -c $<

parser.cmi: parser.mli model.cmi
	ocamlc -c $<

parser.ml: parser.mly
	ocamlyacc $<

parser.cmo: parser.ml parser.cmi model.cmi 
	ocamlc -c $<

lexer.ml: lexer.mll
	ocamllex $<

lexer.cmo: lexer.ml parser.cmo  
	ocamlc -c $<

math.cmo: math.ml
	ocamlc -c $<

transformations.cmo: transformations.ml
	ocamlc -c $<

engine.cmo: math.cmo transformations.cmo engine.ml
	ocamlc -c engine.ml

main.e: parser.cmo lexer.cmo math.cmo transformations.cmo engine.cmo 
	ocamlc graphics.cma unix.cma $+ main.ml -o $@