CFLAGS = -g -Wall -I../include -O2
LIBS = -L../lib -lscriptix
OBJECTS = scriptix.o
#CC = ccmalloc gcc

all: scriptix

scriptix: $(OBJECTS) ../lib/libscriptix.a ../lib/libsxparse.a
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

$(OBJECTS): ../include/scriptix.h

clean:
	rm -f *.o scriptix

dist:
	mkdir ../scriptix/bin/
	cp *.c Makefile ../scriptix/bin

dist-clean: clean
