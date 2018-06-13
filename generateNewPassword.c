
#include "passwordManager.h"

void generateNewPassword() {

	const char* UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char* LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
	const char* NUMBERS = "0123456789";
	//excludes " " because that generally cannot be used as part of a password
	const char* SPECIAL_CHARACTERS = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

	//turn this into a loop so multiple passwords can be generated at once

	printf("*** WARNING ***\nDO NOT USE THIS PASSWORD GENERATOR FOR ANYTHING THAT IS IMPORTANT!!!\n");
	printf("length=%d ", length);
	printf("uppercase=%s ", uppercase ? "enabled" : "disabled");
	printf("lowercase=%s ", lowercase ? "enabled" : "disabled");
	printf("numbers=%s ", numbers ? "enabled" : "disabled");
	printf("specialCharacters=%s\n", specialCharacters ? "enabled" : "disabled");
	printf("Change settings? (y or n)\n");
	
	char input;
	scanf(" %c", &input);

	if (input == 'y' || input == 'Y') {

		printf("Length:\n");
		scanf(" %u", &length);

		printf("Enable uppercase? (y or n)\n");
		scanf(" %c", &input);
		uppercase = (input == 'y' || input == 'Y');

		printf("Enable lowercase? (y or n)\n");
		scanf(" %c", &input);
		lowercase = (input == 'y' || input == 'Y');

		printf("Enable numbers? (y or n)\n");
		scanf(" %c", &input);
		numbers = (input == 'y' || input == 'Y');

		printf("Enable special characters? (y or n)\n");
		scanf(" %c", &input);
		specialCharacters = (input == 'y' || input == 'Y');

		printf("length=%d ", length);
		printf("uppercase=%s ", uppercase ? "enabled" : "disabled");
		printf("lowercase=%s ", lowercase ? "enabled" : "disabled");
		printf("numbers=%s ", numbers ? "enabled" : "disabled");
		printf("specialCharacters=%s\n", specialCharacters ? "enabled" : "disabled");

	}

	size_t charSize = strlen(UPPERCASE)*uppercase + strlen(LOWERCASE)*lowercase + strlen(NUMBERS)*numbers + strlen(SPECIAL_CHARACTERS)*specialCharacters;
	
	if (charSize == 0) {
		printf("You must enable at least one catagory or characters!\n");
		uppercase = 1;
		lowercase = 1;
		numbers = 1;
		specialCharacters = 1;
		return;
	}



	char* characters = malloc( charSize );

	if (uppercase)
		strcpy(characters, UPPERCASE);

	if (lowercase && !uppercase)
		strcpy(characters, LOWERCASE);
	else if (lowercase)
		strcat(characters, LOWERCASE);

	if (numbers && (!uppercase || !lowercase))
		strcpy(characters, NUMBERS);
	else if (numbers)
		strcat(characters, NUMBERS);

	if (specialCharacters && (!uppercase || !lowercase || !numbers))
		strcpy(characters, SPECIAL_CHARACTERS);
	else if (specialCharacters)
		strcat(characters, SPECIAL_CHARACTERS);

	//printf("%s\n", characters);

	srand( time(NULL) );

	char* newPassword = malloc( length+1 );
	for (int i = 0; i < length; i++)
		newPassword[i] = characters[randLong(charSize)];
	newPassword[length] = '\0';

	printf("%s\n", newPassword);
	
	free(characters);

}