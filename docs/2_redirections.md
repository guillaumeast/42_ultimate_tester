# Redirections and output management

You can easily redirect `stdout` and/or `stderr` to capture the output of tested functions.

## Redirect modes

You can redirect `stdout`, `stderr` or both by using tthe following arguments with `redirect_start()` and `get_output()`:
- Use `R_STDOUT` to redirect only `stdout`
- Use `R_STDERR` to redirect only `stderr`
- Use `R_BOTH` to redirect both `stdout` and `stderr`

## MANUAL - Basic redirection

1. Start a redirection by calling `redirect_start()` with `R_STDOUT`, `R_STDERR` or `R_BOTH` as argument.
2. Read the value outputed to the redirection so far by calling `redirect_read()` (⚠️ returns a `malloc`'d pointer, don't forget to `free()` it!)
3. Stop the redirection with `redirect_stop()`

Example:
```c
#include "fut.h"
#include <stdio.h>

Test(basic_redirection, 0)
{
	char	*output;

	redirect_start(R_STDOUT);		// Redirect stdout
	printf("Hello world");			// Output is catched by the redirection
	output = redirect_read();		// output = "Hello world"
	redirect_stop();				// Restore original fds

	free(output);
}
```

## MANUAL - Stacked redirections

You can _stack_ redirections by nestedly calling `redirect_start()`.

Example:
```c
#include "fut.h"
#include <stdio.h>

Test(nested_redirections, 0)
{
	char	*output_1;
	char	*output_2;

	redirect_start(R_STDOUT);		// Start a first redirection
	printf("first redirection");	// Output is catched by the first redirection

	redirect_start(R_STDOUT);		// Start a second redirection
	printf("second redirection");	// Output is catched by the second redirection

	output_2 = redirect_read();		// output_2 = "second redirection"
	redirect_stop();				// Restore the first redirection

	output_1 = redirect_read();		// output_1 = "first redirection"
	redirect_stop();				// Restore original fds

	free(output_1);
	free(output_2);
}
```

## AUTO - One-liner redirection capture

You can easily **create** a redirection, **read** output and **stop** the redirection all at once by using `get_output()`.
The first argument let you choose which `fd` you want to redirect (see `## Redirect modes` TODO: add link).

Example:
```c
#include "fut.h"
#include <stdio.h>

Test(my_test, 0)
{
	char	*output;

	get_output(R_STDOUT, printf("Hello world"), output);
	// output == "Hello world"
	free(output);

	get_output(R_STDERR, fprintf(stderr, "Hello world"), output);
	// output == "Hello world"
	free(output);
}
```

> Warning: Only use with _safe_ expressions, since `get_output()` doesn't `fork`
> Use `capture()` [TODO: add link] if you want to _safely_ capture output

## Print on stdout / stderr while a redirection is active

You can bypass the redirections and print in the _real_ `stdout` / `stderr` by using the `print_stdout()` and `print_stderr()` functions.
Simply use them as you would use `printf()`.

Example:
```c
#include "fut.h"
#include <stdio.h>

Test(bypass_redirection, 0)
{
	redirect_start(R_STDOUT);		// Redirect stdout

	printf("Hello world\n");		// Invisible (captured by active redirection)
	print_stdout("Hello World\n");	// Visible (bypass the active redirection)

	redirect_stop();				// Restore original fds
}
```

## Public API

```c
typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH
}	t_redirect_mode;

void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#define get_output(mode, expr, out_var_name)	\
	do											\
	{											\
		redirect_start(mode);					\
		expr;									\
		out_var_name = redirect_read();			\
		redirect_stop();						\
	} while (0)

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fmt, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fmt, ...);
```
