TARGET = $(TOP)/lib/libkind-tokenizer.a
SRCS   = $(wildcard *.cpp)
OBJS   = $(SRCS:.cpp=.o)
DEPS   = $(SRCS:.cpp=.dep)

all: $(TARGET)

.PHONY: clean all showconf

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

$(TARGET): $(OBJS)
	ar rsv $@ $?

	
showconf:
	@echo TOP=$(TOP)
	@echo CXXFLAGS=$(CXXFLAGS)
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo DEPS=$(DEPS)
	
include $(TOP)/Make_rules.mk
include $(DEPS)

