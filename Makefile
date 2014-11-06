# Generated automatically from Makefile.in by configure.
prefix := /usr/local

debian: all
	if [ ! -d debian ] ; then ln -s deb debian ; fi

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
	( cd include ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	( cd lib ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	( cd bin ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	install -D -d $(DESTDIR)/$(prefix)/share/doc/scriptix-0.11
	install -m 0644 README COPYING $(DESTDIR)/$(prefix)/share/doc/scriptix-0.11

dist: all
	rm -rf scriptix/
	mkdir scriptix
	cp scriptix.spec scriptix.spec.in README COPYING Makefile Makefile.in configure configure.in scriptix/
	( cd include ; make dist )
	( cd lib ; make dist )
	( cd bin ; make dist )
	( cd test ; make dist )
	( cd deb ; make dist )
	mv scriptix/ scriptix-0.11/
	tar -zcf scriptix-0.11.tar.gz scriptix-0.11/
	rm -rf scriptix-0.11/
