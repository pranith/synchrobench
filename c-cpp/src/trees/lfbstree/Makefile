#VERSION = TCMALLOC_NO_UPDATE

ROOT = ../../..

include $(ROOT)/common/Makefile.common

.PHONY:	all clean
all:	main

BINS = $(BINDIR)/lockfree-bst

CFLAGS += -std=gnu++0x

main: test.o
	$(CXX) $(CFLAGS) test.o -o $(BINS) $(LDFLAGS)

test.o: wfrbt.h test.c
	$(CXX) $(CFLAGS) -c test.c
clean:
	-rm -f $(BINS)
