
#include "passwordManager.h"

/*
	Parameters:
		const char* str = the string that needs to be parsed for accounts
*/
void parseAccounts(const char* str) {

	//number of accounts currently stored
	accountsLength = 0;

	//char* array to hold account name, username, password, and notes
	char* buffer[4];

	//variable to maintain the currect place when reading char* str
	unsigned long counter = 0;

	//while a null character has not been found
	while (str[counter] != '\0') {

		//allocate the maximum storage that the variable could possibly need
		//consider allocating less than adding more as we go
		char* temp = malloc(256*4+3+1);

		//integer to hold position of where characters get placed
		unsigned int i;

		for (i = 0; i < 256*4+3 && str[counter] != '\n'; i++, counter++)
			temp[i] = str[counter];

		//append a null character to the end
		temp[++i] = '\0';

		//reallocate memory to save space
		temp = realloc(temp, i);

		//I think this if statement can just be removed
		if (str[counter] != '\n' && str[counter] != '\0') {

			printf("FAILURE\n");
			exit(EXIT_FAILURE);

		}
		counter++;

		//a variable to maintain position in the char* temp
		unsigned int tempCounter = 0;

		for (i = 0; i < 4; i++) {

			//allocate the maximum possible storage needed
			buffer[i] = malloc(256+1);

			//variable for the position of the character that is going to be appended
			unsigned int j;
			//iterate through the char* adding characters to the buffer while a tab or null character is not encountered
			for (j = 0; temp[tempCounter] != '\t' && temp[tempCounter] != '\0'; j++)
				buffer[i][j] = temp[tempCounter++];

			//append a null character to the end of the string
			buffer[i][++j] = '\0';

			//reallocate the memory so that none is wasted
			buffer[i] = realloc(buffer[i], j);

			//move to the next character's position
			tempCounter++;

		}

		//at least one account already exists
		if (accountsLength++)
			//reallocate the memory
			accounts = realloc(accounts, accountsLength*sizeof(Account));
		else
			//allocate memory for the first time
			accounts = malloc(sizeof(Account));

		//store the text from the buffer into the struct
		accounts[accountsLength-1].accountName = buffer[0];
		accounts[accountsLength-1].username = buffer[1];
		accounts[accountsLength-1].password = buffer[2];
		accounts[accountsLength-1].notes = buffer[3];

	}

}