//make sure that I am still using all of these
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <assert.h>


typedef struct {

	char* accountName;
	char* username;
	char* password;
	char* notes;

} Account;


const char* CIPHER_PATH = "Desktop/cipher.data";
const char* PASSWORD_MANAGER_PATH = "Desktop/passwordManager.data";

//password that unlocks the cipher
char* masterPassword;

//array of Account structs which is used to store data from decrypted text in a way that is easier to modify and update
//Account (*accounts)[];
Account* accounts;
unsigned long accountsLength;

//password settings - consider storing these settings into a file
unsigned int length = 8;
short uppercase = 1;
short lowercase = 1;
short numbers = 1;
short specialCharacters = 1;


//Function prototypes
char* inputString(FILE* fp);

void displayHelp();
void viewAccounts();
void addNewAccounts();
void modifyExistingAccount();
void generateNewPassword();
void changeMasterPassword();

long randLong(const long max);
char* readFile(const char* fileName);
void writeFile(const char* text, const size_t length, const char* fileName);
char* reverseEncryption(const char* text, const char* cipher);
char* generateNewCipher(const size_t length);
void parseAccounts(const char* str);



char* inputString(FILE* fp) {

	char* str;
	char ch;
	size_t size = 16;
	size_t length = 0;

	//allocate room for up to 16 characters
	str = realloc(NULL, sizeof(char) * size);

	//check for null
	if(!str)
		return str;

	while( EOF != (ch=fgetc(fp)) && ch != '\n') {

		str[length++] = ch;

		if(length == size) {
			//allocate room for another 16 characters
			str = realloc(str, sizeof(char) * (size+=16));
			
			//check for null
			if(!str)
				return str;
		}

	}

	//Add a null terminator
	str[length++] = '\0';

	//return a char* that doesn't use excess memory
	return realloc(str, sizeof(char) * length);

}


/*
//This is not truly a hash but that's okay for our purposes
char* hash(char* str) {

	//length of the string to be hashed
	unsigned int length = strlen(str);

	char* output = realloc(NULL, length * 2);

	for(int i = 0; i < length; i++) {

		srand(str[i]);
		unsigned int num = rand();
		printf("%d\n", num);

		output[i] = (char) (num%USHRT_MAX);
		output[i+length] = (char) ( (num%USHRT_MAX) >> 8);
		//output[i+length*2] = (char) (num >> 16);
		//output[i+length*3] = (char) (num >> 24);

	}

	return output;

}*/


void displayHelp() {
	printf("Password Manager Instructions:\n");
	printf("\t\"0\" - Instructions\n");
	printf("\t\"1\" - View Accounts\n");
	printf("\t\"2\" - Generate New Password\n");
	printf("\t\"3\" - Add New Account\n");
	printf("\t\"4\" - Modify Existing Account\n");
	//option to delete an account
	printf("\t\"5\" - Change Master Password\n");
	printf("\t\"6\" - Exit and Save\n");
}


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


//this doesn't work (yet) for some reason
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

	accounts[accountsLength-1] = tempAccount; //this causes a segmentation fault

}


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


long randLong(const long max) {

	//if the maximum allowed value is the same as RAND_MAX
	if (max-1 == RAND_MAX)

		//return a random number in the range [0,max)
		return rand();

	else {

		//max must be less than RAND_MAX otherwise this won't work
		assert(max < RAND_MAX);

		//integer division will make sure their is even distribution of the numbers
		long maxValid = RAND_MAX / max;
		//maxValid must be greater than 0
		assert(maxValid > 0);

		//this is the actual maximum
		maxValid *= max;

		//variable for the randomly generated number to be stored into
		long num;
		//while num is not valid, continue to regenerate it a new value
		while ( (num=rand()) >= maxValid );

		//return a number that is in the range [0,max)
		return num % max;

	}

}


//this sometimes doesn't read the file correctly
char* readFile(const char* fileName) {

	char* str;
	char ch;
	size_t size = 16;
	size_t length = 0;

	//allocate room for up to 16 characters
	str = malloc(sizeof(char) * size);

	FILE* file;

	if( access( fileName, F_OK ) != -1 ) {

		file = fopen(fileName, "rb");

		//printf("reading file\n");
		while ((ch = getc(file)) != EOF) {

		    str[length++] = ch;

		    printf("%d ", ch);

		    //printf("%c", ch);

			if (length == size) {
				//allocate room for another 16 characters
				str = realloc(str, sizeof(char) * (size+=16));
					
				//check for null
				if(!str)
					return str;
			}

		}

		//Close the file
		fclose(file);

		//Add a null terminator
		str[length++] = '\0';

		printf("\n");

		//return a char* that doesn't use excess memory
		return realloc(str, sizeof(char) * length);

	} else {
		printf("Failure");
		return str;
	}

}


void writeFile(const char* text, const size_t length, const char* fileName) {
	
	FILE* file = fopen(fileName, "wb");

	for (int i = 0; i < length; i++)
		printf("%d ", text[i]);
	printf("\n");

	fwrite(text, sizeof(char), length, file);

	fclose(file);

}


