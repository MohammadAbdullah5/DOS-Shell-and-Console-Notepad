#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <stack>
#include <deque>
using namespace std;

struct State
{
	list<list<char>> data;
	list<list<char>>::iterator rowIter;
	list<char>::iterator colIter;
	int row = 0;
	int col = 0;
	int size = 0;
};

class File
{
public:
	string name;
	string extension;
	string path;
	bool isHidden;
	int noOfChar;
	int avgCharPerLine; 
	tm createTime;
	State currentState;
	deque<State> undo;
	stack<State> redo;

	File(string fileName = "Untitled.txt", string filePath = "V:\\")
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
		isHidden = false;
		auto now = std::chrono::system_clock::now();

		time_t now_time = time(0);
	
		localtime_s(&createTime, &now_time);
		currentState.data.push_back(list<char>());
	}

	void edit()
	{
		system("cls");
		displayText(currentState);

		gotoxy(0, 0);
		gotoxy(currentState.col, currentState.col);
		currentState.rowIter = currentState.data.begin();
		currentState.colIter = (*currentState.rowIter).begin();
		State newState;
		newState.col = currentState.col;
		newState.row = currentState.row;
		newState.data = currentState.data;
		newState.rowIter = newState.data.begin();
		newState.colIter = (*newState.rowIter).begin();
		undo.push_back(newState);
		while (true)
		{
			gotoxy(newState.col, newState.row);
			char ch = _getch();
			if (ch == -32) 
			{
				ch = _getch();
				if (ch == 72)  // up
				{
					if (newState.row == 0)
					{
						continue;
					}
					newState.row--;
					newState.rowIter--;
					newState.colIter = (*newState.rowIter).begin();
					newState.col = 0;
				}

				else if (ch == 80) // down
				{
					if (newState.row >= newState.data.size() - 1)
					{
						continue;
					}
					newState.rowIter++;
					newState.row++;
					newState.colIter = (*newState.rowIter).begin();
					newState.col = 0;
				}

				else if (ch == 75) // left
				{
					if (newState.col == 0)
					{
						continue;
					}
					newState.colIter--;
					newState.col--;
				}

				else if (ch == 77) // right
				{
					list<char> temp = (*newState.rowIter);
					if (newState.col >= temp.size())
					{
						continue;
					}
					newState.colIter++;
					newState.col++;
				}

				else if (GetAsyncKeyState(VK_DELETE))
				{
					if (newState.col < (*newState.rowIter).size())
					{
						list<char>::iterator temp = --newState.colIter;
						newState.colIter++;
						if (newState.colIter == (*newState.rowIter).end())
						{
							continue;
						}
						(*newState.rowIter).erase(newState.colIter);
						newState.size--;
						temp++;
						newState.colIter = temp;
						if ((*newState.rowIter).size() == 0)
						{
							newState.data.erase(newState.rowIter); 
							newState.row--;
							newState.col = 0;
						}
						system("cls");
						displayText(newState);
						updateUndo(newState);
					}
				}
			}

			else if (GetAsyncKeyState(VK_BACK))
			{
				if (newState.col == 0)
				{
					continue;
				}

				else if (newState.colIter == (*newState.rowIter).begin())
				{

				}

				else if (newState.col < (*newState.rowIter).size())
				{
					bool flag = false;
					list<char>::iterator temp = --newState.colIter;
					if (temp != (*newState.rowIter).begin())
					{
						temp--;
						flag = true;
					}
					if (newState.colIter == (*newState.rowIter).end())
					{
						continue;
					}
					(*newState.rowIter).erase(newState.colIter);
					newState.size--;
					if (flag)
					{
						newState.colIter = ++temp;
					}
					else
					{
						newState.colIter = (*newState.rowIter).begin();
					}
					newState.col--;
					if ((*newState.rowIter).size() == 0)
					{
						newState.data.erase(newState.rowIter);
						newState.row--;
						newState.col = 0;
					}
					system("cls");
					displayText(newState);
				}
				updateUndo(newState);
			}

			else if (GetAsyncKeyState(VK_RETURN))
			{
				list<char> remaining;
				if (newState.colIter != (*newState.rowIter).end())
				{
					int endSize = 0;
					for (list<char>::iterator it = newState.colIter; it != (*newState.rowIter).end(); it++)
					{
						remaining.push_back(*it);
						endSize++;
					}
					list<char>::iterator endIter = next(newState.colIter, endSize);
					(*newState.rowIter).erase(newState.colIter, endIter);
				}
				list<list<char>>::iterator temp = newState.rowIter;
				newState.rowIter++;
				newState.data.insert(newState.rowIter, remaining);
				newState.rowIter = ++temp;
				newState.row++;
				newState.col = 0;
				system("cls");
				displayText(newState);
				newState.colIter = (*newState.rowIter).begin();
				updateUndo(newState);
			}

			else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('S'))
			{
				currentState = newState;
				break;
			}

			else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('Z'))
			{
				if (!undo.empty())
				{
					State undoState = newState;
					redo.push(undoState);
					newState = undo.back();
					newState.rowIter = newState.data.begin();
					newState.colIter = (*newState.rowIter).begin();
					undo.pop_back();
					system("cls");
					displayText(newState);
				}
				continue;
			}

			else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('Y'))
			{
				if (!redo.empty())
				{
					State redoState = newState;
					undo.push_back(redoState);
					newState = redo.top();
					newState.rowIter = newState.data.begin();
					newState.colIter = (*newState.rowIter).begin();
					redo.pop();
					system("cls");
					displayText(newState);
				}
				continue;
			}

			else if (newState.col == 100)
			{
				newState.rowIter++;
				newState.data.insert(newState.rowIter, list<char>());
				newState.col = 0;
				(*newState.rowIter).push_front(ch);
				newState.colIter = (*newState.rowIter).begin();
				newState.row++;
			}

			else
			{
				list<char>::iterator temp = newState.colIter;
				(*newState.rowIter).insert(newState.colIter, ch); 
				newState.col++; 
				system("cls");
				displayText(newState);
				newState.size++;
				newState.colIter = temp;
				updateUndo(newState);
			}
		}
	}

	void displayText(State state)
	{
		gotoxy(0, 0);
		for (list<list<char>>::iterator rowIt = state.data.begin(); rowIt != state.data.end(); rowIt++)
		{
			for (list<char>::iterator colIt = (*rowIt).begin(); colIt != (*rowIt).end(); colIt++)
			{
				cout << *colIt;
			}
			cout << endl;
		}
	}

	void updateUndo(State newstate)
	{
		if (undo.size() > 5)
		{
			undo.pop_front();
		}

		State s;
		s.data = newstate.data;
		s.rowIter = newstate.data.begin();
		s.colIter = (*s.rowIter).begin();
		s.size = newstate.size;
		s.col = 0;	s.row = 0;
		 
		undo.push_back(s);
	}

	void gotoxy(int x, int y)
	{
		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
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