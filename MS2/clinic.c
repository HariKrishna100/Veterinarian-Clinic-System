/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0; 

    if (max == 0)
    {
        printf("*** No records found ***");
    }
    else
    {
        // check for patient records
        for (i = 0; i < max; i++)
        {
            // when the record is valid
            // display patients information
            if (patient[i].patientNumber != 0)
            {
                displayPatientTableHeader();
                for (i = 0; i < max; i++)
                {
                    if (patient[i].patientNumber != 0)
                        displayPatientData(&patient[i], fmt);
                }
            }
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {
        // display search menu
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        // Prompt user input providing the valid menu range
        selection = inputIntRange(0, 2);
        putchar('\n');

        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int freeindex, i = 0, flag = 0;

    // check patients data array if there is a space to add a new record
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            freeindex = i;
            flag = 1;
            break;
        }
    }

    // When flag is 0 there is no space
    //  to accomodate new patient within the slot
    if (flag == 0)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    // when flag is 1 there is space so you can add the Patient data 
    else
    {
        // call nextPatientNumber Function to get the patient unique number
        patient[freeindex].patientNumber = nextPatientNumber(patient, max);

        // Enter Pateints Record
        inputPatient(&patient[freeindex]);
        printf("*** New patient record added ***\n");
    }
    putchar('\n');
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int num, index;

    // Get patient number of record to modify
    printf("Enter the patient number: ");
    num = inputInt();

    // find the index in patients array by patients number
    index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');

    // when index does not exist display error message
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    // Call function menuPatientEdit and pass the patients to be modified
    else
    {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    char decision;
    int num, index = 0;

    // Get patient number of record to be discarded
    printf("Enter the patient number: ");
    num = inputInt();

    // find the index in patients array by patients number
    index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');

    // when index does not exist display error message
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        // Display patients record
        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)\n\n", patient[index].phone.description);

        // Prompt user confirmation to discard the record
        printf("Are you sure you want to remove this patient record? (y/n): ");
        decision = inputCharOption("yn");

        // when user decision is y discard record
        if (decision == 'y')
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
        // cancel record discardation
        else
        {
            printf("Operation aborted.\n");
        }
    }
    putchar('\n');
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int num, index;

    // Get patient number of record to be lookup
    printf("Search by patient number: ");
    num = inputInt();

    // find the index in patients array by patients number
    index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');

    // when index does not exist display error message
    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    // display patient record by calling displayPatientData
    // passing the patients index for patients data to be shown
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNo[PHONE_LEN + 1];
    int i, flag = 0;

    // promt user input for phone number to be looked up
    printf("Search by phone number: ");
    inputCString(phoneNo, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    // check phone number entered matches patients phone number

    for (i = 0; i < max; i++)
    {
        // Display a the Patient data
        if (strcmp(phoneNo, patient[i].phone.number) == 0)
        {
            flag = 1;
            break;
        }
    }
    
    // display table header
    displayPatientTableHeader();
    // when value is not zero
    if (flag == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    else
    {
        for (i = 0; i < max; i++)
        {
            // display single patient record
            if (strcmp(phoneNo, patient[i].phone.number) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    putchar('\n');

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, next = -1;

    // find largest patient number in the array
    // store it in next variable
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > next)
        {
            next = patient[i].patientNumber;
        }
    }
    ++next;

    return next;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, notFound = -1;

    // check patients array when patient number equalls patient number

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            notFound = i;
            break;
        }
    }

    return notFound;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
    // Prompt user input for adding patient data
    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
    int selection;

    // display menu for phone contact information
    printf("Phone Information\n"
        "-----------------\n");
    printf("How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    // Prompt user input providing the valid menu range
    selection = inputIntRange(1, 4);
    putchar('\n');

    // validate menu selection
    // And copy phone description accordingly
    if (selection == 1)
    {
        printf("Contact: ");
        puts("CELL");
        strcpy(phone->description, "CELL");
    }
    if (selection == 2)
    {
        printf("Contact: ");
        puts("HOME");
        strcpy(phone->description, "HOME");
    }
    if (selection == 3)
    {
        printf("Contact: ");
        puts("WORK");
        strcpy(phone->description, "WORK");
    }
    if (selection == 4)
    {
        strcpy(phone->description, "TBD");
    }
    else
    {
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
    }
}