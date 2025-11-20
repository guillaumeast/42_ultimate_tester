#ifndef ULT_STACKTRACE_PRIV_H
#define ULT_STACKTRACE_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#define STACKTRACE_BUFFER_SIZE 64

void	stacktrace_format_addr(void *addr, char *buffer, size_t buffer_size);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_STACKTRACE_PRIV_H */
