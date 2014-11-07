PROGRAM=scriptix
LIBNAME=scriptix
LIBRARY=lib$(LIBNAME)

all: $(LIBRARY).a $(LIBRARY).so $(PROGRAM)

MAJOR=0
MINOR=0

LIB_SRC = \
	src/array.cpp \
	src/eval.cpp \
	src/grammar.cpp \
	src/name.cpp \
	src/system.cpp \
	src/compiler.cpp \
	src/function.cpp \
	src/iter.cpp \
	src/number.cpp \
	src/string.cpp \
	src/type.cpp \
	src/error.cpp \
	src/global.cpp \
	src/optimize.cpp \
	src/struct.cpp \
	src/value.cpp \
	src/parser.cpp \
	src/lexer.cpp

PRG_SRC = \
	program/scriptix.cpp

INCLUDE_DIR = include

SHARED_OBJS = $(LIB_SRC:.cpp=.shared.o)
STATIC_OBJS = $(LIB_SRC:.cpp=.static.o)
PROGRAM_OBJS = $(PRG_SRC:.cpp=.o)

#PKG_CONFIG=
#PKG_CONFIG_CFLAGS=`pkg-config --cflags $(PKG_CONFIG)`
#PKG_CONFIG_LIBS=`pkg-config --libs $(PKG_CONFIG)`

CFLAGS=-O2 -g -Wall 
INCLUDE=-I$(INCLUDE_DIR) 
#INCLUDE=-I$(INCLUDE_DIR) $(PKG_CONFIG_CFLAGS)
STATIC_CFLAGS= -O2 -g -Wall $(CFLAGS) $(INCLUDE)
SHARED_CFLAGS= $(STATIC_CFLAGS) -fPIC

LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined
LIBS=-lgc
#LIBS=$(PKG_CONFIG_LIBS)

$(PROGRAM): $(PROGRAM_OBJS) $(LIBRARY).a $(LIBRARY).so
	g++ $(LDFLAGS) $(PROGRAM_OBJS) -o $@ -l$(LIBNAME) -L. $(LIBS)

$(LIBRARY).so.$(MAJOR).$(MINOR): $(SHARED_OBJS)
	g++ $(LDFLAGS) -shared \
		-Wl,-soname,$(LIBRARY).so.$(MAJOR) \
		-o $(LIBRARY).so.$(MAJOR).$(MINOR) \
		$+ -o $@ $(LIBS)

$(LIBRARY).so: $(LIBRARY).so.$(MAJOR).$(MINOR)
	rm -f $@.$(MAJOR)
	ln -s $@.$(MAJOR).$(MINOR) $@.$(MAJOR)
	rm -f $@
	ln -s $@.$(MAJOR) $@

$(LIBRARY).a: $(STATIC_OBJS)
	ar cru $@ $+

%.shared.o: %.cpp
	g++ -o $@ -c $+ $(SHARED_CFLAGS)

%.shared.o: %.c
	gcc -o $@ -c $+ $(SHARED_CFLAGS)

%.so : %.o
	g++ $(LDFLAGS) -shared $^ -o $@

%.static.o: %.cpp
	g++ -o $@ -c $+ $(STATIC_CFLAGS)

%.static.o: %.c
	gcc -o $@ -c $+ $(STATIC_CFLAGS)

%.o: %.cpp
	g++ -o $@ -c $+ $(STATIC_CFLAGS)

%.o: %.c
	gcc -o $@ -c $+ $(STATIC_CFLAGS)

%.cpp %.h: %.ll
	flex --outfile=$@ --header-file=$(@:.cpp=.h) $<

%.cpp %.h: %.yy
	bison --output=$@ --defines=$(@:.cpp=.h) $<

clean:
	rm -f $(SHARED_OBJS)
	rm -f $(STATIC_OBJS)
	rm -f $(PROGRAM_OBJS)
	rm -f $(PROGRAM)
	rm -f src/lexer.cpp src/lexer.h
	rm -f src/grammar.cpp src/grammar.h
	rm -f *.so *.so* *.a *~

.depend depend dep: $(LIB_SRC) $(PRG_SRC)
	g++ $(CFLAGS) -MM $(LIB_SRC) $(PRG_SRC) $(INCLUDE) $(PKG_CONFIG_CFLAGS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

test: $(PROGRAM)
	for PRG in test/*.sx; do \
		echo ; \
		echo Testing $${PRG}...  ; \
		LD_LIBRARY_PATH="." ./$(PROGRAM) $${PRG} || exit 1 ; \
		done
	echo ; echo Tests OK!

