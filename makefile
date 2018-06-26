
CC=clang
CFLAGS=-I.
DEPS = passwordManager.h
OBJ = main.o displayHelp.o inputString.o generateNewPassword.o changeMasterPassword.o addNewAccount.o modifyExistingAccount.o viewAccounts.o randLong.o readFile.o writeFile.o reverseEncryption.o generateNewCipher.o parseAccounts.o deleteAccount.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)