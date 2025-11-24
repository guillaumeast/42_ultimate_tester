#ifndef ULT_SET_INTERNAL_H
#define ULT_SET_INTERNAL_H

#ifndef __FUT_SET_INSIDE__
/*
**  Internal header for the SET module.
**  Not available outside its compilation unit.
*/
#else

#include "process_priv.h"
#include "set_priv.h"

void	set_run_parent(t_set *set);
void	set_run_child(t_set *set);

#endif /* __FUT_SET_INSIDE__ */

#endif /* ULT_SET_INTERNAL_H */
