# MINISHELL

My 9th project at 42 Network's Hive Helsinki 🐝

An interactive shell: Command-line interpreter and executioner!

> [!TIP]
> If you're at a 42 school and doing this project: It's genuinely so much better to ask fellow students instead of reading online solutions ✨

---

## Description

This project's about creating a small shell, supporting the following features:
- Readline prompts and history
- Command parsing & execution
- Redirections (`<`, `>`, `<<`, and `>>`)
- Piping between commands
- Quotes and their usual shell behavior (without interpreting unclosed closes)
- Environment variables and expansion
- Exit status expansion (`$?`)
- The following shell built-ins:
  - `echo`: Supporting the `-n` flag
  - `cd`: Only with a relative or absolute path
  - `pwd`: With no options
  - `export`: With no options
  - `unset`: With no options
   - `env`: With no options or arguments
  - `exit`: With no options
- Signal-handling for `ctrl-C` (SIGINT) & `ctrl-\` (SIGQUIT), using at most one global variable (we've used zero!)
- EOF support (`ctrl-D`)

I was also happy to voluntarily implement:
- A colorful prompt 🌈🌈
- Current directory as part of the prompt
- Shell-level (`SHLVL`) environment variable incrementation: String-based, so it can go beyond the size of the largest supported integer value!
- Optional through compiling with `make more`:
  - Visualization of the linked-list output from parsing
  - List of files in current directory above the shell prompt (without calling `ls`)
- Graceful SIGPIPE handling
- Process ID expansion (`$$`)
- Hopefully-helpful documentation (on everything I, Eve, personally implemented (outside of main.c) )

---

## Usage

> [!NOTE]
> Code was written and tested for Linux (using Hive's Ubuntu iMacs)

- Optionally, adjust settings at `include/minishell.h`
- Compile by running `make` (or `make more` for visualized parsed output and files list for current directory!)
- Run `./minishell`
- Run some shell commands with the above features!

---

## Credits

- [Eve Keinan](https://github.com/EvAvKein)
- [Aino Havu](https://github.com/a-havu)
