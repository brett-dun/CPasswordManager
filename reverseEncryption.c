
#include "passwordManager.h"

/*
	const char* text = text to be encrypted
	const unsigned long textLength = text length
	const char* cipher = the cipher that is used to encrypt the text
	const unsigned long cipherLength = cipher length
*/
char* reverseEncryption(const char* text, const unsigned long textLength, const char* cipher, const unsigned long cipherLength) {

	//the length cannot be negative
	assert(textLength >= 0);

	//cipherLength must be greater than 0 because x % 0 is not defined
	assert(cipherLength > 0);

	//output will be the same length as the input text
	char* output = malloc(sizeof(char)*textLength);

	for (unsigned long i = 0; i < textLength; i++)
		//byte of text xor byte of cipher 
		output[i] = text[i] ^ cipher[i%cipherLength];
	
	return output;

}