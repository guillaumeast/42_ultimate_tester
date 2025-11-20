#ifndef ULT_HANDLERS_IPC_H
#define ULT_HANDLERS_IPC_H

#ifndef __FUT_IPC_INSIDE__
/*
**  Private header for the ipc subsystem.
**  Not available outside its compilation unit.
*/
#else

#include <signal.h>

extern volatile sig_atomic_t	g_timeout_triggered;

void	handlers_set_target_pid(pid_t target_pid);
void	handlers_set_fd_to_parent(int fd_to_parent);
void	timeout_handler(int sig);
void	sigint_handler(int sig);
void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */
