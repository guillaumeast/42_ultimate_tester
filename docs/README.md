# Documentation

Welcome to the **42 Ultimate Tester** documentation.

Here is everything you need to know to transform from a "printf debugger" to a testing god.

## Table of Contents

### 🚀 [Get Started](0_get_started.md)
Your first steps. Write a test, compile it, and run it in 5 minutes.

### 🧩 [Test Sets](1_set.md)
Learn how to define test suites (`Test()`) and handle timeouts.

### 🔀 [Redirections](2_redirections.md)
Master `stdout` and `stderr`. Redirect outputs, read them back, and keep your terminal clean.

### 🛡️ [Safe Execution (Capture)](3_capture.md)
The core of the framework. Run code in a sandbox (fork) to catch crashes (segfaults) and freezings without killing the tester.

### ✅ [Assertions](4_assert.md)
`assert`, `assert_eq`, `assert_neq`. verify your code logic with type-aware comparisons.

### 🆚 [Comparison](5_compare.md)
`compare`. Run your function against the libc original (e.g. `ft_strlen` vs `strlen`) and let the computer spot the difference.
