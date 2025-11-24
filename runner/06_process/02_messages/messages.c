#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <string.h>
#include <unistd.h>

static inline bool	read_complete(int fd, void *buff, size_t message_size);

void	message_send(int pipe[2], t_message_type type, t_message_data *data)
{
	size_t	len;

	len = 0;
	switch (type)
	{
		case RETURN_VALUE:	len = sizeof(intptr_t); break;
		case RESULT:		len = sizeof(t_result); break;
		case CRASH:			len = sizeof(void *); break;
		case LOG:			len = strlen((char *)data); break;
		default:			exit_if(true, MESSAGE_UNKNOWN_TYPE);
	}
	exit_if(len >= sizeof(t_message_data), MESSAGE_TOO_LONG);

	(void)write(pipe[1], &type, sizeof type);
	(void)write(pipe[1], &len, sizeof len);
	(void)write(pipe[1], data, len);
}

bool	message_receive(int pipe[2], t_message *buff)
{
	size_t	len;

	if (!read_complete(pipe[0], &buff->type, sizeof buff->type))
		return (false);
	if (!read_complete(pipe[0], &len, sizeof len))
		return (false);
	switch (buff->type)
	{
		case RETURN_VALUE:
			exit_if(len != sizeof(size_t), MESSAGE_INVALID_LEN);
			break;
		case RESULT:
			exit_if(len != sizeof(t_result), MESSAGE_INVALID_LEN);
			break;
		case CRASH:
			exit_if(len != sizeof(void *), MESSAGE_INVALID_LEN);
			break;
		case LOG:
			exit_if(len >= sizeof(t_message_data), MESSAGE_INVALID_LEN);
			break;
		default:
			exit_if(true, MESSAGE_UNKNOWN_TYPE);
	}
	if (!read_complete(pipe[0], &buff->data, len))
		return (false);
	if (buff->type == LOG)
		buff->data.log[len] = '\0';
	return (true);
}

bool	message_read_type(int pipe[2], t_message_type *buff)
{
	return (read_complete(pipe[0], buff, sizeof buff));
}

bool	message_read_len(int pipe[2], size_t *buff)
{
	return (read_complete(pipe[0], buff, sizeof buff));
}

bool	message_read_data(int pipe[2], void *buff, size_t len)
{
	return (read_complete(pipe[0], buff, len));
}

static inline bool	read_complete(int fd, void *buff, size_t message_size)
{
	ssize_t	bytes;
	size_t	total;

	total = 0;
	while (total < message_size)
	{
		bytes = read(fd, (char *)buff + total, message_size - total);
		if (bytes == 0 && total == 0)
			return (false);
		else if (bytes == 0)
			exit_if(true, PIPE_CLOSED_EARLY);
		else if (bytes < 0 && errno == EINTR)
			continue;
		exit_if(bytes < 0, PIPE_READ_FAILED);
		total += (size_t)bytes;
	}
	return (true);
}
