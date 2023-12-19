#pragma once
#include "Tree.h"
#include <queue>
using namespace std;

class Shell
{
public:
	DOSTree tree;
	string promptI;
	priority_queue<File*> printingPriorityQ;
	queue<File*> printQ;
	Shell()
	{
		promptI = ":\\>";
	}

	void runEditor()
	{
		File newFile("untitled.txt");
		newFile.edit();		
	}

	void run()
	{
		cout << "        Mohammad Abdullah        ||        2022-CS-155        ||        Data Structures and Algorithms" << endl;
		bool exit = false;
		string command;
		int commandSize = 0;
		while (!exit)
		{
			print();

			getline(cin, command);
			commandSize = command.size();
			if (command.substr(0, 7) == "ATTRIB " || command.substr(0, 7) == "attrib ") // 1
			{
				if (commandSize > 7)
				{
					attrib(command.substr(7, commandSize - 1));
				}

				else
				{
					cout << "Enter the filename." << endl;
				}
			}

			else if (command.substr(0, 6) == "MKDIR " || command.substr(0, 6) == "mkdir ") // 2
			{
				if (commandSize > 6)
				{
					mkdir(command.substr(6, commandSize - 1));
				}

				else
				{
					cout << "Enter the name of folder" << endl;
				}
			}

			else if (command.substr(0, 3) == "DIR" || command.substr(0, 3) == "dir")
			{
				dir();
			}

			else if (command.substr(0, 2) == "CD." || command.substr(0, 2) == "cd.")
			{
				print();
			}

			else if (command.substr(0, 4) == "CD.." || command.substr(0, 4) == "cd..")
			{
				cdPrev();
			}

			else if (command.substr(0, 3) == "CD\\" || command.substr(0, 3) == "cd\\")
			{
				cdRoot();
			}

			else if ((command.substr(0, 3) == "CD " || command.substr(0, 3) == "cd ") && (command.substr(0, 4) != "cd.." || command.substr(0, 4) != "CD.." || command.substr(0, 3) != "CD\\" || command.substr(0, 3) != "cd\\"))
			{
				if (commandSize > 3)
				{
					cd(command.substr(3, commandSize - 1));
				}

				else
				{
					cout << "Enter the name of directory." << endl;
				}
			}

			else if (command.substr(0, 6) == "FORMAT" || command.substr(0, 6) == "format")
			{
				format();
			}

			else if (command.substr(0, 7) == "PROMPT " || command.substr(0, 7) == "prompt ")
			{
				prompt(command.substr(7, commandSize-1));
			}

			else if (command.substr(0, 6) == "RMDIR " || command.substr(0, 6) == "rmdir ")
			{
				if (commandSize > 6)
				{
					rmdir(command.substr(6, commandSize - 1));
				}

				else
				{
					cout << "Enter the name of a directory." << endl;
				}
			}

			else if (command.substr(0, 3) == "VER" || command.substr(0, 3) == "ver")
			{
				ver();
			}

			else if (command.substr(0, 4) == "TREE" || command.substr(0, 4) == "tree")
			{
				treeCommand();
			}

			else if (command.substr(0, 4) == "EXIT" || command.substr(0, 4) == "exit")
			{
				break;
			}

			else if (command.substr(0, 6) == "CREATE" || command.substr(0, 6) == "create")
			{
				if (commandSize > 6)
				{
					create(command.substr(7, commandSize - 1));
				}
			}

			else if (command.substr(0, 3) == "PWD" || command.substr(0, 3) == "pwd")
			{
				cout << tree.currentFolder->name << endl;
			}

			else if (command.substr(0, 3) == "DEL" || command.substr(0, 3) == "del")
			{
				if (commandSize > 3)
				{
					del(command.substr(3,commandSize-1));
				}
			}

			else if (command.substr(0, 4) == "EDIT" || command.substr(0, 4) == "edit")
			{
				if (commandSize > 4)
				{
					edit(command.substr(5, commandSize - 1));
				}
			}

			else if (command.substr(0, 5) == "FINDF" || command.substr(0, 5) == "findf")
			{
				if (commandSize > 6)
				{
					command = command.substr(8, commandSize);
					int index = command.find(' ');
					string source = command.substr(0, index);
					string input = command.substr(source.length() + 2, commandSize - 1);
					findf(source, input);
				}
			}

			else if (command.substr(0, 7) == "FINDSTR" || command.substr(0, 7) == "findstr")
			{
				if (commandSize > 8)
				{
					string input = command.substr(9, commandSize - 1);
					findstr(input);
				}
			}

			else if (command.substr(0, 4) == "FIND" || command.substr(0, 4) == "find")
			{
				if (commandSize > 4)
				{
					find(command.substr(4, commandSize - 1));
				}
			}

			else if (command.substr(0, 4) == "HELP" || command.substr(0, 4) == "help")
			{
				if (commandSize > 4)
				{
					help(command.substr(4, commandSize - 1));
				}
			}

			else if (command.substr(0, 7) == "CONVERT" || command.substr(0, 7) == "convert")
			{
				if (commandSize > 9)
				{
					convert(parse(command.substr(8, commandSize - 1), 1), parse(command.substr(8, commandSize - 1), 2));
				}
			}

			else if (command.substr(0, 6) == "RENAME" || command.substr(0, 6) == "rename")
			{
				if (commandSize > 9)
				{
					renameFile(parse(command.substr(7, commandSize - 1), 1), parse(command.substr(7, commandSize - 1), 2));
				}
			}

			else if (command.substr(0, 4) == "COPY" || command.substr(0, 4) == "copy") 
			{
				if (commandSize > 6)
				{
					command = command.substr(7, commandSize);
					int index = command.find(' ');
					string source = command.substr(0, index);
					string destination = command.substr(source.length() + 3, commandSize);
					copy(source, destination);
				}
			}

			else if (command.substr(0, 4) == "MOVE" || command.substr(0, 4) == "move")
			{
				if (commandSize > 6)
				{
					command = command.substr(7, commandSize);
					int index = command.find(' ');
					string source = command.substr(0, index);
					string destination = command.substr(source.length() + 3, commandSize);
					move(source, destination);
				}
			}

			else if (command.substr(0, 6) == "PPRINT" || command.substr(0, 6) == "pprint")
			{
				if (commandSize >= 7)
				{
					pprint(command.substr(7, commandSize));
				}
			}

			else if (command.substr(0, 5) == "PRINT" || command.substr(0, 5) == "print")
			{
				if (commandSize >= 6)
				{
					print(command.substr(6, commandSize));
				}
			}

			else if (command.substr(0, 6) == "PQUEUE" || command.substr(0, 6) == "pqueue")
			{
				if (commandSize == 6)
				{
					pqueue();
				}
			}

			else if (command.substr(0, 5) == "QUEUE" || command.substr(0, 5) == "queue")
			{
				if (commandSize == 5)
				{
					queueb();
				}
			}

			else
			{
				cout << "There is no such command" << endl;
			}
		}
	}

