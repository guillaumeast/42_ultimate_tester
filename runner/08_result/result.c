#define __FUT_INSIDE__
#include "result_priv.h"
#undef __FUT_INSIDE__

void	result_compute(t_result *res)
{
	res->total = res->passed + res->failed + res->timed + res->crashed;

	if (res->passed == res->total)
		res->status = PASSED;
	else if (res->failed > 0)
		res->status = FAILED;
	else if (res->timed > 0)
		res->status = TIMED;
	else if (res->crashed > 0)
		res->status = CRASHED;
}
