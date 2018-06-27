INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src
include_HEADERS = suites.h LogTest.h ExceptionTest.h TaskQueueTest.h DispatcherTest.h ThreadPoolTest.h TimerTest.h
noinst_PROGRAMS = ../bin/test
___bin_test_SOURCES = test.cc LogTest.cc ExceptionTest.cc \
	BasicFileTest.cc SocketTest.cc TaskQueueTest.cc DispatcherTest.cc ThreadPoolTest.cc \
	TimerTest.cc

___bin_test_LDADD = ../src/libunp.la
___bin_test_LDFLAGS = -lboost_unit_test_framework -lpthread
