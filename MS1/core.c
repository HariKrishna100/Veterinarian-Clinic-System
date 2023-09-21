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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
};

// Prompt input from keyboard
int inputInt()
{
    int num = 0;
    char newline = '0';

    // validate input when enter key is hit
    while (newline != '\n')
    {
        scanf("%d%c", &num, &newline);

        // when enter key is hit exit loop
        if (newline == '\n')
        {
            break;
        }
        // Clear Memory and retake input
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    return num;
}

// Prompt user for positive interger
int inputIntPositive()
{
    int num;

    num = inputInt(); // get input

    // Prompt input until value is a positive number
    while (num <= 0)
    {
        printf("ERROR! Value must be > 0: ");
        num = inputInt();
    }
    return num;
}

// Prompt user for values withing provided range
int inputIntRange(int lwb, int upb)
{
    int num;

    num = inputInt();

    // Keep prompting user input it meets the range
    while (num < lwb || num > upb)
    {
        printf("ERROR! Value must be between %d and %d inclusive: ", lwb, upb);
        num = inputInt();
    }
    return num;
}

// Prompt for a character and validate it from the received character string 
char inputCharOption(const char* validChars)
{
    char cinput;
    int i, flag = 0;
    int len = strlen(validChars);

    // Exit when user input matches any valid letter from string provided
    // while not matching display error message indicating the valid string
    while (flag == 0)
    {
        scanf(" %c", &cinput);

        if (getchar() != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
            clearInputBuffer();
            flag = 0;
        }
        else
        {
            // check if user input matches any character from string provided
            for (i = 0; i < len; i++)
            {
                if (cinput == validChars[i])
                {
                    flag = 1;
                }
            }

            if (flag == 0)
            {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
            else
            {
                flag = 1;
            }
        }
    }
    return cinput;
}

// Prompt user for input of characters within the provided range
void inputCString(char* cString, int minChars, int maxChars)
{
    char inputCString[100 + 1];
    int flag = 0;

    // Exit when string lenght meets the range provided
    // Until its not meeting the requirments display error message and provide range
    while (flag == 0)
    {
        scanf(" %[^\n]%*c", inputCString);

        // when minimun length equals maximun lenght
        if (minChars == maxChars)
        {

            if (strlen(inputCString) != minChars)
            {
                printf("ERROR: String length must be exactly %d chars: ", maxChars);
            }
            else
            {
                flag = 1;
            }
        }
        else
        {
            if (strlen(inputCString) > maxChars)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChars);

            }
            else if (strlen(inputCString) < minChars)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChars, maxChars);
            }
            else
            {
                flag = 1;
            }
        }
    }
    strcpy(cString, inputCString);
}

// display phone number an array of 10 digit number
void displayFormattedPhone(const char* phone_No)
{
    int i = 0, count = 0, len = 0;

    if (phone_No == NULL)
    {
        printf("(___)___-____");
        return;
    }

    len = strlen(phone_No);

    // Check is phone number length is 10 digits
    for (i = 0; i < len; i++)
    {
        if (phone_No[i] >= '0' && phone_No[i] <= '9')
        {
            count++;
        }
    }

    if (len != 10 || len != count)
    {
        printf("(___)___-____");
    }
    else
    {
        printf("(%c%c%c)%c%c%c-%c%c%c%c",
            phone_No[0],
            phone_No[1],
            phone_No[2],
            phone_No[3],
            phone_No[4],
            phone_No[5],
            phone_No[6],
            phone_No[7],
            phone_No[8],
            phone_No[9]);
    }
}