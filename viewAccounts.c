
#include "passwordManager.h"

void viewAccounts() {

	printf("# :: Account Name :: Username :: Password :: Notes\n");

	for (int i = 0; i < accountsLength; i++)
		printf("%d :: %s :: %s :: %s :: %s\n", i, accounts[i].accountName, accounts[i].username, "******", accounts[i].notes);

	while (1) {

		printf("Enter account number to view its password. (Enter -1 to exit)\n");

		int accountNumber;
		scanf(" %d", &accountNumber);

		if (accountNumber == -1)
			break;

		if (accountNumber < 0 || accountNumber >= accountsLength) {
			printf("Invalid account number.\n");
			continue;
		}

		printf("Account Name: %s\n", strlen(accounts[accountNumber].accountName) ? accounts[accountNumber].accountName : "[empty]");
		printf("Username: %s\n", strlen(accounts[accountNumber].username) ? accounts[accountNumber].username : "[empty]");
		printf("Password: %s\n", strlen(accounts[accountNumber].password) ? accounts[accountNumber].password : "[empty]");
		printf("Notes: %s\n", strlen(accounts[accountNumber].notes) ? accounts[accountNumber].notes : "[empty]");

	}

}