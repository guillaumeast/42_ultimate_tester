#ifndef ITERATE_H
# define ITERATE_H

void	iterate_no_arg(const char *format);
void	iterate_on_string(const char *format, const char *arg);
void	iterate_on_long(const char *format, long arg);
void	iterate_on_unsigned(const char *format, unsigned int arg);
void	iterate_on_pointer(const char *format, void *arg);

#endif
