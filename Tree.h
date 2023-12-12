#pragma once
#include "Folder.h"
using namespace std;

class DOSTree
{
public:
	Folder* root;
	Folder* currentFolder;

	DOSTree()
	{
		root = new Folder("V", nullptr, "V:\\>");
		currentFolder = root;
	}

	

	void printTree()
	{
		if (currentFolder == root)
		{
			cout << "V" << endl;
			currentFolder->printFolderStructure(0);
		}

		else
		{
			cout << currentFolder->name << endl;
			currentFolder->printFolderStructure(0);
		}
	}
};
