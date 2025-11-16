#define __FUT_INSIDE__
#include "timeout_priv.h"
#include "error_priv.h"
#undef __FUT_INSIDE__

#include <unistd.h>

volatile sig_atomic_t			g_timeout_triggered = false;
static volatile sig_atomic_t	s_target_pid = -1;

static void	timeout_handler(int sig);

bool	timeout_init(pid_t target_pid, unsigned int time)
{
	struct sigaction	new_action = {0};

	if (time == 0)
		return (true);

	g_timeout_triggered = false;
	s_target_pid = (sig_atomic_t)target_pid;

	if (sigemptyset(&new_action.sa_mask) == -1)
		return (error_log(ALARM_SET_FAILED));
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = timeout_handler;

	if (sigaction(SIGALRM, &new_action, NULL) == -1)
		return (error_log(ALARM_SET_FAILED));

	(void)alarm(time);
	return (true);
}

bool	timeout_cancel(void)
{
	struct sigaction action = {0};

	g_timeout_triggered = false;
	if (s_target_pid == -1)
		return (true);

	action.sa_handler = SIG_DFL;
	if (sigaction(SIGALRM, &action, NULL) == -1)
		return (error_log(ALARM_CANCEL_FAILED));
	(void)alarm(0);

	s_target_pid = -1;

	return (true);
}

static void	timeout_handler(int sig)
{
	(void)sig;
	
	if (s_target_pid != -1)
    	kill((pid_t)s_target_pid, SIGKILL);

	g_timeout_triggered = true;
	s_target_pid = -1;
}
