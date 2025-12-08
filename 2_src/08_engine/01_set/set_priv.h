#ifndef ULT_SET_PRIV_H
#define ULT_SET_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "set_pub.h"

extern t_result	g_result;

void	set_init(t_set *first_set, t_set *last_set);
void	set_run(t_set *set);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SET_PRIV_H */
