#ifndef ULT_STATUS_PUB_H
#define ULT_STATUS_PUB_H

#include <signal.h>
#include <stdio.h>

#define STATUS_BUFFER_SIZE 32

typedef enum e_status_type
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	DONE,	
}	t_status_type;

// TODO: x-macro (cf error)
static const char *status_names[] =
{
	"QUEUED",
	"RUNNING",
	"PASSED",
	"FAILED",
	"TIMED",
	"CRASHED",
	"DONE",	
};

typedef struct s_status
{
	t_status_type	type;
	int				sig;
	void			*crash_address;
	size_t			timeout;
}	t_status;

static inline const char	*status_sig(t_status *status)
{
	switch (status->sig)
	{
		case SIGINT:	return ("SIGINT");
		case SIGQUIT:	return ("SIGQUIT");
		case SIGILL:	return ("SIGILL");
		case SIGABRT:	return ("SIGABRT");
		case SIGFPE:	return ("SIGFPE");
		case SIGKILL:	return ("SIGKILL");
		case SIGSEGV:	return ("SIGSEGV");
		case SIGPIPE:	return ("SIGPIPE");
		case SIGALRM:	return ("SIGALRM");
		case SIGTERM:	return ("SIGTERM");
		case SIGBUS:	return ("SIGBUS");
		case SIGSYS:	return ("SIGSYS");
		case SIGTRAP:	return ("SIGTRAP");
		case SIGCHLD:	return ("SIGCHLD");
		case SIGSTOP:	return ("SIGSTOP");
		case SIGTSTP:	return ("SIGTSTP");
		case SIGCONT:	return ("SIGCONT");
		case SIGURG:	return ("SIGURG");
		default:		return ("UNKNOWN_SIGNAL");
	}
}

static inline void	status_format(t_status *status, char *buffer, size_t buffer_size)
{
	if (status->type == TIMED)
		(void)snprintf(buffer, buffer_size, "%s (%zus)", status_names[status->type], status->timeout);
	else if (status->type == CRASHED)
		(void)snprintf(buffer, buffer_size, "%s (%s)", status_names[status->type], status_sig(status));
	else
		(void)snprintf(buffer, buffer_size, "%s", status_names[status->type]);
}

#endif /* ULT_STATUS_PUB_H */
