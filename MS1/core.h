/*
*****************************************************************************
                        Assignment 1 - Milestone 1
Full Name  : Harikrishna Paresh Patel
Student ID#: 150739217
Email      : Hpatel296@myseneca.ca
Section    : NII

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/


// Clear the standard input buffer 
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue 
void suspend(void);

// Prompt input from keyboard
int inputInt(void);

// Prompt user for positive interger
int inputIntPositive(void);

// Prompt user for values withing provided range
int inputIntRange(int lwb, int upb);

// Prompt for a character and validate it from the received character string 
char inputCharOption(const char* validChars);

// Prompt user for input of characters within the provided range
void inputCString(char* cString, int minChars, int maxChars);

// display phone number an array of 10 digit number
void displayFormattedPhone(const char* phone_No);