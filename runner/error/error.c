#include "error_pub.h"

void	ult_print_err_priv(t_error err)
{
	ult_fprintf(ULT_STDERR, "%s %s Internal error: %s. Please try again or report the issue. %s\n",
		RED, EMJ_ERR,
		(err > 0 && err <= REDIRECT_START_FAILED ? names[err] : "UNKNOWN"),
		NONE);
}
