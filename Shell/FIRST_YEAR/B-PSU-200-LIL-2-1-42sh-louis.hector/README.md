# 42sh

**42sh** is a project from the PSU module, aimed at reproducing a functional Unix shell based on **Tcsh**.

## Summary

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Project Constraints](#project-constraints)
- [Authors](#authors)

---

## Features

### Basic Features

- Execution of simple commands (ls, echo, etc.)
- Redirections (>, <, >>)
- Pipes (|)
- Built-in commands: cd, exit, setenv, unsetenv
- Error handling (with correct return codes)

### Specific scripts and commands

- Scripts : `foreach`, `repeat`, `which`, `where`
- Aliases (`alias hide "ls -a"`)

### Advanced features

- Globbing (`*`, `?`, `[]`)
- Line editing (auto-completion, history)
- Easter eggs

---

## Installation

### 1. Clone the repository

```bash
git clone <repository-url>
cd repo
```

### 2. Compile the project

```bash
make
```

## Usage

### Launch the shell

```bash
./42sh
```

## Project Structure

```bash
.
├── include/           # Header files
├── lib/               # Utility functions
├── src/               # Main source code
├── tests/             # Unit tests
├── unit_tests/        # Specific unit tests
├── Makefile           # Compilation (make, clean, fclean, re)
└── README.md          # This file
```

## Project Constraints

Language: C

- Compilation via Makefile (make, clean, fclean, re)
- Allowed functions: all functions from the libC and the ncurses library
- Errors must be displayed on the error output (stderr) with the correct exit codes (as in Tcsh)

## Authors

- Paul A.
- Louis H.
- Keryan P.
- Silas D.
- Laumé L.