	void attrib(string filename) 
	{
		File* curr = tree.currentFolder->searchAndReturnFile(filename);
		if (curr != nullptr)
		{
			cout << "\t" << curr->extension << endl;
		}
	}

	void prompt(string input)
	{
		if (input != "")
		{
			promptI = input;
		}

		else
		{
			cout << "Enter a prompt." << endl;
		}
	}

	void mkdir(string name)
	{
		if (name != "")
		{
			bool flag = tree.currentFolder->searchFolder(name);
			if (flag)
			{
				cout << "There already exists a folder with that name." << endl;
			}

			else
			{
				tree.currentFolder->insertFolder(name);
			}
		}

		else
		{
			tree.currentFolder->insertFolder();

		}
	}

	void del(string filename)
	{
		File* curr = tree.currentFolder->searchAndReturnFile(filename);
		if (curr != nullptr)
		{
			tree.currentFolder->removeFile(filename);
		}

		else
		{
			cout << "There is no file with such a name." << endl;
		}
	}

	void find(string filename)
	{
		File* file = tree.currentFolder->searchAndReturnFile(filename);
		if (file != nullptr)
		{
			cout << file->retDate() << "\t" << file->retTime() << "\t" << file->name << file->extension << "\t" << file->currentState.size << endl;
		}

		else
		{
			cout << "No such file exists in current directory." << endl;
		}
	}

