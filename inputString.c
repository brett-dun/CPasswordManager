
#include "passwordManager.h"

char* inputString(FILE* fp) {

	char* str;
	char ch;
	size_t size = 16;
	size_t length = 0;

	//allocate room for up to 16 characters
	str = realloc(NULL, sizeof(char) * size);

	//check for null
	if(!str)
		return str;

	while( EOF != (ch=fgetc(fp)) && ch != '\n') {

		str[length++] = ch;

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