
#include "passwordManager.h"


const char* CIPHER_PATH = "Desktop/cipher.data";
const char* PASSWORD_MANAGER_PATH = "Desktop/passwordManager.data";

unsigned int length = 8;
short uppercase = 1;
short lowercase = 1;
short numbers = 1;
short specialCharacters = 1;

unsigned long cipherLength;

/*
	Bugs/Features to Add
	- Fix encryption/decryption -> figure out how to determine the length of the char*
	- Allow accounts to be deleted
*/

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

		//printf("reading cipher\n");

		char* encryptedCipher;

		readFile(&encryptedCipher, &cipherLength, CIPHER_PATH);

		//printf("%s\n", encryptedCipher);
		//printf("%lu\n", cipherLength);

		//printf("file 1 read\n");

		//open the file that contains the encrypted cipher and decrypt it using the master password
		decryptedCipher = reverseEncryption( encryptedCipher, cipherLength, masterPassword , strlen(masterPassword));

		//printf("reading text\n");

		char* encryptedText;
		unsigned long encryptedTextLength;

		readFile(&encryptedText, &encryptedTextLength, PASSWORD_MANAGER_PATH);

		//printf("file 2 read\n");

		//open the file that contains the encrypted usernames and passwords and decrypt it using the cipher
		decryptedText = reverseEncryption( encryptedText, encryptedTextLength, decryptedCipher, cipherLength);

		//parse decrypted text into accounts array
		parseAccounts(decryptedText);

		//printf("%s\n", readFile("Desktop/test.txt"));

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

	//printf("%s\n", decryptedText);

	//generate new cipher text each time the program exits
	decryptedCipher = generateNewCipher( strlen(decryptedText) );
	cipherLength = strlen(decryptedText);

	//printf("here\n");

	/*char* eText = reverseEncryption(decryptedText, decryptedCipher);

	//printf("or here\n");

	char* eCipher = reverseEncryption(decryptedCipher, masterPassword);

	char* dCipher = reverseEncryption(eCipher, masterPassword);
	//printf("dCipher: %s\n", dCipher);

	char* dText = reverseEncryption(eText, dCipher);

	//printf("or maybe here\n");

	printf("dText: %s\n", dText);*/

	//writeFile(temp2, "Desktop/test.txt");*/
	/*char* temp = malloc(10);

	for (char i = 0; i < 10; i++)
		temp[i] = i;

	writeFile(temp, "Desktop/test.bin");*/

	//printf("writing text\n");
	//encrypt the text with the cipher and sotre it to the password manager file
	writeFile( reverseEncryption(decryptedText, strlen(decryptedText), decryptedCipher, cipherLength), strlen(decryptedText), PASSWORD_MANAGER_PATH );

	/*char* temp = reverseEncryption(decryptedText, decryptedCipher);
	for (int i = 0; i < strlen(decryptedText)+1; i++)
		printf("%d ", temp[i]);
	printf("\n");*/

	//printf("%s\n", reverseEncryption(temp, decryptedCipher));

	/*

	"Floating point exception: 8" occurs sometime arround here
	- Doesn't occur every time, it may be an issue with how many accounts exist
	- has worked when there are multiple accounts

	- the cipher isn't the same length as the text for some reason

	*/

	//printf("writing cipher\n");

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

