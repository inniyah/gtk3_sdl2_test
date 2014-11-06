TESTS=\
	test-fact test-comments test-inc test-logic test-array \
	test-assoc test-thread test-global test-struct test-iter \
	test-string
SCRIPT_TESTS=\
	fact.sx comments.sx inc.sx logic.sx array.sx \
	assoc.sx thread.sx global.sx struct.sx iter.sx \
	string.sx

EXTRA_DIST=$(SCRIPT_TESTS)
	
noinst_DATA=$(TESTS)

SX := ../bin/scriptix

../bin/scriptix:
	touch $@

test-fact: fact.sx $(SX)
	echo '>> fact.sx:' >> test.log
	$(SX) fact.sx 1000 2>&1 | tee -a test.log | grep -q 720
	touch $@

test-comments: comments.sx $(SX)
	echo '>> comments.sx:' >> test.log
	$(SX) comments.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-inc: inc.sx $(SX)
	echo '>> inc.sx:' >> test.log
	$(SX) inc.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-logic: logic.sx $(SX)
	echo '>> logic.sx:' >> test.log
	$(SX) logic.sx 2 1 2>&1 | tee -a test.log | grep -q Success
	$(SX) logic.sx 1 2 2>&1 | tee -a test.log | grep -q Failure
	touch $@

test-array: array.sx $(SX)
	echo '>> array.sx:' >> test.log
	$(SX) array.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-iter: iter.sx $(SX)
	echo '>> iter.sx:' >> test.log
	$(SX) iter.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-thread: thread.sx $(SX)
	echo '>> thread.sx:' >> test.log
	$(SX) thread.sx >> test.log
	touch $@

test-assoc: assoc.sx $(SX)
	echo '>> assoc.sx:' >> test.log
	$(SX) assoc.sx 2>&1 | tee -a test.log | grep -q 'My name is Assoc!'
	touch $@

test-global: global.sx $(SX)
	echo '>> global.sx:' >> test.log
	$(SX) global.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-struct: struct.sx $(SX)
	echo '>> struct.sx:' >> test.log
	$(SX) struct.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

test-string: string.sx $(SX)
	echo '>> string.sx:' >> test.log
	$(SX) string.sx 2>&1 | tee -a test.log | grep -q Success
	touch $@

clean-local:
	rm -f $(TESTS)
