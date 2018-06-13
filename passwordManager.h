
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

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

extern const char* CIPHER_PATH;
extern const char* PASSWORD_MANAGER_PATH;

//password that unlocks the cipher
char* masterPassword;

//array of Account structs which is used to store data from decrypted text in a way that is easier to modify and update
//Account (*accounts)[];
Account* accounts;
unsigned long accountsLength;

//password settings - consider storing these settings into a file
extern unsigned int length;
extern short uppercase;
extern short lowercase;
extern short numbers;
extern short specialCharacters;

//Function prototypes
char* inputString(FILE* fp);

void displayHelp();
void viewAccounts();
void addNewAccount();
void modifyExistingAccount();
void generateNewPassword();
void changeMasterPassword();

long randLong(const long max);
char* readFile(const char* fileName);
void writeFile(const char* text, const size_t length, const char* fileName);
char* reverseEncryption(const char* text, const char* cipher);
char* generateNewCipher(const size_t length);
void parseAccounts(const char* str);

#endif