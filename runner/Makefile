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
	$(wildcard 01_main/*.c) \
	$(wildcard 02_error/*.c)	\
	$(wildcard 03_io/01_file/*.c) \
	$(wildcard 03_io/02_redirect/*.c) \
	$(wildcard 03_io/03_print/*.c) \
	$(wildcard 04_ipc/01_timeout/*.c) \
	$(wildcard 04_ipc/02_fork/*.c) \
	$(wildcard 05_status/*.c) \
	$(wildcard 06_result/*.c) \
	$(wildcard 07_engine/01_set/*.c) \
	$(wildcard 07_engine/02_capture/*.c) \
	$(wildcard 07_engine/03_compare/*.c) \
	$(wildcard 07_engine/04_assert/*.c) \
	$(wildcard 08_report/*.c)
FUT_INCLUDES	:= \
	-I. \
	-I01_main \
	-I02_error \
	-I03_io/01_file \
	-I03_io/02_redirect \
	-I03_io/03_print/includes \
	-I04_ipc/01_timeout \
	-I04_ipc/02_fork \
	-I05_status \
	-I06_result \
	-I07_engine/01_set \
	-I07_engine/02_capture \
	-I07_engine/03_compare \
	-I07_engine/04_assert \
	-I08_report

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
