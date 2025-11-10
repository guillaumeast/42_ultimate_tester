NAME			:= tester
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

SRCS			:= $(wildcard srcs/*c)
INCLUDES		:= -Iincludes

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