	void edit(string filename)
	{
		File* file = tree.currentFolder->searchAndReturnFile(filename);
		if (file != nullptr)
		{
			file->edit();
			system("cls");
		}

		else
		{
			cout << "There is no file with such a name." << endl;
		}
	}

	void rmdir(string name)
	{
		if (name != "")
		{
			tree.currentFolder->removeFolder(name);
		}

		else
		{
			cout << "Enter a valid name" << endl;
		}
	}

	void create(string name)
	{
		if (name != "")
		{
			tree.currentFolder->createFiles(name);
			string filenameWithoutExt;
			int size = name.size();
			for (int i = 0; i < size; i++)
			{
				if (name[i] != '.')
				{
					filenameWithoutExt += name[i];
				}

				else
				{
					break;
				}
			}
			File* currFile = tree.currentFolder->searchAndReturnFile(filenameWithoutExt);
			system("cls");
			currFile->edit();
			system("cls");
		}

		else
		{
			tree.currentFolder->createFiles();
		}
	}

	void cdPrev()
	{
		if (tree.currentFolder->parent != nullptr)
		{
			tree.currentFolder = tree.currentFolder->parent;
		}
	}

	void cdRoot()
	{
		if (tree.root != nullptr)
		{
			tree.currentFolder = tree.root;
		}
	}

	void copy(string source, string destination)
	{
		File* fileToCopy = new File();
		Folder* currentDir = tree.root;
		string f;
		while (source.length() > 0)
		{
			f = source.substr(0, source.find('\\'));
			source = source.substr(f.length() + 1, source.length());
			if (source.length() != 0)
			{
				currentDir = currentDir->searchAndReturnFolder(f);
			}

			if (currentDir == nullptr)
			{
				cout << "The path was not found." << endl;
				return;
			}
		}
		int size = f.size();
		string temp;
		for (int i = 0; i < size; i++)
		{
			if (f[i] == '.')
			{
				break;
			}
			temp += f[i];
		}
		f = temp;
		fileToCopy = currentDir->searchAndReturnFile(f);

		currentDir = tree.root;
		
		while (destination.length() > 0)
		{
			f = destination.substr(0, destination.find('\\'));
			destination = destination.substr(f.length() + 1, destination.length());
			currentDir = currentDir->searchAndReturnFolder(f);
			if (currentDir == nullptr)
			{
				cout << "The path was not found." << endl;
				return;
			}
		}
			currentDir->files.push_back(fileToCopy);
		
	}

	void renameFile(string prev, string next)
	{
		File* curr = tree.currentFolder->searchAndReturnFile(prev);
		File* isNextUsed = tree.currentFolder->searchAndReturnFile(next);
		if (curr != nullptr && isNextUsed == nullptr)
		{
			curr->name = next;
		}

		else if (curr == nullptr)
		{
			cout << "There is no file with such a name." << endl;
		}

		else
		{
			cout << "The new name has already been used." << endl;
		}
	}

	void cd(string foldername)
	{
		if (foldername != "")
		{
			Folder* folder = tree.currentFolder->searchAndReturnFolder(foldername);
			tree.currentFolder = folder;
		}
	}

	void dir()
	{
		int totalFilesSize = 0;
		int filesCount = 0;
		int foldersCount = 0;
		Folder* curr = tree.currentFolder;
		for (list<Folder*>::iterator it = curr->subDirectories.begin(); it != curr->subDirectories.end(); it++)
		{
			cout << (*it)->retDate() << "    " << (*it)->retTime() << "\t <DIR> \t" << (*it)->name << endl;
			foldersCount++;
		}

		for (list<File*>::iterator it = curr->files.begin(); it != curr->files.end(); it++)
		{
			cout << (*it)->retDate() << "    " << (*it)->retTime() << "\t " << (*it)->currentState.size << " bytes" << "\t" << (*it)->name << (*it)->extension << endl;
			filesCount++;
			totalFilesSize += (*it)->currentState.size;
		}
		cout << endl;
		cout << "\t     \t\t " << totalFilesSize << "bytes" << endl;
		cout << "\t    \t" << foldersCount << " sub-directories \t\t" << filesCount << " files" << endl;
	}

