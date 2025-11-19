#ifndef ULT_RESULT_PRIV_H
#define ULT_RESULT_PRIV_H

#include "status_pub.h"
#include <stddef.h>

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
void	result_add(const t_result *from, t_result *to);

#endif /* ULT_RESULT_PRIV_H */
