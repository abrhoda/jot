# forcing CC = gcc isn't a good idea but works for now.
CC = gcc
CFLAGS += -std=c89 -Wpedantic -pedantic-errors -Werror -Wall -Wextra
CFLAGS += -Waggregate-return
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wdeclaration-after-statement
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-declarations
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wnested-externs
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -Wsequence-point
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wswitch
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wunused-but-set-parameter
CFLAGS += -Wwrite-strings

# Add debug flags
CFLAGS += -g -O0

#CC = clang
#CFLAGS += -std=c99
#CFLAGS += -Wpedantic
#CFLAGS += -Werror
#CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Wmost

NAME := jot
BIN_DIR := bin

.PHONY: all
all: $(NAME)

$(NAME): $(BIN_DIR)
	@$(CC) $(CFLAGS) $(NAME).c -o $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/*
