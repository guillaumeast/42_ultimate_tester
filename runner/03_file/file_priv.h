#ifndef ULT_FILE_PRIV_H
#define ULT_FILE_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Internal header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>
#include <stdio.h>

bool	create_tmp_file(void);
ssize_t	file_get_len(FILE *f);
bool	file_reset(FILE *f);
void	flush_all();

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FILE_PRIV_H */
