TESTS := test-fact test-scope test-comments test-inc test-class test-error test-logic test-array
SX := LD_LIBRARY_PATH=../lib ../bin/scriptix

all: $(TESTS) 

test-fact:
	$(SX) fact.sx 1000 | grep -q 720 || /bin/false

test-scope:
	$(SX) scope.sx > /dev/null

test-comments:
	$(SX) comments.sx > /dev/null

test-inc:
	$(SX) inc.sx > /dev/null

test-class:
	$(SX) class.sx > /dev/null

test-logic:
	$(SX) logic.sx 2 1 | grep -q Success > /dev/null
	$(SX) logic.sx 1 2 | grep -q Failure > /dev/null

test-error:
	$(SX) error.sx > /dev/null

test-array:
	$(SX) array.sx > /dev/null

clean:

dist-clean: clean

dist:
	mkdir ../scriptix/test
	cp Makefile $(TESTS:test-%=%.sx) ../scriptix/test/
