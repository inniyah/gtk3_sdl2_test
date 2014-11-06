# Generated automatically from Makefile.in by configure.
CC := gcc
CFLAGS := -I../include -g -O2 -Wall
OBJECTS := scriptix.o
#CC = ccmalloc gcc

all: scriptix scriptix-shared

scriptix-shared: $(OBJECTS)
	$(CC)  -L../lib -lscriptix -lsxparse -o $@ $(CFLAGS) $^

scriptix: $(OBJECTS) ../lib/libsxparse.a ../lib/libscriptix.a 
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) ../lib/libsxparse.a ../lib/libscriptix.a

$(OBJECTS): ../include/scriptix.h

clean:
	rm -f *.o scriptix

dist:
	mkdir ../scriptix/bin/
	cp *.c Makefile.in scriptix-conf.in ../scriptix/bin

dist-clean: clean

install:
	install -d $(DESTDIR)/$(prefix)/bin
	if test -x scriptix-shared ; then install -s -m 0755 scriptix-shared $(DESTDIR)/$(prefix)/bin/scriptix ; else install -s -m 0755 scriptix $(DESTDIR)/$(prefix)/bin/scriptix ; fi
	install -m 0755 scriptix-conf $(DESTDIR)/$(prefix)/bin/scriptix-conf
