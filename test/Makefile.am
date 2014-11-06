TARGET_TESTS=\
	test-fact test-comments test-inc test-logic test-array \
	test-assoc test-thread test-global test-struct test-iter \
	test-string test-extend test-types test-big
SCRIPT_TESTS=\
	fact.sx comments.sx inc.sx logic.sx array.sx \
	assoc.sx thread.sx global.sx struct.sx iter.sx \
	string.sx extend.sx types.sx big.sx

EXTRA_DIST=$(SCRIPT_TESTS)
	
noinst_DATA=$(TARGET_TESTS)

SX := ../bin/scriptix

test-fact: fact.sx $(SX)
	echo '>> fact.sx:' >> test.log
	$(SX) $< 1000 2>&1 | tee -a test.log | grep 720 > /dev/null && touch $@

test-comments: comments.sx $(SX)
	echo '>> comments.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-inc: inc.sx $(SX)
	echo '>> inc.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-logic: logic.sx $(SX)
	echo '>> logic.sx:' >> test.log
	$(SX) $< 2 1 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@
	$(SX) $< 1 2 2>&1 | tee -a test.log | grep Failure > /dev/null && touch $@

test-array: array.sx $(SX)
	echo '>> array.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-iter: iter.sx $(SX)
	echo '>> iter.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-thread: thread.sx $(SX)
	echo '>> thread.sx:' >> test.log
	$(SX) $< >> test.log && touch $@

test-assoc: assoc.sx $(SX)
	echo '>> assoc.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep 'My name is Assoc!' > /dev/null && touch $@

test-global: global.sx $(SX)
	echo '>> global.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-struct: struct.sx $(SX)
	echo '>> struct.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-string: string.sx $(SX)
	echo '>> string.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-extend: extend.sx $(SX)
	echo '>> extend.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-types: types.sx $(SX)
	echo '>> types.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

test-big: big.sx $(SX)
	echo '>> big.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep Success > /dev/null && touch $@

clean-local:
	rm -f $(TARGET_TESTS) test.log
