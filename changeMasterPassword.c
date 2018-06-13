
#include "passwordManager.h"

void changeMasterPassword() {

	printf("*** WARNING ***\nDO NOT FORGET YOUR MASTER PASSWORD (there is no way to recover the data without it)\nType your old password:\n");
	char* temp = malloc(256);
	scanf(" %s", temp);
	//temp = realloc(temp, strlen(temp)+1);
	printf("%s\n", masterPassword);
	printf("%lu\n", strlen(masterPassword));
	printf("%s\n", temp);
	printf("%lu\n", strlen(temp));
	if ( strcmp(masterPassword, temp) != 0) {
		printf("INCORRECT\n");
		return;
	}

	printf("Type in a new master password:\n");
	char* pass = malloc(256);
	scanf(" %s", pass);
	printf("Retype the new master password:\n");

	while (1) {
		free(temp);
		temp = malloc(256);
		scanf(" %s", temp);
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