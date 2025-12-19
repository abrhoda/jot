debug ?= 0
sanitize ?= 0
NAME := jot
INCLUDE_DIR := include
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
BIN_DIR := bin

# For containing make's dependency (.d) files. Read more here: https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
DEPS_DIR := deps

# Set Clang Options
#CC = clang
#CFLAGS += -std=c99
#CFLAGS += -Wpedantic
#CFLAGS += -Werror
#CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Wmost

# Set c standard
CFLAGS += -std=c89

# Set headers dir
CFLAGS += -I./$(INCLUDE_DIR)

# Poor man's static analyzer
CFLAGS += -Wpedantic -pedantic-errors -Werror -Wall -Wextra
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

# Sanitizers
ifneq ($(sanatize), 0)
	CFLAGS += -fsanitize=address,leak,undefined
endif

# Optimization settings
ifeq ($(debug), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3 -DNDEBUG
endif

# Linker opts. Remember to set LDFLAGS before objs and LDLIBS after objs to avoid undefined refs when linking.
#LDFLAGS += -L/$(LIBS)/libspecific
#LDLIBS += -lm, -lpthread

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS := $(SRC:$(SRC_DIR)/%.c=$(DEPS_DIR)/%.d)

.PHONY: all
all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEPS_DIR)/$*.d -c $< -o $@

$(NAME): $(OBJS) | setup
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

.PHONY: test
test:
	@echo "There are no tests yet. RIP."

.PHONY: check
check:
	@echo "I should use valgrind with a normal human but instead I'm using sanitizer options right now. I'll probably regret that decision later."

.PHONY: setup
setup:
	mkdir -p $(BUILD_DIR) $(BIN_DIR) $(DEPS_DIR)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/* $(DEPS_DIR)/*.d

# includes our generated .d deps files with the `include` directive. `-` at the beginning makes it not an error if the file doesn't exist (such as it hasn't be generated yet).
-include $(DEPS)
