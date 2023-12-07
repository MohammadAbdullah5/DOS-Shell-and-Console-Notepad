#pragma once
#include "Tree.h"
using namespace std;

class Shell
{
public:
	DOSTree tree;
	Shell(){}

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
			if (command.substr(0, 6) == "ATTRIB" || command.substr(0, 6) == "attrib")
			{
				attrib(command.substr(8, commandSize - 1));
			}

			else if (command.substr(0, 5) == "MKDIR" || command.substr(0, 5) == "mkdir")
			{
				mkdir(command.substr(6, commandSize - 1));
			}

			else if (command.substr(0, 3) == "DIR" || command.substr(0, 3) == "dir")
			{
				dir();
			}

			else
			{
				cout << "There is no such command" << endl;
			}
		}
	}

	void attrib(string filename) // Write code for attrib after create command
	{
		cout << "Run" << endl;
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
			cout << "Enter a valid name for directory." << endl;
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
			cout << (*it)->retDate() << "    " << (*it)->retTime() << "\t " << (*it)->size() << "\t" << (*it)->name << endl;
		}
	}

	void print()
	{
		if (tree.currentFolder->name == "V")
		{
			cout << "V:\\>";
		}

		else
		{
			cout << tree.currentFolder->path;
		}
	}
};