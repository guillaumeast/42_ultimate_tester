#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#include "file_io.h"
#include "error_priv.h"
#include "redirect_io.h"
#undef __FUT_IO_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

void	create_tmp_file(void)
{
	exit_if(!(g_output.out_file = tmpfile()), FILE_CREATION_FAILED);
	g_output.out_fd = fileno(g_output.out_file);
}

size_t file_get_len(FILE *file)
{
	long	position;
	ssize_t	len;

	position = ftell(file);
	exit_if(position < 0, FILE_LEN_FAILED);
	exit_if(fseek(file, 0, SEEK_END) != 0, FILE_LEN_FAILED);
	len = ftell(file);
	exit_if(len < 0, FILE_LEN_FAILED);
	exit_if(fseek(file, position, SEEK_SET) != 0, FILE_LEN_FAILED);
	return ((size_t)len);
}

void	file_nread(char *buffer, FILE *file, size_t n)
{
	size_t	res_len;
	size_t	nread;

	res_len = 0;
	while (res_len < n)
	{
		nread = fread(buffer + res_len, 1, n - res_len, file);
		if (ferror(file))
		{
			free(buffer);
			exit_if(true, REDIRECT_READ_FAILED);
		}
		if (nread == 0)
			break;
		res_len += (ssize_t)nread;
	}
	buffer[res_len] = '\0';
}

void	file_reset(FILE *file)
{
	int	fd;

	fd = fileno(file);
	exit_if(fd == -1, FILE_RESET_FAILED);
	exit_if(ftruncate(fd, 0) != 0, FILE_RESET_FAILED);
	exit_if(fseek(file, 0, SEEK_SET) != 0, FILE_RESET_FAILED);
	clearerr(file);
}

void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (g_output.activ)
		fflush(g_output.out_file);
}
