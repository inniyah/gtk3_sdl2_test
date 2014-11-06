noinst_DATA=manual-stamp

DOCBOOK := tutorial.xml
if BUILD_DOCS
TXT := $(DOCBOOK:%.xml=%.txt)
HTML := $(DOCBOOK:%.xml=%.html)
if BUILD_PDF
PDF := $(DOCBOOK:%.xml=%.pdf)
endif
endif
DOCS := $(TXT) $(HTML) $(PDF)

EXTRA_DIST=$(DOCBOOK)

docdir = ${prefix}/share/doc/@PACKAGE_TARNAME@-@VERSION@
doc_DATA = $(TXT)

htmldir = ${prefix}/share/doc/@PACKAGE_TARNAME@-@VERSION@
html_DATA = $(HTML)

pdfdir = ${prefix}/share/doc/@PACKAGE_TARNAME@-@VERSION@
pdf_DATA = $(PDF)

manual-stamp: ../include/scriptix.h
	if test -n '@PATH_CCDOC@' ; then \
		if ! test -d manual ; then mkdir manual ; fi ; \
		if test -f ccdoc.db ; then rm -f ccdoc.db ; fi ; \
		@PATH_CCDOC@ -db ccdoc.db -index -html manual/ ../include/scriptix.h ; \
	fi
	touch manual-stamp

%.html: %.xml
	@PATH_XMLTO@ html-nochunks $<

%.txt: %.xml
	@PATH_XMLTO@ txt $<

%.pdf: %.xml
	@PATH_XMLTO@ pdf $<

clean-local:
	rm -f manual-stamp
	rm -fr manual/
	rm -fr $(HTML) $(TXT) $(PDF) 
