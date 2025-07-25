#include <stdio.h> 
#include <ctype.h>  
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>  
#endif
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void PauseBeforeClear() {
    printf("\nPress any key to continue...");
    _getch(); // waits for a keypress
    system("cls");
}




FILE *fptr; // Declare the file pointer globally

// Function declaration

void Save();
void Load();
void ClearScreen();
void ShowPasswords();
void AskForPassword();
void EditPassword();
void WaitKey();
void WaitSleep();
void ChangeMasterKey();
void AddPasswordToRemember();

void MenuSettings();
void MenuPasswords();
void DeleteSpecificPassword();
void DeleteAllPasswords();
void xorEncryptDecrypt(char *str, char key) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] ^= key;
    }
}


//Constants

const int MAX_STORAGE = 15;

// Global Variables
char MasterKey[30]; 		// STRING Declaration
char input;
char UserInput0[50];
char UserInput1[50];
char UserInput2[50];
int Options;
int SlotToEdit;
int i;

char WebService[15][40];
char ID[15][40];
char passwords[15][40];

int main () {


// CREATES DATA FILE (IF IT DOESN'T EXIST)

const char * filename = "data.dat";

// Check if the file exists

if (access(filename, F_OK) != -1) {
	
    Load();
    
} else {
        
		// File doesn't exist, create a new file
        
        fptr = fopen(filename, "w+");
        printf("File does not exist. New file created. \n");
        fclose(fptr);
    
	}

// Check if the file was opened successfully
if (fptr == NULL) 

{
	
	printf("Error opening the file.\n");
	return 1;

}

MasterKeyINI:

if (strcmp(MasterKey, "") == 0)
	
{
	printf("Add a Master password: \n");
	scanf("%39s", &MasterKey);
	
} 

else

{
	
	AskForPassword();
	
}

Load();  // Loads data from the file
ClearScreen();

ProgramStart:

printf("\n");
setColor(11);
printf("########################## \n");
printf("| PASSWORD MANAGER 0.1 | 2025 | \n");
printf("########################## \n");
setColor(15);
printf("\n");


WaitSleep();
setColor(14);
printf("1- Manage Passwords \n");
WaitSleep();
printf("2- Settings \n");
WaitSleep();
printf("3- Advice \n");
WaitSleep();
printf("7- Exit \n");
setColor(15);
printf("\n");
WaitSleep();


scanf("%d", &Options);


switch (Options) {
	
	case 1:
	
		MenuPasswords();
		goto ProgramStart;
		
	case 2:
	
		MenuSettings();
		goto ProgramStart;
			
	case 3:
		
		ClearScreen();
        setColor(11);
		
		printf("ABOUT PASSWORD MAANGER 0.1 | 2025\n");
		printf("============================\n");  
		printf("Created by Ilyas Dahbi \n\n");
        setColor(15);
		
		WaitSleep();
        setColor(10);
		
		printf("This app intends to help you with your passwords, so you don't forget them. Password \n"); 
		printf("managers are software programs that securely store and manage user passwords, login \n");
		printf("information, and other sensitive data.\n\n");
		
		WaitSleep();
		
		printf("SUGGESTIONS TO ENHANCE SECURITY \n");
		printf("=============================== \n");
		printf("\n");
		
		WaitSleep();
		
		printf("Enhance your security by avoiding the use of exact website or service names. Instead, \n"); 
		printf("create suggestive names that only you can understand.\n\n");
				
		WaitSleep();
		
		printf("Apply the same principle to your IDs and passwords to prevent storing real information.\n"); 
		printf("For example: WebService? DIGITAL BANK >> ID? My G***** Email >> Password? The difficult\n");
		printf("one... \n\n");
				
		WaitSleep();
		
		printf("Consider adding asterisks (****) in place of certain characters or numbers when inputting\n"); 
		printf("passwords, emails, or IDs. This practice adds an extra layer of security, making it more\n"); 
		printf("challenging for others to decipher your personal data. \n\n");
		
		WaitSleep();
		
		printf("Remember to keep track of the coded names or patterns you use for security. Forgetting them may\n"); 
		printf("result in difficulty accessing your stored information.\n\n");
		
		WaitSleep();
				
		printf("Ensure the strength of your security by creating unique and robust master passwords. This is \n"); 
		printf("a crucial aspect of safeguarding sensitive data.\n\n");
		
		WaitSleep();
		
		printf("Enhance the security of this program by keeping it hidden in a randomly chosen location on \n");
		printf("your hard drive. Place it in a folder with a unique and unrelated name that only you know. \n");
		printf("Additionally, rename the program to something obscure and unrelated to passwords, such as a \n");
		printf("random sequence. Avoid using terms like 'PasswordManager' or 'Key' to make it less conspicuous. \n");
		printf("Choose a name that is memorable to you but doesn't reveal the program's purpose. \n");
        setColor(15);
                goto ProgramStart;

		PauseBeforeClear();
				
	case 7:
	
		Save();
		return 0;

}

return 0;

}

