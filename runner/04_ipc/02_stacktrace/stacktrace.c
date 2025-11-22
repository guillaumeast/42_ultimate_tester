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

#if defined(__APPLE__)
#define PATH_FALLBACK ""
#else
#define PATH_FALLBACK "/proc/self/exe"
#endif


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
	if (dladdr((void *)&get_binary_path, &info) != 0 \
		&& info.dli_fname && info.dli_fname[0] != '\0')
		snprintf(buffer, buffer_size, "%s", info.dli_fname);
	else
		snprintf(buffer, buffer_size, PATH_FALLBACK);
}

#if defined(__APPLE__)
static inline void	build_atos_cmd(void *addr, char *cmd_buff, size_t buffer_size)
{
	Dl_info	info;
	char	binary_path[PATH_MAX];

	if (!addr || dladdr(addr, &info) == 0 || !info.dli_fbase)
		return ;

	get_binary_path(binary_path, sizeof binary_path);
	snprintf(cmd_buff, buffer_size, "atos -o \"%s\" -l %#lx %#lx 2>/dev/null",
		binary_path, (unsigned long)info.dli_fbase, (unsigned long)addr
	);
}

static inline void	run_atos_cmd(const char *cmd, char *buffer, size_t buffer_size)
{
	FILE	*fp;

	fp = popen(cmd, "r");
	if (!fp)
		return;

	if (!fgets(buffer, buffer_size, fp))
	{
		pclose(fp);
		return;
	}
	pclose(fp);

	if (buffer[0] == '\0' || strstr(buffer, "0x") == buffer)
		return;
	buffer[strcspn(buffer, "\r\n")] = '\0';
}

static inline void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	char	cmd[PATH_MAX + 256];
	char	resolved[256];
	char	*opening_par;
	char	*closing_par;

	if (!addr || !buffer)
		return;

	build_atos_cmd(addr, cmd, sizeof cmd);
	run_atos_cmd(cmd, resolved, sizeof resolved);

	opening_par = strrchr(resolved, '(');
	closing_par = strrchr(resolved, ')');

	if (opening_par && closing_par && closing_par > opening_par + 1)
	{
		*closing_par = '\0';
		snprintf(buffer, buffer_size, "%s", opening_par + 1);
	}
	else
	{
		snprintf(buffer, buffer_size, "unknown location");
	}
}
#else
static inline void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	char	binary_path[PATH_MAX];
	char	cmd[PATH_MAX + 128];
	char	loc[256];
	char	func[256];
	FILE	*fp;

	get_binary_path(binary_path, sizeof binary_path);
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
