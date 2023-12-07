#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
using namespace std;

class File
{
public:
	string name;
	string extension;
	string path;
	int noOfChar;
	int avgCharPerLine; 
	tm createTime;

	File(string fileName = "Untitled.txt", string filePath = "V:\\>")
	{
		string filenameWithoutExt;
		string ext;
		int size = fileName.size();
		int i;
		for (i = 0; i < size; i++)
		{
			if (fileName[i] != '.')
			{
				filenameWithoutExt += fileName[i];
			}

			else
			{
				break;
			}
		}

		for (i = 0; i < size; i++)
		{
			ext += fileName[i];
		}
		name = filenameWithoutExt;
		extension = ext;
		path = filePath;
		noOfChar = 0;
		avgCharPerLine = 0;
		auto now = std::chrono::system_clock::now();

		time_t now_time = time(0);

		localtime_s(&createTime, &now_time);
	}

	int size()
	{
		return 0;
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