# Virtual File System

Welcome to the Virtual File System. This application simulates a basic file system environment, allowing users to create, read, write, and delete files and directories within a simulated environment.

## What does it do?

The simulated file system offers the following functionalities:

- 📁 Create and navigate directories
- 📄 Create and edit files
- 📝 Write content to files
- 📖 Read file contents
- 🗑️ Delete files and directories
- 📋 List directory contents

## Why I made it

I wanted to create a simple, safe environment for practicing and understanding basic file system operations. This project provides a hands-on way to learn about file system structures and commands without the risk of affecting the actual file system. It also gave me an opportunity to work with tree-like data structures and command parsing in C++.

## How to Use

To use this Virtual File System, follow these steps:

1. Make sure you have a C++ compiler installed (like g++).
2. Clone this repository.
3. Build the project by executing the following command in your terminal:
   ```sh
   make all
   ```
4. Run the Virtual File System by executing:
   ```sh
   make run
   ```
5. You'll see a prompt `>` where you can enter commands. Available commands are:

   - `mkdir <directory_name>`: Create a new directory
   - `cd <path>`: Change current directory
   - `ls [path]`: List contents of a directory
   - `touch <filename>`: Create a new empty file
   - `write <filename> <content>`: Write content to a file
   - `cat <filename>`: Display the contents of a file
   - `rm <path>`: Remove a file or directory
   - `exit`: Exit the program

6. The program will provide feedback for each operation, including error messages for invalid operations.
