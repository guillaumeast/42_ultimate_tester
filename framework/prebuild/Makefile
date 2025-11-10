NAME		:= prebuilder
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

SRCS		:= $(wildcard srcs/*c)
INCLUDES	:= -Iincludes

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

TESTS_DIR 	:= ../../printf
OUT_DIR		:= outputs
TEMPLATE	:= templates/try.c

all: $(NAME)
	@rm -rf $(OUT_DIR)
	@mkdir -p $(OUT_DIR)
	@for file in $(TESTS_DIR)/*.c; do \
		out="$(OUT_DIR)/$$(basename $$file)"; \
		cp $$file $$out; \
		./$(NAME) "Try(...)" "$(TEMPLATE)" "$$file" "$$out"; \
	done

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(OUT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
