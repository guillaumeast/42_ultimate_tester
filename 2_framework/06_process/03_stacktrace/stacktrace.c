#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "messages_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__


#include <signal.h>
#include <stddef.h>
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

static volatile sig_atomic_t	s_fd_to_parent = -1;

static void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext);

void	stacktrace_init(int fd_to_parent)
{
	struct sigaction	action = {0};

	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = stacktrace_handler;
	sigemptyset(&action.sa_mask);

	sigaction(SIGSEGV, &action, NULL);
	sigaction(SIGBUS, &action, NULL);
	sigaction(SIGFPE,  &action, NULL);
	sigaction(SIGILL, &action, NULL);
	sigaction(SIGABRT, &action, NULL);

	s_fd_to_parent = (sig_atomic_t)fd_to_parent;
}

static void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext)
{
	ucontext_t		*proc_context;
	void			*program_counter;
	t_message_type	type;
	size_t			len;

	(void)sig;
	(void)info;

	proc_context = (ucontext_t *)ucontext;
	program_counter = GET_PROGRAM_COUNTER(proc_context);

	if (s_fd_to_parent != -1)
	{
		type = CRASH;
		len = sizeof program_counter;
		(void)write(s_fd_to_parent, &type, sizeof type);
		(void)write(s_fd_to_parent, &len, sizeof len);
		(void)write(s_fd_to_parent, &program_counter, len);
	}

	signal(sig, SIG_DFL);
	raise(sig);
}
