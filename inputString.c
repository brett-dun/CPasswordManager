
#include "passwordManager.h"

/*
	Parameters:
		FILE* fp = the file to read from
	Return Value:
		char* = the first line of text found in the file
*/
char* inputString(FILE* fp) {

	//current string
	char* str;
	//current character
	char ch;
	//amount of memory allocated
	size_t size = 16;
	//length of string
	size_t length = 0;

	//allocate room for up to 16 characters
	str = realloc(NULL, sizeof(char) * size);

	//check for null
	if(!str)
		return str;

	//while the end of the file has not been reached and the current character is not a newline character
	while( EOF != (ch=fgetc(fp)) && ch != '\n') {

		//append the character to the string
		str[length++] = ch;

		//if all of the allocated memory has been used
		if(length == size) {
			//allocate room for another 16 characters
			str = realloc(str, sizeof(char) * (size+=16));
			
			//check for null
			if(!str)
				return str;
		}

	}

	//Add a null terminator
	str[length++] = '\0';

	//return a char* that doesn't use excess memory
	return realloc(str, sizeof(char) * length);

}