#pragma once
#include "Tree.h"
using namespace std;

class Shell
{
public:
	DOSTree tree;
	string promptI;
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
			cout << endl;
			commandSize = command.size();
			if (command.substr(0, 7) == "ATTRIB " || command.substr(0, 7) == "attrib ")
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

			else if (command.substr(0, 6) == "MKDIR " || command.substr(0, 6) == "mkdir ")
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
				rmdir(command.substr(6, commandSize - 1));
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
					create(command.substr(6, commandSize - 1));
				}
			}

			else if (command.substr(0, 3) == "PWD" || command.substr(0, 3) == "pwd")
			{
				print();
			}

			else if (command.substr(0, 3) == "DEL" || command.substr(0, 3) == "del")
			{
				if (commandSize > 3)
				{
					del(command.substr(3,commandSize-1));
				}
			}

			else
			{
				cout << "There is no such command" << endl;
			}
		}
	}

	void attrib(string filename) // Write code for attrib after create command
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
		Folder* curr = tree.currentFolder;
		for (list<Folder*>::iterator it = curr->subDirectories.begin(); it != curr->subDirectories.end(); it++)
		{
			cout << (*it)->retDate() << "    " << (*it)->retTime() << "\t <DIR> \t" << (*it)->name << endl;
		}

		for (list<File*>::iterator it = curr->files.begin(); it != curr->files.end(); it++)
		{
			cout << (*it)->retDate() << "    " << (*it)->retTime() << "\t " << (*it)->currentState.size << "\t" << (*it)->name << endl;
		}
	}

	void format()
	{
		DOSTree newTree;
		tree = newTree;
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

	void notepad(File* file)
	{
		system("cls");
		file->edit();
	}
};