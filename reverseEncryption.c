
#include "passwordManager.h"

char* reverseEncryption(const char* text, const unsigned long textLength, const char* cipher, const unsigned long cipherLength) {

	assert(textLength >= 0);
	assert(cipherLength > 0);
	//printf("assertion complete\n");

	char* output = malloc(sizeof(char)*textLength);
	//printf("memory allocated\n");

	//printf("%s\n", text);

	for (unsigned long i = 0; i < textLength; i++) {
		//printf("%lu\n", i);
		//printf("cipher: %c\n", cipher[i%cipherLength]);
		//printf("text: %c\n", text[i]); // segmentation fault 11
		output[i] = text[i] ^ cipher[i%cipherLength];
		
	}

	//printf("preparing to return\n");
	
	return output;

}