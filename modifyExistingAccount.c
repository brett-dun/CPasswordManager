
#include "passwordManager.h"

void modifyExistingAccount() {

	printf("#\tAccount Name\n");

	for (int i = 0; i < accountsLength; i++)
		printf("%d\t%s\n", i, accounts[i].accountName);

	printf("Type the account number that you would like to modify\n");

	unsigned int accountNumber;
	scanf(" %u", &accountNumber);

	if (accountNumber >= accountsLength) {
		printf("Invalid account number.\n");
		return;
	}

	while (1) {

		printf("Which field would you like to modify?\n");
		printf("[0] Account Name: %s\n", accounts[accountNumber].accountName);
		printf("[1] Username: %s\n", accounts[accountNumber].username);
		printf("[2] Password: %s\n", accounts[accountNumber].password);
		printf("[3] Notes: %s\n", accounts[accountNumber].notes);
		printf("[4] (Exit)\n");

		unsigned int option;
		scanf(" %u", &option);

		if (option == 4)
			break;

		if (option > 4) {
			printf("Invalid option.\n");
			continue;
		}

		printf("Update the field:\n");

		char* updated = malloc(256);
		scanf(" %s", updated);
		updated = realloc(updated, strlen(updated)+1);

		switch (option) {
			case 0:
				accounts[accountNumber].accountName = updated;
				break;
			case 1:
				accounts[accountNumber].username = updated;
				break;
			case 2:
				accounts[accountNumber].password = updated;
				break;
			case 3:
				accounts[accountNumber].notes = updated;
				break;
		}

	}



}