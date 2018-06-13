
#include "passwordManager.h"

//this sometimes doesn't read the file correctly
char* readFile(const char* fileName) {

	char* str;
	char ch;
	size_t size = 16;
	size_t length = 0;

	//allocate room for up to 16 characters
	str = malloc(sizeof(char) * size);

	FILE* file;

	if( access( fileName, F_OK ) != -1 ) {

		file = fopen(fileName, "rb");

		//printf("reading file\n");
		while ((ch = getc(file)) != EOF) {

		    str[length++] = ch;

		    printf("%d ", ch);

		    //printf("%c", ch);

			if (length == size) {
				//allocate room for another 16 characters
				str = realloc(str, sizeof(char) * (size+=16));
					
				//check for null
				if(!str)
					return str;
			}

		}

		//Close the file
		fclose(file);

		//Add a null terminator
		str[length++] = '\0';

		printf("\n");

		//return a char* that doesn't use excess memory
		return realloc(str, sizeof(char) * length);

	} else {
		printf("Failure");
		return str;
	}

}