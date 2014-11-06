VERSION := "`cat include/scriptix.h | grep VERSION | sed 's/^.*VERSION \"\(.*\)\".*$$/\1/'`"
DESTDIR := /

all:
	( cd include ; make all )
	( cd lib ; make all )
	( cd bin ; make all )
	( cd test ; make all )
	( cd deb ; make all )

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

install: all
	( cd include ; make install DESTDIR=$(DESTDIR) )
	( cd lib ; make install DESTDIR=$(DESTDIR) )
	( cd bin ; make install DESTDIR=$(DESTDIR) )
	install -D -d $(DESTDIR)/usr/local/doc/scriptix
	install -m 0644 README COPYING $(DESTDIR)/usr/local/doc/scriptix

dist: all
	rm -rf scriptix/
	mkdir scriptix
	cp README COPYING Makefile scriptix/
	( cd include ; make dist )
	( cd lib ; make dist )
	( cd bin ; make dist )
	( cd test ; make dist )
	( cd deb ; make dist )
	mv scriptix/ scriptix-$(VERSION)/
	tar -zcf scriptix-$(VERSION).tar.gz scriptix-$(VERSION)/
	rm -rf scriptix-$(VERSION)/
