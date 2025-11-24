#------ This variables will be exported by shell script ------#
PROJ_NAME		:= printf

PROJ_DIR		:= /Users/gui/repos/printf
PROJ_LIBS		:= $(PROJ_DIR)/libftprintf.a
PROJ_SRCS		:= $(wildcard $(PROJ_DIR)/*.c)
PROJ_INCLUDES	:= -I$(PROJ_DIR)/includes

TESTS_DIR		:= /Users/gui/repos/42_ultimate_tester/tests/$(PROJ_NAME)
TESTS_SRCS		:= $(wildcard $(TESTS_DIR)/*.c) $(wildcard $(TESTS_DIR)/mandatory/*.c) $(wildcard $(TESTS_DIR)/bonus/*.c)
TESTS_INCLUDES	:=
#-------------------------------------------------------------#

NAME			:= ultimate_tester_$(PROJ_NAME)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3

FUT_SRCS		:= 								\
	$(wildcard 01_main/*.c) 					\
	$(wildcard 02_error/*.c) 					\
	$(wildcard 03_status/*.c) 					\
	$(wildcard 04_result/*.c) 					\
	$(wildcard 05_io/01_file/*.c) 				\
	$(wildcard 05_io/02_redirect/*.c) 			\
	$(wildcard 05_io/03_print_wrapper/*.c) 		\
	$(wildcard 06_process/01_context/*.c) 		\
	$(wildcard 06_process/02_messages/*.c)		\
	$(wildcard 06_process/03_stacktrace/*.c)	\
	$(wildcard 06_process/04_timeout/*.c) 		\
	$(wildcard 06_process/05_fork/*.c) 			\
	$(wildcard 07_logs/01_colors/*.c) 			\
	$(wildcard 07_logs/02_emojis/*.c) 			\
	$(wildcard 07_logs/03_format/*.c) 			\
	$(wildcard 07_logs/04_manager/*.c) 			\
	$(wildcard 07_logs/05_send/*.c) 			\
	$(wildcard 08_engine/01_set/*.c) 			\
	$(wildcard 08_engine/02_memcheck/*.c) 		\
	$(wildcard 08_engine/03_capture/*.c) 		\
	$(wildcard 08_engine/04_compare/*.c) 		\
	$(wildcard 08_engine/05_assert/*.c) 		\
	$(wildcard 09_report/*.c)
FUT_INCLUDES	:= 								\
	-I. 										\
	-I01_main 									\
	-I02_error 									\
	-I03_status 								\
	-I04_result 								\
	-I05_io			 							\
	-I05_io/01_file 							\
	-I05_io/02_redirect 						\
	-I05_io/03_print_wrapper 					\
	-I06_process			 					\
	-I06_process/01_context 					\
	-I06_process/02_messages 					\
	-I06_process/03_stacktrace 					\
	-I06_process/04_timeout 					\
	-I06_process/05_fork 						\
	-I07_logs			 						\
	-I07_logs/01_colors 						\
	-I07_logs/02_emojis 						\
	-I07_logs/03_format 						\
	-I07_logs/04_manager 						\
	-I07_logs/05_send	 						\
	-I08_engine		 							\
	-I08_engine/01_set 							\
	-I08_engine/02_memcheck 					\
	-I08_engine/03_capture 						\
	-I08_engine/04_compare 						\
	-I08_engine/05_assert 						\
	-I09_report

SRCS			:= $(FUT_SRCS) $(PROJ_SRCS) $(TESTS_SRCS)
INCLUDES		:= $(FUT_INCLUDES) $(PROJ_INCLUDES) $(TESTS_INCLUDES)
ifeq ($(shell uname -s),Linux)
    LIBS := $(PROJ_LIBS) -ldl
else
    LIBS := $(PROJ_LIBS)
endif

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

project:
	@make -C $(PROJ_DIR) || true

$(NAME): project $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

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
