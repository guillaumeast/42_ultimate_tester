#ifndef ULT_REDIRECT_H
# define ULT_REDIRECT_H

# include <stdbool.h>
# include <stdio.h>

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH,
	R_NULL,
}	t_redirect_mode;

typedef struct s_redirect
{
	bool			activ;
	t_redirect_mode mode;
	int				real_stdout_fd;
	int				real_stderr_fd;
	FILE			*out_file;
	int				out_fd;
	FILE			*logs_file;	// TODO
	int				logs_fd;	// TODO
}	t_redirect;

extern t_redirect current_redirect;

bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read();
bool		redirect_reset(const char *error_message);

# define redirect_stop()	redirect_reset(NULL);

#endif
