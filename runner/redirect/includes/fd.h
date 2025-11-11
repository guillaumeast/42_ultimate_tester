#ifndef ULT_FD_H
# define ULT_FD_H

#include <stdbool.h>

bool	save_original_file_descriptors(void);
bool	switch_file_descriptors(void);
void	reset_file_descriptor(int *original_fd, int target_fd);

#endif
