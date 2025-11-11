#include "file.h"
#include "redirect.h"
#include <unistd.h>

extern t_redirect	current_redirect;

bool	create_tmp_file(void)
{
	if (!(current_redirect.out_file = tmpfile()))
		return (false);
	current_redirect.out_fd = fileno(current_redirect.out_file);
	if (current_redirect.out_fd == -1)
		return (false);
	return (true);
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

void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (current_redirect.activ)
		fflush(current_redirect.out_file);
	// TODO: flush logs_out and logs_err too
}