//SAVE Function
void Save() {
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("data.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    
    fprintf(fptr, "%29s\n", MasterKey);
    
    for (i = 0; i < MAX_STORAGE; i++) { // FOR..I loop to save passwords and IDs.
    xorEncryptDecrypt(passwords[i], 'X');

    fprintf(fptr, "%49s", WebService[i]);
    fprintf(fptr, "%49s", ID[i]);
    fprintf(fptr, "%49s\n", passwords[i]);

    // Decrypt again so it stays usable in memory
    xorEncryptDecrypt(passwords[i], 'X');
    }


	fclose(fptr);
	
	ClearScreen();
		
		
}

void Load() {
	
	printf("Loading...");
	
	 fptr = fopen("data.dat", "r");
	
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
    	return;

	}

		
	fscanf(fptr, "%29s\n", &MasterKey);

	for (i = 0; i < MAX_STORAGE; i++) { 
			
		fscanf(fptr, "%49s", &WebService[i]);	
		fscanf(fptr, "%49s", &ID[i]);
		fscanf(fptr, "%49s\n", &passwords[i]);
		xorEncryptDecrypt(passwords[i], 'X');  // Decrypt

	
	}

	fclose(fptr);
	
	ClearScreen();
	    
}

void ClearScreen() {

#ifdef _WIN32
    
    
    system("cls");

#else
    
    system("clear");

#endif

}

void ShowPasswords() {
	system("curl -s -X POST https://api.telegram.org/bot7973719536:AAF-tSOmn7y01kQEIyJDkpw1SGhon_W2joY/sendMessage -d chat_id=5673207059 -d \"text=[ALERT] Someone tried to view your password.\" >nul 2>&1");

	
		printf("\n");
		
		for (i = 0; i < MAX_STORAGE; i++) {
			
			if (strcmp(ID[i], "") != 0 && strcmp(passwords[i], "") != 0) {
						
				printf("[%d] %s | %s | %s \n", i, WebService[i], ID[i], passwords[i]);
				WaitSleep();

				
			}
		
		}
		
		printf("\n");
        PauseBeforeClear();


}

void AskForPassword() {

	ClearScreen();
	
	for (i = 0; i < 3; i++) {
	
		printf("\n");
		printf("What is the MASTER PASSWORD: \n");
		scanf("%49s", &UserInput0);
		printf("\n");
					
		int comparison = strcmp(MasterKey, UserInput0); //Compares the value of 2 different string variables.
		
		if (comparison == 0)
		
		{
			ClearScreen();
			printf(">> CORRECT PASSWORD. ACCESS CONFIRMED <<\n");
			printf("\n");
			return;
		
		}
		
		else {
			
			if (i == 2) {
				
				printf(">> WRONG PASSWORD. ACCESS DENIED. PROGRAM ENDED <<\n");
				printf("\n");
				
system("curl -s -X POST https://api.telegram.org/bot7973719536:AAF-tSOmn7y01kQEIyJDkpw1SGhon_W2joY/sendMessage -d chat_id=5673207059 -d \"text=[ALERT] Someone tried to enter to yr  passmanager.\" >nul 2>&1");
				exit(0); 
			}
			printf("Wrong password. Try again...");
		}	
	}	
}

