#ifndef ULT_REDIRECT_PUB_H
#define ULT_REDIRECT_PUB_H

#include <stdbool.h>
#include <stddef.h>

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH
}	t_redirect_mode;

void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#define get_output(mode, expr, out_var_name)	\
	do											\
	{											\
		redirect_start(mode);					\
		expr;									\
		out_var_name = redirect_read();			\
		redirect_stop();						\
	} while (0)

#endif
