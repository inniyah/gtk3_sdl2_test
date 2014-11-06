TESTS := test-fact test-scope test-comments test-inc test-class test-error test-logic test-array
SX := ../bin/scriptix

all: $(TESTS) 

../bin/scriptix:
	touch $@

test-fact: fact.sx $(SX)
	$(SX) fact.sx 1000 | grep -q 720 || /bin/false
	touch $@

test-scope: scope.sx $(SX)
	$(SX) scope.sx > /dev/null
	touch $@

test-comments: comments.sx $(SX)
	$(SX) comments.sx > /dev/null
	touch $@

test-inc: inc.sx $(SX)
	$(SX) inc.sx > /dev/null
	touch $@

test-class: class.sx $(SX)
	$(SX) class.sx > /dev/null
	touch $@

test-logic: logic.sx $(SX)
	$(SX) logic.sx 2 1 | grep -q Success > /dev/null
	$(SX) logic.sx 1 2 | grep -q Failure > /dev/null
	touch $@

test-error: error.sx $(SX)
	$(SX) error.sx > /dev/null
	touch $@

test-array: array.sx $(SX)
	$(SX) array.sx > /dev/null
	touch $@

clean:
	rm -f $(TESTS)

dist-clean: clean

dist:
	mkdir ../scriptix/test
	cp Makefile $(TESTS:test-%=%.sx) ../scriptix/test/