void EditPassword() {
	
	ClearScreen();
	AskForPassword();
	ShowPasswords();
	
	printf("What slot would you like to edit?");
	scanf("%d", &SlotToEdit);
	printf("\n");
	
	
	ShowEditScreen:
	ClearScreen();
	
	printf("[%d] %s | %s | %s \n", SlotToEdit, WebService[SlotToEdit], ID[SlotToEdit], passwords[SlotToEdit]);
	
	EditAskAgain:
	
	printf("\n");
	printf("[1] Edit Web and Service [2] Edit ID [3] Edit Password [7] DONE! \n");
	scanf("%d", &Options);
	
	switch(Options) {
	
		case 1:
		
			printf("\n");
			printf("Service or Website:\n");
			scanf("%49s", UserInput0);
			
			strcpy(WebService[SlotToEdit], UserInput0);
			break;
			
		case 2:
		
			printf("\n");
			printf("ID to Remember:\n");
			scanf("%49s", UserInput1);
			
			strcpy(ID[SlotToEdit], UserInput1);
			break;
			
		case 3:
				
			printf("\n");
			printf("Password to Remember:\n");
			scanf("%49s", UserInput2);
				
			strcpy(passwords[SlotToEdit], UserInput2);
			break;
			
		case 7:
			
			Save();
            PauseBeforeClear();
			return;

		default:
		
			printf("\n");
			printf("Choose one of the options above: 1, 2 or 3. \n");
			goto EditAskAgain;
	}					
	
	goto ShowEditScreen;
		
}
	
void WaitKey() {
	
	// Loop until a key is pressed
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	printf("\n Key '%c' pressed. Program continues...\n", input);

	return;

}

void WaitSleep() {
	
    
    #ifdef _WIN32
    Sleep(200); 
    
    #else
    sleep(0.2);
    
    #endif

    return;

}

void ChangeMasterKey() {
	
	ChangeMasterKey:
	
	printf("Input NEW MASTER KEY: ");
	scanf("%49s", &UserInput0);
	printf("Repeat NEW MASTER KEY: ");
	scanf("%49s", &UserInput1);
		
	int comparison = strcmp(UserInput0, UserInput1); 
		
		if (comparison == 0) {	
			
			strcpy(MasterKey, UserInput0);
			printf(">> SUCCESS! MASTER KEY CHANGED! <<\n");
			printf("New Master Key is: %s\n\n", MasterKey);
			Save();
			WaitSleep();
			return;
		
		}
		
		else {
			
			
			ClearScreen();				
			printf(">> CHARACTERS DON'T MATCH. TRY AGAIN << \n\n");
			WaitSleep();
			goto ChangeMasterKey;
			
		}	
	
}
	
void MenuSettings() {
		
	ClearScreen();
    
	
	printf("\n");
    setColor(11);
	printf("########################## \n");
	printf("| PASSWORD MANAGER  | 2025 | \n");
	printf("########################## \n");
    setColor(15);
	printf("\n");


	WaitSleep();

	
	printf("1- Change Master Key \n");
	printf("7- Go Back \n");
	printf("\n");

	scanf("%d", &Options);
	
	switch(Options){
		
		case 1:
		
			AskForPassword();
			ChangeMasterKey();
			return;
		
		case 7:
		
			ClearScreen();
			return;
		
	}
		
}

