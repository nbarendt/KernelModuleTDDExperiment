default:
	$(MAKE) -C src

.PHONY: CppUTest
CppUTest:
	$(MAKE) -C CppUTest all extensions

.PHONY: module_clean
module_clean:
	$(MAKE) -C src clean 

.PHONY: test
test:  CppUTest module_clean
	$(MAKE) -C test
