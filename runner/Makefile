#------ This variables will be exported by shell script ------#
PROJ_NAME		:= printf

PROJ_DIR		:= /Users/gui/repos/printf
PROJ_LIBS		:= $(PROJ_DIR)/libftprintf.a
PROJ_SRCS		:= $(wildcard $(PROJ_DIR)/*.c)
PROJ_INCLUDES	:= -I$(PROJ_DIR)/includes

TESTS_DIR		:= /Users/gui/repos/42_ultimate_tester/tests/$(PROJ_NAME)
TESTS_SRCS		:= $(wildcard $(TESTS_DIR)/*.c)
TESTS_INCLUDES	:=
#-------------------------------------------------------------#

NAME			:= ultimate_tester_$(PROJ_NAME)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3

FUT_SRCS		:= \
	$(wildcard assert/*.c) \
	$(wildcard compare/*.c)	\
	$(wildcard error/*.c) \
	$(wildcard file/*.c) \
	$(wildcard fork/*.c) \
	$(wildcard main/*.c) \
	$(wildcard print/*.c) \
	$(wildcard redirect/*.c) \
	$(wildcard set/*.c) \
	$(wildcard timeout/*.c)
FUT_INCLUDES	:= -I. -Iassert -Icompare -Ierror -Ifile -Ifork -Iprint -Iredirect -Iset -Itimeout

SRCS			:= $(FUT_SRCS) $(PROJ_SRCS) $(TESTS_SRCS)
INCLUDES		:= $(FUT_INCLUDES) $(PROJ_INCLUDES) $(TESTS_INCLUDES)
LIBS			:= $(PROJ_LIBS)

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

project:
	@make -C $(PROJ_DIR) || true

$(NAME): project $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(PROJ_LIBS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(PROJ_DIR) clean || true
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(PROJ_DIR) fclean || true
	@rm -f $(NAME)

re: fclean all

.PHONY: all project clean fclean re run
