#ifndef ULT_ERROR_PRIV_H
#define ULT_ERROR_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Internal header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>

typedef enum e_error
{
#define X_ERROR(name) name,
#include "error.x"
# undef X_ERROR
}	t_error;

bool	error_log(t_error error);
void	error_reset_trace(void);
void	error_print_trace(void);
void	exit_if(bool condition);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_ERROR_PRIV_H */
