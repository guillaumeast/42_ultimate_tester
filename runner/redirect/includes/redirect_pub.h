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

typedef struct s_redirect	t_redirect;

bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read();
void		redirect_stop(void);

#endif
