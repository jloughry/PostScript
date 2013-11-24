target = notes_on_the_centroid_of_a_shield

#
# Filenames
#

latex_source = $(target).tex
postscript_source = shield.eps
logfile = $(target).log
pdf = $(target).pdf
dvi = $(target).dvi

#
# Executable Commands
#

# latex_cmd = pdflatex
latex_cmd = latex
pdf_cmd = dvipdfm

include ../Makefiles/git1.mk

all: $(dvi)

include ../Makefiles/git2.mk

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

spell:
	aspell --lang=en_GB check $(documentation)

