# include "timeout_priv.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

volatile sig_atomic_t			g_timeout_triggered = false;
static volatile sig_atomic_t	s_target_pid = -1;

static void	timeout_handler(int sig);

t_error	timeout_init(pid_t target_pid, unsigned int time)
{
	struct sigaction	new_action = {0};

	if (time == 0)
		return (NO_ERR);

	g_timeout_triggered = false;
	s_target_pid = (sig_atomic_t)target_pid;

	if (sigemptyset(&new_action.sa_mask) == -1)
		return (ALRM_SET);
	new_action.sa_flags = 0;
	new_action.sa_handler = timeout_handler;

	if (sigaction(SIGALRM, &new_action, NULL) == -1)
		return (ALRM_SET);

	(void)alarm(time);
	return (NO_ERR);
}

t_error	timeout_cancel(void)
{
	struct sigaction action = {0};

	if (s_target_pid == -1)
		return (NO_ERR);

	action.sa_handler = SIG_DFL;
	if (sigaction(SIGALRM, &action, NULL) == -1)
		return (ALRM_CANCEL);
	(void)alarm(0);

	g_timeout_triggered = false;
	s_target_pid = -1;

	return (NO_ERR);
}

static void	timeout_handler(int sig)
{
	(void)sig;
	
	if (s_target_pid != -1)
    	kill((pid_t)s_target_pid, SIGKILL);

	g_timeout_triggered = true;
	s_target_pid = -1;
}
