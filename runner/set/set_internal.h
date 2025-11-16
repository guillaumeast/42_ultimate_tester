#ifndef ULT_SET_INTERNAL_H
#define ULT_SET_INTERNAL_H

#ifndef __FUT_SET_INSIDE__
/*
**  Internal header for the set module.
**  Not available outside its compilation unit.
*/
#else

#include "set_priv.h"

void	print_set_title(const t_set *set);
void	print_set_result(const t_set *set);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SET_INTERNAL_H */
