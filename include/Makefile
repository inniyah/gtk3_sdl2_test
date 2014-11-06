all:

clean:

dist-clean: clean

install:
	install -D -d $(DESTDIR)/$(prefix)/include/scriptix
	install -m 0644 scriptix.h config.h $(DESTDIR)/$(prefix)/include/scriptix

dist:
	mkdir ../scriptix/include
	cp Makefile scriptix.h config.h config.h.in ../scriptix/include/

