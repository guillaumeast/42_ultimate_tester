#ifndef ULT_TIMEOUT_PRIV_H
#define ULT_TIMEOUT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Internal header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <signal.h>
#include <stdbool.h>

bool	timeout_init(pid_t target_pid, unsigned int time);
bool	timeout_cancel(void);

extern volatile sig_atomic_t	g_timeout_triggered;

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */
