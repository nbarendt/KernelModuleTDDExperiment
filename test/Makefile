
PWD := $(shell pwd)

CPPUTEST_HOME := $(PWD)/../CppUTest

COMPONENT_NAME = KernelModuleTDD

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

SRC_DIRS = \
    $(PWD)/../src \
    test_doubles

TEST_SRC_DIRS = \
    AllTests

INCLUDE_DIRS = \
    $(PWD)/../src \
    $(CPPUTEST_HOME)/include \
	include \
	test_doubles \

CPPUTEST_WARNINGFLAGS = -Wall


include $(CPPUTEST_HOME)/build/MakefileWorker.mk
