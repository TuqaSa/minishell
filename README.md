# Minishell 🐚

A lightweight Unix shell implementation in C that recreates core functionalities of bash. This project provides an interactive command-line interface with process management, pipes, redirections, and built-in commands, offering deep insights into how shells work under the hood.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Code Breakdown](#code-breakdown)
- [Technical Deep Dive](#technical-deep-dive)
- [Examples](#examples)
- [Learning Outcomes](#learning-outcomes)
- [Resources](#resources)
- [Authors](#authors)
- [License](#license)

---

## 🎯 Overview

Minishell is a Unix shell that provides a command-line interface for executing commands, managing processes, and handling I/O operations. Built from scratch in C, this project demonstrates mastery of:

- **Process Management**: Fork, exec, wait system calls
- **File Descriptor Manipulation**: Pipes and redirections
- **Signal Handling**: Interactive interrupt and quit signals
- **Lexical Analysis**: Tokenization and parsing
- **Environment Management**: Variable expansion and modification

The shell faithfully recreates bash behavior for command execution, quoting, expansion, and error handling while maintaining clean, norminette-compliant code.

---

## ✨ Features

### Core Shell Functionality
- **Interactive Prompt**: Displays `minishell$` and awaits user input
- **Command History**: Full readline integration with up/down arrow navigation
- **Path Resolution**: Searches executables via PATH or accepts absolute/relative paths
- **Exit Status Tracking**: Maintains `$?` for last command's exit code

### Redirections
| Operator | Description | Example |
|----------|-------------|---------|
| `<` | Input redirection | `cat < file.txt` |
| `>` | Output redirection (truncate) | `echo "text" > out.txt` |
| `>>` | Output redirection (append) | `echo "more" >> out.txt` |
| `<<` | Heredoc (read until delimiter) | `cat << EOF` |

### Pipes
- **Pipeline Execution**: `cmd1 | cmd2 | cmd3`
- **Multi-Command Support**: Unlimited pipeline length
- **Proper FD Management**: All file descriptors properly closed

### Environment Variables
- **Expansion**: `$VAR` expands to variable value
- **Exit Status**: `$?` expands to last command's exit code
- **Positional Parameters**: `$0`, `$1`, `$2`, etc.
- **Empty Expansion**: Undefined variables expand to empty string

### Quote Handling
```bash
# Single quotes - literal interpretation
echo '$HOME'        # Output: $HOME

# Double quotes - expansion enabled (except for $)
echo "$HOME"        # Output: /home/user

# No quotes - expansion + word splitting
echo $PATH          # Split on spaces
```

### Built-in Commands

| Command | Description | Options/Arguments |
|---------|-------------|-------------------|
| `echo` | Display text | `-n` (no newline) |
| `cd` | Change directory | Relative/absolute path, `~`, `-` |
| `pwd` | Print working directory | None |
| `export` | Set environment variable | `KEY=value` |
| `unset` | Remove environment variable | Variable name |
| `env` | Display environment | None |
| `exit` | Exit the shell | Optional numeric code |

### Signal Handling

| Signal | Key Combo | Behavior |
|--------|-----------|----------|
| `SIGINT` | Ctrl-C | Display new prompt on new line |
| `SIGQUIT` | Ctrl-\ | Ignored (does nothing) |
| EOF | Ctrl-D | Exit the shell |

**Special Cases:**
- In heredoc mode: Ctrl-C aborts heredoc and returns to prompt
- During execution: Signals handled by child processes

---

## 🏗 Architecture

```
minishell/
├── include/
│   └── minishell.h              # Main header with all structures
│
├── lib/
│   └── libft/                   # Custom C standard library
│       ├── src/
│       │   ├── libft/           # String, memory, conversion functions
│       │   ├── ft_printf/       # Printf implementation
│       │   └── gnl/             # Get Next Line (file reading)
│       └── include/             # Library headers
│
├── src/
│   ├── builtins/                # Built-in command implementations
│   │   ├── builtin_dispatch.c   # Command routing
│   │   ├── builtin_echo.c       # Echo with -n flag
│   │   ├── builtin_cd.c         # Directory navigation
│   │   ├── builtin_pwd.c        # Working directory
│   │   ├── builtin_export.c     # Environment variable setter
│   │   ├── builtin_unset.c      # Environment variable remover
│   │   ├── builtin_env.c        # Environment display
│   │   └── builtin_exit.c       # Shell exit with validation
│   │
│   ├── env/                     # Environment variable management
│   │   ├── env_access.c         # Get variable values
│   │   ├── env_modify.c         # Set/unset variables
│   │   ├── env_lifecycle.c      # Initialize/free environment
│   │   └── env_utils.c          # Helper functions
│   │
│   ├── exec/                    # Execution engine
│   │   ├── exec_pipeline.c      # Multi-command pipeline execution
│   │   ├── exec_builtin.c       # Built-in command handler
│   │   ├── exec_child.c         # Child process setup
│   │   ├── exec_redirection.c   # File descriptor manipulation
│   │   ├── exec_heredoc.c       # Heredoc implementation
│   │   ├── exec_wait.c          # Process synchronization
│   │   └── exec_utils.c         # Helper functions
│   │
│   ├── expand/                  # Variable expansion
│   │   ├── expand_word.c        # Main expansion logic
│   │   ├── expand_variable.c    # Variable substitution
│   │   ├── expand_char.c        # Character processing
│   │   └── expand_utils.c       # Status conversion utilities
│   │
│   ├── lexer/                   # Tokenization
│   │   ├── lexer_core.c         # Main tokenization loop
│   │   ├── lexer_word.c         # Word token handling
│   │   ├── lexer_ops.c          # Operator token handling
│   │   ├── lexer_string.c       # String buffer management
│   │   ├── lexer_token.c        # Token vector operations
│   │   └── lexer_word_utils.c   # Word processing helpers
│   │
│   ├── parser/                  # Syntax analysis
│   │   ├── parser_core.c        # Main parsing entry point
│   │   ├── parser_cmd.c         # Command structure building
│   │   ├── parser_pipeline.c    # Pipeline segmentation
│   │   ├── parser_word.c        # Word expansion & splitting
│   │   ├── parser_redir.c       # Redirection processing
│   │   ├── parser_arrays.c      # Dynamic array management
│   │   ├── parser_utils.c       # Syntax validation
│   │   └── parser_cleanup.c     # Memory cleanup
│   │
│   ├── utils/                   # Utility functions
│   │   ├── path_resolver.c      # PATH search algorithm
│   │   ├── path_checker.c       # Executable validation
│   │   └── path_utils.c         # Path string manipulation
│   │
│   ├── main.c                   # Entry point & REPL loop
│   ├── signals.c                # Signal handlers
│   ├── signals_handler.c        # Signal mode configuration
│   └── term.c                   # Terminal settings (echoctl)
│
├── Makefile                     # Build configuration
└── README.md                    # This file
```

---

## 📦 Installation

### Prerequisites

- **GCC** or **Clang** compiler
- **Make** build system
- **Readline library** development files
  ```bash
  # Ubuntu/Debian
  sudo apt-get install libreadline-dev

  # macOS (via Homebrew)
  brew install readline
  ```

### Build Steps

```bash
# Clone the repository
git clone <repository-url> minishell
cd minishell

# Compile the project
make

# The executable will be created at bin/minishell
./bin/minishell
```

### Makefile Targets

| Target | Description |
|--------|-------------|
| `make` or `make all` | Compile the entire project |
| `make clean` | Remove object files |
| `make fclean` | Remove objects and executable |
| `make re` | Full recompilation (fclean + all) |

---

## 🚀 Usage

### Starting the Shell

```bash
./bin/minishell
```

You'll be greeted with the prompt:
```
minishell$
```

### Basic Commands

```bash
# Simple command execution
minishell$ ls -la
minishell$ pwd
minishell$ echo "Hello, World!"

# Using PATH
minishell$ cat file.txt        # Searches /bin, /usr/bin, etc.

# Absolute/relative paths
minishell$ /bin/echo test
minishell$ ./my_program
```

### Redirections

```bash
# Output redirection (overwrite)
minishell$ echo "Hello" > output.txt
minishell$ ls -l > files.txt

# Output redirection (append)
minishell$ echo "World" >> output.txt

# Input redirection
minishell$ cat < input.txt
minishell$ wc -l < file.txt

# Heredoc
minishell$ cat << EOF
heredoc> Line 1
heredoc> Line 2
heredoc> Line 3
heredoc> EOF
Line 1
Line 2
Line 3
```

### Pipes

```bash
# Two-command pipeline
minishell$ ls -l | grep .txt

# Multi-command pipeline
minishell$ cat file.txt | grep pattern | wc -l

# Complex pipeline with redirections
minishell$ cat < input.txt | grep error | sort > errors.txt
```

### Environment Variables

```bash
# Display all variables
minishell$ env

# Set variable
minishell$ export MY_VAR=hello
minishell$ export PATH=/custom/path:$PATH

# Use variable
minishell$ echo $MY_VAR
hello

# Remove variable
minishell$ unset MY_VAR
minishell$ echo $MY_VAR
                          # Empty line (undefined variable)

# Exit status
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
```

### Built-in Commands

```bash
# Echo with -n flag
minishell$ echo -n "No newline"
No newline minishell$

# Echo with multiple -n flags (all valid)
minishell$ echo -nnn -nn "Still no newline"
Still no newline minishell$

# Change directory
minishell$ cd /tmp
minishell$ cd ..
minishell$ cd ~              # Home directory
minishell$ cd -              # Previous directory

# Exit with status code
minishell$ exit 42
exit
$ echo $?                    # Back in parent shell
42
```

### Quoting

```bash
# Single quotes - everything literal
minishell$ echo '$HOME is $USER'
$HOME is $USER

# Double quotes - expand variables
minishell$ echo "$HOME is $USER"
/home/john is john

# Mixed quoting
minishell$ echo '$HOME' "is $HOME"
$HOME is /home/john

# Empty variable expansion
minishell$ echo "$UNDEFINED_VAR"
                          # Empty line
```

### Exiting the Shell

```bash
# Method 1: exit command
minishell$ exit

# Method 2: Ctrl-D (EOF)
minishell$ ^D
exit

# Method 3: exit with code
minishell$ exit 0
```

---

## 🔍 Code Breakdown

### 1. Main Loop (`src/main.c`)

The heart of the shell is the **REPL** (Read-Eval-Print Loop):

```c
int main(int argc, char **argv, char **envp)
{
    t_ms    ms;
    char    *line;
    int     rc;

    main_init_shell(&ms, argc, argv, envp);

    while (1)
    {
        ms_signals_interactive();
        line = readline("minishell$ ");

        if (!line)              // Ctrl-D pressed
            break;

        if (!main_only_space(line))
            add_history(line);  // Add to history

        rc = ms_run_line_simple(&ms, line);
        free(line);

        if (rc == 1)            // Exit requested
            break;
    }

    env_context_free(ms.envp);
    return (ms.last_status);
}
```

**Key Shell State Structure:**
```c
typedef struct s_ms {
    int         last_status;    // Exit code of last command ($?)
    char        **envp;         // Environment variables
    int         argc;           // Argument count (for $0, $1, etc.)
    char        **argv;         // Argument vector
    int         (*pipe_fds)[2]; // Array of pipe file descriptors
    pid_t       *child_pids;    // Array of child process IDs
} t_ms;
```

---

### 2. Lexer (`src/lexer/`)

Transforms raw input into structured tokens.

**Input Processing:**
```
"echo hello | cat > file.txt"
         ↓
[WORD:"echo"] [WORD:"hello"] [PIPE] [WORD:"cat"]
[REDIR_OUT] [WORD:"file.txt"]
```

**Token Types:**
```c
typedef enum e_toktype {
    TOK_WORD,       // Regular word/argument
    TOK_PIPE,       // |
    TOK_REDIR_IN,   // <
    TOK_REDIR_OUT,  // >
    TOK_DLESS,      // <<
    TOK_DGREAT      // >>
} t_toktype;
```

**Main Functions:**
- `lexer_tokenize()` - Entry point, orchestrates tokenization
- `lexer_handle_word()` - Processes words with quote awareness
- `lexer_handle_operator()` - Identifies and creates operator tokens
- `lexer_handle_quotes()` - Toggles quote state for proper parsing

**Quote Handling Example:**
```c
Input:  echo "hello world" 'single' $VAR
                ↓
Tokens: [WORD:echo] [WORD:"hello world"] [WORD:'single'] [WORD:$VAR]
                                         (quotes preserved for expansion)
```

---

### 3. Parser (`src/parser/`)

Converts tokens into executable command structures.

**Data Structures:**
```c
typedef struct s_cmd {
    char    **argv;     // Command and arguments: ["ls", "-la", NULL]
    t_redir *reds;      // Array of redirections
    size_t  nreds;      // Number of redirections
} t_cmd;

typedef struct s_pipeline {
    t_cmd   *cmds;      // Array of commands
    size_t  n;          // Number of commands in pipeline
} t_pipeline;

typedef struct s_redir {
    t_redirtype type;   // R_IN, R_OUT, R_APPEND, R_HEREDOC
    char        *arg;   // Filename or heredoc delimiter
    int         hdoc_fd;// Heredoc file descriptor (-1 if not heredoc)
} t_redir;
```

**Parsing Pipeline:**
```
Tokens → Split by Pipes → Parse Each Segment → Build Commands
                                                      ↓
                                            Apply Redirections
```

**Example:**
```bash
Input: cat < in.txt | grep pattern > out.txt
                    ↓
Pipeline with 2 commands:
  Command 1: argv=["cat", NULL]
             reds=[{R_IN, "in.txt"}]

  Command 2: argv=["grep", "pattern", NULL]
             reds=[{R_OUT, "out.txt"}]
```

**Key Functions:**
- `ms_parse_pipeline()` - Main entry point
- `parser_parse_segments()` - Splits by pipe operators
- `parse_cmd()` - Builds individual command structures
- `parser_handle_redir_token()` - Processes redirection tokens

---

### 4. Expansion (`src/expand/`)

Performs variable substitution before execution.

**Expansion Types:**

1. **Environment Variables**
   ```bash
   Input:  echo $HOME/documents
   Output: echo /home/user/documents
   ```

2. **Exit Status**
   ```bash
   Input:  echo $?
   Output: echo 0
   ```

3. **Positional Parameters**
   ```bash
   Input:  echo $0 $1
   Output: echo minishell arg1
   ```

**Quote Behavior:**
```c
// Single quotes - NO expansion
'$HOME'         →  $HOME

// Double quotes - YES expansion
"$HOME"         →  /home/user

// No quotes - expansion + word splitting
$PATH           →  /usr/bin /bin /usr/local/bin
                   (split into separate arguments)
```

**Implementation:**
```c
char *expand_word(t_ms *ms, const char *raw)
{
    char    *output = NULL;
    size_t  i = 0;
    int     in_single = 0;
    int     in_double = 0;

    while (raw[i]) {
        if (quote_toggle_check(raw, &i, &in_single, &in_double))
            continue;

        if (raw[i] == '$' && !in_single) {
            if (raw[i+1] == '?')
                status_expansion_handle(ms, &i, &output);
            else
                expand_variable_substitute(ms, raw, &i, &output);
        } else {
            char_append_to_output(raw, &i, &output);
        }
    }
    return output;
}
```

---

### 5. Execution (`src/exec/`)

The execution engine handles both built-in and external commands.

#### Single Command Execution

```c
ms_exec_cmd_with_pipeline(ms, cmd, pipeline)
  ├── Empty command check (just redirections)
  ├── Built-in check
  │   ├── Save stdin/stdout (dup)
  │   ├── Apply redirections
  │   ├── Execute built-in
  │   └── Restore stdin/stdout
  └── External command
      ├── fork()
      ├── Apply redirections
      └── execve()
```

#### Pipeline Execution

```c
ms_exec_pipeline(ms, pipeline)
  ├── Create N-1 pipes (for N commands)
  ├── Allocate PID array
  ├── Fork N children
  │   └── For each child:
  │       ├── Setup pipe file descriptors
  │       ├── Close unused pipes
  │       ├── Apply redirections
  │       └── Execute command
  ├── Parent: Close all pipes
  └── Wait for all children
```

**Pipe Setup Example:**
```
cmd1 | cmd2 | cmd3

     pipe[0]       pipe[1]
     [r][w]        [r][w]
       ↓  ↓         ↓  ↓
cmd1 ─┘   └─→ cmd2 ─┘   └─→ cmd3

Child 1: stdout → pipe[0][1]
Child 2: stdin  → pipe[0][0], stdout → pipe[1][1]
Child 3: stdin  → pipe[1][0]
```

**Redirection Application:**
```c
int ms_apply_redirs(const t_cmd *command)
{
    for (i = 0; i < command->nreds; i++)
    {
        fd = redir_open_fd(&command->reds[i]);

        if (type == R_IN || type == R_HEREDOC)
            dup2(fd, STDIN_FILENO);   // Redirect input
        else
            dup2(fd, STDOUT_FILENO);  // Redirect output

        close(fd);
    }
}
```

---

### 6. Built-ins (`src/builtins/`)

Commands executed in the shell process itself.

**Why Built-ins Must Run In-Process:**

```c
// ❌ Won't work if forked:
cd /tmp         // Child changes dir, parent unchanged
export VAR=x    // Child's env modified, parent unchanged
exit 42         // Child exits, parent continues

// ✅ Must modify shell's own state:
builtin_cd()     → chdir() affects shell process
builtin_export() → Modifies ms->envp directly
builtin_exit()   → Exits shell process
```

**Built-in Execution Flow:**
```c
int ms_exec_builtin_check(t_ms *ms, t_cmd *cmd)
{
    if (!is_builtin(cmd->argv[0]))
        return 1;  // Not a built-in

    // Save original stdin/stdout
    saved_in  = dup(STDIN_FILENO);
    saved_out = dup(STDOUT_FILENO);

    // Apply redirections (may redirect output)
    ms_apply_redirs(cmd);

    // Execute built-in
    result = run_builtin(argc, cmd->argv, ms);

    // Restore stdin/stdout
    dup2(saved_in,  STDIN_FILENO);
    dup2(saved_out, STDOUT_FILENO);
    close(saved_in);
    close(saved_out);

    return result;
}
```

**Example: `export` Implementation:**
```c
int builtin_export(int argc, char **argv, t_ms *ms)
{
    if (argc == 1)
        return export_print_all(ms);  // No args: print all

    for (i = 1; i < argc; i++)
    {
        // Parse "KEY=value"
        equals_pos = strchr(argv[i], '=');
        key = extract_key(argv[i], equals_pos);
        value = extract_value(equals_pos);

        // Validate and set
        if (!is_valid_key(key))
            return error("not a valid identifier");

        env_variable_set(ms, key, value);
    }
    return 0;
}
```

---

### 7. Environment Management (`src/env/`)

Dynamic environment variable storage.

**Data Structure:**
```c
ms->envp = ["HOME=/home/user", "PATH=/bin:/usr/bin", "USER=john", NULL]
```

**Operations:**

```c
// Get variable value
const char *value = env_value_get(ms, "HOME");
// Searches for "HOME=" prefix, returns "/home/user"

// Set variable
env_variable_set(ms, "MY_VAR", "hello");
// Adds "MY_VAR=hello" to envp (or updates if exists)

// Unset variable
env_variable_unset(ms, "MY_VAR");
// Removes "MY_VAR=hello" from envp, shrinks array
```

**Dynamic Array Management:**
```c
// Setting a variable requires:
1. Check if variable exists → Update in-place
2. If new → Allocate larger array
3. Copy old entries
4. Add new "KEY=value" entry
5. Free old array

// Unsetting requires:
1. Find variable index
2. Allocate smaller array
3. Copy entries except removed one
4. Free old array
```

---

### 8. Signal Handling (`src/signals.c`)

Manages interactive shell signals across different modes.

**Signal Modes:**

1. **Interactive Mode** (waiting for input)
   ```c
   void ms_signals_interactive(void)
   {
       signal(SIGINT, signals_sigint_handler);  // Ctrl-C
       signal(SIGQUIT, SIG_IGN);                // Ctrl-\ ignored
   }

   void signals_sigint_handler(int signo)
   {
       g_sig = SIGINT;                // Set global flag
       write(1, "\n", 1);             // New line
       rl_replace_line("", 0);        // Clear readline buffer
       rl_on_new_line();              // Readline: new prompt
       rl_redisplay();                // Redisplay prompt
   }
   ```

2. **Heredoc Mode**
   ```c
   void ms_signals_heredoc(void)
   {
       signal(SIGINT, signals_heredoc_sigint_handler);
   }

   // Ctrl-C aborts heredoc, returns to prompt
   ```

3. **Execution Mode** (pipeline running)
   ```c
   void ms_signals_ignore(void)
   {
       signal(SIGINT,  SIG_IGN);  // Parent ignores
       signal(SIGQUIT, SIG_IGN);  // Let children handle
   }
   ```

4. **Child Process Mode**
   ```c
   void ms_signals_child(void)
   {
       signal(SIGINT,  SIG_DFL);  // Default: terminate
       signal(SIGQUIT, SIG_DFL);  // Default: terminate + core dump
   }
   ```

**Global Signal Variable:**
```c
volatile sig_atomic_t g_sig = 0;
```
- Only stores signal number (SIGINT, etc.)
- Used to communicate between signal handler and main code
- Checked after readline returns to update `$?`

---

### 9. Heredoc (`src/exec/exec_heredoc.c`)

Implements `<< DELIMITER` functionality.

**Implementation:**
```c
int ms_heredoc_collect(t_ms *ms, const char *delimiter, int *output_fd)
{
    int pipe_fds[2];

    pipe(pipe_fds);                    // Create pipe
    ms_signals_heredoc();              // Enable Ctrl-C handling

    while (1)
    {
        write(1, "> ", 2);             // Heredoc prompt

        // Read line (blocking)
        line = read_line();

        if (g_sig == SIGINT)           // Ctrl-C pressed
        {
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            return -1;                 // Abort
        }

        if (strcmp(line, delimiter) == 0)
            break;                     // End of heredoc

        write(pipe_fds[1], line, strlen(line));
        write(pipe_fds[1], "\n", 1);
    }

    close(pipe_fds[1]);               // Close write end
    *output_fd = pipe_fds[0];         // Return read end
    ms_signals_interactive();          // Restore normal signals

    return 0;
}
```

**Usage in Command:**
```bash
cat << EOF
line1
line2
EOF
        ↓
Command: argv=["cat", NULL]
         reds=[{R_HEREDOC, "EOF", hdoc_fd=3}]

Execution:
  dup2(hdoc_fd, STDIN_FILENO)  // Redirect stdin to pipe
  execve("cat", ...)            // Cat reads from heredoc
```

---

## 🔬 Technical Deep Dive

### Process Management

**Fork-Exec Pattern:**
```c
pid_t pid = fork();

if (pid < 0) {
    perror("fork");           // Fork failed
    return -1;

} else if (pid == 0) {
    // CHILD PROCESS

    // Setup environment
    ms_signals_child();       // Reset signal handlers
    ms_apply_redirs(cmd);     // Apply I/O redirections

    // Execute command
    if (is_builtin(cmd->argv[0]))
        exit(run_builtin(...));
    else {
        path = ms_resolve_path(ms, cmd->argv[0]);
        execve(path, cmd->argv, ms->envp);
        perror("execve");     // Only reaches if exec fails
        exit(127);
    }

} else {
    // PARENT PROCESS

    ms_signals_ignore();      // Ignore signals during wait
    waitpid(pid, &status, 0); // Wait for child
    ms_signals_interactive(); // Re-enable interactive signals

    // Extract exit status
    if (WIFEXITED(status))
        ms->last_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        ms->last_status = 128 + WTERMSIG(status);
}
```

### File Descriptor Management

**Redirection Mechanism:**
```c
// Before: stdin=0, stdout=1, stderr=2

fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// fd = 3

dup2(fd, STDOUT_FILENO);
// Now: stdout (FD 1) points to file.txt
// FD 3 still open (redundant)

close(fd);
// Now: only FD 1 points to file.txt

execve(...);
// Child inherits FD 1 → file.txt
```

**Pipe Setup (3-command pipeline):**
```c
// Create pipes
int pipes[2][2];
pipe(pipes[0]);  // {3, 4}
pipe(pipes[1]);  // {5, 6}

// Child 1 (cmd1)
dup2(pipes[0][1], STDOUT_FILENO);  // stdout → pipe[0] write
close(pipes[0][0]);                 // Close read end
close(pipes[0][1]);                 // Close original write FD
close(pipes[1][0]);                 // Close unused pipe
close(pipes[1][1]);

// Child 2 (cmd2)
dup2(pipes[0][0], STDIN_FILENO);   // stdin  → pipe[0] read
dup2(pipes[1][1], STDOUT_FILENO);  // stdout → pipe[1] write
close(pipes[0][0]);
close(pipes[0][1]);
close(pipes[1][0]);
close(pipes[1][1]);

// Child 3 (cmd3)
dup2(pipes[1][0], STDIN_FILENO);   // stdin  → pipe[1] read
close(pipes[0][0]);
close(pipes[0][1]);
close(pipes[1][0]);
close(pipes[1][1]);

// Parent
close(pipes[0][0]);
close(pipes[0][1]);
close(pipes[1][0]);
close(pipes[1][1]);
```

### Exit Status Codes

| Code | Meaning |
|------|---------|
| `0` | Command succeeded |
| `1` | General error |
| `2` | Misuse of shell builtin |
| `126` | Command found but not executable |
| `127` | Command not found |
| `128 + N` | Terminated by signal N |
| `130` | Ctrl-C (SIGINT = 2, so 128+2) |
| `131` | Ctrl-\ (SIGQUIT = 3, so 128+3) |

**Implementation:**
```c
void ms_exec_handle_signals(int process_status, t_ms *ms)
{
    if (WIFEXITED(process_status))
        ms->last_status = WEXITSTATUS(process_status);

    else if (WIFSIGNALED(process_status))
    {
        signal_num = WTERMSIG(process_status);
        ms->last_status = 128 + signal_num;

        if (signal_num == SIGQUIT)
            ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
    }
}
```

---

## 📝 Examples

### Complex Pipeline Example

```bash
minishell$ cat < input.txt | grep "error" | sort -u | head -5 > errors.txt
```

**Execution Flow:**
1. **Lexer** produces 12 tokens
2. **Parser** creates pipeline with 4 commands
3. **Executor**:
   - Creates 3 pipes
   - Forks 4 children
   - Each child sets up its FDs and executes
   - Parent waits for all children

### Variable Expansion Example

```bash
minishell$ export NAME="John Doe"
minishell$ echo "Hello, $NAME! Status: $?"
Hello, John Doe! Status: 0
```

**Expansion Steps:**
1. `"Hello, $NAME! Status: $?"` is one token (in double quotes)
2. Expander finds `$NAME` → replaces with "John Doe"
3. Expander finds `$?` → replaces with "0"
4. Result: `Hello, John Doe! Status: 0`

---

## 📚 Learning Outcomes

This project provides hands-on experience with:

1. **Systems Programming**
   - Process creation and management (fork, exec, wait)
   - Signal handling and async-safe programming
   - File descriptor manipulation

2. **Compiler Design Basics**
   - Lexical analysis (tokenization)
   - Syntax analysis (parsing)
   - Abstract Syntax Trees (command structures)

3. **Unix Internals**
   - How shells work under the hood
   - Environment variable management
   - Terminal I/O and control

4. **Software Engineering**
   - Modular code organization
   - Memory management in C
   - Error handling strategies

---

## 📖 Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [The Linux Programming Interface](https://man7.org/tlpi/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

---

## 👥 Authors

- **ealshari** - 42 Amman
- **tsaeed** - 42 Amman

---

## 📜 License

This project is part of the 42 School curriculum.
