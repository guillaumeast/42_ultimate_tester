#ifndef ULT_REDIRECT_PRIV_H
#define ULT_REDIRECT_PRIV_H

#ifndef __FUT_IO_INSIDE__
/*
**  Private header for the IO subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "redirect_pub.h"
#include <stdio.h>

typedef enum e_ult_fds
{
	ULT_STDOUT,
	ULT_STDERR,
}	t_ult_fd;

typedef struct s_redirect
{
	bool			activ;
	int				real_stdout_fd;
	int				real_stderr_fd;
	FILE			*out_file;
	int				out_fd;
}	t_redirect;

extern t_redirect	g_output;

#endif /* __FUT_INSIDE__ */

#endif /* ULT_REDIRECT_PRIV_H */
