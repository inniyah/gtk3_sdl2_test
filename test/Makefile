TESTS := test-fact test-scope test-comments test-inc test-class test-error test-logic test-array

all: $(TESTS) 

test-fact:
	../bin/scriptix fact.sx 1000 | grep -q 44 || /bin/false

test-scope:
	../bin/scriptix scope.sx > /dev/null

test-comments:
	../bin/scriptix comments.sx > /dev/null

test-inc:
	../bin/scriptix inc.sx > /dev/null

test-class:
	../bin/scriptix class.sx > /dev/null

test-logic:
	../bin/scriptix logic.sx 2 1 | grep -q Success > /dev/null
	../bin/scriptix logic.sx 1 2 | grep -q Failure > /dev/null

test-error:
	../bin/scriptix error.sx > /dev/null

test-array:
	../bin/scriptix array.sx > /dev/null

clean:

dist-clean: clean

dist:
	mkdir ../scriptix/test
	cp Makefile $(TESTS:test-%=%.sx) ../scriptix/test/
