#
#  Makefile
#
#  Copyright (c) 2021 by Daniel Kelley
#

DEBUG ?= -g

PREFIX ?= /usr/local

# address thread undefined etc.
ifneq ($(SANITIZE),)
DEBUG += -fsanitize=$(SANITIZE)
endif

REVKIT ?= $(CURDIR)/revkit
INC := -I$(REVKIT)/lib/easy
INC += -I$(REVKIT)/lib/kitty
INC += -I$(REVKIT)/lib/glucose
#Needed for lorina
#INC += -I$(REVKIT)/lib/fmt
#INC += -I$(REVKIT)/lib/rang
#INC += -I$(REVKIT)/lib/lorina

WARN ?= -Wall
WARN += -Wextra
WARN += -Werror
# RevKit needs the following...
WARN += -Wno-class-memaccess
WARN += -Wno-misleading-indentation
WARN += -Wno-type-limits
WARN += -Wno-error=sign-compare
WARN += -Wno-sign-compare

DEBUG += -std=c++17
CPPFLAGS := $(INC) -MP -MMD
CXXFLAGS += $(WARN)
CXXFLAGS += $(DEBUG)

SRC := xtg.cpp
SRC += xtg_tt_reader.cpp
#PLA reader needs lingkage debugging
#SRC += xtg_pla_reader.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

LDFLAGS := $(DEBUG)

LDLIBS += $(SANLIBS)
LDLIBS += -lboost_program_options
LDLIBS += -lm

PROG := xtg

.PHONY: all install uninstall check clean

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

install: $(PROG)
	install -p -m 755 $(PROG) $(PREFIX)/bin

uninstall:
	-rm -f $(PREFIX)/bin/$(PROG)

check: $(PROG)
	make -C test

clean:
	-rm -rf $(OBJ) $(DEP) $(PROG)

%.o: %.cpp
	$(CXX) $(DEBUG) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

-include $(DEP)
