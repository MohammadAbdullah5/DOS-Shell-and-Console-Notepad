#pragma once
#include <iostream>
#include <list>
#include <string>
#include <ctime>
#include "File.h"
using namespace std;

class Folder
{
public:
	string name;
	list<Folder*> subDirectories;
	list<File*> files;
	Folder* parent;
	string path;
	tm createTime;

	bool isHidden;

	Folder(string nameInput = "New Folder", Folder* ancestor = nullptr, string pat = "")
	{
		name = nameInput;
		parent = ancestor;
		path = pat;
		isHidden = false;
		time_t now_time = time(0);

		localtime_s(&createTime, &now_time);
	}

	void insertFolder(string folderName = "New Folder")
	{
		Folder* folder = new Folder(folderName);
		folder->parent = this;
		int length = path.length();
		folder->path = path.substr(0, length - 1) + folderName;
		subDirectories.push_back(folder);
	}

	void createFiles(string filename = "Untitled.txt")
	{
		File* newFile = new File(filename, path+filename);
		files.push_back(newFile);
	}

	void removeFolder(string foldername)
	{
		list<Folder*>::iterator i;
		for (i = subDirectories.begin(); i != subDirectories.end(); i++)
		{
			if ((*i)->name == foldername)
			{
				subDirectories.erase(i);
				break;
			}
		}
	}

	void removeFile(string filename)
	{
		list<File*>::iterator i;
		for (i = files.begin(); i != files.end(); i++)
		{
			if ((*i)->name == filename)
			{
				files.erase(i);
				break;
			}
		}
	}

	bool searchFolder(string folder)
	{
		for (list<Folder*>::iterator i = subDirectories.begin(); i != subDirectories.end(); i++)
		{
			if ((*i)->name == folder)
			{
				return true;
			}
		}
		return false;
	}

	Folder* searchAndReturnFolder(string folder)
	{
		for (list<Folder*>::iterator i = subDirectories.begin(); i != subDirectories.end(); i++)
		{
			if ((*i)->name == folder)
			{
				return *i;
			}
		}
		return nullptr;
	}

	File* searchAndReturnFile(string file)
	{
		for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
		{
			if ((*i)->name == file)
			{
				return *i;
			}
		}
		return nullptr;
	}

	string retDate()
	{
		char date[12]; 
		strftime(date, sizeof(date), "%d/%m/%Y", &createTime);
		return date;
	}

	string retTime() 
	{
		char timed[9];  
		strftime(timed, sizeof(timed), "%I:%M %p", &createTime);
		return timed;
	}

	int calculateDepth() 
	{
		int depth = 0;

		for (list<Folder*>::iterator i = subDirectories.begin(); i != subDirectories.end(); i++)
		{
			depth = max(depth, (*i)->calculateDepth());
		}
		return depth + 1;
	}

	void printFolderStructure(int depth)
	{
		for (list<Folder*>::iterator it = subDirectories.begin(); it != subDirectories.end(); it++)
		{
			if (depth == 0)
			{
				cout << string((depth) * 4, ' ') << "|____" << (*it)->name << endl;
				(*it)->printFolderStructure(depth + 1);

			}

			else
			{
				cout << "|" << string((depth) * 4, ' ') << "|____" << (*it)->name << endl;
				(*it)->printFolderStructure(depth + 1);
			}
		}
	}
};