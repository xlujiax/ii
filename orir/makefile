.PHONY: all
all: presentation.pdf
presentation.pdf: presentation.tex
	pdflatex presentation.tex

textemp = *.aux *.log *.nav *.out *.snm *.toc
clear:
	rm -f $(textemp)
	rm presentation.pdf
