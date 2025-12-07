#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_pub.h"
#include "error_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <stddef.h>
#include <signal.h>

static void	sigint_handler(int sig);

t_context				g_context;
volatile sig_atomic_t	g_handlers_target_pid = -1;

void	context_init(void)
{
	g_context.has_parent = false;
	g_context.has_child = false;
	g_context.child_pid = -1;
	g_context.child_timeout = -1;
	g_context.pipe_to_parent[0] = -1;
	g_context.pipe_to_parent[1] = -1;
	g_context.pipe_to_child[0] = -1;
	g_context.pipe_to_child[1] = -1;
}

void	context_set_target_pid(pid_t target_pid)
{
	g_handlers_target_pid = (sig_atomic_t)target_pid;
}

void	context_init_sigint_handler(void)
{
	struct sigaction	new_action = {0};

	exit_if(sigemptyset(&new_action.sa_mask) == -1, SIGINT_HANDLER_SET_FAILED);
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = sigint_handler;
	exit_if(sigaction(SIGINT, &new_action, NULL) == -1, SIGINT_HANDLER_SET_FAILED);
}

void	context_cancel_sigint_handler(void)
{
	struct sigaction action = {0};
	
	action.sa_handler = SIG_DFL;
	exit_if(sigaction(SIGINT, &action, NULL) == -1, SIGINT_HANDLER_CANCEL_FAILED);
}

static void	sigint_handler(int sig)
{
	(void)sig;

	signal(SIGINT, SIG_IGN);
	if (g_handlers_target_pid != -1)
    	kill((pid_t)g_handlers_target_pid, SIGKILL);

	signal(sig, SIG_DFL);
	raise(sig);
}
