# 🐚 Minishell

## 📌 Table of Contents
- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Mandatory Features](#mandatory-features)
- [Compilation](#compilation)
- [Execution](#execution)
- [Project Structure](#project-structure)
- [Implementation Overview](#implementation-overview)
- [Resources](#resources)

---

## 🧩 Introduction

**Minishell** is a 42 school project where you build your own simple shell from scratch using C. The goal is to replicate basic behavior of Bash with your own parser, executor, and environment handling, including job control and signal handling.

---

## 🎯 Project Objectives

- Understand how shells work internally.
- Learn about process creation and management (`fork`, `exec`, `wait`).
- Parse and interpret command lines.
- Handle Unix signals.
- Manage environment variables.
- Implement pipelines, redirections, and logical operators.

---

## ✅ Mandatory Features

- Display a prompt and wait for user input.
- Read and parse command lines.
- Execute:
  - Executables in `PATH`.
  - Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Support:
  - Pipes (`|`)
  - Redirections (`<`, `>`, `>>`)
  - Environment variables (`$VAR`)
  - Quoting (`'`, `"`)
  - `$?` (last return value)
- Proper error handling and exit codes.
- Signal handling for `SIGINT` and `SIGQUIT`.
- Support for command history.
- Code norm-compliant and modular design.
- Here-document (`<<`) with variable expansion.
---

## 🛠 Compilation

To compile the project, run:

```bash
make
````

To remove object files:

```bash
make clean
```

To remove everything including the executable:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

The shell executable is named `minishell`.

---

## 🚀 Execution

Launch the shell by running:

```bash
./minishell
```

From there, you can interact using standard shell syntax. Try:

```bash
echo hello world
ls -la | grep minishell > out.txt
```

Use `Ctrl+C` to interrupt commands and `exit` to close the shell.

---

## 🧠 Implementation Overview

* **Lexer**: Tokenizes input based on quotes, pipes, and redirections.
* **Parser**: Builds an abstract syntax tree or command structure.
* **Executor**: Handles built-ins, forks child processes for other commands.
* **Redirections**: Implemented using `dup2()`.
* **Environment**: Managed using a custom key-value structure.
* **Signals**: Customized handling for interactive behavior.
* **Here-doc**: Reads input until a delimiter is met and pipes it to command input.

---

## 📚 Resources

* `man bash`, `man fork`, `man execve`, `man dup2`, `man signal`, `man waitpid`
* [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
* 42 Forum and peer review

---
🛠 Built with love and frustration as part of the 42 Network curriculum.