char* reverseEncryption(const char* text, const char* cipher) {

	int textLength = strlen(text);
	int cipherLength = strlen(cipher);

	char* output = malloc(sizeof(char)*textLength);

	for (int i = 0; i < textLength; i++)
		output[i] = text[i] ^ cipher[i%cipherLength];
	
	return output;

}


//generate a new cipher that is of equal length to the text
char* generateNewCipher(const size_t length) {

	/*char* cipher;
	size_t size = 16;
	size_t length = 0;

	cipher = malloc(sizeof(char)*size);

	srand(time(NULL));

	for (length = 0; text[length] != '\0'; length++) {

		cipher[length] = (char) rand();

		if (length == size) {

			cipher = realloc(cipher, sizeof(char)*(size+=16));

			if (!cipher)
				return cipher;

		}

	}
	
	return realloc(cipher, sizeof(text)*length);*/

	char* cipher = malloc(length);
	for (int i = 0; i < length; i++)
		cipher[i] = (char) rand();

	return cipher;

}


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


int main(int argc, char* argv[]) {

	//cipher used for encrypting usernames and passwords
	char* decryptedCipher;

	//usernames, passwords, and other associated data
	char* decryptedText;

	printf("PASSWORD MANAGER\n");

	if ( access( PASSWORD_MANAGER_PATH , F_OK ) == -1 || access( CIPHER_PATH , F_OK ) == -1 ) {

		printf("Welcome...\n");
		printf("Please set a master password:\n");

		//read the master password from the console
		masterPassword = inputString(stdin);

		//there are no accounts stored yet
		accountsLength = 0;

	} else {

		printf("Please input your master password to unlock: ");

		//read the master password from the console
		masterPassword = inputString(stdin);

		//open the file that contains the encrypted cipher and decrypt it using the master password
		decryptedCipher = reverseEncryption( readFile(CIPHER_PATH) , masterPassword );

		//open the file that contains the encrypted usernames and passwords and decrypt it using the cipher
		decryptedText = reverseEncryption( readFile(PASSWORD_MANAGER_PATH) , decryptedCipher );

		//parse decrypted text into accounts array
		parseAccounts(decryptedText);

		printf("%s\n", readFile("Desktop/test.txt"));

	}

	short exit = 0;
	while (!exit) {

		printf("What do you want to do? (type \"0\" for instructions)\n");
		char* command = malloc(256);
		scanf(" %256s", command);

		switch(command[0]) {
			//view accounts
			case '1':
				viewAccounts();
				break;
			//generate a new password
			case '2':
				generateNewPassword();
				break;
			//add new account
			case '3':
				addNewAccount();
				break;
			//modify existing account
			case '4':
				modifyExistingAccount();
				break;
			//change the master password
			case '5':
				changeMasterPassword();
				break;
			//exit and save
			case '6':
				exit = 1;
				break;
			//show the help menu	
			default:
				displayHelp();
				break;
		}

		

	}

	//update decrypted text from accounts
	free(decryptedText);
	decryptedText = malloc( sizeof(char)*4*256 );

	for (int i = 0; i < accountsLength; i++) {
		strcat(decryptedText, accounts[i].accountName);
		strcat(decryptedText, "\t");
		strcat(decryptedText, accounts[i].username);
		strcat(decryptedText, "\t");
		strcat(decryptedText, accounts[i].password);
		strcat(decryptedText, "\t");
		strcat(decryptedText, accounts[i].notes);
		strcat(decryptedText, "\n");
	}

	strcat(decryptedText, "\0");

	decryptedText = realloc(decryptedText, strlen(decryptedText)+1);

	printf("%s\n", decryptedText);

	//generate new cipher text each time the program exits
	decryptedCipher = generateNewCipher( strlen(decryptedText) );

	/*printf("here\n");

	char* temp = reverseEncryption(decryptedText, decryptedCipher);

	printf("or here\n");

	char* temp2 = reverseEncryption(temp, decryptedCipher);

	printf("or maybe here\n");

	printf("%s\n", temp2);

	writeFile(temp2, "Desktop/test.txt");*/
	/*char* temp = malloc(10);

	for (char i = 0; i < 10; i++)
		temp[i] = i;

	writeFile(temp, "Desktop/test.bin");*/

	//encrypt the text with the cipher and sotre it to the password manager file
	writeFile( reverseEncryption(decryptedText, decryptedCipher), strlen(decryptedText)+1, PASSWORD_MANAGER_PATH );

	char* temp = reverseEncryption(decryptedText, decryptedCipher);
	for (int i = 0; i < strlen(decryptedText)+1; i++)
		printf("%d ", temp[i]);
	printf("\n");

	printf("%s\n", reverseEncryption(temp, decryptedCipher));

	/*

	"Floating point exception: 8" occurs sometime arround here
	- Doesn't occur every time, it may be an issue with how many accounts exist
	- has worked when there are multiple accounts

	- the cipher isn't the same length as the text for some reason

	*/

	//encrypt the cipher text using the master password and write it to the cipher file
	writeFile( reverseEncryption(decryptedCipher, masterPassword), strlen(decryptedText)+1, CIPHER_PATH);


	//free the memory allocated to pointers by malloc and realloc
	free(masterPassword);
	free(decryptedCipher);
	free(decryptedText);

	printf("\n");

	//program has ended successfully
	return 0;

}

