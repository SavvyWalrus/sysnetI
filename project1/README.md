# **MyShell: A Custom Shell Implementation**

## **Purpose**

The purpose of this project is to develop a simplified custom shell called `myshell`, which allows users to enter commands, execute processes, and handle input/output redirection and background execution. This shell is built to demonstrate fundamental operating system concepts, including process creation, execution, and synchronization.

The shell parses user commands, creates new processes, and manages process execution using system calls such as `fork()`, `execvp()`, and `waitpid()`. Additionally, it prevents zombie processes by ensuring all child processes are properly terminated.

---

## **Features**

- **Command Parsing**: The shell parses user input into commands and arguments.
- **Foreground and Background Execution**: The shell can execute commands either in the foreground (the shell waits for the command to finish) or in the background (the shell remains responsive while the command executes).
- **Input and Output Redirection**: The shell supports input (`<`) and output (`>`) redirection, allowing commands to read from and write to files.
- **Debug Mode**: The shell can be run in debug mode by passing the `-Debug` option, which prints the parsed command structure for easier debugging.


## **Compiling and Running the Program**
**To compile and run the shell:**

- **Run the following command to compile in bash:**

"make"

- **To start the shell:**

"./myshell"

- **To start the shell in debug mode:**

"./myshell -Debug"


## **Files**
 - myshell.cpp: Implements the main shell functionality (command parsing, process handling, etc.).
 - parse.cpp: Handles the parsing of command-line input into tokens (for use in process execution).
 - param.cpp: Implements the Param class, which stores parsed input (arguments, redirection files, etc.).
 - param.hpp: Defines the Param class and its methods.
 - Makefile: Builds the project and produces the myshell executable.
 - README: Describes the purpose, usage, and details of the shell.