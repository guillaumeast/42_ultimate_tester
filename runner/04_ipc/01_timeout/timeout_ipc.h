#ifndef ULT_TIMEOUT_IPC_H
#define ULT_TIMEOUT_IPC_H

#ifndef __FUT_IPC_INSIDE__
/*
**  Private header for the ipc subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "timeout_priv.h"
#include <signal.h>
#include <stdbool.h>

void	timeout_init(pid_t target_pid, unsigned int time);
void	timeout_cancel(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */
