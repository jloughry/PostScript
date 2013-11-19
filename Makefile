target = notes_on_the_centroid_of_a_shield

#
# Filenames
#

latex_source = $(target).tex
postscript_source = shield.eps
logfile = $(target).log
pdf = $(target).pdf
dvi = $(target).dvi

documentation = README.md

#
# Executable Commands
#

# latex_cmd = pdflatex
latex_cmd = latex
pdf_cmd = dvipdfm

#
# Note: make requires that we set the value of a variable OUTSIDE any rules.
#

timestamp = `date +%Y%m%d.%H%M`

#
# Default makefile target
#

all: $(dvi)

#
# Helper makefile targets
#

$(dvi): $(latex_source) $(postscript_source)
	$(latex_cmd) $(latex_source)
	bibtex $(target)
	while ( \
		$(latex_cmd) $(latex_source) ; \
		grep "Rerun to get cross" $(logfile) > /dev/null ) do true ; \
	done
	$(pdf_cmd) $(dvi)

vi:
	vi $(latex_source)

picture:
	ps2pdf st_cross_shield.eps

clean:
	rm -f $(dvi) *.aux *.bbl *.blg *.idx *.ilg *.ind *.log .pdf

allclean: clean
	rm $(pdf) st_cross_shield.pdf

touch:
	touch $(latex_source)

readme:
	vi $(documentation)

spell:
	aspell --lang=en_GB check $(documentation)

commit:
	git add .
	git commit -am "commit from Makefile $(timestamp)"
	git pull --rebase
	git push

