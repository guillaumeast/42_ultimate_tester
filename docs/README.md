# Documentation

Welcome to the **42 Ultimate Tester** documentation.

Here is everything you need to know to transform from a "printf debugger" to a testing god.

## Table of Contents

### 🚀 [Get Started](0_get_started.md)
Your first steps. Write a test, compile it, and run it in less than a minute.

### 🧩 [Test Sets](1_sets.md)
Learn more about Test Sets and global timeouts.
- `Test()`: create isolated executable test blocks.

### 🔀 [Redirections](2_redirections.md)
Master `stdout` and `stderr` redirections.  
- `redirect_start()`, `redirect_read()`, `redirect_stop()`: manually redirect outputs and read them back.  
- `get_output()`: Easily capture outputs in only one line.

### ✅ [Assertions](3_assertions.md)
Understand how to verify correctness, compare behaviors and detect crashes/freezes with safe and flexible assertion tools.  
- `assert()`, `assert_eq()`, `assert_neq()`: verify your code logic with type-aware comparisons.  
- `compare()`: compare behaviors of two functions.  
- `*_label()`: use custom labels instead of default ones.

### 🧠 [Memchecks](4_memchecks.md)
Catch memory leaks and unsafe memory accesses directly from your tests.
- `memleaks()`: detect unfreed allocations.
- `memsafety()`: detect null dereferences, unsafe malloc usage, and crash-prone memory operations.
