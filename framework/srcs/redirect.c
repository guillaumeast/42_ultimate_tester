# include "redirect.h"

void	redirect_start(t_redirect *r)
{
	r->original_fd_copy = dup(STDOUT_FILENO);
	r->tmp_file = tmpfile();
	r->tmp_fd = fileno(r->tmp_file);
	dup2(r->tmp_fd, STDOUT_FILENO);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(r->tmp_file, NULL, _IONBF, 0);
}

size_t redirect_read(t_redirect *r, char **out)
{
	size_t	total = 0;
	size_t	cap = BUFFER_SIZE;
	char	*res = malloc(cap);
	size_t	n;

	if (!res)
		return (*out = NULL, 0);
	fseek(r->tmp_file, 0, SEEK_SET);
    while ((n = fread(res + total, 1, cap - total - 1, r->tmp_file)) > 0)
    {
        total += n;
        if (cap - total <= 1)
        {
            cap *= 2;
            char *tmp = realloc(res, cap);
            if (!tmp)
                return (free(res), *out = NULL, 0);
            res = tmp;
        }
    }
	res[total] = '\0';
	ftruncate(r->tmp_fd, 0);
	fseek(r->tmp_file, 0, SEEK_SET);
    return (*out = res, total);
}

void	redirect_stop(t_redirect *r)
{
	dup2(r->original_fd_copy, STDOUT_FILENO);
	close(r->original_fd_copy);
	fclose(r->tmp_file);
}
