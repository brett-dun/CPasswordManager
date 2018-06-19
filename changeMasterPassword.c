
#include "passwordManager.h"

void changeMasterPassword(void) {

	printf("*** WARNING ***\nDO NOT FORGET YOUR MASTER PASSWORD (there is no way to recover the data without it)\nType your old password:\n");
	//change this to use inputString(stdin)
	char* temp = malloc(256);
	scanf(" %s", temp);
	//temp = realloc(temp, strlen(temp)+1);

	//if the strings are different
	if ( strcmp(masterPassword, temp) != 0) {
		printf("INCORRECT\n");
		return;
	}

	printf("Type in a new master password:\n");
	//change this to use inputString(stdin)
	char* pass = malloc(256);
	scanf(" %s", pass);
	printf("Retype the new master password:\n");

	while (1) {
		free(temp);
		//change this to use inputString(stdin)
		temp = malloc(256);
		scanf(" %s", temp);

		//if the new password matches the retyped new password
		if ( strcmp(pass, temp) == 0 ) {

			//this variable is no longer needed, let's free it's memory
			free(temp);
			
			printf("Success!\n");

			//does not calling this cause a memory leak?
			//free(masterPassword); //this causes an exception if the password has already been changed once

			masterPassword = realloc(pass, strlen(pass)+1);

			free(pass);
			
			break;

		} else
		
			printf("Passwords do not match. Try again:\n");

	}

}