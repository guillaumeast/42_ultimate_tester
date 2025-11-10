#ifndef REDIRECT_H
# define REDIRECT_H

# include "ult_types.h"

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
