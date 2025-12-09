# Comparison

The `compare` macro allows you to run two functions side-by-side (usually your implementation vs the original libc one) and assert that they behave identically.

## Usage

It takes 5 arguments:
1. **Mode**: What to capture (`RET`, `OUT`, `ERR`, `BOTH`...).
2. **Timeout**: Max execution time in milliseconds.
3. **Function 1**: The first function (e.g., `strlen`).
4. **Function 2**: The second function (e.g., `ft_strlen`).
5. **Arguments**: The arguments to pass, in parentheses.

```c
#include "fut.h"
#include <string.h>

Test(comparison_test, 0)
{
    // Check if ft_strlen behaves like strlen for "Hello"
    compare(RET, 100, strlen, ft_strlen, ("Hello"));

    // Check if ft_putstr outputs the same thing as printf
    compare(OUT, 100, printf, ft_putstr, ("Hello"));
}
```

## How it works

1. It runs Function 1 in a child process (safe execution).
2. It captures the result/output.
3. It runs Function 2 in a child process.
4. It captures the result/output.
5. It asserts that both `t_capture` results are identical (status, return value, output, signal, etc.).

If they differ, a diff is displayed.

## Public API

```c
#define compare(cap_mode, timeout_sec, fn1_name, fn2_name, fn_args) ...
#define compare_label(cap_mode, timeout_sec, label, fn1_name, fn2_name, fn_args) ...
```

**Parameters**
- `fn_args`: Arguments must be enclosed in parentheses `(arg1, arg2)`.