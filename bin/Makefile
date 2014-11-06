CFLAGS := -g -Wall -I../include -O2 $(CFLAGS)
OBJECTS := scriptix.o
#CC = ccmalloc gcc

all: scriptix

scriptix: $(OBJECTS) ../lib/libscriptix.a ../lib/libsxstdlib.a ../lib/libsxparse.a
	$(CC) -o $@ $(CFLAGS) $^

$(OBJECTS): ../include/scriptix.h

clean:
	rm -f *.o scriptix

dist:
	mkdir ../scriptix/bin/
	cp *.c Makefile ../scriptix/bin

dist-clean: clean

install:
	install -D -d $(DESTDIR)/$(prefix)/bin
	install -s -m 0755 scriptix $(DESTDIR)/$(prefix)/bin
