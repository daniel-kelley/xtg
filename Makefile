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

REVKIT ?= $(HOME)/oss/revkit
INC := -I$(REVKIT)/lib/easy
INC += -I$(REVKIT)/lib/kitty
INC += -I$(REVKIT)/lib/glucose
INC += -I$(REVKIT)/lib/fmt
INC += -I$(REVKIT)/lib/lorina
INC += -I$(REVKIT)/lib/rang

WARN :=
#WARN := -Wall
#WARN += -Wextra
#WARN += -Werror
# -std=c++17
CPPFLAGS := $(INC) -MP -MMD
CXXFLAGS := $(WARN) $(DEBUG)

SRC := xtg.cpp
#SRC += xtg_pla_reader.cpp
SRC += xtg_tt_reader.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

LDFLAGS :=

LDLIBS += -lstdc++
LDLIBS += -lm

#
# Valgrind
#
VG ?= valgrind --leak-check=full --show-leak-kinds=all

PROG := xtg

.PHONY: all install uninstall check clean

all: $(PROG)

$(PROG): $(OBJ)

install: $(PROG)
	install -p -m 755 $(PROG) $(PREFIX)/bin

uninstall:
	-rm -f $(PREFIX)/bin/$(PROG)

check:
	@echo nothing...

clean:
	-rm -rf $(OBJ) $(DEP) $(PROG)

-include $(DEP)
