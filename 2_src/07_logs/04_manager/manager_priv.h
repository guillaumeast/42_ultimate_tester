#ifndef ULT_MANAGER_PRIV_H
#define ULT_MANAGER_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"

__attribute__((format(printf, 1, 2)))
void	logs_print_h1(const char *fmt, ...);

void	logs_print_indicator(t_status *status);

__attribute__((format(printf, 1, 2)))
void	logs_store_h2(const char *fmt, ...);
void	logs_print_h2(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_MANAGER_PRIV_H */
