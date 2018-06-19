
#include "passwordManager.h"

/*
	Parameters:
		const char* text = data to be written to the file
		const size_t length = length of the data
		const char* fileName = name of the file to be written to
*/
void writeFile(const char* text, const size_t length, const char* fileName) {
	
	//open file as a binary file
	FILE* file = fopen(fileName, "wb");

	//write the data to the file
	fwrite(text, sizeof(char), length, file);

	fclose(file);

}
