#define __FUT_INSIDE__
#define __FUT_IPC_INSIDE__
#include "handlers_ipc.h"
#include "stacktrace_ipc.h"
#undef __FUT_IPC_INSIDE__
#undef __FUT_INSIDE__

#include <dlfcn.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	stacktrace_init(void)
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
}

static void	get_binary_path(char *buffer, size_t buffer_size)
{
	Dl_info	info;

	if (!buffer || buffer_size == 0)
		return;
	buffer[0] = '\0';
	if (dladdr((void *)&stacktrace_format_addr, &info) != 0 \
		&& info.dli_fname && info.dli_fname[0] != '\0')
		snprintf(buffer, buffer_size, "%s", info.dli_fname);
	else
		snprintf(buffer, buffer_size, "/proc/self/exe");
}

/* ---------- TODO: REFACTO THIS AI SHIT 🤪 - START ---------- */

#if defined(__APPLE__)
static void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	Dl_info info;
	char binary_path[PATH_MAX];
	char cmd[PATH_MAX + 256];
	FILE *fp;
	char loc[256];

	if (!addr || dladdr(addr, &info) == 0 || !info.dli_fbase)
		return;

	get_binary_path(binary_path, sizeof binary_path);
	snprintf(cmd, sizeof cmd,
		"atos -o \"%s\" -l %#lx %#lx 2>/dev/null",
		binary_path,
		(unsigned long)info.dli_fbase,
		(unsigned long)addr
	);

	fp = popen(cmd, "r");
	if (!fp)
		return;
	if (!fgets(loc, sizeof loc, fp))
	{
		pclose(fp);
		return;
	}
	pclose(fp);

	if (loc[0] == '\0' || strstr(loc, "0x") == loc)
		return;
	loc[strcspn(loc, "\r\n")] = '\0';

	/* --- Extract only file:line from atos output --- */
	char *p1 = strrchr(loc, '(');
	char *p2 = strrchr(loc, ')');

	if (p1 && p2 && p2 > p1 + 1)
	{
		*p2 = '\0'; /* cut after ')' */
		snprintf(buffer, buffer_size, "%s", p1 + 1);
	}
	else
	{
		snprintf(buffer, buffer_size, "unknown location");
	}
}
#else
static void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	char	binary_path[PATH_MAX];
	char	cmd[PATH_MAX + 128];
	FILE	*fp;
	char	loc[256];

	get_binary_path(binary_path, sizeof binary_path);
	char	func[256];
	snprintf(cmd, sizeof cmd, "addr2line -f -e \"%s\" %p 2>/dev/null", binary_path, addr);
	fp = popen(cmd, "r");
	if (!fp)
		return;
	if (!fgets(func, sizeof func, fp))
	{
		pclose(fp);
		return;
	}
	if (!fgets(loc, sizeof loc, fp))
	{
		pclose(fp);
		return;
	}
	pclose(fp);
	func[strcspn(func, "\r\n")] = '\0';
	loc[strcspn(loc, "\r\n")] = '\0';
	snprintf(buffer, buffer_size, "%s() in %s", func, loc);
}
#endif

/* ---------- TODO: REFACTO THIS AI SHIT 🤪 - END ---------- */

void	stacktrace_format_addr(void *addr, char *buffer, size_t buffer_size)
{
	if (!buffer || buffer_size == 0)
		return;

	if (!addr)
		snprintf(buffer, buffer_size, "unknown location");
	else
	{
		snprintf(buffer, buffer_size, "%p", addr);
		buffer[0] = '\0';
		resolve_address(addr, buffer, buffer_size);
		if (buffer[0] == '\0')
			snprintf(buffer, buffer_size, "%p", addr);
	}
}
