#ifndef ULT_SEND_PRIV_H
#define ULT_SEND_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "process_priv.h"

#include <inttypes.h>
#include <stdio.h>

void	send_incorrect_status(int pipe[2], const char *expr, t_status *got, t_status *exp);
void	send_incorrect_return(int pipe[2], const char *expr, t_format fmt, intptr_t got, intptr_t *exp);
void	send_incorrect_output(int pipe[2], const char *expr, const char *got, const char *exp);
void	send_leak(int pipe[2], const char *expr, size_t size, void *caller);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SEND_PRIV_H */
