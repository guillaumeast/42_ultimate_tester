#ifndef ULT_REDIRECT_PRIV_H
# define ULT_REDIRECT_PRIV_H

# include "redirect_pub.h"

typedef struct s_redirect
{
	bool			activ;
	t_redirect_mode mode;
	int				real_stdout_fd;
	int				real_stderr_fd;
	FILE			*out_file;
	int				out_fd;
}	t_redirect;

extern t_redirect	g_output;

bool	init_redirection(void);

#endif
