/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

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
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

 

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Get a valid integer from keyboard
int inputInt(void)
{
   char newline = 'x';
   int  value;
   while (newline != '\n')
   {
       // read an integer value as user input
       scanf("%d%c", &value, &newline);
       // if newline is found break out of the loop
       if (newline == '\n')
       {
           break;
       }
       // if newline is not found, clear the buffer
       // and display the error message
       else
       {
           clearInputBuffer();
           printf("Error! Input a whole number: ");
       }

   }
   
   return value;
}

int inputIntPositive(void)
{
  
   int value = inputInt();

   while (value <= 0)
   {
       printf("Error! Value must be > 0: ");
       value = inputInt();
   }
   
   return value;
}

int inputIntRange(int lower_limit, int upper_limit)
{
   int value = inputInt();
 
   while (value < lower_limit || value > upper_limit)
   {
       printf("Error! Value must be between %d and %d inclusive: ", lower_limit, upper_limit);
       value = inputInt();
   }

   return value;
}

char inputCharOption(const char* valid_characters)
{
   int  len = strlen(valid_characters);
   int  i;
   char option;
   while (1)
   {
       scanf(" %c", &option);
       if (getchar() != '\n')
       {
           printf("Error! Character must me one of [%s]: ", valid_characters);
           clearInputBuffer();
           continue;
       }
       int flag = 0;
 
       for (i = 0; i < len; i++)
       {
           if (option == valid_characters[i])
           {
               flag = 1;
               break;
           }
       }
       
       if (flag == 1)
       {
           break;
       }
      
       else
       {
           printf("Error! Character must me one of [%s]: ", valid_characters);
       }

   }
   
   return option;
}

void inputCString(char* inputString, int minLen, int maxLen)
{
   char tempString[100];
   while (1)
   {
       scanf(" %[^\n]%*c", tempString);
       if (minLen == maxLen)
       {
           
           if (strlen(tempString) != minLen)
           {
               printf("Error! String length must be exactly %d chars: ", minLen);
           }
           
           else
           {
               break;
           }
       }
       else
       {
           
           if (strlen(tempString) > maxLen)
           {
               printf("Error! String length must be no more than %d chars: ", maxLen);
           }
           
           else if (strlen(tempString) < minLen)
           {
               printf("Error! String length must be between %d and %d chars: ", minLen, maxLen);
           }
           
           else
           {
               break;
           }
       }
   }
   
   strcpy(inputString, tempString);
}

void displayFormattedPhone(const char* phone_number)
{
   
   if (phone_number == NULL)
   {
       printf("(___)___-____");
       return;
   }
   int i = 0;
   int count = 0;
   int len = strlen(phone_number);
   for (i = 0; i < len; i++)
   {
       if (phone_number[i] >= '0' && phone_number[i] <= '9')
       {
           count++;
       }
   }
  
   if (len != 10 || len != count)
   {
       printf("(___)___-____");
   }
   // display the formatted phone number
   else
   {
       printf("(%c%c%c)%c%c%c-%c%c%c%c",
           phone_number[0],
           phone_number[1],
           phone_number[2],
           phone_number[3],
           phone_number[4],
           phone_number[5],
           phone_number[6],
           phone_number[7],
           phone_number[8],
           phone_number[9]);
   }
}