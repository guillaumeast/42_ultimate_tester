#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_process.h"
#include "error_priv.h"
#include "timeout_process.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <unistd.h>

static void	timeout_handler(int sig);

static bool				active = false;
volatile sig_atomic_t	g_timeout_triggered = (sig_atomic_t)false;

void	timeout_init(size_t timeout)
{
	g_context.child_timeout = timeout;
}

void	timeout_start(void)
{
	struct sigaction	new_action = {0};

	if (g_context.child_timeout == 0)
		return ;

	g_timeout_triggered = false;

	exit_if(sigemptyset(&new_action.sa_mask) == -1, ALARM_SET_FAILED);
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = timeout_handler;
	exit_if(sigaction(SIGALRM, &new_action, NULL) == -1, ALARM_SET_FAILED);

	(void)alarm(g_context.child_timeout);
	active = true;
}

void	timeout_cancel(void)
{
	struct sigaction action = {0};

	g_timeout_triggered = false;
	if (active == false)
		return ;

	action.sa_handler = SIG_DFL;
	exit_if(sigaction(SIGALRM, &action, NULL) == -1, ALARM_CANCEL_FAILED);
	(void)alarm(0);

	active = false;
	g_context.child_timeout = -1;
}

bool	timeout_is_triggered(void)
{
	return ((bool)g_timeout_triggered);
}

static void	timeout_handler(int sig)
{
	(void)sig;
	
	if (g_handlers_target_pid != -1)
    	kill((pid_t)g_handlers_target_pid, SIGKILL);

	g_timeout_triggered = true;
	g_handlers_target_pid = -1;
}
