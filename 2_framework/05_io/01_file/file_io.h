#ifndef ULT_FILE_IO_H
#define ULT_FILE_IO_H

#ifndef __FUT_IO_INSIDE__
/*
**  Private header for the io subsystem.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>
#include <stdio.h>

void	create_tmp_file(void);
size_t	file_get_len(FILE *file);
void	file_nread(char *buffer, FILE *file, size_t n);
void	file_reset(FILE *file);
void	flush_all();

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FILE_IO_H */
