CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3

# Lib minimale de test
LIB_NAME	:= libtest.so
LIB_CFLAGS	:= -Wall -Wextra -Werror -fPIC -g3
LIB_SRC		:= lib.c

# Framework réel
FUT_DIR		:= /Users/gui/repos/42_ultimate_tester
FUT_INC		:= -I$(FUT_DIR)/3_include
FUT_LIB		:= -L$(FUT_DIR) -lfut

all: test_lib test_fut

# Test avec lib minimale
test_lib: $(LIB_NAME) test_lib.c
	@$(CC) $(CFLAGS) test_lib.c -L. -ltest -o test_lib
	@echo "=== RUN test_lib ==="
	@DYLD_LIBRARY_PATH=. ./test_lib

# Test avec framework réel
test_fut: test_fut.c
	@make -C $(FUT_DIR) re > /dev/null
	@$(CC) $(CFLAGS) $(FUT_INC) test_fut.c $(FUT_LIB) -o test_fut
	@echo "=== RUN test_fut ==="
	@DYLD_LIBRARY_PATH=$(FUT_DIR) ./test_fut

clean:
	rm -f $(LIB_NAME) test_lib test_fut

.PHONY: all clean test_lib test_fut symbols linkage debug
