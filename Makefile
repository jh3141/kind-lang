export TOP=$(PWD)
export CXXFLAGS=-std=c++11 -O3 -I$(TOP)/include
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
	
# implicit rules to be used by subdirectory makefiles below here

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -M $(CXXFLAGS) $< > $@

