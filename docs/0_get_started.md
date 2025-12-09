# Get Started

Ready to break your code? Let's get started.

> ⚡️ You can run your first test in just a few seconds

## Table of contents
- [1. Create a test file](#1-create-a-test-file)
- [2. Compile](#2-compile)
- [3. Run](#3-run)
- [Go further](#go-further)

## 1. Create a test file

Create a new file (e.g., `test.c`).

> ✌️ You don't need a `main` function; the framework provides its own entry point.

```c
#include "fut.h"
#include <string.h>

// Define a test set named 'simple_test' with a 0s timeout (disabled)
Test(simple_test, 0)
{
    // Define a basic assert with a 1s timeout
    assert(1, strlen("42") == 2);
}
```

## 2. Compile

Link against the `fut` library.

If you installed the library **globally**, you only need the `-lfut` flag:
```bash
cc test.c -lfut -o my_tester
```

If you installed the library **locally**, you'll need to add `-I` and `-L` flags:
```bash
cc test.c -I ~/.local/include -L ~/.local/lib -lfut -o my_tester
```

## 3. Run

Execute the binary to run your tests.
```bash
./my_tester
```

You should see output similar to this:  
[_**TODO: add screenshot**_]

## Go further

You can learn more about the framework capabilities by reading the following docs:
- [Sets](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/1_sets.md)
	- `Test()`
- [Redirections](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/2_redirections.md)
	- `redirect_start()`
	- `redirect_read()`
	- `redirect_stop()`
	- `get_output()`
- [Assertions](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/3_assertions.md)
	- `assert()`
	- `assert_eq()`
	- `assert_neq()`
	- `compare()`
	- `*_label()` variants
- [Memchecks](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/4_memchecks.md)
	- `memleaks()`
	- `memsafety()`
