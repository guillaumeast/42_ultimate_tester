#ifndef ULT_FD_PRIV_H
# define ULT_FD_PRIV_H

#include <stdbool.h>

bool	switch_file_descriptors(void);
void	reset_file_descriptor(int *original_fd, int target_fd);

#endif
