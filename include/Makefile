all:

clean:

dist-clean: clean

install:
	install -D -d $(DESTDIR)/usr/local/include
	install -m 0644 scriptix.h $(DESTDIR)/usr/local/include

dist:
	mkdir ../scriptix/include
	cp Makefile scriptix.h ../scriptix/include/

