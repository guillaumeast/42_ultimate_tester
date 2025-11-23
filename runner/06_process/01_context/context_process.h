#ifndef ULT_CONTEXT_PROCESS_H
#define ULT_CONTEXT_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "context_pub.h"
#include <signal.h>

extern volatile sig_atomic_t	g_handlers_target_pid;

void	context_set_target_pid(pid_t target_pid);
void	context_init_sigint_handler(t_context *context);
void	context_cancel_sigint_handler(t_context *context);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_CONTEXT_PROCESS_H */
