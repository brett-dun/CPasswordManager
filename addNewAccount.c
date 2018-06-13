
#include "passwordManager.h"

void addNewAccount() {

	if (accountsLength++) {

		accounts = realloc(accounts, sizeof(Account)*accountsLength);

	} else {

		accounts = malloc( sizeof(Account)*accountsLength );

	}

	Account tempAccount;

	printf("Account name:\n");
	tempAccount.accountName = malloc(256);
	scanf(" %s", tempAccount.accountName);
	tempAccount.accountName = realloc(tempAccount.accountName, strlen(tempAccount.accountName)+1);

	printf("Account username:\n");
	tempAccount.username = malloc(256);
	scanf(" %s", tempAccount.username);
	tempAccount.username = realloc(tempAccount.username, strlen(tempAccount.username)+1);

	printf("Account password:\n");
	tempAccount.password = malloc(256);
	scanf(" %s", tempAccount.password);
	tempAccount.password = realloc(tempAccount.password, strlen(tempAccount.password)+1);

	printf("Account notes:\n");
	tempAccount.notes = malloc(256);
	scanf(" %s", tempAccount.notes);
	tempAccount.notes = realloc(tempAccount.notes, strlen(tempAccount.notes)+1);

	printf("%s\n", tempAccount.accountName);
	printf("%s\n", tempAccount.username);
	printf("%s\n", tempAccount.password);
	printf("%s\n", tempAccount.notes);
	printf("%lu\n", accountsLength);

	accounts[accountsLength-1] = tempAccount;

}