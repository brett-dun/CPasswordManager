
#include "passwordManager.h"

/*
	Parameters:
		char** result = address of char* data from the file will be stored to
		unsigned long* length = address of long that stores the length of the result
		const char* fileName = name of the file to be read
*/
void readFile(char** result, unsigned long* length, const char* fileName) {

	FILE* file;

	//if the file is able to be accessed
	if ( access( fileName, F_OK ) != -1 ) {

		//read file as a binary file
		file = fopen(fileName, "rb");

		//go to the end of the file
		fseek(file, 0, SEEK_END);

		//store the length of the file
		*length = ftell(file);

		//allocate memory equal to the length of the file
		*result = malloc( sizeof(char) * (*length) );

		//go back to the beginning of the file 
		if ( fseek(file, 0L, SEEK_SET) != 0 )
			printf("Failure");

		//read data from the file into the result
		fread(*result, sizeof(char), (*length)+1, file);

		//Close the file
		fclose(file);

	} else

		printf("Failure");


}