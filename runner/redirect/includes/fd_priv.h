#ifndef ULT_FD_PRIV_H
# define ULT_FD_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

#include <stdbool.h>

bool	switch_file_descriptors(void);
void	reset_file_descriptor(int *original_fd, int target_fd);

#endif
