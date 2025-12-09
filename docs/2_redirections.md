# Redirections

**Redirections** allow you to temporarily reroute `stdout` and/or `stderr` so you can capture the output of any expression or function.

> 💡 Each redirection captures exactly what the underlying function writes to `stdout` and/or `stderr`.  
> There is **no** trimming or newline added automatically.

## Table of contents

- [Redirect Modes](#redirect-modes)
- [Start Redirection: `redirect_start()`](#start-redirection-redirect_start)
- [Read Redirection: `redirect_read()`](#read-redirection-redirect_read)
- [Stop Redirection: `redirect_stop()`](#stop-redirection-redirect_stop)
- [One-liner: `get_output()`](#one-liner-get_output)
- [Simple Usage Example](#simple-usage-example)
- [Nested Usage Example](#nested-usage-example)
- [Bypass redirections: `print_stdout()` and `print_stderr()`](#bypass-redirections-print_stdout-and-print_stderr)

## Redirect Modes

With the `mode` argument, you can redirect `stdout`, `stderr` or both:
- `R_STDOUT`: redirect **only** `stdout`
- `R_STDERR`: redirect **only** `stderr`
- `R_BOTH`: redirect **both** `stdout` and `stderr`

## Start Redirection: `redirect_start()`

Start a redirection by calling `redirect_start()`

**Syntax**  
`redirect_start(mode)`

**Parameters**  
- `mode`: See [Redirect Modes](#redirect-modes)

**Example**
```c
redirect_start(R_STDOUT);	// Redirect only stdout
// ...
redirect_stop();
```

## Read Redirection: `redirect_read()`

Read the output value stored in the active redirection by calling `redirect_read()`

> ⚠️ `redirect_read()` returns a `malloc`'d pointer, don't forget to `free()` it!

**Syntax**  
`redirect_read()`

**Example**
```c
redirect_start(R_STDOUT);
// ...

char *output = redirect_read();	// Get output value

// ...
redirect_stop();
free(output);
```

## Stop Redirection: `redirect_stop()`

Stop the active redirection by calling `redirect_stop()`

**Syntax**  
`redirect_stop()`

**Example**
```c
redirect_start(R_STDOUT);
// ...

redirect_stop();	// Stop the active redirection
```

## One-liner: `get_output()`

You can easily **create** a redirection, **read** output and **stop** the redirection all at once by using `get_output()`.

**Syntax**  
`get_output(mode, expression, var_name)`

**Parameters**  
- `mode`: See [Redirect Modes](#redirect-modes)
- `expression`: The expression from which you want to capture the output
- `var_name`: The name of the variable in which you want to store the captured output

**Example**
```c
char	*output;

get_output(R_STDOUT, printf("Hello world"), output);	// output = "Hello world"

// ...
free(output);
```

> 💡 You can use `get_output()` even if one or more redirections are already active

## Simple Usage Example

You can manually [start](#start-redirection-redirect_start), [read](#read-redirection-redirect_read) and [stop](#stop-redirection-redirect_stop) redirections:
```c
char	*output;

redirect_start(R_STDOUT);		// Redirect stdout
printf("Hello world");			// Output is captured by the redirection
output = redirect_read();		// output = "Hello world"
redirect_stop();				// Restore original fds

// ...
free(output);
```

Or you can do it [all at once](#one-liner-get_output):
```c
char	*output;

get_output(R_STDOUT, printf("Hello world"), output);	// output = "Hello world"

// ...
free(output);
```

## Nested Usage Example

You can _stack_ redirections by calling [`redirect_start()`](#start-redirection-redirect_start) inside another active redirection:

```c
char	*output_1;
char	*output_2;

redirect_start(R_STDOUT);		// Start a first redirection
printf("first redirection");	// Output is captured by the first redirection

redirect_start(R_STDOUT);		// Start a second redirection
printf("second redirection");	// Output is captured by the second redirection

output_2 = redirect_read();		// output_2 = "second redirection"
redirect_stop();				// Restore the first redirection

output_1 = redirect_read();		// output_1 = "first redirection"
redirect_stop();				// Restore original fds

free(output_1);
free(output_2);
```

## Bypass redirections: `print_stdout()` and `print_stderr()`

You can bypass the redirections and print in the _real_ `stdout` / `stderr` by using the `print_stdout()` and `print_stderr()` functions.

**Syntax**  
- `print_stdout(const char *format, ...)`  
- `print_stderr(const char *format, ...)`  

**Parameters**
- `format`: Format string
- `...`: Any number of args to be converted

> 💡 Use them as you would use `printf()`

Example:
```c
redirect_start(R_STDOUT);		// Redirect stdout

printf("Hello world\n");		// Invisible (captured by active redirection)
print_stdout("Hello World\n");	// Visible (bypass the active redirection)

redirect_stop();				// Restore original fds
```
