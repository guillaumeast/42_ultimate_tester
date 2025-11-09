#ifndef REDIRECT_H
# define REDIRECT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_redirect {
	int		original_fd_copy;
	FILE	*tmp_file;
	int		tmp_fd;
}	t_redirect;

void	redirect_start(t_redirect *r);
size_t redirect_read(t_redirect *r, char **out);
void	redirect_clear(t_redirect *r);
void	redirect_stop(t_redirect *r);

#endif
