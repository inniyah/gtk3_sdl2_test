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
	rm -f config.cache config.status config.log
	( cd include ; make dist-clean )
	( cd lib ; make dist-clean )
	( cd bin ; make dist-clean )
	( cd test ; make dist-clean )

install: all
	( cd include ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	( cd lib ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	( cd bin ; make install prefix=$(prefix) DESTDIR=$(DESTDIR) )
	install -D -d $(DESTDIR)/$(prefix)/share/doc/scriptix
	install -m 0644 README COPYING $(DESTDIR)/$(prefix)/share/doc/scriptix
	install -m 0755 scriptix-conf $(DESTDIR)/$(prefix)/bin/scriptix-conf

dist: all
	rm -rf scriptix/
	mkdir scriptix
	cp scriptix.spec scriptix.spec.in scriptix-conf.in README COPYING Makefile Makefile.in configure configure.in api.lst api.chk check-api.sh scriptix/
	( cd include ; make dist )
	( cd lib ; make dist )
	( cd bin ; make dist )
	( cd test ; make dist )
	( cd deb ; make dist )
	mv scriptix/ scriptix-0.19/
	tar -zcf scriptix-0.19.tar.gz scriptix-0.19/
	rm -rf scriptix-0.19/

deb:
	if [ ! -d debian/ ] ; then ln -s deb debian ; fi
	debuild -rfakeroot

rpm: dist
	rpm -ta scriptix-0.19.tar.gz

.PHONY: deb rpm dist install clean all dist-clean
