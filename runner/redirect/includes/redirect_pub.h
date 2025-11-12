#ifndef ULT_REDIRECT_PUB_H
# define ULT_REDIRECT_PUB_H

# include <stdbool.h>
# include <stdio.h>

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

typedef enum e_ult_fds
{
	ULT_STDOUT,
	ULT_STDERR,
}	t_ult_fd;

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH,
	R_NULL,
}	t_redirect_mode;

// TODO: implement macro `char *get_output(t_ult_fd fd, function_call)` (redirect_start -> function_call() -> redirect_stop)
bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read(void);
void		redirect_stop(void);

#endif
