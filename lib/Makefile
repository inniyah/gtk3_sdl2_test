CFLAGS := -g -Wall -I../include -O2
LIBS := libscriptix.a libsxparse.a libsxstdlib.a
SXOBJ := eval.o value.o var.o thread.o mem.o system.o class.o
YYOBJ := y.tab.o lex.sx.o
SLOBJ := stdlib.o
OBJECTS := $(SXOBJ) $(YYOBJ) $(SLOBJ)
#CC = ccmalloc gcc

all: libscriptix.a libsxparse.a libsxstdlib.a

libscriptix.a: $(SXOBJ)
	$(AR) -cr $@ $^

libsxparse.a: $(YYOBJ)
	$(AR) -cr $@ $^

libsxstdlib.a: $(SLOBJ)
	$(AR) -cr $@ $^

lex.sx.c: lexer.l y.tab.h ../include/scriptix.h
	$(LEX) -Psx lexer.l

y.tab.c y.tab.h: grammar.y ../include/scriptix.h
	$(YACC) -p sx -d grammar.y

$(OBJECTS): ../include/scriptix.h

clean:
	rm -f *.o *.a

dist:
	mkdir ../scriptix/lib/
	cp $(OBJECTS:%.o=%.c) Makefile grammar.y lexer.l ../scriptix/lib/

dist-clean: clean
	rm -f lex.yy.c y.tab.c y.tab.h

install:
	install -D -d $(DESTDIR)/usr/local/lib
	install -s -m 0644 $(LIBS) $(DESTDIR)/usr/local/lib
