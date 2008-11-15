all: 3d.e
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

3d.e: parser.cmo lexer.cmo 3d.ml
	ocamlc $+ -o $@


