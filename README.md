<p>
  <img width="100%" alt="Capture d’écran 2025-11-08 à 19 52 42" src="https://github.com/user-attachments/assets/22ebd326-5736-4643-897f-db7c725c5bc1" />
</p>

<p>
  
  [![42](https://img.shields.io/badge/-black?logo=42&style=flat)](#)
  [![Zsh](https://img.shields.io/badge/Shell-Zsh-89e051?style=flat&logo=gnu-bash)](#)
  [![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c&logoColor=white)](#)
  [![Version](https://img.shields.io/badge/version-1.0.0-blue)](#)
  
</p>

**Think your 42 project is bulletproof? Test it!** 💥

---

## ⚙️ Install

From anywhere, just run:
```bash
curl -fsSL https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/1_launcher/install.zsh | zsh
```
or:
```bash
wget -qO- https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/1_launcher/install.zsh | zsh
```

This will:
1. Install `42 Ultimate Tester` globally in `~/.42_ultimate_tester/`
2. Add the aliases `test` and `rmtest` to your `.zshrc` file

> ✌️ No setup, no dependency, no editing, no excuses.

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

> The best bugs are the ones you didn’t expect.

---

## 📦 Supported Projects

| Project | Status | Mandatory Test Cases | Bonus Test Cases |
|---------|--------|----------------------|------------------|
| `libft` | 🧱 Work in progress | _ | _ |
| `ft_printf` | ✅ Ready | 300+ 🧨 | _ |
| `get_next_line` | 🧱 Work in progress | _ | _ |
| Others | 🤷‍♂️ We'll see | _ | _ |

> More will come — when they’re good enough to hurt you.

---

## 🧰 What’s included

This tester ships with:

1. **All Francinette tests** (for supported projects)
2. **Extra tests** I wrote myself  
3. **Makefile checks** (because your Makefile *will* betray you at some point)

> If your project survives `42 Ultimate Tester`, the `Moulinette` will be a formality.

---

## 🔧 Requirements

Nothing fancy - just make sure you've got these:

| Tool | Why |
|------|--------|
| `zsh` | Because we're not animals |
| `curl` or `get` | To fetch the **installer** |
| `git` | To pull **automatic updates** |
| `make` | To **build** the tester |

> 💡 Don't worry - all of these come preinstalled on the 42 Ubuntu machines.

---

## 🧹 Cleanup

Wanna start fresh? Easy:

``` bash
rmtest
```

> You’ll be able to pretend this never happened — and that you nailed it on the first try.

---

## ⚠️ Important Warnings

- **Norminette** is **NOT** checked by the tester  
  *(wip: coming very soon)*  
- Only **ft_printf mandatory** is fully available for now  
  *(wip: `libft`, `gnl`, and bonus tests coming very soon)*  
- Tested **only on macOS ARM** for now  
  *(wip: `macOS x86` and `Linux` support coming soon)*  
- Stacktraces may show **incorrect source locations**  
  *(still work in progress — but it crashes beautifully)*

> Knowing the limitations is part of mastering the tool.

---

### 🧩 Contributing

Want to make other 42 students cry too? 😈  
You can help expand `42_ultimate_tester` by adding new test suites!

1. Fork the repo: [guillaumeast/42_ultimate_tester](https://github.com/guillaumeast/42_ultimate_tester)
2. Add your test folder (e.g. `libft/`, `printf/`, etc.)
3. Keep it **fully standalone** and **easily removable** (no external setup, no global installs)
4. Open a pull request with a short description of what your tests cover

Feel free to contact me at **[gastesan@student.42.fr](mailto:gastesan@student.42.fr)**.

> Bonus points if your test breaks your own code first — that’s science
