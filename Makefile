export TOP=$(PWD)
export CXXFLAGS=-std=c++11 -O3 -I$(TOP)/include -Wno-multichar
export LDFLAGS=-L$(TOP)/lib
export LIBS=-lkind-tokenizer
SUBDIRS=tokenizer parser tests

# rules for the top level makefile here

all: $(SUBDIRS) runtests

.PHONY: $(SUBDIRS) runtests

$(SUBDIRS):
	$(MAKE) -C $@

runtests: $(SUBDIRS)
	bin/kind-runtests

showconf:
	$(MAKE) -C tokenizer showconf
	
