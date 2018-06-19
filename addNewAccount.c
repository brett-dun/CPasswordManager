
#include "passwordManager.h"

void addNewAccount(void) {

	//if at least one account exists
	if (accountsLength++)
		//reallocate the memory
		accounts = realloc(accounts, sizeof(Account)*accountsLength);
	else
		//allocate memory for the first time
		accounts = malloc( sizeof(Account)*accountsLength );

	//instead of using this, use "accounts[accountsLength-1]"
	Account tempAccount;

	printf("Account name:\n");
	//change this to use inputString(stdin)
	tempAccount.accountName = malloc(256);
	scanf(" %s", tempAccount.accountName);
	tempAccount.accountName = realloc(tempAccount.accountName, strlen(tempAccount.accountName)+1);

	printf("Account username:");
	//change this to use inputString(stdin)
	tempAccount.username = malloc(256);
	scanf(" %s", tempAccount.username);
	tempAccount.username = realloc(tempAccount.username, strlen(tempAccount.username)+1);

	printf("Account password:\n");
	//change this to use inputString(stdin)
	tempAccount.password = malloc(256);
	scanf(" %s", tempAccount.password);
	tempAccount.password = realloc(tempAccount.password, strlen(tempAccount.password)+1);

	printf("Account notes:\n");
	//change this to use inputString(stdin)
	tempAccount.notes = malloc(256);
	scanf(" %s", tempAccount.notes);
	tempAccount.notes = realloc(tempAccount.notes, strlen(tempAccount.notes)+1);

	//save the new account into the array
	accounts[accountsLength-1] = tempAccount;

}