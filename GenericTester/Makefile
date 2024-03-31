CPP=g++
SHARED_CFLAGS=-Wall -O3 -std=c++17
CFLAGS=$(SHARED_CFLAGS) -DBUILDING_LIB -fvisibility=hidden
INCLUDE=../shared
HEADERS=$(shell find . -name '*.hpp') $(shell find ../shared -name '*.hpp')
SOURCES=$(shell find . \( -name '*.cpp' -and -not -name '*_wrapper.cpp' \))
SHARED_SOURCES=$(shell find ../shared -name '*.cpp')
OBJS=$(patsubst ./%,./.objs/%,$(SOURCES:%.cpp=%.o))
SHARED_OBJS=$(patsubst ../shared/%,./.shobjs/%,$(SHARED_SOURCES:%.cpp=%.o))
LDFLAGS=-ldl -rdynamic -Wl,-rpath,'$$ORIGIN'

TESTED_CFLAGS=$(SHARED_CFLAGS) -nostdlib -nodefaultlibs -nostartfiles
TESTED_LDFLAGS=-shared -fPIC
TESTED_SOURCE=tested_code_wrapper.cpp

TARGET=generic_tester
TESTED_TARGET=solution.so

CFLAGS += -DARDUINO_PROGRAM=\"$(TESTED_TARGET)\"

.PHONY: all clear clean purge

all: $(TARGET) $(TESTED_TARGET)

# Calculate dependencies...

Makefile.dep: $(SOURCES) $(HEADERS) $(TESTED_SOURCE)
	@echo Calculating dependencies...
	@$(CPP) $(CFLAGS) -MM $(addprefix -I,$(INCLUDE)) $(SOURCES) > $@
	@$(CPP) $(TESTED_CFLAGS) -MM $(addprefix -I,$(INCLUDE)) $(TESTED_SOURCE) >> $@

-include Makefile.dep


# Building Targets

$(TESTED_TARGET): $(TESTED_SOURCE) $(HEADERS)
	@echo Compiling tested program "$@" ...
	@$(CPP) $(TESTED_CFLAGS) $(addprefix -I,$(INCLUDE)) $(TESTED_LDFLAGS) $(TESTED_SOURCE) -o $@

$(TARGET): .objs .shobjs $(OBJS) $(SHARED_OBJS) $(HEADERS)
	@echo Compiling and linking executable "$@" ...
	@$(CPP) $(CFLAGS) $(addprefix -I,$(INCLUDE)) $(LDFLAGS) $(addprefix -L,$(LIBDIRS)) $(addprefix -l,$(LIBS)) $(OBJS) $(SHARED_OBJS) -o $@

.objs:
	@mkdir -p "$@"

.shobjs:
	@mkdir -p "$@"

.objs/%.o: %.cpp
	@echo Compiling \'"$@"\' ...
	@$(CPP) -c $(CFLAGS) $(addprefix -I,$(INCLUDE)) "$<" -o "$@"

.shobjs/%.o: ../shared/%.cpp
	@echo Compiling \'"$@"\' ...
	@$(CPP) -c $(CFLAGS) $(addprefix -I,$(INCLUDE)) "$<" -o "$@"


# Cleaning Stuff

clear:
	@echo Removing object files ...
	-@rm -rf ./.objs
	-@rm -rf ./.shobjs

clean: clear

purge: clear
	@echo Removing executables ...
	-@rm -f ./$(TARGET) ./$(TESTED_TARGET) ./Makefile.dep
