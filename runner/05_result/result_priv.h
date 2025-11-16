#ifndef ULT_RESULT_PRIV_H
#define ULT_RESULT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stddef.h>

typedef enum e_status
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	DONE,
}	t_status;

typedef struct s_result
{
	t_status	status;
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

void	result_compute(t_result *res);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_RESULT_PRIV_H */
