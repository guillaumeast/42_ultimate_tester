#define __FUT_INSIDE__
#define __FUT_IPC_INSIDE__
#include "timeout_ipc.h"
#include "error_priv.h"
#undef __FUT_IPC_INSIDE__
#undef __FUT_INSIDE__

#include <unistd.h>

static bool	active = false;

void	timeout_init(unsigned int time)
{
	struct sigaction	new_action = {0};

	if (time == 0)
		return ;

	g_timeout_triggered = false;

	exit_if(sigemptyset(&new_action.sa_mask) == -1, ALARM_SET_FAILED);
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = timeout_handler;
	exit_if(sigaction(SIGALRM, &new_action, NULL) == -1, ALARM_SET_FAILED);

	(void)alarm(time);
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
}
