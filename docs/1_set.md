# Test Sets

A **Test Set** is a self-contained unit of testing that is automatically registered and run by the framework.  
You do **NOT** need to declare it in a header or register it manually. The linker magic does it for you 🪄.

**Syntax**  
`Test(name, timeout_sec)`

**Parameters**
- `name`: The **unique** name of the **test set** to create.
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).

## Defining a Test

Use the `Test()` macro to define a new test set.  

```c
#include "fut.h"

Test(name_of_the_test, 0)
{
    // Write your test code here
}
```

## Setting a timeout

You can enforce a global timeout for the entire test set.  
If the test set takes longer than the specified time, it will be killed and marked as `TIMED`.

```c
#include "fut.h"

Test(performance_test, 2)
{
	// This test must complete within 2 seconds
}
```

> If you use `capture` or `assert` [TODO: add links] inside the test set, detailed timeout handling is managed separately, but this global timer is the ultimate deadline.
