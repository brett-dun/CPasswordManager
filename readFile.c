
#include "passwordManager.h"

//this sometimes doesn't read the file correctly
void readFile(char** result, unsigned long* length, const char* fileName) {

	//free(result);

	FILE* file;

	if ( access( fileName, F_OK ) != -1 ) {

		file = fopen(fileName, "rb");

		fseek(file, 0, SEEK_END);

		*length = ftell(file);

		//printf("%lu\n", *length);

		*result = malloc(*length);

		//printf("%s\n", *result);

		//printf("memory allocated\n");

		if ( fseek(file, 0L, SEEK_SET) != 0 ) {
			printf("Failure");
		}

		int temp = fread(*result, sizeof(char), (*length)+1, file);

		//printf("%s\n", *result);

		//printf("file read\n");

		//Close the file
		fclose(file);
		//printf("file closed\n");

		//printf("%s\n", *result);

		

	} else

		printf("Failure");


}