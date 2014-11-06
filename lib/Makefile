# Generated automatically from Makefile.in by configure.
CC := gcc
RANLIB := ranlib
CFLAGS := -I../include -g -O2 -Wall
LIBS := libscriptix.a libsxparse.a
SOLIBS := libscriptix.so.0.22 libsxparse.so.0.22
SXOBJ := \
	array.o \
	block.o \
	closure.o \
	error.o \
	eval.o \
	function.o \
	mem.o \
	name.o \
	number.o \
	object.o \
	stdlib.o \
	string.o \
	system.o \
	thread.o \
	type.o \
	value.o \
	var.o
SOSXOBJ := $(SXOBJ:%.o=%.lo)
YYOBJ := \
	lex.sx.o \
	y.tab.o \
	parser.o \
	compiler.o \
	transform.o 
SOYYOBJ := $(YYOBJ:%.o=%.lo)
OBJECTS := $(SXOBJ) $(YYOBJ)
SOOBJECTS := $(SOSXOBJ) $(SOYYOBJ)
#CC = ccmalloc gcc

all: $(LIBS) $(SOLIBS)

libscriptix.a: $(SXOBJ)
	$(AR) -cr $@ $(SXOBJ)
	$(RANLIB) $@
libsxparse.a: $(YYOBJ)
	$(AR) -cr $@ $(YYOBJ)
	$(RANLIB) $@

libscriptix.so.0.22: $(SOSXOBJ)
	$(CC) -shared -Wl,--soname,$@ -o $@ $^
	ln -sf $@ libscriptix.so.0
	ln -sf libscriptix.so.0 libscriptix.so

libsxparse.so.0.22: $(SOYYOBJ)
	$(CC) -shared -Wl,--soname,$@ -o $@ $^
	ln -sf $@ libsxparse.so.0
	ln -sf libsxparse.so.0 libsxparse.so

lex.sx.c: lexer.l y.tab.h ../include/scriptix.h
	$(LEX) -Psx lexer.l

y.tab.c y.tab.h: grammar.y ../include/scriptix.h
	$(YACC) -p sx -d grammar.y

$(OBJECTS) $(SOOBJECTS): ../include/scriptix.h ../include/config.h ../include/parser.h

%.lo: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(SOOBJECTS) $(LIBS) $(SOLIBS)

dist: lex.sx.c y.tab.c y.tab.h
	mkdir ../scriptix/lib/
	cp $(OBJECTS:%.o=%.c) y.tab.h Makefile.in grammar.y lexer.l ../scriptix/lib/

dist-clean: clean
	rm -f lex.sx.c y.tab.c y.tab.h

install:
	install -d $(DESTDIR)/$(prefix)/lib
	install -m 0644 $(LIBS) $(SOLIBS) $(DESTDIR)/$(prefix)/lib
	cd $(DESTDIR)/$(prefix)/lib ;\
	ranlib libscriptix.a ;\
	ranlib libsxparse.a ;\
	ln -sf libscriptix.so.0.22 libscriptix.so.0 ;\
	ln -sf libsxparse.so.0.22 libsxparse.so.0 ;\
	ln -sf libscriptix.so.0 libscriptix.so ;\
	ln -sf libsxparse.so.0 libsxparse.so
