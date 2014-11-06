noinst_DATA=html-stamp

html-stamp: ../include/scriptix.h
	if test -n '@PATH_CCDOC@' ; then \
		if ! test -d html ; then mkdir html ; fi ; \
		if test -f ccdoc.db ; then rm -f ccdoc.db ; fi ; \
		@PATH_CCDOC@ -db ccdoc.db -index -html html/ ../include/scriptix.h ; \
	fi
	touch html-stamp

clean-local:
	rm -f html-stamp
	rm -fr html/
