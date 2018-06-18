
#include "passwordManager.h"

//does not parse accounts properly
void parseAccounts(const char* str) {

	printf("%s\n", str);
	
	accountsLength = 0;

	char* buffer[4];
	//unsigned long bufferLength = 0;

	unsigned int counter = 0;

	while (str[counter] != '\0') {

		//buffer[bufferLength++] = malloc(256*4+3+1);
		char* temp = malloc(256*4+3+1);

		unsigned int i;

		for (i = 0; i < 256*4+3 && str[counter] != '\n'; i++, counter++)
			temp[i] = str[counter];

		temp[++i] = '\0';

		temp = realloc(temp, i);

		printf("%c\n", str[counter]);

		if (str[counter] != '\n' && str[counter] != '\0') {

			printf("FAILURE\n");
			exit(EXIT_FAILURE);

		}
		counter++;

		printf("%s\n\n", temp);

		unsigned int tempCounter = 0;

		for (i = 0; i < 4; i++) {

			buffer[i] = malloc(256+1);

			unsigned int j;
			for (j = 0; temp[tempCounter] != '\t' && temp[tempCounter] != '\0'; j++) {

				buffer[i][j] = temp[tempCounter++];

			}

			buffer[i][++j] = '\0';

			buffer[i] = realloc(buffer[i], j);

			printf("%u :: %s\n", i, buffer[i]);

			tempCounter++;

		}

		if (accountsLength++)
			accounts = realloc(accounts, accountsLength*sizeof(Account));
		else
			accounts = malloc(sizeof(Account));

		accounts[accountsLength-1].accountName = buffer[0];
		accounts[accountsLength-1].username = buffer[1];
		accounts[accountsLength-1].password = buffer[2];
		accounts[accountsLength-1].notes = buffer[3];

	}

	/*while (1) {

		printf("accountsLength: %lu\n", accountsLength);
		
		short tabs = 0;

		for (int i = 0; i < 4; i++) {

			printf("%d\n", i);

			buffer[i] = malloc(256);

			int j;
			for (j = 0; j < 256 && str[counter] != '\t' && str[counter] != '\n' && str[counter] != '\0'; j++, counter++) {
				printf("counter: %d\n", counter);
				buffer[i][j] = str[counter];
			}

			if (str[counter] == '\t')
				tabs++;
			else if (str[counter] == '\0') {
				printf("return\n");
				return;
			}

			buffer[i][++j] = '\0';
			buffer[i] = realloc(buffer[i], j);

			counter++;

			printf("tabs: %d; buffer[%d]: %s\n", tabs, i, buffer[i]);

			printf("i: %d\n", i);

		}

		printf("%c,%d\n", str[counter], tabs);

		if (str[counter] == '\n' && tabs == 0) {

			printf("return\n");
			return;

		} else if (str[counter] == '\n' && tabs != 3) {

			printf("Either the master password was incorrect or a file has become corrupted.\n");
			exit(EXIT_FAILURE);

		} else {

			if (accountsLength++) {

				accounts = realloc(accounts, accountsLength*sizeof(Account));

			} else {

				accounts = malloc(accountsLength*sizeof(Account));

			}

			accounts[accountsLength-1].accountName = buffer[0];
			accounts[accountsLength-1].username = buffer[1];
			accounts[accountsLength-1].password = buffer[2];
			accounts[accountsLength-1].notes = buffer[3];

		}

		counter++;

	}*/

	/*//buffer[0] = malloc(strlen(str)+1);
	while (str[counter] != '\0') 
		printf("%c", str[counter++]);
	printf("\n");

	counter = 0;
	while (str[counter] != '\0') 
		printf("%d ", str[counter++]);
	printf("\n");*/
	//exit(EXIT_FAILURE);

}