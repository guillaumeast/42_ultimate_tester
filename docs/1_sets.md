# Test Sets

A **Test Set** is a single executable test block.  

All your [assertions](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/3_assertions.md) / [memchecks](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/4_memchecks.md) must be enclosed in **Test Sets**.  
You can put as many [assertions](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/3_assertions.md) / [memchecks](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/4_memchecks.md) as you want inside each **Test Set**.

🛡️ **All Test Sets are safe**: they run in a forked process, catch crashes, handle timeouts and protect the test suite.

🪄 Each **Test Set** is **automatically registered and run** by the framework.  

**Syntax**  
`Test(name, timeout_sec)`

**Parameters**
- `name`: **Unique label** for this Test Set (shown in the test report).
- `timeout_sec`: **Max execution time** in seconds (`0` for no timeout).

**Example**
```cs
#include "fut.h"

Test(name_of_the_test, 1)
{
    // Assertions and memchecks go here
}
```

> If the **Test Set** takes longer than the specified `timeout_sec`, it will be killed and marked as `TIMED`.

> [Assertions](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/3_assertions.md) and [memchecks](https://github.com/guillaumeast/42_ultimate_tester/blob/master/docs/4_memchecks.md) inside the **Test Set** have their own **timeouts**,  
but the **Test Set timeout** is the hard upper limit: if the block runs longer, the whole **Test Set** is stopped.
