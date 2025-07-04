
# Unix Shell

## Description

This project presents a thorough recreation of a Unix-like shell, commonly referred to as a command-line interface or terminal. It faithfully mimics the functionality and visual aspects of conventional shells, while also enhancing their capabilities through various added features.

## Display

The shell prompt mimics the structure of a Unix-style shell, offering an intuitive interface for users. It manifests as `<username@system_name:curr_dir>`, continuously adjusting to showcase the present working directory.

## User-Implemented Commands

### Hop (`cd`)

The `hop` command represents an advanced iteration of the `cd` command in the Bash shell, providing an array of flags and accommodating both absolute and relative paths. This command boasts the following flag functionalities:

- `~`: Effortlessly traverse to the user's home directory.
- `..`: Ascend to the parent directory.
- `.`: Remain within the present directory.
- `-`: Conveniently return to the preceding directory.
[ChatGpt Prompt Links](https://chatgpt.com/share/81265304-25a0-4d1a-b08b-b1d9430a9b67)

### Reveal (`ls`)

The `reveal` command provides a comprehensive listing of files and directories within a designated directory or directories, sorted alphabetically. By default, it omits hidden files from the display. The `reveal` command offers the following options:

- `-l`: Presents additional details pertaining to files and directories.
- `-a`: Exhibits all files, encompassing hidden ones.
[ChatGpt Prompt Link](https://chatgpt.com/share/2a1fc4c3-fa2f-442e-bc76-e466033843b6)

### Seek (`find`)

The `seek` command is a versatile tool for locating files or directories, whether you want to search within a specific target directory or within the current working directory if none is specified. It provides a result list containing relative paths to matching files (displayed in green) and directories (displayed in blue), with each entry separated by newline characters.

Here are the available options:

- `-d`: Exclusively search for directories, disregarding any matching file names.
- `-f`: Exclusively search for files, disregarding any matching directory names.
- `-e`: When a single file or directory with the specified name is found:
  - If only one file (and no directories) is located, the command prints the result.
  - If only one directory (and no files) is discovered, it alters the current working directory to match it.
  - Otherwise, the flag has no impact. The `-e` flag can be used in conjunction with both the `-d` and `-f` flags.

### Log Commands (`history`)

The `log` command offers users a retrospective glimpse into their past interactions with the shell, displaying a detailed history of previously executed shell commands, their respective outcomes, and any encountered error messages. This functionality aids users in monitoring and resolving issues related to their shell interactions.

Flags and Arguments for `log`:

- No argument: Displays the most recent 15 commands executed by the user.
- `Purge`: Erases the entire command history.
- `Execute <position>`: Executes the command located at the specified position within the `log` history, ordered from the latest to the oldest entries.
[ChatGpt Prompt Link](https://chatgpt.com/share/4cb22548-c343-4c25-9397-ffa9756d98b5)

### Foreground and Background Processes

This versatile shell allows you to execute processes in either the foreground or the background. Here are two illustrative scenarios:

- When you execute a command, such as `vi`, in the foreground, the shell will wait for its execution to finish before accepting any further input.
- Alternatively, by appending `&` to the end of a command, it becomes a background process, permitting you to seamlessly continue entering additional commands.

### Proclore

The `proclore` command helps us to obtain information of a process such as :-

- Process ID
- Process Status (R/R+/S/S+)
- Process Group
- Virtual Memory
- Executable path process
[ChatGpt Prompt Link](https://chatgpt.com/share/9f8cd3b0-3c0b-4f74-a5fe-3135f21f6454)

### Output and Input Redirection

The shell allows you to redirect the output of commands to files and read input data from files. Error handling is in place, including checks for non-existent input files. Examples include:

- Output redirection: `diff file1.txt file2.txt > output.txt`
- Input redirection: `sort < lines.txt`
- Input-Output redirection: `sort < lines.txt > sorted-lines.txt`

### Pipelines

The shell facilitates the creation of pipelines by utilizing the | symbol, allowing for the sequential execution of multiple commands. It supports an unrestricted number of pipes, as demonstrated in the following examples:

- Utilizing two commands: `more file.txt | wc`
- Employing three commands: `grep "new" temp.txt | cat somefile.txt | wc`

### iMan

Introducing the iMan command, a valuable enhancement to this shell that empowers users to effortlessly access manual pages encompassing a wide array of commands and utilities. This feature offers comprehensive insights into command utilization, available options, and practical examples, facilitating a seamless and efficient shell navigation experience.
[ChatGpt Prompt Link](https://chatgpt.com/c/66e13ae2-e7a4-8006-93ba-5511d246c416)

### neonate

The "neonate" command represents a robust functionality that streamlines repetitive actions, enabling users to devise and run personalized scripts within the shell environment. This feature elevates the shell's scripting potential, granting users the ability to automate intricate processes effortlessly.
[Claude Ai Prompt Link](https://claude.ai/chat/86507a83-87a7-470e-9db7-a32716feba6e)


### myshrc

The "myshrc" feature tends to beteer the shell experience by providing us the opportunity create aliases for different commands in a bash file and then run those commands through those aliases. 
For example, `home = hop ~` Here `home` command can be used to return to the home directory.
[Claude Ai Prompt Link](https://claude.ai/chat/810a59af-0c0c-415b-86b0-e204655e89aa)

### activities

Activities command helps to get a detail about all the process being run or runned in the past at the present session.
[ChatGpt Prompt Link](https://chatgpt.com/c/66daab8b-4618-8006-b238-9f7af0ebab8c)

### Additional Commands

Here are some essential keyboard shortcuts for controlling processes in a shell environment:

- "CTRL-Z": This shortcut allows you to transition the current job's status to "stopped" and moves it to the background.

- "CTRL+D": Use this key combination to exit the shell gracefully.

- "CTRL+C": This key combination emulates the functionality of the bash shell and can be employed to terminate a running process.




# Assumptions

1. Change in directories in format `hop .. X` will first revert back to the parent directory and then the target directory. For direct changes use `hop ../X` format.
2. Separation of Commands with the help of `&` in not supported.
3. Any command or (multiple commands) having `log` present in it will not be a stored in the log.
4. Any foreground process will also display the time taken by the process to be finished and the printing might not be in any definite pattern.
5. For exiting the custom C Shell hit `CTRL + D`.
6. Error messages are displayed but are not highlighted.
7. For applying any kind of `reveal` command in the current file, it is suggested to use in the format `reveal -la .`.
8. Activities command handles five states of a process i.e. `Running, Sleeping, Stopped, Zombie, Unknown`.
9. myshrc has been done only for the aliases part.
10. Any process relating to piping or input redirection would not print the time taken by the process.
11. If there is an invalid command for iMan. It just prints that there is no match. 

