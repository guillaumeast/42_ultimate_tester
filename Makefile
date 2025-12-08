NAME		:= libfut.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -fPIC -g3

SRCS		:= 										\
	$(wildcard 2_src/01_main/*.c) 					\
	$(wildcard 2_src/02_error/*.c) 					\
	$(wildcard 2_src/03_status/*.c) 				\
	$(wildcard 2_src/04_result/*.c) 				\
	$(wildcard 2_src/05_io/01_file/*.c) 			\
	$(wildcard 2_src/05_io/02_redirect/*.c) 		\
	$(wildcard 2_src/05_io/03_print_wrapper/*.c) 	\
	$(wildcard 2_src/06_process/01_context/*.c) 	\
	$(wildcard 2_src/06_process/02_messages/*.c)	\
	$(wildcard 2_src/06_process/03_stacktrace/*.c)	\
	$(wildcard 2_src/06_process/04_timeout/*.c) 	\
	$(wildcard 2_src/06_process/05_fork/*.c) 		\
	$(wildcard 2_src/07_logs/01_colors/*.c) 		\
	$(wildcard 2_src/07_logs/02_emojis/*.c) 		\
	$(wildcard 2_src/07_logs/03_format/*.c) 		\
	$(wildcard 2_src/07_logs/04_manager/*.c) 		\
	$(wildcard 2_src/07_logs/05_send/*.c) 			\
	$(wildcard 2_src/08_engine/01_set/*.c) 			\
	$(wildcard 2_src/08_engine/02_memcheck/*.c) 	\
	$(wildcard 2_src/08_engine/03_capture/*.c) 		\
	$(wildcard 2_src/08_engine/04_compare/*.c) 		\
	$(wildcard 2_src/08_engine/05_assert/*.c) 		\
	$(wildcard 2_src/09_report/*.c)

INCLUDES	:= 										\
	-I2_src	 										\
	-I2_src/01_main 								\
	-I2_src/02_error 								\
	-I2_src/03_status 								\
	-I2_src/04_result 								\
	-I2_src/05_io			 						\
	-I2_src/05_io/01_file 							\
	-I2_src/05_io/02_redirect 						\
	-I2_src/05_io/03_print_wrapper 					\
	-I2_src/06_process			 					\
	-I2_src/06_process/01_context 					\
	-I2_src/06_process/02_messages 					\
	-I2_src/06_process/03_stacktrace 				\
	-I2_src/06_process/04_timeout 					\
	-I2_src/06_process/05_fork 						\
	-I2_src/07_logs			 						\
	-I2_src/07_logs/01_colors 						\
	-I2_src/07_logs/02_emojis 						\
	-I2_src/07_logs/03_format 						\
	-I2_src/07_logs/04_manager 						\
	-I2_src/07_logs/05_send	 						\
	-I2_src/08_engine		 						\
	-I2_src/08_engine/01_set 						\
	-I2_src/08_engine/02_memcheck 					\
	-I2_src/08_engine/03_capture 					\
	-I2_src/08_engine/04_compare 					\
	-I2_src/08_engine/05_assert 					\
	-I2_src/09_report

LIBS		:=
ifeq ($(shell uname -s),Linux)
    LIBS	+= -ldl
endif

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# TODO: add test rule

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)*

re: fclean all

.PHONY: all clean fclean re
