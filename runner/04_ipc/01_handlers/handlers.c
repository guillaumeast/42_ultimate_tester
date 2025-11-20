#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(__APPLE__)
#include <sys/ucontext.h>
#else
#include <ucontext.h>
#endif

#if defined(__APPLE__) && defined(__x86_64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext->__ss.__rip)
#elif defined(__APPLE__) && defined(__aarch64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext->__ss.__pc)
#elif defined(__linux__) && defined(__x86_64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.gregs[REG_RIP])
#elif defined(__linux__) && defined(__i386__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.gregs[REG_EIP])
#elif defined(__linux__) && defined(__riscv)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.sc_pc)
#elif defined(__linux__) && defined(__aarch64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.pc)
#elif defined(__linux__) && defined(__powerpc64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.regs->nip)
#elif defined(__linux__) && defined(__powerpc__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.regs->nip)
#elif defined(__linux__) && defined(__s390x__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.psw.addr)
#elif defined(__linux__) && (defined(__arm__) || defined(__ARM_ARCH))
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.arm_pc)
#else
	#define GET_PROGRAM_COUNTER(ctx) ((void *)0)
#endif

volatile sig_atomic_t			g_timeout_triggered = false;
static volatile sig_atomic_t	s_target_pid = -1;
static volatile sig_atomic_t	s_fd_to_parent = -1;

void	handlers_set_target_pid(pid_t target_pid)
{
	s_target_pid = (sig_atomic_t)target_pid;
}

void	handlers_set_fd_to_parent(int fd_to_parent)
{
	s_fd_to_parent = (sig_atomic_t)fd_to_parent;
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

	signal(SIGINT, SIG_IGN);
	if (s_target_pid != -1)
    	kill((pid_t)s_target_pid, SIGKILL);

	signal(sig, SIG_DFL);
	raise(sig);
}

void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext)
{
	ucontext_t	*proc_context;
	void		*program_counter;

	(void)sig;
	(void)info;

	proc_context = (ucontext_t *)ucontext;
	program_counter = GET_PROGRAM_COUNTER(proc_context);

	if (s_fd_to_parent != -1)
		write((int)s_fd_to_parent, &program_counter, sizeof program_counter);

	signal(sig, SIG_DFL);
	raise(sig);
}
