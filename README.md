# 🧪 42 Ultimate Tester

**Think your 42 project is bulletproof? Test it!** 💥

`42_ultimate_tester` is a **dependence-free**, one-command testing tool for 42 projects
> ✌️ No setup, no dependecy, no `Makefile` editing, no excuses.

---

## ⚙️ How to Install

From anywhere, just run:
```bash
curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/install.zsh | zsh
```

> 💡 Don't forget to restart your terminal or run `source ~/.zshrc`

This will:
1. Install `42 Ultimate Tester` globally in `~/.42_ultimate_tester/`
2. Add the aliases `test` and `rmtest` to your `.zshrc` file
3. Display a short help message explaining how to use them

---

## 🚀 How to Use

From your project root (e.g. `get_next_line/`), just run:

``` bash
test
```

This will:
1. Detect which project you're in
2. Run the matching test suite

> 💡 Perfect for testing projects lightning-fast during the 42 cursus.

---

## 📦 Supported Projects

| Project | Status |
|---------|--------|
| `get_next_line` | ✅ Ready to break your code |
| `ft_printf` | 🧱 Work in progress |
| `libft` | 🧾 Planned |
| Others | 🤷‍♂️ We'll see |

---

## ⚠️ Norminette Reminder

Sorry `norminette` fans --- this tester won't (yet) run it for you.\
You'll have to check your style manually like a real dev:

``` bash
norminette
```

> If your tests pass but `norminette` fails, you're still not safe 😈

---

## 🔧 Requirements

Nothing fancy --- just make sure you've got these:

| Tool | Why |
|------|--------|
| `curl` | To fetch the `42_ultimate_tester` archive |
| `tar` | To unpack the `42_ultimate_tester` archive |
| `zsh` | Because we're not animals |

> 💡 Don't worry - all of these come preinstalled on the 42 Ubuntu machines.

---

## 🧹 Cleanup

Wanna start fresh? Easy:

``` bash
rmtest
```

---

### 🧩 Contributing

Want to make other 42 students cry too? 😈  
You can help expand `42_ultimate_tester` by adding new test suites!

1. Fork the repo: [guillaumeast/42_ultimate_tester](https://github.com/guillaumeast/42_ultimate_tester)
2. Add your test folder (e.g. `libft/`, `printf/`, etc.)
3. Keep it **dependence-free** and **removable** (no external setup, no global installs)
4. Open a pull request with a short description of what your tests cover

> 💬 Bonus points if your test breaks your own code first — that’s science
