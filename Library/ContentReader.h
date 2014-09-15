#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <map>
using namespace std;

class ContentReader
{

public:
	ContentReader();
	ContentReader(string contentToRead);

	void setContentToRead(string contentToRead);

	char nextCharacter();
	int getLine();
	int getColumn();
	
private:
	string content;
	int currentPosition;
	int line;
	int column;
};