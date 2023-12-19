#pragma once
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

class VimNotepad
{
	class Node
	{
	public:
		char data;
		Node* left;
		Node* right;
		Node* down;
		Node* up;
		Node()
		{
			left = nullptr;
			up = nullptr;
			right = nullptr;
			down = nullptr;
		}

		Node(char input)
		{
			left = nullptr;
			up = nullptr;
			right = nullptr;
			down = nullptr;
			data = input;
		}
	};

public:
	Node* cursor;
	Node* first;

	VimNotepad()
	{
		cursor = nullptr;
		first = nullptr;;
	}

	void insert(char ch)
	{
		Node* newChar = new Node(ch);
		if (first == nullptr)
		{
			first = newChar;
			cursor = first;
			return;
		}

		if (cursor->data == '\0')
		{
			cursor->data = ch;
		}

		else if (cursor->right == nullptr) 
		{
			newChar->left = cursor;
			cursor->right = newChar;
			cursor = newChar;
		}

		else
		{
			newChar->left = cursor;
			cursor->right->left = newChar;
			newChar->right = cursor->right;
			cursor->right = newChar;
			cursor = newChar;
		}

		if (cursor->left != nullptr)
		{
			if (cursor->left->up != nullptr)
			{
				cursor->up = cursor->left->up->right;
			}
		}

		if (cursor->right != nullptr)
		{
			if (cursor->right->up != nullptr)
			{
				cursor->up = cursor->right->up->left;
			}
		}

		if (cursor->up != nullptr)
		{
			cursor->up->down = cursor;
		}

		if (cursor->down != nullptr)
		{
			cursor->down->up = cursor;
		}
	}

	void nextLine()
	{
		Node* newNode = new Node();
		if (first == nullptr)
		{
			first = new Node();
			first->down = newNode;
			newNode->up = first;
			cursor = newNode;
		}

		else
		{
			Node* temp = cursor;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			temp->down = newNode;
			newNode->up = temp;
			cursor = newNode;
		}
	}

	void deleteLeft()
	{
		if (cursor == nullptr)
		{
			return;
		}

		if (cursor->left != nullptr)
		{
			cursor = cursor->left;
			deleteRight();
		}
	}

	void deleteRight()
	{
		if (cursor == nullptr)
		{
			return;
		}

		Node* temp = cursor;
		Node* upper;
		Node* lower;
		if (temp->right != nullptr)
		{
			upper = temp->right->up;
			lower = temp->right->down;
			temp->right = temp->right->right;
			temp = temp->right;
			while (temp != nullptr && upper != nullptr)
			{
				upper->down = temp;
				temp->up = upper;
				temp->down = lower;
				if (lower != nullptr)
				{
					lower->up = temp;
				}
				temp = temp->right;
				upper = upper->right;
			}
			temp = cursor->right;
			while (temp != nullptr && lower != nullptr)
			{
				temp->down = lower;
				lower = lower->right;
			}
		}
	}

	
	void display()
	{
		Node* temp = first;
		while (temp != nullptr)
		{
			Node* inner = temp;
			while (inner != nullptr)
			{
				cout << inner->data;
				inner = inner->right;
			}
			if (temp->down != nullptr)
			{
				cout << endl;
			}
			temp = temp->down;
		}
	}

	void run()
	{
		int x = 0;
		int y = 0;
		display();
		char ch;

		while (true)
		{
			system("cls");
			display();
			gotoxy(x, y);
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();

				if (ch == 72)  // up
				{
					if (cursor != nullptr && cursor->up != nullptr)
					{
						cursor = cursor->up;
						y--;
					}
				}

				else if (ch == 80) // down
				{
					if (cursor != nullptr && cursor->down != nullptr)
					{
						cursor = cursor->down;
						y++;
					}
				}

				else if (ch == 75) // left
				{
					if (cursor != nullptr && cursor->left != nullptr)
					{
						cursor = cursor->left;
						x--;
					}
				}

				else if (ch == 77) // right
				{
					if (cursor != nullptr && cursor->right != nullptr)
					{
						cursor = cursor->right;
						x++;
					}
				}

				else if (GetAsyncKeyState(VK_DELETE))
				{
					if (cursor->right != nullptr)
					{
						deleteRight();
					}
				}
			}

			else if (GetAsyncKeyState(VK_RETURN))
			{
				nextLine();
				y++;
				x = 0;
			}

			else if (GetAsyncKeyState(VK_BACK))
			{
				if (cursor->left != nullptr)
				{
					deleteLeft();
					x--;
				}
			}

			else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('S'))
			{
				break;
			}
			
			else
			{
				insert(ch);
				x++;
			}
		}
	}

	void gotoxy(int x, int y)
	{
		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
	}

};