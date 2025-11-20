#define __FUT_INSIDE__
#define __FUT_IPC_INSIDE__
#include "error_priv.h"
#undef __FUT_IPC_INSIDE__
#undef __FUT_INSIDE__
#include <signal.h>
#include <stdbool.h>

volatile sig_atomic_t			g_timeout_triggered = false;
static volatile sig_atomic_t	s_target_pid = -1;

void	handlers_set_target_pid(pid_t pid)
{
	s_target_pid = (sig_atomic_t)pid;
}

void	timeout_handler(int sig)
{
	(void)sig;
	
	if (s_target_pid != -1)
    	kill((pid_t)s_target_pid, SIGKILL);

	g_timeout_triggered = true;
	s_target_pid = -1;
}

void	sigint_handler(int sig)
{
	(void)sig;

	if (s_target_pid != -1)
    	kill((pid_t)s_target_pid, SIGKILL);
	kill(0, SIGKILL);

	s_target_pid = -1;
}
