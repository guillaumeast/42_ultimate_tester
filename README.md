# 🧪 42 Ultimate Tester

**Think your 42 project is bulletproof? Test it!** 💥

`42_ultimate_tester` is a **dependence-free**, one-command testing tool for 42 projects
> _Built to make your life easier and your code cry (just a little)_

---

## 🚀 How to Use

From your project root (e.g. `get_next_line/`), just run:

``` bash
curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/42_ultimate_tester.zsh | zsh
```

The script will:
1. Detect which project you're in
2. Download the matching test suite
3. Install it inside a local folder `./42_ultimate_tests/`
4. Run the test suite automatically

No setup, no `Makefile` editing, no excuses.

---

## ⚡️ Recommended Aliases

Want to make testing even faster? Add these handy aliases to your
`~/.zshrc`:

``` bash
# Installs and runs the appropriate test suite automatically
alias test="curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/42_ultimate_tester.zsh | zsh"

# Re-runs the last downloaded test suite
alias retest="./42_ultimate_tests/test.zsh"

# Cleans up downloaded tests
alias rmtest="rm -rf ./42_ultimate_tests"
```

After adding them, reload your shell with:

``` bash
source ~/.zshrc
```

Then you can simply use:

``` bash
test      # to install + run
retest    # to re-run existing tests
rmtest    # to remove test files
```

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
| `git` | To grab the branches and updates |
| `curl` | To fetch the script and test archives |
| `unzip` | To unpack the test files |
| `zsh` | Because we're not animals |

> 💡 Don't worry --- all of these come preinstalled on the 42 Ubuntu machines.

---

## 🧹 Cleanup

Wanna start fresh? Easy:

``` bash
rm -rf ./42_ultimate_tests
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

