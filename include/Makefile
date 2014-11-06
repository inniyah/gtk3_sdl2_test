HEADERS := scriptix.h config.h system.h parser.h

all:

clean:

dist-clean: clean

install:
	install -D -d $(DESTDIR)/$(prefix)/include/scriptix
	install -m 0644 $(HEADERS) $(DESTDIR)/$(prefix)/include/scriptix

dist:
	mkdir ../scriptix/include
	cp Makefile config.h.in $(HEADERS) ../scriptix/include/

