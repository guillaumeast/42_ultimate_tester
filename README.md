<p>
  <img width="100%" alt="Capture d’écran 2025-11-08 à 19 52 42" src="https://github.com/user-attachments/assets/22ebd326-5736-4643-897f-db7c725c5bc1" />
</p>

<p>
  
  [![42](https://img.shields.io/badge/-black?logo=42&style=flat)](#)
  [![Zsh](https://img.shields.io/badge/Shell-Zsh-89e051?style=flat&logo=gnu-bash)](#)
  [![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c&logoColor=white)](#)
  
</p>

**Think your 42 project is bulletproof? Test it!** 💥

---

## ⚙️ Install

From anywhere, just run:
```bash
curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/install.zsh | zsh
```

This will:
1. Install `42 Ultimate Tester` globally in `~/.42_ultimate_tester/`
2. Add the aliases `test` and `rmtest` to your `.zshrc` file

> ✌️ No setup, no dependency, no `Makefile` editing, no excuses.

---

## 🚀 Use

From your project root (e.g. `get_next_line/`), just run:

``` bash
test
```

This will:
1. Auto-update
2. Detect which project you're in
3. Run the matching test suite

> 👇 Example output when running tests for `ft_printf`

<img width="514" height="866" alt="Capture d’écran 2025-11-08 à 19 30 05" src="https://github.com/user-attachments/assets/4580112c-06b2-4bcc-89be-44127e68bdd2" />

---

## 📦 Supported Projects

| Project | Status | Mandatory Test Cases | Bonus Test Cases |
|---------|--------|----------------------|------------------|
| `get_next_line` | ✅ Ready | ~150 🧨 | 0 (Work in progress) |
| `ft_printf` | ✅ Ready | ~100 🧨 | 0 (Work in progress) |
| `libft` | 🧱 Work in progress | 0 (Work in progress) | 0 (Work in progress) |
| Others | 🤷‍♂️ We'll see | n.a. | n.a. |

---

## ⚠️ Norminette Reminder

Sorry `norminette` fans - this tester won't (yet) run it for you.\
You'll have to check your style manually like a real dev:

``` bash
norminette
```

> If your tests pass but `norminette` fails, you're still not safe 😈

---

## 🔧 Requirements

Nothing fancy - just make sure you've got these:

| Tool | Why |
|------|--------|
| `curl` | To fetch the `42_ultimate_tester` installer |
| `git` | To download the `42_ultimate_tester` files and pull updates |
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
3. Keep it **fully standalone** and **easily removable** (no external setup, no global installs)
4. Open a pull request with a short description of what your tests cover

> 💬 Bonus points if your test breaks your own code first — that’s science
