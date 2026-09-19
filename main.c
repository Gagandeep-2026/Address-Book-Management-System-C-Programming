/*
Description :
Name            : Gagandeep MT
Roll No         : 26012_071
Start date      : 17/07/2026
End date        : 19/07/2026
Sample input    : 

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 1
Press 0 to Cancelle the operation
Enter the name :Gagandeep MT
Enter the number:8861656648
Enter the Email: gagandeepmt08@gmail.com
----------------------------------------------------------------------
11      Gagandeep       8861656648      gagandeepmt08@gmail.com
----------------------------------------------------------------------
Contact created Successfully

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 2
1. Search by name: 
2. Search by phone: 
3. Search by email: 
4. exit
Enter the choice:1
Enter the name :Alice Smith
----------------------------------------------------------------------
2       Alice Smith     0987654321      alice@example.com
----------------------------------------------------------------------

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 3
1.Edit by name:
2.Edit by Phonenumber:
3.Edit by email:
4.Exit
Enter the choice:1
Enter the name :Eve Davis
----------------------------------------------------------------------
6       Eve Davis       6665554444      eve@example.com
----------------------------------------------------------------------
Enter the name for Edit:Gagan
----------------------------------------------------------------------
6       Gagan   6665554444      eve@example.com
----------------------------------------------------------------------
Contact edited successfully !

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 4
1. Delete by Name
2. Delete by Phone Number
3. Delete by Email
4. Exit
Enter your choice: 2
Enter the Phone Number: 7778889999

Contact Found:
Name  : David Brown
Phone : 7778889999
Email : david@example.com

Delete this contact? (y/n): y
Contact deleted successfully.

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 5
Select sort criteria:
1. Sort by name
2. Sort by phone
3. Sort by email
Enter your choice: 1
Sorting based on name:
Index           name            phone           email
1       Alice Smith     0987654321      alice@example.com
2       Bob Johnson     1112223333      bob@company.com
3       Carol White     4445556666      carol@company.com
4       David Brown     7778889999      david@example.com
5       Eve Davis       6665554444      eve@example.com
6       Frank Miller    3334445555      frank@example.com
7       Grace Wilson    2223334444      grace@example.com
8       Hannah Clark    5556667777      hannah@example.com
9       Ian Lewis       8889990000      ian@example.com
10      John Doe        1234567890      john@example.com

      ADDRESS BOOK      
========================
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
------------------------
Enter your choice: 6
Saving and Exiting...x 
*/
#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {

        printf("\n      ADDRESS BOOK      \n");
        printf("========================\n");
        printf("Address Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}