#ifndef ULT_ERROR_PUB_H
# define ULT_ERROR_PUB_H

# include "print_pub.h"

typedef enum e_error
{
	NO_ERR,
	PIPE_ERR,
	FORK_ERR,
	ALRM_SET,
	ALRM_CANCEL,
}	t_error;

# define ult_err_priv(error_code) \
	ult_fprintf(ULT_STDERR, \
		"%s %s Internal error: " #error_code ". Please try again or report the issue. %s\n", \
		RED, EMJ_ERR, NONE)

#endif
