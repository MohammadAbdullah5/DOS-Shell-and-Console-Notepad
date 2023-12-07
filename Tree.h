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



};