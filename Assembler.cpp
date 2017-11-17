/*
	Assembler Program - Old
	Manchester Baby - AC21009
	Group 16
	Andrew Brodrick - 170017286 
	Peter West - 
	Peter Short - 
	Juri Ilmjarv - 
*/

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;

string textFile[32];
string memory[32];

	string instructions[8][3] = 
	{

	{"VAR", "Yes", "NULL"},
	{"JMP", "Yes", "000"},
	{"JRP", "Yes", "100"},
	{"LDN", "Yes", "010"},
	{"STO", "Yes", "110"},
	{"SUB", "Yes", "001"},
	{"CMP", "No", "011"},
	{"STP", "No", "111"},

	};

int takeInCodeFile()
{
	
	string line;
	int iterate;
	int ignore;

	ifstream file("BabyTest1-Assembler.txt");

	if(!file)
	{
		cout << "The program is unable to open the file" << endl;
		return 1;
	}

	while(getline(file, line))
	{
		ignore = line.find_first_not_of("\t");

		if(line.at(ignore) != (';'))
		{
			if(iterate < 32)
			{
				textFile[iterate] = line;
				iterate++;
				cout << "Successfully added to the text file\t" << line << endl;
			}
			else
			{
				cout << "ERROR: The memory store is full" << endl;
				return 0;
			}
		}
	}

	file.close();

	return 0;
}

int changeFileToWorkingFile()
{
	int fileLength;
	string currentLine;
	int end;
	char currentCharacter;

	for(int i=0; i<32; i++)
	{
		fileLength = textFile[i].size();
		currentLine = textFile[i];
		end = fileLength;

		if(currentLine.at(0) == '#')
		{
			return 1;
		}

		for(int j=0; j<fileLength; j++)
		{
			currentCharacter = currentLine.at(j);

			if(currentCharacter == ';')
			{
				end = j;
			}
		}

		textFile[i] = currentLine.substr(0,end);

		cout << textFile[i] << endl;
	}
}

string scanFile()
{
	string error = "";
	int currentPosition;
	int startOfLine;
	bool isCorrect;

	for(int i=0; i<32; i++)
	{
		if(textFile[i].at(0) == '#')
		{
			return "The scan has been completed";
		}

		currentPosition = 0;
		size_t foundCharacter = textFile[i].find(':');
		startOfLine = 0;

		if(foundCharacter != string::npos)
		{
			currentPosition = (textFile[i].find_first_not_of(':')+1);
		}

		isCorrect = false;

		startOfLine = textFile[i].find_first_not_of(" \t", currentPosition);
		string hold = textFile[i].substr(startOfLine, 3);

		for(int j=0; j<5; j++)
		{
			if(hold == instructions[j][0])
			{
				isCorrect = true;
			}
		}

		if(isCorrect == false)
		{
			error = "ERROR: there is an error on line ";
			error += to_string(i);
			error += ", there is a problem with the opcode: ";
			error += hold;
			return error;
		}

		cout << textFile[i] << "\n";
	}
}

string convertCodeToBinary(int decimalValue)
{
	string binaryValue;
	
	for(int i=0; i<32; i++) 
	{
		binaryValue += to_string(decimalValue%2);
		decimalValue/=2;
	}

	return binaryValue;
}

void writeToFile()
{
	string newCodeFile = "AssemblerComplete.txt";

	ofstream file (newCodeFile.c_str());

	for(int i=0; i<32; i++)
	{
		file << textFile[i] << "\n";
	}

	file.close();
}

int main()
{
	string error_return = "";

	 
  	for (int i=0; i<32; i++) 
  	{
  		textFile[i] = "#";
  	}

	takeInCodeFile();

	cout << "\nFile has finished loading...\n\n";

	changeFileToWorkingFile();

	cout << "\nconverting finished.\n";

	error_return = scanFile();
    cout << error_return << endl;

	writeToFile();
	
	cout << "\nWriting finished.\n";

	return 0;
}
