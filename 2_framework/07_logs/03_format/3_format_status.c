#include "status_pub.h"
#include <stdio.h>
#include <signal.h>

#define STATUS_BUFF_SIZE 64

static const char *status_names[] =
{
	"queued",
	"running",
	"passed",
	"failed",
	"timed out",
	"crashed",
	"leaked",
	"done",	
};

static inline const char	*format_sig(t_status *status)
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

const char	*format_status(t_status *status)
{
	static char	buffer[STATUS_BUFF_SIZE];

	switch (status->type)
	{
		case TIMED:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "timed out (%zus)", status->timeout);
			break;
		case CRASHED:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "crashed (%s)", format_sig(status));
			break;
		default:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "%s", status_names[status->type]);
			break;
	}
	return (buffer);
}