	void format()
	{
		DOSTree newTree;
		tree = newTree;
	}

	void move(string source, string destination)
	{
		File* fileToMove = new File();
		Folder* currentDir = tree.root;
		string f;
		while (source.length() > 0)
		{
			f = source.substr(0, source.find('\\'));
			source = source.substr(f.length() + 1, source.length());
			if (source.length() != 0)
			{
				currentDir = currentDir->searchAndReturnFolder(f);
			}

			if (currentDir == nullptr)
			{
				cout << "The path was not found." << endl;
				return;
			}
		}
		int size = f.size();
		string temp;
		for (int i = 0; i < size; i++)
		{
			if (f[i] == '.')
			{
				break;
			}
			temp += f[i];
		}
		f = temp;
		fileToMove = currentDir->searchAndReturnFile(f);
		currentDir->removeFile(f);
		currentDir = tree.root;

		while (destination.length() > 0)
		{
			f = destination.substr(0, destination.find('\\'));
			destination = destination.substr(f.length() + 1, destination.length());
			currentDir = currentDir->searchAndReturnFolder(f);
			if (currentDir == nullptr)
			{
				cout << "The path was not found." << endl;
				return;
			}
		}
		currentDir->files.push_back(fileToMove);

	}

	void ver()
	{
		cout << "Mohammad Abdullah DOS Shell [Version 11.2.193]" << endl;
	}

	void treeCommand()
	{
		tree.printTree();
	}

	void print()
	{
		if (tree.currentFolder->name == "V")
		{
			cout << "V" << promptI;
		}

		else
		{
			cout << tree.currentFolder->path << promptI;
		}
	}

