#ifndef ULT_STREAM_H
# define ULT_STREAM_H

#include <stdbool.h>
#include <stdio.h>

bool	create_tmp_file(void);
ssize_t	file_get_len(FILE *f);
bool	file_reset(FILE *f);
void	flush_all();

#endif
