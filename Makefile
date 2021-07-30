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
INC += -I$(REVKIT)/lib/fmt
INC += -I$(REVKIT)/lib/lorina
INC += -I$(REVKIT)/lib/rang

WARN ?= -Wall
WARN += -Wextra
WARN += -Werror
# RevKit needs the following...
WARN += -Wno-class-memaccess
WARN += -Wno-misleading-indentation
WARN += -Wno-type-limits
WARN += -Wno-error=sign-compare
WARN += -Wno-sign-compare

CPPFLAGS := $(INC) -MP -MMD
CXXFLAGS := -std=c++17
CXXFLAGS += $(WARN)
CXXFLAGS += $(DEBUG)

SRC := xtg.cpp
SRC += xtg_tt_reader.cpp
#PLA reader needs lingkage debugging
#SRC += xtg_pla_reader.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

LDFLAGS :=

LDLIBS += $(SANLIBS)
LDLIBS += -lboost_program_options
LDLIBS += -lstdc++
LDLIBS += -lm

PROG := xtg

.PHONY: all install uninstall check clean

all: $(PROG)

$(PROG): $(OBJ)

install: $(PROG)
	install -p -m 755 $(PROG) $(PREFIX)/bin

uninstall:
	-rm -f $(PREFIX)/bin/$(PROG)

check: $(PROG)
	make -C test

clean:
	-rm -rf $(OBJ) $(DEP) $(PROG)

-include $(DEP)
