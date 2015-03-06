export TOP=$(PWD)
export CXXFLAGS=-std=c++11 -g -I$(TOP)/include -Wno-multichar
export LDFLAGS=-L$(TOP)/lib
export LIBS=-lkind-parser -lkind-tokenizer
SUBDIRS=tokenizer parser tests

# rules for the top level makefile here

all: $(SUBDIRS) runtests

.PHONY: $(SUBDIRS) runtests showconf clean

$(SUBDIRS):
	$(MAKE) -C $@

runtests: $(SUBDIRS)
	bin/kind-runtests

showconf:
	$(MAKE) -C tokenizer showconf
	
clean: 
	rm -f bin/kind* lib/*.a */*.o */*.dep