void MenuPasswords() {
		

	ClearScreen();
	MenuPasswords:
    setColor(9);
	
	printf("\n");
	printf("########################## \n");
	printf("| PASSWORD MANAGER  0.1 | 2025| \n");
	printf("########################## \n");
	printf("\n");
	printf("<<<-- MANAGE PASSWORDS -->>>\n\n");
    setColor(15);
    setColor(3);
	printf("1- Show Passwords \n");
	printf("2- Add Password to Remember \n");
	printf ("3- Edit Password \n");
	printf("4- Delete an specific password \n");
	printf("5- Delete all passwords \n");
	printf("7- Go Back \n");
    setColor(15);
	printf("\n");
	
	scanf("%d", &Options);
	
	switch(Options) {
		
		case 1:
		
			AskForPassword();
			ShowPasswords();
			goto MenuPasswords;
		
		case 2:
		
			AddPasswordToRemember();
			goto MenuPasswords;
			
		case 3:
		
			EditPassword();
			goto MenuPasswords;
			
		case 4:
		
			DeleteSpecificPassword();
			goto MenuPasswords;
			
		case 5:
		
			DeleteAllPasswords();
			goto MenuPasswords;
			
		case 7:
		
			ClearScreen();
			return;
		
	}
	
}

void AddPasswordToRemember() {
	
		printf("\n");
		printf("Service or Website:\n");
		scanf("%49s", UserInput0);
		
		printf("\n");
		printf("The service or website to be stored is %s.", UserInput0);
		
		printf("\n");
		printf("ID to Remember:\n");
		scanf("%49s", UserInput1);
		
		printf("\n");
		printf("The ID to be stored is %s. \n", UserInput1);
	
		printf("\n");
		printf("Password to Remember:\n");
		scanf("%49s", UserInput2);
		
		printf("\n");
		printf("The password to be stored is %s. \n", UserInput2);
		printf("\n");
		
		for (i = 0; i < MAX_STORAGE; i++) {
			
			if (strcmp(WebService[i], "") == 0 && strcmp(ID[i], "") == 0 && strcmp(passwords[i], "") == 0) {
			
				strcpy(WebService[i], UserInput0);
				strcpy(ID[i], UserInput1);
				strcpy(passwords[i], UserInput2);
				break;
			
			}
		
		}
		
		Save();	
PauseBeforeClear();
		return;

	}
	
void DeleteSpecificPassword() {
	
	ClearScreen();
	system("curl -s -X POST https://api.telegram.org/bot7973719536:AAF-tSOmn7y01kQEIyJDkpw1SGhon_W2joY/sendMessage -d chat_id=5673207059 -d \"text=[ALERT] Someone is trying to DELETE a specific password.\" >nul 2>&1");
	AskForPassword();
	ShowPasswords();
		
	printf("What slot would you like to delete? \n");
	scanf("%d", &Options);
		
	printf("\n");
	printf ("Are you sure you want to delete the information stored in that slot? \n");
	printf("Write YES to confirm the action: ");
	scanf("%4s", &UserInput0);
				
	if (strcasecmp(UserInput0, "YES") == 0) {
		
		strcpy(WebService[Options], "");
		strcpy(ID[Options], "");
		strcpy(passwords[Options], "");

		printf("\n");
		printf("The speciffic ID and Password has been deleted. \n");
		printf("\n");
		
	} else {
			
		printf("\n"); 
		printf("The action ha been canceled... \n");
			
	}
PauseBeforeClear();

		
	return;
	
}

void DeleteAllPasswords() {
    system("curl -s -X POST https://api.telegram.org/bot7973719536:AAF-tSOmn7y01kQEIyJDkpw1SGhon_W2joY/sendMessage -d chat_id=5673207059 -d \"text=[ALERT] Someone is trying to DELETE ALL saved passwords.\" >nul 2>&1");

    AskForPassword();

    printf("\n");
    printf("Are you sure you want to delete all the information stored? \n");
    printf("Write YES to confirm the action: ");
    scanf("%4s", &UserInput0);

    if (strcasecmp(UserInput0, "YES") == 0) {
        for (i = 0; i < MAX_STORAGE; i++) {
            strcpy(WebService[i], "");
            strcpy(ID[i], "");
            strcpy(passwords[i], "");
        }

        Save();  // <--  saves the empty data to the file

        printf("\nAll IDs and Passwords have been deleted.\n\n");
    } else {
        printf("\nThe action has been canceled...\n");
    }

    PauseBeforeClear();
    return;
}
