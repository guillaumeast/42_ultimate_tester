#ifndef ULT_MESSAGES_PRIV_H
#define ULT_MESSAGES_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "context_process.h"
#include "logs_priv.h"
#include "result_pub.h"

#include <stdbool.h>
#include <stddef.h>

typedef enum e_message_type
{
	RESULT,
	CRASH,
	LOG
}	t_message_type;

typedef union u_message_data
{
	t_result		result;
	void			*crash_addr;
	char			log[H2_CAP];
}	t_message_data;

typedef struct s_message
{
	t_message_type	type;
	t_message_data	data;
}	t_message;

void	message_send(int pipe[2], t_message_type type, t_message_data *data);
bool	message_receive(int pipe[2], t_message *buff);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_MESSAGES_PRIV_H */
