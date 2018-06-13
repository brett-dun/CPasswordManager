
#include "passwordManager.h"

char* reverseEncryption(const char* text, const char* cipher) {

	int textLength = strlen(text);
	int cipherLength = strlen(cipher);

	char* output = malloc(sizeof(char)*textLength);

	for (int i = 0; i < textLength; i++)
		output[i] = text[i] ^ cipher[i%cipherLength];
	
	return output;

}