	void help(string command)
	{
		if (command == "ATTRIB" || command == "attrib")
		{
			cout << "Displays file (name provided as input) attributes" << endl;
			cout << "Syntax: ATTRIB filename.extension" << endl;
		}

		else if (command == "CD" || command == "cd")
		{
			cout << "Changes the current directory to its subdirectory (name provided as input)" << endl;
			cout << "Syntax: CD subdirectory" << endl;
		}

		else if (command == "CD." || command == "cd.")
		{
			cout << "Prints working directory (i.e. your current directory in your tree structure" << endl;
			cout << "Syntax: CD." << endl;
		}

		else if (command == "CD.." || command == "cd..")
		{
			cout << "Change directory to previous directory" << endl;
			cout << "Syntax: CD.." << endl;
		}

		else if (command == "CD\\" || command == "cd\\")
		{
			cout << "Changes directory to root directory (i.e. V:\\>)" << endl;
			cout << "Syntax: CD\\" << endl;
		}

		else if (command == "CONVERT" || command == "convert")
		{
			cout << "Asks two types and converts extension of all files of one type to another type" << endl;
			cout << "Syntax: CONVERT CURRENT.ext SUBSTITUTED.ext" << endl;
		}

		else if (command == "COPY" || command == "copy")
		{
			cout << "Copies one file in the current directory to another location (directory)" << endl;
			cout << "Syntax: COPY SOURCE DESTINATION" << endl;
			cout << "SOURCE: V\\SUBDIRECTORIES\\FILENAME.EXT\\" << endl;
			cout << "DESTINATION: V\\SUBDIRECTORIES\\" << endl;
		}

		else if (command == "CREATE" || command == "create")
		{
			cout << "Creates a file with the name provided and allows the user to enter contents of the file." << endl;
			cout << "Syntax: CREATE FILENAME" << endl;
		}

		else if (command == "DEL" || command == "del")
		{
			cout << "Delete a file whose name is provided in input." << endl;
			cout << "Syntax: DEL FILENAME" << endl;
		}

		else if (command == "DIR" || command == "dir")
		{
			cout << "Displays a list of files and subdirectories in a directory." << endl;
			cout << "Syntax: DIR" << endl;
		}

		else if (command == "EDIT" || command == "edit")
		{
			cout << "Opens a file and allows the user to edit and save the contents ofthe file." << endl;
			cout << "Syntax: EDIT FILENAME" << endl;
		}
		
		else if (command == "EXIT" || command == "exit")
		{
			cout << "Quits the program." << endl;
			cout << "Syntax: EXIT" << endl;
		}

		else if (command == "FIND" || command == "find")
		{
			cout << "Searches for a file in your current virtual directory whose name is provided as input." << endl;
			cout << "Syntax: FIND FILENAME" << endl;
		}

		else if (command == "FINDF" || command == "findf")
		{
			cout << "Searches for a text string in the currently open file or the file whose name is provided as input." << endl;
			cout << "Syntax: FINDF string" << endl;
		}

		else if (command == "FINDSTR" || command == "findstr")
		{
			cout << "Searches for strings in all files of your current virtual directory, prints names of files with the string" << endl;
			cout << "Syntax: FINDSTR FILENAME" << endl;
		}

		else if (command == "FORMAT" || command == "FORMAT")
		{
			cout << "Formats the current virtual directory i.e. empties the current directory and all its subdirectories" << endl;
			cout << "Syntax: FORMAT" << endl;
		}

		else if (command == "LOADTREE" || command == "loadtree")
		{
			cout << "Load a given tree in your tree structure." << endl;
			cout << "Syntax: loadtree FILENAME" << endl;
		}

		else if (command == "MKDIR" || command == "mkdir")
		{
			cout << "Creates a virtual directory." << endl;
			cout << "Syntax: MKDIR FOLDERNAME" << endl;
		}

		else if (command == "MOVE" || command == "move")
		{
			cout << "Moves one file (whose name is provided as input) from one directory to another directory." << endl;
			cout << "Syntax: MOVE SOURCE DESTINATION" << endl;
			cout << "SOURCE: V\\SUBDIRECTORIES\\FILENAME.EXT\\" << endl;
			cout << "DESTINATION: V\\SUBDIRECTORIES\\" << endl;
		}

		else if (command == "PPRINT" || command == "pprint")
		{
			cout << "Adds a text file to the priority based print queue, and displays the current priority queue. " << endl;
			cout << "Syntax: PPRINT" << endl;
		}

		else if (command == "PROMPT" || command == "prompt")
		{
			cout << "Changes the Windows command prompt (for example from V:\> to V$)." << endl;
			cout << "Syntax: PROMPT string" << endl;
		}

		else if (command == "PRINT" || command == "print")
		{
			cout << "Adds a text file to the print queue, and displays the current queue." << endl;
			cout << "Syntax: PRINT FILENAME" << endl;
		}

		else if (command == "PQUEUE" || command == "pqueue")
		{
			cout << "Shows current state of the priority based print queue, with time left for each element" << endl;
			cout << "Syntax: PQUEUE" << endl;
		}

		else if (command == "PWD" || command == "pwd")
		{
			cout << "Prints working directory." << endl;
			cout << "Syntax: PWD" << endl;
		}

		else if (command == "QUEUE" || command == "queue")
		{
			cout << "Shows current state of the print queue, with time left for each element." << endl;
			cout << "Syntax: QUEUE" << endl;
		}

		else if (command == "RENAME" || command == "rename")
		{
			cout << "Renames a file whose current and new name is provided as input." << endl;
			cout << "Syntax: RENAME PREVIOUS NEXT" << endl;
		}

		else if (command == "RMDIR" || command == "rmdir")
		{
			cout << "Removes a directory along with its contents." << endl;
			cout << "Syntax: RMDIR FOLDERNAME" << endl;
		}

		else if (command == "SAVE" || command == "save")
		{
			cout << "Saves the currently open file to disk." << endl;
			cout << "Syntax: SAVE" << endl;
		}

		else if (command == "TREE" || command == "tree")
		{
			cout << "Displays the complete directory structure." << endl;
			cout << "Syntax: TREE" << endl;
		}

		else if (command == "VER" || command == "ver")
		{
			cout << "Displays the version of your program." << endl;
			cout << "Syntax: VER" << endl;
		}

		else
		{
			cout << "No such command exists in this version of DOS." << endl;
		}
	}
	
