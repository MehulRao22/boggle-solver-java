#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_ROW 4
#define MAX_COL 4

void makeBoardFile(string, char[MAX_ROW][MAX_COL], int[MAX_ROW][MAX_COL]);


void printBoard(char[MAX_ROW][MAX_COL]);

void printPath(int[MAX_ROW][MAX_COL]);

void printBoth(char[MAX_ROW][MAX_COL], int[MAX_ROW][MAX_COL]);

void clearPath(int[MAX_ROW][MAX_COL]);

void solveBoard(char[MAX_ROW][MAX_COL], int[MAX_ROW][MAX_COL], Dictionary, bool&, Dictionary);

void searchForWord(int, int, int, string&,
	char, int, Dictionary, bool&, int&, bool&, Dictionary);

int main()
{
	int row = 0, startRow = 0, startCol = 0,
	finalRow = 4, finalCol = 4, currStep = 0;

	bool done = false;
	
	bool userPrint = false;
	
	Dictionary wordExists;
	 
	string fileName;
	
	fileName = "dictionary.txt";

	Dictionary dictFile(fileName);

	char map[MAX_ROW][MAX_COL];
	int path[MAX_ROW][MAX_COL];
	
	string fileNameBoard = "board.txt";

	
	makeBoardFile(fileNameBoard, map, path);

	
	char choice;
	cout << "\nShow board? (yes/no): ";
	cin >> choice;

	if(choice == 'yes')
	{
		userPrint = true;
		solveBoard(map, path, dictFile, userPrint, wordExists);
		return 0;
	}

	else
	{
		userPrint = false;
		solveBoard(map, path, dictFile, userPrint, wordExists);
	}

	return 0;
}

void makeBoardFile(string fileName, char map[MAX_ROW][MAX_COL], int path[MAX_ROW][MAX_COL])
{
	ifstream mazeFile(fileName);

	if (!mazeFile)
	{
		cout << "File not found!" << endl;
		exit(0);
	}

	char fileChar;

	cout << "Your Board: \n-----------\n";

	
	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << "Row " << i << ": ";
		for (int j = 0; j < MAX_COL; j++)
		{
			mazeFile >> fileChar;
			map[i][j] = fileChar;
			path[i][j] = 0;
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

}


void printBoard(char map[MAX_ROW][MAX_COL])
{
	cout << "Your Board: \n----------\n";
	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << "Row " << i + 1 << ": ";
		for (int j = 0; j < MAX_COL; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

}

void printPath(int path[MAX_ROW][MAX_COL])
{
	cout << "Your Board: \n----------\n";
	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << "Row " << i + 1 << ": ";
		for (int j = 0; j < MAX_COL; j++)
		{
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
}

void printBoth(char map[MAX_ROW][MAX_COL], int path[MAX_ROW][MAX_COL])
{
	cout << "Your Board: \n----------\n";
	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << "Row " << i + 1 << ": ";
		for (int j = 0; j < MAX_COL; j++)
		{
			if (path[i][j] != 0)
			{
				cout << " '" << map[i][j] << "' ";
			}
			
			else
			{
				cout << "  " << map[i][j] << "  ";
			}
		}
		
		cout << "\t\t";
		
			for (int k = 0; k < MAX_COL; k++)
			{
				
				cout << "  " << path[i][k] << "  ";
			}
		cout << endl;
	}
}

void clearPath(int path[MAX_ROW][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			path[i][j] = 0;
		}
	}
}


void searchForWord(int row, int col, int currStep, string& prog, 
	char map[MAX_ROW][MAX_COL], int path[MAX_ROW][MAX_COL], 
	Dictionary dict, bool& done, int& wordCount, bool& userPrint, Dictionary wordExists)
{
	
	if(done)
	{
		return;
	}

	
	if(row < 0 || col < 0 || row >= MAX_ROW || col >= MAX_COL)
	{
		return;
	}
	
	
	if (path[row][col] != 0)
	{
		return;
	}

	
	if (dict.isPrefix(prog + map[row][col]) == false)
	{
		return;
	}

	prog = prog + map[row][col];
	
	if (dict.isWord(prog) == true && wordExists.isWord(prog) == false)
	{
		currStep++;
		path[row][col] = currStep;
		wordCount++;
		wordExists.addWord(prog);
		
		
		cout << "\nWord #" << wordCount << ": " << prog << endl;
		
		if (userPrint == true)
		{
			printBoth(map, path);
		}
	}

	
	if (dict.isPrefix(prog) == true && dict.isWord(prog) == false)
	{
		currStep++;
		path[row][col] = currStep;
	}

	
	searchForWord(row - 1, col - 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row + 1, col, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row + 1, col + 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row - 1, col, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row, col - 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row + 1, col - 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row, col + 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	searchForWord(row - 1, col + 1, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
	
	
	
	if (dict.isPrefix(prog) == false && dict.isWord(prog) == false)
	{
		done = true;
		
		clearPath(path);
		prog.clear();
		
		return;
	}

	if(!done)
	{
		
		prog.erase(prog.length() - 1);
		path[row][col] = 0;
	}
	
}

void solveBoard(char map[MAX_ROW][MAX_COL], int path[MAX_ROW][MAX_COL], Dictionary dict, bool& userPrint, Dictionary wordExists)
{
	string prog = "";
	
	int currStep = 0;
	
	bool done = false;
	
	int wordCount = 0;
	
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			done = false;
			
			searchForWord(i, j, currStep, prog, map, path, dict, done, wordCount, userPrint, wordExists);
		}
	}
}