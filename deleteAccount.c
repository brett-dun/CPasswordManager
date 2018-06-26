
#include "passwordManager.h"

void deleteAccount(void) {

	while (1) {

		printf("# :: Account Name\n");
		for (int i = 0; i < accountsLength; i++) {
			printf("%d :: %s\n", i, accounts[i].accountName);
		}
		printf("Which account do you want to delete? (-1 to exit)\n");

		int accountToBeRemoved;
		scanf(" %d", &accountToBeRemoved);

		if (accountToBeRemoved == -1)
			break;

		if (accountToBeRemoved >= accountsLength) {
			printf("Invalid account.\n");
			continue;
		}

		printf("Are you sure that you want to delete the following account?\n");
		printf("Account Name: %s\n", accounts[accountToBeRemoved].accountName);
		printf("Username: %s\n", accounts[accountToBeRemoved].username);
		printf("Password: ********\n");
		printf("Notes: %s\n", accounts[accountToBeRemoved].notes);

		for (int i = accountToBeRemoved; i < accountsLength-1; i++)
			accounts[i] = accounts[i+1];

		accounts = realloc(accounts, sizeof(Account)*(--accountsLength));

		/*for (int i = 0; i < accountsLength; i++) {
			printf("%s :: %s :: %s :: %s\n", accounts[i].accountName, accounts[i].username, accounts[i].password, accounts[i].notes);
		}*/

	}

}