	string parse(string line, int idx)
	{
		int commaCount = 1;
		string price;
		int len = line.length();
		for (int x = 0; x < len; x++)
		{
			if (line[x] == ' ')
			{
				commaCount++;
			}
			else if (commaCount == idx)
			{
				price = price + line[x];
			}
		}
		idx = 0;
		return price;
	}

	void convert(string prev, string next)
	{
		for (list<File*>::iterator it = tree.currentFolder->files.begin(); it != tree.currentFolder->files.end(); it++)
		{
			if ((*it)->extension == prev)
			{
				(*it)->extension = next;
			}
		}
	}

	void findf(string source, string str)
	{
		File* file = new File();
		Folder* currentDir = tree.root;
		string f;
		while (source.length() > 0)
		{
			f = source.substr(0, source.find('\\'));
			source = source.substr(f.length() + 1, source.length());
			if (source.length() != 0)
			{
				currentDir = currentDir->searchAndReturnFolder(f);
			}

			if (currentDir == nullptr)
			{
				cout << "The path was not found." << endl;
				return;
			}
		}
		int size = f.size();
		string temp;
		for (int i = 0; i < size; i++)
		{
			if (f[i] == '.')
			{
				break;
			}
			temp += f[i];
		}
		f = temp;
		file = currentDir->searchAndReturnFile(f);
		str = str.substr(0, str.find('\"'));

		bool flag = file->ifStringExists(str);
		if (flag)
		{
			cout << "This string exists in the file" << endl;
		}

		else
		{
			cout << "This string does not exists in the file" << endl;
		}
	}

	void findstr(string input)
	{
		int i = 0;
		input = input.substr(0, input.find('\"'));

		for (list<File*>::iterator it = tree.currentFolder->files.begin(); it != tree.currentFolder->files.end(); it++)
		{
			if ((*it)->ifStringExists(input))
			{
				i++;
				cout << "\t\t" << i << ".\t" << (*it)->name << (*it)->extension << endl;
			}
		}

		if (i == 0)
		{
			cout << "\t\t\t The input string was not found in any file." << endl;
		}

		else
		{
			cout << "\t\t\t" << "The input string was found in " << i << " files." << endl;
		}
	}

	void pprint(string filename)
	{
		if (filename != "")
		{
			int size = filename.size();
			string temp;
			for (int i = 0; i < size; i++)
			{
				if (filename[i] == '.')
				{
					break;
				}
				temp += filename[i];
			}
			filename = temp;
			File* file = tree.currentFolder->searchAndReturnFile(filename);
			printingPriorityQ.push(file);
			cout << filename << " has been pushed to the printing priority queue." << endl;
		}
	}

	void print(string filename)
	{
		if (filename != "")
		{
			int size = filename.size();
			string temp;
			for (int i = 0; i < size; i++)
			{
				if (filename[i] == '.')
				{
					break;
				}
				temp += filename[i];
			}
			filename = temp;
			File* file = tree.currentFolder->searchAndReturnFile(filename);
			printQ.push(file);
			cout << filename << " has been pushed to the printing queue." << endl;
		}
	}

	void queueb()
	{
		if (!printQ.empty())
		{
			queue<File*> pq = printQ;

			int i = 0;
			while (!pq.empty())
			{
				i++;
				cout << "\t" << i << ". \t" << pq.front()->name << pq.front()->extension << endl;
				pq.pop();
			}
			cout << i << " number of files are in the queue." << endl;
		}
	}

	void pqueue()
	{
		if (!printingPriorityQ.empty())
		{
			priority_queue<File*> pq = printingPriorityQ;

			int i = 0;
			while (!pq.empty())
			{
				i++;
				cout << "\t" << i << ". \t" << pq.top()->name << pq.top()->extension << endl;
				pq.pop();
			}
			cout << i << " number of files are in the priority queue." << endl;
		}
	}
};