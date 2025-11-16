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

// TODO: implement macro `char *get_output(t_redirect_mode mode, function_call)` (redirect_start -> function_call() -> redirect_stop)
void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#endif
