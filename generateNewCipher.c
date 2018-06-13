
#include "passwordManager.h"


//generate a new cipher that is of equal length to the text
char* generateNewCipher(const size_t length) {


	char* cipher = malloc(length);
	for (int i = 0; i < length; i++)
		cipher[i] = (char) rand();

	return cipher;

}