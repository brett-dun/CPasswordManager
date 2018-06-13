
#include "passwordManager.h"

//this doesn't parse correctly [still]
void parseAccounts(const char* str) {

	printf("%s\n", str);
	
	accountsLength = 0;

	char* buffer[4];
	int counter = 0;

	while (1) {

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

	}

}