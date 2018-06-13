
#include "passwordManager.h"

void writeFile(const char* text, const size_t length, const char* fileName) {
	
	FILE* file = fopen(fileName, "wb");

	for (int i = 0; i < length; i++)
		printf("%d ", text[i]);
	printf("\n");

	fwrite(text, sizeof(char), length, file);

	fclose(file);

}
