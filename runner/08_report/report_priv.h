#ifndef ULT_GLOBAL_PRIV_H
#define ULT_GLOBAL_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "result_pub.h"

void	print_start(void);
void	print_result(const t_result *result);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_GLOBAL_PRIV_H */
