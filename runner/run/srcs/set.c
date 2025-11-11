#include "set.h"
#include "print.h"
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline void	run_parent(t_set *set, pid_t pid);
static inline void	run_child(t_set *set);
static inline void	handle_timeout(int sig);

extern t_result					global_result;
static t_result					current_set_result;
static pid_t					current_child_pid = -1;
static volatile sig_atomic_t	timeout_triggered = false;

void	run_set(t_set *set)
{
	print_set_title(set);
	set->status = RUNNING;
	memset(&current_set_result, 0, sizeof(current_set_result));
	current_child_pid = fork();
	if (current_child_pid < 0)
		fprintf(stderr, " %s|%s ❗️ Internal error: Fork failed%s\n", GREY, RED, NONE);
	else if (current_child_pid == 0)
		run_child(set);
	else
		run_parent(set, current_child_pid);
	set->status = DONE;
	print_set_result(&current_set_result);
}

static inline void	run_parent(t_set *set, pid_t pid)
{
	int	status;

	timeout_triggered = false;
	signal(SIGALRM, handle_timeout);
	alarm(set->timeout);

	waitpid(pid, &status, 0);
	alarm(0);

	if (timeout_triggered)
		global_result.timed++;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		global_result.passed++;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		global_result.failed++;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
		global_result.timed++;
	else if (WIFSIGNALED(status))
		global_result.crashed++;

	global_result.total++;

	signal(SIGALRM, SIG_DFL);
	current_child_pid = -1;
}

static inline void	run_child(t_set *set)
{
	set->func();
	exit(EXIT_SUCCESS);
}

static inline void	handle_timeout(int sig)
{
	(void)sig;
	timeout_triggered = true;
    kill(current_child_pid, SIGKILL);
}
