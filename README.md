# 42 ULTIMATE TESTER

[![42](https://img.shields.io/badge/-black?logo=42&style=flat)](#)
[![sh](https://img.shields.io/badge/Shell-sh-89e051?style=flat&logo=gnu-bash)](#)
[![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c&logoColor=white)](#)
[![Version](https://img.shields.io/badge/version-0.9.0-orange)](#)

The Testing Framework You Wish You Had Earlier.

Say goodbye to printf debugging.
Say hello to clean, automated, crash-proof testing for your C projects.

42 Ultimate Tester is a fast, lightweight, dependency-free testing framework built for real C developers.

## Table of contents
- [What's inside?](#-whats-inside)
- [Install](#️-install)
- [Update and uninstall](#️-update-and-uninstall)
- [Documentation](#-documentation)
- [Limitations](#️-limitations)
- [Contribute](#-contribute)

## ✨ What’s inside?

### 🔥 A testing experience that just works

- No setup, no dependencies, no main function required
- Automatic test discovery
- Clean, readable logs with file + line info
- Isolated execution in forked processes (no more global crashes)

### 🧠 Smart & powerful checks

- Type-aware assertions (check return values and/or outputs)
- Function-to-function comparison
- Automatic `stdout`/`stderr` redirections
- One-liner output capturing
- Custom labels

### 🛡 Memory checks built-in

- Detect unfreed allocations with precise file/line reporting
- Detect bad malloc protection, null deref, unsafe access, SIGSEGV/SIGBUS, etc.

### 🧩 Designed for 42 standards

- Pure POSIX C
- Works on Linux and macOS (`x86` and `ARM`)
- Zero external dependencies
- _No-`sudo`_ install option
- Perfect for `libft`, `ft_printf`, `gnl`, `minitalk`, and all 42 projects

> ✌️ Just write what you want to test, and let the framework handle all the complicated stuff.

<div style="display: flex; gap: 10px;">
    <img src="docs/assets/passed_tests.png" width="49%">
    <img src="docs/assets/failed_tests.png" width="49%">
</div>

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
3. Link the library and header to your system (global or local)

You can now run your first test in just a few seconds by following this [guide](docs/0_get_started.md) ⚡️

> ✌️ No setup, no dependencies, no editing, no excuses.

## 🛠️ Update and uninstall

You can update by running the following command:
```bash
~/.42_ultimate_tester/1_scripts/update.sh
```

You can uninstall the framework by running the following command:
```bash
~/.42_ultimate_tester/1_scripts/uninstall.sh
```

To make your life easier, you can set up aliases in your shell config.  
For example, if you use `zsh` shell, run the following commands:

```bash
echo "alias fut_update='~/.42_ultimate_tester/1_scripts/update.sh'" >> ~/.zshrc
echo "alias fut_uninstall='~/.42_ultimate_tester/1_scripts/uninstall.sh'" >> ~/.zshrc
source ~/.zshrc
```

Now you can simply:
- Update with `fut_update`
- Uninstall with `fut_uninstall` (but you won't, right?)

## 📚 Documentation

### 🚀 [Get Started](docs/0_get_started.md)
Your first steps. Write a test, compile it, and run it in less than a minute.

### 🧩 [Test Sets](docs/1_sets.md)
Learn more about Test Sets and global timeouts.
- `Test()`: create isolated executable test blocks.

### 🔀 [Redirections](docs/2_redirections.md)
Master `stdout` and `stderr` redirections.  
- `redirect_start()`, `redirect_read()`, `redirect_stop()`: manually redirect outputs and read them back.  
- `get_output()`: Easily capture outputs in a single line.

### ✅ [Assertions](docs/3_assertions.md)
Understand how to verify correctness, compare behaviors and detect crashes/freezes with safe and flexible assertion tools.  
- `assert()`, `assert_eq()`, `assert_neq()`: verify your code logic with type-aware comparisons.  
- `compare()`: compare behaviors of two functions.  
- `*_label()`: use custom labels instead of default ones.

### 🧠 [Memchecks](docs/4_memchecks.md)
Catch memory leaks and unsafe memory accesses directly from your tests.
- `memleaks()`: detect unfreed allocations.
- `memsafety()`: detect null dereferences, unsafe malloc usage, and crash-prone memory operations.

## ⚠️ Limitations

- **Nested Timeouts**: Using `assert*()`/`compare*()`/`mem*()` timeouts inside a `Test()` which also have a timeout enabled **may introduce race conditions**. (WIP)
- **Struct Comparison**: `assert_eq*()` and `assert_neq*()` do not support struct comparison yet. (WIP)
- **Nested redirections**: Using `print_stdout()` or `print_stderr()` inside nested redirections is not supported yet. (WIP)
- **Logs length**: Test set titles and failed assertions logs are limited to 256 characters max. (WIP)

> Knowing the limitations is part of mastering the tool.

## 🤝 Contribute

Contributions are welcome!

Whether you want to fix a bug, improve the documentation, add features, or optimize the core, feel free to open a Pull Request.

### How to contribute
1. Fork the repository  
2. Create a feature branch:
   ```bash
   git checkout -b feature/my-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "feat: add my feature"
   ```
4. Push your branch and open a Pull Request

> 💡 Make sure your contribution follows the project's structure and conventions.

If you're unsure about something, feel free to open an issue — discussion is welcome.
