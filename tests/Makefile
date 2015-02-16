TARGET = $(TOP)/bin/kind-runtests
SRCS   = $(wildcard *.cpp)
OBJS   = $(SRCS:.cpp=.o)
DEPS   = $(SRCS:.cpp=.dep)

all: $(TARGET)

.PHONY: clean all showconf

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

$(TARGET): $(OBJS) $(TOP)/lib/*.a
	g++ -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	
showconf:
	@echo TOP=$(TOP)
	@echo CXXFLAGS=$(CXXFLAGS)
	@echo LDFLAGS=$(LDFLAGS)
	@echo LIBS=$(LIBS)
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo DEPS=$(DEPS)
	
include $(TOP)/Make_rules.mk
include $(DEPS)

