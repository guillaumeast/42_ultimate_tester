NAME 		:= ultimate_tester_printf

LIBFT
CC			:= cc
CFLAGS		:=

SRCS		:= srcs/main.c $(wildcard srcs/runner/*.c) $(wildcard srcs/units/*.c)
INCLUDES

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -I./includes -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -I./includes -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re