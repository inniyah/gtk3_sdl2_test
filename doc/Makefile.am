noinst_DATA=html-stamp

DOCBOOK := tutorial.xml
if DOCBOOK_TXT
TXT := $(DOCBOOK:%.xml=%.txt)
endif
if DOCBOOK_HTML
HTML := $(DOCBOOK:%.xml=%.html)
endif
if DOCBOOK_PDF
PDF := $(DOCBOOK:%.xml=%.pdf)
endif
DOCS := $(TXT) $(HTML) $(PDF)

EXTRA_DIST=$(DOCBOOK)

docdir = ${prefix}/@PACKAGE_TARNAME@-@VERSION@/doc
doc_DATA = $(TXT)

htmldir = ${prefix}/@PACKAGE_TARNAME@-@VERSION@/doc/html
html_DATA = $(HTML)

pdfdir = ${prefix}/@PACKAGE_TARNAME@-@VERSION@/doc/pdf
pdf_DATA = $(PDF)

html-stamp: ../include/scriptix.h
	if test -n '@PATH_CCDOC@' ; then \
		if ! test -d html ; then mkdir html ; fi ; \
		if test -f ccdoc.db ; then rm -f ccdoc.db ; fi ; \
		@PATH_CCDOC@ -db ccdoc.db -index -html html/ ../include/scriptix.h ; \
	fi
	touch html-stamp

%.html: %.xml
	@PATH_DOCBOOK2HTML@ -u $<

%.txt: %.xml
	@PATH_DOCBOOK2TXT@ $<

%.pdf: %.xml
	@PATH_DOCBOOK2PDF@ $<

clean-local:
	rm -f html-stamp
	rm -fr html/
	rm -f $(HTML) $(TXT) $(PDF) 
