#------- This variables are exported by shell scripts -------#

# PROJ_NAME		:= e.g. `libft` / `printf` / `gnl`

# PROJ_SRCS		:= e.g. `/Users/me/my_project/main.c`
# PROJ_INCLUDES	:= e.g. `-I/Users/me/my_project/includes`
# PROJ_LIBS		:= e.g. `/Users/me/my_project/my_lib.a`

#------------------------ FUT inputs ------------------------#

NAME			:= ultimate_tester_$(PROJ_NAME)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3

FUT_SRCS		:= 											\
	$(wildcard 2_framework/01_main/*.c) 					\
	$(wildcard 2_framework/02_error/*.c) 					\
	$(wildcard 2_framework/03_status/*.c) 					\
	$(wildcard 2_framework/04_result/*.c) 					\
	$(wildcard 2_framework/05_io/01_file/*.c) 				\
	$(wildcard 2_framework/05_io/02_redirect/*.c) 			\
	$(wildcard 2_framework/05_io/03_print_wrapper/*.c) 		\
	$(wildcard 2_framework/06_process/01_context/*.c) 		\
	$(wildcard 2_framework/06_process/02_messages/*.c)		\
	$(wildcard 2_framework/06_process/03_stacktrace/*.c)	\
	$(wildcard 2_framework/06_process/04_timeout/*.c) 		\
	$(wildcard 2_framework/06_process/05_fork/*.c) 			\
	$(wildcard 2_framework/07_logs/01_colors/*.c) 			\
	$(wildcard 2_framework/07_logs/02_emojis/*.c) 			\
	$(wildcard 2_framework/07_logs/03_format/*.c) 			\
	$(wildcard 2_framework/07_logs/04_manager/*.c) 			\
	$(wildcard 2_framework/07_logs/05_send/*.c) 			\
	$(wildcard 2_framework/08_engine/01_set/*.c) 			\
	$(wildcard 2_framework/08_engine/02_memcheck/*.c) 		\
	$(wildcard 2_framework/08_engine/03_capture/*.c) 		\
	$(wildcard 2_framework/08_engine/04_compare/*.c) 		\
	$(wildcard 2_framework/08_engine/05_assert/*.c) 		\
	$(wildcard 2_framework/09_report/*.c)
FUT_INCLUDES	:= 											\
	-I2_framework	 										\
	-I2_framework/01_main 									\
	-I2_framework/02_error 									\
	-I2_framework/03_status 								\
	-I2_framework/04_result 								\
	-I2_framework/05_io			 							\
	-I2_framework/05_io/01_file 							\
	-I2_framework/05_io/02_redirect 						\
	-I2_framework/05_io/03_print_wrapper 					\
	-I2_framework/06_process			 					\
	-I2_framework/06_process/01_context 					\
	-I2_framework/06_process/02_messages 					\
	-I2_framework/06_process/03_stacktrace 					\
	-I2_framework/06_process/04_timeout 					\
	-I2_framework/06_process/05_fork 						\
	-I2_framework/07_logs			 						\
	-I2_framework/07_logs/01_colors 						\
	-I2_framework/07_logs/02_emojis 						\
	-I2_framework/07_logs/03_format 						\
	-I2_framework/07_logs/04_manager 						\
	-I2_framework/07_logs/05_send	 						\
	-I2_framework/08_engine		 							\
	-I2_framework/08_engine/01_set 							\
	-I2_framework/08_engine/02_memcheck 					\
	-I2_framework/08_engine/03_capture 						\
	-I2_framework/08_engine/04_compare 						\
	-I2_framework/08_engine/05_assert 						\
	-I2_framework/09_report
ifeq ($(shell uname -s),Linux)
    FUT_LIBS := -ldl
else
    FUT_LIBS :=
endif

#----------------- Project specific inputs ------------------#

TESTS_DIR		:= 3_tests/$(PROJ_NAME)
TESTS_SRCS		:= $(wildcard $(TESTS_DIR)/mandatory/*.c) $(wildcard $(TESTS_DIR)/bonus/*.c)

#---------------------- Merged inputs -----------------------#

SRCS			:= $(FUT_SRCS) $(PROJ_SRCS) $(TESTS_SRCS)
INCLUDES		:= $(FUT_INCLUDES) $(PROJ_INCLUDES)
LIBS			:= $(FUT_LIBS) $(PROJ_LIBS)

#----------------------- Object rules -----------------------#

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

#------------------------ Make rules ------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run:
	@$(MAKE) -s all > /dev/null 2>&1 || { \
		printf '❗️ Internal error: unable to compile\n' >&2; \
		exit 1; \
	}
	@./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all project clean fclean re run
