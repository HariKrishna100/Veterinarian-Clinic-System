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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
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


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{

    struct Date d;
    displayScheduleTableHeader(&d, 1);
    sortAppointments(data);
    int i = 0;
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientData.patientNumber > 0)
        {
            displayScheduleData(&data->patients[findPatientIndexByPatientNum(data->appointments[i].patientData.patientNumber, data->patients, data->maxPatient)], &data->appointments[i], 1);
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    struct Date d;
    int i = 0;

    sortAppointments(data);

    printf("Year        : ");
    d.year = inputIntPositive();

    printf("Month (1-12): ");
    d.month = inputIntRange(1, 12);

    int febdays = d.year % 4 == 0 ? 29 : 28;
    int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    printf("Day (1-%d)  : ", months[d.month - 1]);
    d.day = inputIntRange(1, months[d.month - 1]);
    putchar('\n');

    displayScheduleTableHeader(&d, 0);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientData.patientNumber > 0)
        {
            if (isEqual(&d, &data->appointments[i].date))
            {

                displayScheduleData(&data->patients[findPatientIndexByPatientNum(data->appointments[i].patientData.patientNumber, data->patients, data->maxPatient)], &data->appointments[i], 0);
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int isavailable = 0, done = 0, patientDone = 0, dateDone = 0, timeDone = 0, number = 0, isSame = 0;
    int i = 0, end_Min = 0;
    struct Date d;
    struct Time t;

    for (i = 0; i < maxAppointments && !isavailable; i++)
    {
        if (appointments[i].patientData.patientNumber < 1)
        {
            isavailable = i;
        }
    }
    while (!done && isavailable)
    {
        while (!patientDone)
        {
            printf("Patient Number: ");
            number = inputIntPositive();
            int result = findPatientIndexByPatientNum(number, patients, maxPatient);
            if (result > -1)
            {
                patientDone = 1;
            }
            else
            {
                printf("Invalid Entry, try again: \n");
            }
        }
        while (!dateDone)
        {
            printf("Year        : ");
            d.year = inputIntPositive();
           
            printf("Month (1-12): ");
            d.month = inputIntRange(1, 12);

            int febdays = d.year % 4 == 0 ? 29 : 28;
            int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            printf("Day (1-%d)  : ", months[d.month - 1]);
            d.day = inputIntRange(1, months[d.month - 1]);

            dateDone = 1;
        }
        while (!timeDone)
        {
            end_Min = 0;
            printf("Hour (0-23)  : ");
            t.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            t.min = inputIntRange(0, 59);
            if (t.hour == END_HOUR) {
                if (t.min != 0) {
                    end_Min = 1;
                }
            }

            if (t.hour >= START_HOUR && t.hour <= END_HOUR && (t.min % INTERVAL == 0) && !end_Min)
            {
                timeDone = 1;
            }
            else
            {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, INTERVAL);
            }
        }
        isSame = 0;
        for (i = 0; i < maxAppointments && !isSame; i++)
        {
            if (isEqual(&d, &appointments[i].date) && appointments[i].time.hour == t.hour && appointments[i].time.min == t.min)
            {
                isSame = 1;
            }
        }
        if (isSame)
        {
            printf("\n"
                "ERROR: Appointment timeslot is not available!\n\n");
            dateDone = 0;
            timeDone = 0;
        }
        else
        {
            done = 1;
            appointments[isavailable].date = d;
            appointments[isavailable].time = t;
            appointments[isavailable].patientData.patientNumber = number;
            printf("\n"
                "*** Appointment scheduled! ***\n\n");
        }
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int i = 0, found = 0, newindex = 0;

    printf("Patient Number: ");
    int number = inputIntPositive();
    int result = findPatientIndexByPatientNum(number, patients, maxPatient);

    if (result == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        struct Date d;
        printf("Year        : ");
        d.year = inputIntPositive();

        int febdays = d.year % 4 == 0 ? 29 : 28;
        int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        printf("Month (1-12): ");
        d.month = inputIntRange(1, 12);

        printf("Day (1-%d)  : ", months[d.month - 1]);
        d.day = inputIntRange(1, months[d.month - 1]);

        for (i = 0; i < maxAppointments && !found; i++)
        {
            if ((appointments[i].patientData.patientNumber == number) && isEqual(&d, &appointments[i].date))
            {
                found = 1;
                newindex = i;          
            }
        }
        putchar('\n');

        displayPatientData(&patients[result], FMT_FORM);
        printf("Are you sure you want to remove this appointment (y,n): ");
        char option = inputCharOption("yn");

        if (option == 'y')
        {
            appointments[newindex].patientData.patientNumber = 0;
            appointments[newindex].date.year = 0;
            appointments[newindex].date.month = 0;
            appointments[newindex].date.day = 0;
            printf("\n"
                "Appointment record has been removed!\n");
        }
        else
        {
            printf("\n"
                " Operation Aborted!\n");
        }

        putchar('\n');
    }
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
    // when data is not zero
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

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    int read = 0;

    if (fp != NULL)
    {
        while (!feof(fp) && read < max)
        {
            fscanf(fp, "%d|%29[^|]|%4[^|]|", &patients[read].patientNumber, patients[read].name, patients[read].phone.description);

            if (!(strcmp(patients[read].phone.description, "TBD") == 0))
            {
                fscanf(fp, "%[^\n]%*c", patients[read].phone.number);
            }
            read++;
        }
        fclose(fp);
    }
    return read;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    int read = 0;

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[read].patientData.patientNumber, &appoints[read].date.year, &appoints[read].date.month, &appoints[read].date.day, &appoints[read].time.hour, &appoints[read].time.min) == 6 && read < max)
        {

            read++;
        }
        fclose(fp);
    }

    return read;
}

//////////////////////////////////////
// HELPER FUNCTIONS 
//////////////////////////////////////

// sort appointments data
void sortAppointments(struct ClinicData* data)
{
    int i, j;
    struct Appointment temp;

    for (i = data->maxAppointments - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (dateSet(&data->appointments[j].date, &data->appointments[j].time) > dateSet(&data->appointments[j + 1].date, &data->appointments[j + 1].time) && data->appointments[j].patientData.patientNumber > 0 && data->appointments[j + 1].patientData.patientNumber > 0)
            {
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
        }
    }
}

// verify date match for setting
int isEqual(const struct Date* d1, const struct Date* d2)
{
    return d1->year == d2->year && d1->month == d2->month && d1->day == d2->day;
}

// set dates
int dateSet(const struct Date* d, const struct Time* t)
{
    return d->year * 100000 + d->month * 10000 + d->day * 1000 + t->hour * 100 + t->min; // this
}