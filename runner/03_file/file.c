#define __FUT_INSIDE__
#include "file_priv.h"
#include "error_priv.h"
#include "redirect_priv.h"
#undef __FUT_INSIDE__

#include <unistd.h>

bool	create_tmp_file(void)
{
	if (!(g_output.out_file = tmpfile()))
		return (error_log(FILE_CREATION_FAILED));
	g_output.out_fd = fileno(g_output.out_file);
	return (g_output.out_fd != -1);
}

ssize_t file_get_len(FILE *f)
{
	long	pos;
	ssize_t	len;

	pos = ftell(f);
	if (pos < 0)
	{
		error_log(FILE_LEN_FAILED);
		return (-1);
	}
	if (fseek(f, 0, SEEK_END) != 0)
	{
		error_log(FILE_LEN_FAILED);
		return (-1);
	}
	if ((len = ftell(f)) < 0)
	{
		error_log(FILE_LEN_FAILED);
		return (-1);
	}
	if (fseek(f, pos, SEEK_SET) != 0)
	{
		error_log(FILE_LEN_FAILED);
		return (-1);
	}
	return (len);
}

bool	file_reset(FILE *f)
{
	int	fd;

	fd = fileno(f);
	if (fd == -1)
		return (error_log(FILE_RESET_FAILED));
	if (ftruncate(fd, 0) != 0)
		return (error_log(FILE_RESET_FAILED));
	if (fseek(f, 0, SEEK_SET) != 0)
		return (error_log(FILE_RESET_FAILED));
	clearerr(f);
	return (true);
}

void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (g_output.activ)
		fflush(g_output.out_file);
}
