#include "print_priv.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

static inline void	run_parent(t_set *set, pid_t pid);
static inline void	run_child(t_set *set);
static void			handle_timeout(int sig);
static void			handle_sigint(int sig);

t_result						g_result;
t_set							*g_current_set;
static pid_t					current_child_pid = -1;
static volatile sig_atomic_t	timeout_triggered = false;

void	run_set(t_set *set)
{
	struct sigaction	old_action;
	struct sigaction	new_action;

	new_action.sa_handler = handle_sigint;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	if (sigaction(SIGINT, &new_action, &old_action) == -1)
	{
		ult_err("sigaction failed to add SIGINT handler. Please report this issue.");
		exit(EXIT_FAILURE);
	}

	g_current_set = set;
	print_set_title(set);
	set->status = RUNNING;

	current_child_pid = fork();
	if (current_child_pid < 0)
	{
		ult_err("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (current_child_pid == 0)
		run_child(set);
	else
		run_parent(set, current_child_pid);

	set->status = DONE;
}

// TODO: refactor
static inline void	run_parent(t_set *set, pid_t pid)
{
	int					status;
	struct sigaction	old_action;
	struct sigaction	new_action;

	timeout_triggered = false;
	new_action.sa_handler = handle_timeout;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	if (sigaction(SIGALRM, &new_action, &old_action) == -1)
	{
		perror("sigaction failed to add SIGALRM handler. Please report this issue.");
		exit(EXIT_FAILURE);
	}
	alarm(set->timeout);

	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		continue;
	alarm(0);

	if (timeout_triggered || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
	{
		g_current_set->result.timed++;
		g_current_set->result.total++;
		g_result.timed++;
		print_set_timed();
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		g_current_set->result.passed++;
		g_current_set->result.total++;
		g_result.passed++;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		g_current_set->result.failed++;
		g_current_set->result.total++;
		g_result.failed++;
	}
	else if (WIFSIGNALED(status))
	{
		g_current_set->result.crashed++;
		g_current_set->result.total++;
		g_result.crashed++;
		print_set_crashed();
	}

	g_result.total++;

	if (sigaction(SIGALRM, &old_action, NULL) == -1)
		perror("sigaction failed to restore SIGALARM. Please report this issue.");
	current_child_pid = -1;
}

static inline void	run_child(t_set *set)
{
	set->func();
	if (g_current_set->result.passed == g_current_set->result.total)
	{
		print_set_passed(set);
		exit(EXIT_SUCCESS);
	}
	else
	{
		print_set_failed(set);
		exit(EXIT_FAILURE);
	}
}

static void	handle_timeout(int sig)
{
	(void)sig;
	timeout_triggered = true;
    kill(current_child_pid, SIGKILL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	ult_err("Interrupted by user (Ctrl+C)");
	exit(130);
}
