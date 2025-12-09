# 42 ULTIMATE TESTER

<p>
  [![42](https://img.shields.io/badge/-black?logo=42&style=flat)](#)
  [![Zsh](https://img.shields.io/badge/Shell-Zsh-89e051?style=flat&logo=gnu-bash)](#)
  [![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c&logoColor=white)](#)
  [![Version](https://img.shields.io/badge/version-1.0.0-darkgreen)](#)
</p>

**Think your project is bulletproof? Test it!** 💥

42 Ultimate Tester is a **lightweight, standalone C unit testing library**.  
No complex frameworks, no dependencie—just you, your code, and the cold hard truth.

---

## ⚙️ Install

From anywhere, just run:
```bash
curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/1_scripts/install.sh | sh
```
or:
```bash
wget -qO- https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/1_scripts/install.sh | sh
```

This will:
1. Clone the repo to `~/.42_ultimate_tester/`
2. Build the `libfut.a` static library
3. Link the library and header to your system (Global or Local)

> ✌️ No setup, no dependency, no editing, no excuses.

---

## 🛠️ Management

To make your life easier, set up aliases in your shell config.

For example, if you use `zsh` shell, run the following commands:

```bash
echo "alias fut_update='~/.42_ultimate_tester/1_scripts/update.sh'" >> ~/.zshrc
echo "alias fut_uninstall='~/.42_ultimate_tester/1_scripts/uninstall.sh'" >> ~/.zshrc
source ~/.zshrc
```

Now you can simply:
- Update with `fut_update`
- Uninstall with `fut_uninstall` (but you won't, right?)

---

## 🚀 Usage

### 1. Include the header
```c
#include <fut.h>
```

### 2. Write your tests
Wrap your tests in `Test()` blocks. No main function required—we handle that.

### TODO: add link to docs

```c
#include <fut.h>
#include <string.h>

Test(test_strlen, 0) // Name, Timeout (0 = disabled)
{
    // Simple verification
    assert(1, strlen("Hello") == 5);

    // Advanced comparison
    compare(RET, 1, strlen, ft_strlen, ("Hello"));
}
```

### 3. Compile & Run
Link against the library (`-lfut`) and run the executable.

```bash
# If installed globally (/usr/local)
cc my_tests.c -lfut && ./a.out

# If installed locally (~/.local)
cc my_tests.c -I ~/.local/include -L ~/.local/lib -lfut && ./a.out
```

---

## 📚 API Reference

Here are the tools at your disposal to break your code.

### 🧪 Test Sets
Define a suite of tests with a timeout (or 0 to disable timeout).
```c
Test(name, timeout_s)
{
	// Your tests
}
```

### 🔀 Redirections
Manually control standard outputs.  
Start a redirection with `redirect_start()`, ``
```c
redirect_start(R_STDOUT); // R_STDERR, R_BOTH
// ... do stuff ...
char *output = redirect_read();
redirect_stop();
```

### ⚡ Unsafe Output
Quickly capture output (no fork, runs in current process).
```c
char *out;
get_output(R_STDOUT, printf("42"), out);
```

### 🛡️ Safe Capture
Runs expression in a child process. Handles crashes and timeouts.
```c
t_capture res;
// mode: RET, OUT, ERR, BOTH, RET_OUT...
capture(OUT, 100, printf("42"), res); 

if (res.status.type == CRASHED) ...
if (strcmp(res.out, "42") == 0) ...
```

### ✅ Assertions
All assertions are **safe** (forked).

**Basic Assertion**
```c
assert(timeout, expression);
assert(100, 1 + 1 == 2);
```

**Equality Check**
```c
// mode for capturing (RET, OUT...), timeout, got, expected
assert_eq(RET, 100, ft_strlen("abc"), 3);
```

**Inequality Check**
```c
assert_neq(RET, 100, ft_strlen("abc"), 0);
```

**Function Comparison**
Compare your function against the original (or another reference).
```c
// mode, timeout, func1, func2, (args)
compare(RET, 100, strlen, ft_strlen, ("abc"));
```

> Knowing the limitations is part of mastering the tool.

---

## ⚠️ Important Warnings

- **Nested Timeouts**: Using `assert()` or `compare()` inside a `Test()` (which implies forking inside a forked process with timers) **may introduce race conditions**. (WIP)
- **Struct Comparison**: `assert_eq` does not support struct comparison yet. (WIP)
- **Direct Printing**: Using `printf` or similar inside `Test()` is **Undefined Behavior** because of how the runner manages output pipes. Use logging macros or keep it silent. (WIP)

> Bonus points if your test breaks your own code first — that’s science.

---

## 🧹 Cleanup

Wanna start fresh?
```bash
fut_uninstall
```

> You’ll be able to pretend this never happened — and that you nailed it on the first try.
