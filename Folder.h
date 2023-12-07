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
		folder->path = path.substr(0, length - 1) + folderName + ">";
		subDirectories.push_back(folder);
	}

	void createFiles(string filename = "Untitled.txt")
	{
		File* newFile = new File(filename, path+filename);
		files.push_back(newFile);
	}

	void removeFolder(string foldername)
	{
		for (list<Folder*>::iterator i = subDirectories.begin(); i != subDirectories.end(); i++)
		{
			if ((*i)->name == foldername)
			{
				delete* i;
				i = subDirectories.erase(i);
			}
		}
	}

	void removeFile(string filename)
	{
		for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
		{
			if ((*i)->name == filename)
			{
				delete* i;
				i = files.erase(i);
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
};