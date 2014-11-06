CFLAGS := -g -Wall -I../include -O2
SXOBJ := eval.o value.o var.o thread.o node.o mem.o system.o stdlib.o
YYOBJ := y.tab.o lex.sx.o
OBJECTS := $(SXOBJ) $(YYOBJ)
#CC = ccmalloc gcc

all: libscriptix.a libsxparse.a

libscriptix.a: $(SXOBJ)
	$(AR) -cr $@ $^

libsxparse.a: $(YYOBJ)
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
	cp *.c *.h Makefile *.y *.l ../scriptix/lib/

dist-clean: clean
	rm -f lex.yy.c y.tab.c y.tab.h
