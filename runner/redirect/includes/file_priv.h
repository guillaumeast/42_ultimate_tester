#ifndef ULT_FILE_PRIV_H
# define ULT_FILE_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

#include <stdbool.h>
#include <stdio.h>

bool	create_tmp_file(void);
ssize_t	file_get_len(FILE *f);
bool	file_reset(FILE *f);
void	flush_all();

#endif
