#ifndef ULTIMATE_PREBUILD_ARGS_H
# define ULTIMATE_PREBUILD_ARGS_H

# include "pb_types.h"

bool	parse_target(t_target *target, char *raw);
bool	parse_args(t_target *target, const char *str, t_string *output);

#endif
