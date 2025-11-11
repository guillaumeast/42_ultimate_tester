#ifndef ULT_REDIRECT_H
# define ULT_REDIRECT_H

# include "utils.h"

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH,
	R_NULL,
}	t_redirect_mode;

bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read();
void		redirect_stop();

#endif
