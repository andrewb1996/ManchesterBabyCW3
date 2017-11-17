/*
	Assembler Program
	AC21009(CW3) - Manchester Baby - Group 16
	Andrew Brodrick
	Peter West
	Peter Short
	Juri Ilmjarv 
*/

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <bitset>
#include <string>

using namespace std;

string textFile[32];

string instructionSet[8][3] = {
{"VAR", "Yes", "NULL"},
{"JMP", "Yes", "000"},
{"JRP", "Yes", "100"},
{"LDN", "Yes", "010"},
{"STO", "Yes", "110"},
{"SUB", "Yes", "001"},
{"CMP", "No", "011"},
{"STP", "No", "111"},
};


int loadCodeFile()
{


	ifstream inputFile("BabyTest1-Assembler.txt");

	if(!inputFile)
	{
		cout << "ERROR: The program cannot open the file.\n";
		return 1;
	}
	
	string line;
	int iterate = 0;
	int ignoreValue = 0;

	while(getline(inputFile, line))
	{

		ignoreValue = line.find_first_not_of("\t");

		if(line.at(ignoreValue) != (';'))
		{


			if(iterate < 32)
			{
				

				textFile[iterate] = line;
				iterate++;
				cout << "Added to textFile\t" << line << endl;
			}
			else
			{
				cout << "ERROR: You are trying to add to a full memory store\n";
				return 1;
			}
		}
	}


	inputFile.close();

	return 0;
}

int convertCode() 
{

  	for (int i=0; i<32; i++) 
  	{

    		int length = textFile[i].size();
    		string currentLine = textFile[i];
    		int endOfFile = length;    
    	

    		if (currentLine.at(0) == '#') 
    		{
				return 1; 
			}


    		for (int j=0;j<length; j++) 
    		{

    	  		char currentCharacter = currentLine.at(j);

      			if (currentCharacter == ';') 
      			{
					endOfFile = j;
     			}
    		}

    		textFile[i] = currentLine.substr(0,endOfFile);

    		cout << textFile[i] << endl;
	}		
}


string scanCode() 
{

	string errorString = "";

	for (int i=0;i<32; i++) 
	{

		if (textFile[i].at(0) == '#') 
		{
			return "The scan has been completed";  
		}
		

		int currentPosition = 0;
		size_t searchCharacter = textFile[i].find(':');
		int startCharacter = 0;

		if (searchCharacter!=string::npos) 
		{
			currentPosition = (textFile[i].find_first_of(':')+1);
		}

		bool correct = false;

		startCharacter = textFile[i].find_first_not_of(" \t",currentPosition);
		string opcode = textFile[i].substr(startCharacter,3);

		for (int j=0; j<8 ; j++) 
		{

			if (opcode == instructionSet[j][0]) 
			{
				correct = true;
			}
		}


		if (correct == false) 
		{
			errorString = "ERROR: line " + to_string(i) + ". The opcode: " + opcode + " has encountered an error.";
		}

		cout << textFile[i] << "\n";
	}
}

string convertIntToBinary()
{

}


void writeCodeToExternalFile()
{

	string fileName = "AssemblerComplete.txt";


	ofstream outputFile(fileName);
	
	for(int i=0; i<32; i++)
	{
		outputFile << textFile[i] << "\n";	
	}


	outputFile.close();
}

int main() 
{


  	for (int times = 0; times < 32; times++) 
  	{
  		textFile[times] = "#";
  	}

	string return_error = "";

	loadCodeFile();

	cout << "\nFinished loading.\n\n";

	convertCode();

	cout << "\nconverting finished.\n";

	return_error = scanCode();
    	cout << return_error << endl;

	writeCodeToExternalFile();
	
	cout << "\nWriting finished.\n";
}