# Get Started

Ready to break your code? Let's get started.

## 1. Create a test file

Create a new file (e.g., `main_test.c`). You don't need a `main` function; the framework provides its own entry point.

```c
#include "fut.h"
#include <string.h>

// Define a test set named 'simple_test' with a 0s timeout (disabled)
Test(simple_test, 0)
{
    // syntax: assert(timeout, boolean_expression)
    assert(1, 1 + 1 == 2);
    
    // syntax: assert_eq(mode, timeout, got, expected)
    assert_eq(RET, 1, strlen("42"), 2);
}
```

## 2. Compile

Link against the `fut` library.

### Global Install (`/usr/local`)

If you installed the library globally:
```bash
cc main_test.c -lfut -o my_tester
```

### Local Install (`~/.local`)

If you installed the library locally:
```bash
cc main_test.c -I ~/.local/include -L ~/.local/lib -lfut -o my_tester
```

## 3. Run

Execute the binary to run your tests.
```bash
./my_tester
```
