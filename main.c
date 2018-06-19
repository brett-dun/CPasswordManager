
#include "passwordManager.h"

const char* SETTINGS_PATH = "Desktop/settings.data";
const char* CIPHER_PATH = "Desktop/cipher.data";
const char* PASSWORD_MANAGER_PATH = "Desktop/passwordManager.data";

unsigned int length = 8;
short uppercase = 1;
short lowercase = 1;
short numbers = 1;
short specialCharacters = 1;

/*
	Bugs/Features to Add
	- Allow accounts to be deleted
	- Store password generation settings
*/

int main(int argc, char* argv[]) {

	//length of the cipher
	unsigned long cipherLength;

	//cipher used for encrypting usernames and passwords
	char* decryptedCipher;

	//usernames, passwords, and other associated data
	char* decryptedText;

	printf("PASSWORD MANAGER\n");

	//if the files cannot be found
	if ( access( PASSWORD_MANAGER_PATH , F_OK ) == -1 || access( CIPHER_PATH , F_OK ) == -1 /*|| access( SETTINGS_PATH, F_OK ) != -1*/ ) {

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

		//the cipher that has not yet been decrypted
		char* encryptedCipher;

		//read the encrypted cipher
		readFile(&encryptedCipher, &cipherLength, CIPHER_PATH);

		//open the file that contains the encrypted cipher and decrypt it using the master password
		decryptedCipher = reverseEncryption( encryptedCipher, cipherLength, masterPassword , strlen(masterPassword));

		char* encryptedText;
		unsigned long encryptedTextLength;

		readFile(&encryptedText, &encryptedTextLength, PASSWORD_MANAGER_PATH);

		//open the file that contains the encrypted usernames and passwords and decrypt it using the cipher
		decryptedText = reverseEncryption( encryptedText, encryptedTextLength, decryptedCipher, cipherLength);

		//parse decrypted text into accounts array
		parseAccounts(decryptedText);

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

	//concatenate all of the dat from the accounts together
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

	//append null terminating character
	strcat(decryptedText, "\0");

	//reallocate memory to save space
	decryptedText = realloc(decryptedText, strlen(decryptedText)+1);

	//generate new cipher text each time the program exits correctly
	decryptedCipher = generateNewCipher( strlen(decryptedText) );
	//store the length of the cipher
	cipherLength = strlen(decryptedText);

	//encrypt the text with the cipher and sotre it to the password manager file
	writeFile( reverseEncryption(decryptedText, strlen(decryptedText), decryptedCipher, cipherLength), strlen(decryptedText), PASSWORD_MANAGER_PATH );

	//encrypt the cipher text using the master password and write it to the cipher file
	writeFile( reverseEncryption(decryptedCipher, cipherLength, masterPassword, strlen(masterPassword)), strlen(decryptedText)+1, CIPHER_PATH);

	//free the memory allocated to pointers by malloc and realloc
	free(masterPassword);
	free(decryptedCipher);
	free(decryptedText);

	printf("\n");

	//program has ended successfully
	return 0;

}

