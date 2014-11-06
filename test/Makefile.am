TARGET_TESTS=\
	test-fact test-comments test-inc test-logic test-array \
	test-assoc test-thread test-global test-struct test-iter \
	test-string test-extend test-types
SCRIPT_TESTS=\
	fact.sx comments.sx inc.sx logic.sx array.sx \
	assoc.sx thread.sx global.sx struct.sx iter.sx \
	string.sx extend.sx types.sx

EXTRA_DIST=$(SCRIPT_TESTS)
	
noinst_DATA=$(TARGET_TESTS)

SX := ../bin/scriptix

test-fact: fact.sx $(SX)
	echo '>> fact.sx:' >> test.log
	$(SX) $< 1000 2>&1 | tee -a test.log | grep -q 720
	touch $@ || /bin/true

test-comments: comments.sx $(SX)
	echo '>> comments.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-inc: inc.sx $(SX)
	echo '>> inc.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-logic: logic.sx $(SX)
	echo '>> logic.sx:' >> test.log
	$(SX) $< 2 1 2>&1 | tee -a test.log | grep -q Success
	$(SX) $< 1 2 2>&1 | tee -a test.log | grep -q Failure
	touch $@ || /bin/true

test-array: array.sx $(SX)
	echo '>> array.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-iter: iter.sx $(SX)
	echo '>> iter.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-thread: thread.sx $(SX)
	echo '>> thread.sx:' >> test.log
	$(SX) $< >> test.log
	touch $@ || /bin/true

test-assoc: assoc.sx $(SX)
	echo '>> assoc.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q 'My name is Assoc!'
	touch $@ || /bin/true

test-global: global.sx $(SX)
	echo '>> global.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-struct: struct.sx $(SX)
	echo '>> struct.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-string: string.sx $(SX)
	echo '>> string.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-extend: extend.sx $(SX)
	echo '>> extend.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

test-types: types.sx $(SX)
	echo '>> types.sx:' >> test.log
	$(SX) $< 2>&1 | tee -a test.log | grep -q Success
	touch $@ || /bin/true

clean-local:
	rm -f $(TARGET_TESTS) test.log
