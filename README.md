# DOS Shell and Console Notepad

This project implements a DOS/command window shell with various commands for file and directory management. Upon execution, the program displays author information and a virtual drive prompt (`V:\>`), awaiting user input. Commands include file attribute display, directory navigation, file operations, text editing.

## Features

- **Shell Commands**: Supports various commands for file and directory management.
- **File Operations**: Perform operations like copying, moving, renaming, deleting, and creating files.
- **Directory Navigation**: Navigate directories, display directory structure, and manage virtual directories.
- **Text Editing**: Edit text files with features like insert, delete, backspace, append, and undo/redo.
- **Printing**: Manage print queues with priority-based printing and virtual printing functionality.

## Usage

1. **CD**: Navigate directories using `CD` commands:
   - `CD <directory>`: Change to specified directory.
   - `CD.`: Print working directory.
   - `CD..`: Move to previous directory.
   - `CD\`: Change to root directory.

2. **EDIT**: Edit text files with editing capabilities like insert, delete, and undo/redo.

3. **PRINT**: Manage print queues with priority-based printing and virtual printing functionality.

4. **TREE**: Display the complete directory structure in a tree-like format.

5. **HELP**: Get help information for all available commands.

## Notepad 

Part 2 of the project involves implementing a text editor similar to Vim, allowing file creation and editing using linked lists. The entire document is represented as a linked list of characters, enabling features like insertion, deletion, navigation, and undo/redo operations.

## Built with Linked List and Trees

The project is built using linked lists for text editing functionalities in the Notepad section. Each line of the document is represented as a linked list of characters, enabling efficient editing operations.

Additionally, the directory structure and file system functionalities are implemented using tree data structures. Directories and files are organized hierarchically, mimicking the structure of a file system.

## Running the Program

To run the program, follow these steps:

1. Clone the repository: `git clone <repository-url>`
2. Navigate to the project directory in the command prompt.
3. Compile the C++ program using a C++ compiler.
4. Run the compiled program in the command prompt.
