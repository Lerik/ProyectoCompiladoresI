#include "stdafx.h"
#include "ContentReader.h"

#include <ctype.h>

ContentReader::ContentReader()
{
	content = "";
	currentPosition = 0;
	line = 1;
	column = 0;
}

ContentReader::ContentReader(string contentToRead)
{
	content = contentToRead;
	currentPosition = 0;
	line = 1;
	column = 0;
}

void ContentReader::setContentToRead(string contentToRead)
{
	content = contentToRead;
	currentPosition = 0;
}

char ContentReader::nextCharacter()
{
	if(currentPosition == content.length())
		return '\n';
	else
	{
		++currentPosition;

		if(content[currentPosition-1]=='\n')
		{
			++line;
			column = 0;
			return ' ';
		}
		else
		{
			char valueToSent = content[currentPosition - 1];
			++column;

			if(isalpha(valueToSent))
			{
				if(isupper(valueToSent))
					return tolower(valueToSent);
				else
					return valueToSent;
			}
			else
			{
				return valueToSent;
			}
		}
	}
}

int ContentReader::getColumn()
{
	return column;
}

int ContentReader::getLine()
{
	return line;
}
