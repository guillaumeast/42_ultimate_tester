# Memchecks

**Memchecks** allow you to detect **memory leaks** and **unsafe memory accesses**.

🛡️ **All memchecks are safe**: they run in a forked process, catch crashes, track allocations, and protect the test suite.

## Table of contents

- [Memory Leak Check: `memleaks()`](#memory-leak-check-memleaks)
- [Memory Safety Check: `memsafety()`](#memory-safety-check-memsafety)

## Memory Leak Check: `memleaks()`

`memleaks()` executes an expression and checks whether any **allocated memory was not freed**.

If one or more allocations are leaked, the memcheck fails and is marked as `LEAKED`.

**Syntax**  
`memleaks(timeout_sec, expression)`

**Parameters**
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).
- `expression`: The expression you want to run and monitor for leaks.

**Example**
```c
memleaks(1, leak());    // Fails if leak() does not free its allocations
```

If the expression leaks memory, logs look like:
```
⤷ leak() leaked 4 bytes at leak.c:10
```

## Memory Safety Check: `memsafety()`

`memsafety()` verifies that all `malloc()` calls in the expression are **properly protected**:

- NULL check is present  
- No unsafe dereference  
- No invalid pointer access  

If the expression performs an unsafe memory access, the memcheck fails and is marked as `CRASHED`.

**Syntax**  
`memsafety(timeout_sec, expression)`

**Parameters**
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).
- `expression`: The expression to monitor for unsafe memory usage.

**Example**
```c
memsafety(1, not_safe());   // Fails if the function dereferences NULL
```

If the expression performs an unsafe access, logs look like:
```
⤷ not_safe() crashed (SIGSEGV) at not_safe.c:23
```
