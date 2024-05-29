# Minishell

## As beautiful as a shell

### Summary
This project involves creating a simple shell in C, similar to bash. You will learn a lot about processes and file descriptors.

## Introduction
Shells are essential software in computing, allowing communication with a computer via interactive command lines. Minishell lets you revisit the issues faced before the existence of Windows.

## Common Instructions
- Display a prompt while waiting for a new command.
- Have a working command history.
- Search and launch the correct executable based on the PATH variable or using a relative or absolute path.
- Implement redirections (`<`, `>`, `<<`, `>>`).
- Implement pipes (`|`).
- Handle environment variables and exit statuses.
- Handle signals (`ctrl-C`, `ctrl-D`, `ctrl-\`) as in bash.
- Implement builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## How to Use

1. **Clone the repository:**
   ```sh
   git clone https://github.com/Arnaud212/Minishell.git
   cd minishell
   ```

2. **Complie the project:**
   ```sh
   make
   ```

3. **Run the shell:**
   ```sh
   ./minishell
   ```

4. **Basic usage:**
   
   - Type commands as you would in a classic shell.
   - Use `cd` to change directories.
   - Use `echo`, `pwd`, `export`, `unset`, `env`, and `exit` for their respective functions.
