
#include "passwordManager.h"

void generateNewPassword(void) {

	//characters that are optionally part of the password
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
	//change this to use inputString(stdin)
	scanf(" %c", &input);

	if (input == 'y' || input == 'Y') {

		printf("Length:\n");
		//change this to use inputString(stdin)
		scanf(" %u", &length);

		printf("Enable uppercase? (y or n)\n");
		//change this to use inputString(stdin)
		scanf(" %c", &input);
		uppercase = (input == 'y' || input == 'Y');

		printf("Enable lowercase? (y or n)\n");
		//change this to use inputString(stdin)
		scanf(" %c", &input);
		lowercase = (input == 'y' || input == 'Y');

		printf("Enable numbers? (y or n)\n");
		//change this to use inputString(stdin)
		scanf(" %c", &input);
		numbers = (input == 'y' || input == 'Y');

		printf("Enable special characters? (y or n)\n");
		//change this to use inputString(stdin)
		scanf(" %c", &input);
		specialCharacters = (input == 'y' || input == 'Y');

		//display the updated settings
		printf("length=%d ", length);
		printf("uppercase=%s ", uppercase ? "enabled" : "disabled");
		printf("lowercase=%s ", lowercase ? "enabled" : "disabled");
		printf("numbers=%s ", numbers ? "enabled" : "disabled");
		printf("specialCharacters=%s\n", specialCharacters ? "enabled" : "disabled");

	}

	//length of the string that contains valid character options
	size_t charSize = strlen(UPPERCASE)*uppercase + strlen(LOWERCASE)*lowercase + strlen(NUMBERS)*numbers + strlen(SPECIAL_CHARACTERS)*specialCharacters;
	
	//if all settings were disabled
	if (charSize == 0) {

		printf("You must enable at least one catagory or characters!\n");

		//renable all options
		uppercase = 1;
		lowercase = 1;
		numbers = 1;
		specialCharacters = 1;

		//exit to main menu
		return;
	}

	//allocate the necessary memory
	char* characters = malloc( charSize );

	//append char* to the char* characters based on whether or not that option was enabled
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

	//seed the random number generator with the current time
	srand( time(NULL) );

	//allocate memory for the length of the password plus a null terminating character
	char* newPassword = malloc( sizeof(char)*(length+1) );

	for (int i = 0; i < length; i++)
		//randomly generate a new character and append it to the password
		newPassword[i] = characters[randLong(charSize)];

	//append a null terminating character at the end of the password
	newPassword[length] = '\0';

	//display the password for the user to copy or use
	printf("%s\n", newPassword);
	
	//free pointers that were allocated memory
	free(characters);
	free(newPassword);

}