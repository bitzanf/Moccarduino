CPP=g++
CFLAGS=-Wall -O3 -std=c++17
INCLUDE=../shared
HEADERS=./test.hpp $(shell find ../shared -name '*.hpp')
SOURCES=$(shell find ./tests -name '*.cpp')
SHARED_SOURCES=$(shell find ../shared -name '*.cpp')
OBJS=$(patsubst ./tests/%,./.objs/%,$(SOURCES:%.cpp=%.o))
SHARED_OBJS=$(patsubst ../shared/%,./.shobjs/%,$(SHARED_SOURCES:%.cpp=%.o))
MAIN_SOURCE=unit_tests_main.cpp
TARGET=unit_tests


.PHONY: all clear clean purge

all: $(TARGET)

# Calculate dependencies...

Makefile.dep: $(SOURCES) $(HEADERS)
	@echo Calculating dependencies...
	@$(CPP) $(CFLAGS) -MM $(addprefix -I,$(INCLUDE)) $(SOURCES) > $@

-include Makefile.dep


# Building Targets

$(TARGET): $(MAIN_SOURCE) .objs .shobjs $(OBJS) $(HEADERS) $(SHARED_OBJS)
	@echo Compiling and linking executable "$@" ...
	@$(CPP) $(CFLAGS) $(addprefix -I,$(INCLUDE)) $(LDFLAGS) $(addprefix -L,$(LIBDIRS)) $(addprefix -l,$(LIBS)) $(OBJS) $(MAIN_SOURCE) $(SHARED_OBJS) -o $@

.objs:
	@mkdir -p "$@"

.shobjs:
	@mkdir -p "$@"

.objs/%.o: tests/%.cpp
	@echo Compiling \'"$@"\' ...
	@$(CPP) -c $(CFLAGS) $(addprefix -I,$(INCLUDE)) "$<" -o "$@"

.shobjs/%.o: ../shared/%.cpp
	@echo Compiling \'"$@"\' ...
	@$(CPP) -c $(CFLAGS) $(addprefix -I,$(INCLUDE)) "$<" -o "$@"

# Cleaning Stuff

clear:
	@echo Removing object files ...
	-@rm -rf ./.objs

clean: clear

purge: clear
	@echo Removing executable ...
	-@rm -f ./$(TARGET) ./Makefile.dep
