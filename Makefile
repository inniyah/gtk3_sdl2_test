VERSION := "`cat include/scriptix.h | grep VERSION | sed 's/^.*VERSION \"\(.*\)\".*$$/\1/'`"

all:
	( cd include ; make all )
	( cd lib ; make all )
	( cd bin ; make all )
	( cd test ; make all )

clean:
	( cd include ; make clean )
	( cd lib ; make clean )
	( cd bin ; make clean )
	( cd test ; make clean )

dist-clean:
	( cd include ; make dist-clean )
	( cd lib ; make dist-clean )
	( cd bin ; make dist-clean )
	( cd test ; make dist-clean )

dist:
	rm -rf scriptix/
	mkdir scriptix
	cp README COPYING Makefile scriptix/
	( cd include ; make dist )
	( cd lib ; make dist )
	( cd bin ; make dist )
	( cd test ; make dist )
	mv scriptix/ scriptix-$(VERSION)/
	tar -zcf scriptix-$(VERSION).tar.gz scriptix-$(VERSION)/
	rm -rf scriptix-$(VERSION)/
