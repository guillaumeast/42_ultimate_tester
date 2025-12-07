#define __FUT_INSIDE__
#include "result_pub.h"
#undef __FUT_INSIDE__

void	result_compute(t_result *res)
{
	res->total = res->passed + res->failed + res->timed + res->crashed + res->leaks;

	if (res->passed == res->total)
		res->status.type = PASSED;
	else if (res->failed > 0)
		res->status.type = FAILED;
	else if (res->timed > 0)
		res->status.type = TIMED;
	else if (res->crashed > 0)
		res->status.type = CRASHED;
	else if (res->leaks > 0)
		res->status.type = LEAKED;
}

void	result_add(const t_result *from, t_result *to)
{
	to->passed += from->passed;
	to->failed += from->failed;
	to->timed += from->timed;
	to->crashed += from->crashed;
	to->leaks += from->leaks;

	result_compute(to);
}
