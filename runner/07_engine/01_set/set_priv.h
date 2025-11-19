#ifndef ULT_SET_PRIV_H
#define ULT_SET_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "set_pub.h"
#include <stdbool.h>
#include <stddef.h>

extern t_result	g_result;

void	set_run(t_set *set);
void	set_add_result(t_result *result);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SET_PRIV_H */
