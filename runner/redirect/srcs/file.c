#include "file_priv.h"
#include "redirect_priv.h"
#include <unistd.h>

bool	create_tmp_file(void)
{
	if (!(g_output.out_file = tmpfile()))
		return (false);
	g_output.out_fd = fileno(g_output.out_file);
	return (g_output.out_fd != -1);
}

ssize_t file_get_len(FILE *f)
{
	long	pos;
	ssize_t	len;

	pos = ftell(f);
	if (pos < 0)
		return (-1);
	if (fseek(f, 0, SEEK_END) != 0)
		return (-1);
	len = ftell(f);
	if (len < 0)
		return (-1);
	if (fseek(f, pos, SEEK_SET) != 0)
		return (-1);
	return (len);
}

bool	file_reset(FILE *f)
{
	int	fd;

	fd = fileno(f);
	if (fd == -1)
		return (false);
	if (ftruncate(fd, 0) != 0)
		return (false);
	if (fseek(f, 0, SEEK_SET) != 0)
		return (false);
	clearerr(f);
	return (true);
}

// Delete because all I/0 are already unbuffered ?
void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (g_output.activ)
		fflush(g_output.out_file);
}
