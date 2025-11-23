#ifndef ULT_STATUS_PUB_H
#define ULT_STATUS_PUB_H

#include <stddef.h>

#define STATUS_BUFFER_SIZE 32

typedef enum e_status_type
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	LEAKED,
	DONE,	
}	t_status_type;

typedef struct s_status
{
	t_status_type	type;
	int				sig;
	void			*crash_address;
	size_t			timeout;
}	t_status;

#endif /* ULT_STATUS_PUB_H */
