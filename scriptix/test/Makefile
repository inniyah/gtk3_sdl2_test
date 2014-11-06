TESTS := test-fact test-comments test-inc test-logic test-array test-closure
SX := ../bin/scriptix

all: $(TESTS) 

../bin/scriptix:
	touch $@

test-fact: fact.sx $(SX)
	$(SX) fact.sx 1000 | grep -q 720 || /bin/false
	touch $@

test-comments: comments.sx $(SX)
	$(SX) comments.sx > /dev/null
	touch $@

test-inc: inc.sx $(SX)
	$(SX) inc.sx > /dev/null
	touch $@

test-logic: logic.sx $(SX)
	$(SX) logic.sx 2 1 | grep -q Success > /dev/null
	$(SX) logic.sx 1 2 | grep -q Failure > /dev/null
	touch $@

test-array: array.sx $(SX)
	$(SX) array.sx > /dev/null
	touch $@

test-closure: closure.sx $(SX)
	$(SX) closure.sx 1000 | grep -q 2046 || /bin/false
	touch $@

clean:
	rm -f $(TESTS)

dist-clean: clean

dist:
	mkdir ../scriptix/test
	cp Makefile $(TESTS:test-%=%.sx) ../scriptix/test/
