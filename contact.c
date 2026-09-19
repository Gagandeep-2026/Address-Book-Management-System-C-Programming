#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    switch(sortCriteria)
    {
        case 1:
        printf("Sorting based on name:\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount -i -1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp = addressBook->contacts[j];  //swapping according to the name
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t\tname\t\tphone\t\temail\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break ;
        case 2:
        printf("Sorting based on Phone:\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp = addressBook->contacts[j];  //swapping according to the phone
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t\tname\t\tphone\t\temail\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break ;
        case 3:
        printf("Sorting based on email:\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp = addressBook->contacts[j];    //swapping according to the email
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t\tname\t\tphone\t\temail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("----------------------------------------------------------------------\n");
            printf("%d\t%s\t%s\t%s\n",i+1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
        break ;
        default:
         printf("Invalid choice. Please try again.\n");
    }
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to filez
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	char name[50];
    char phone[20];
    char email[50];
    int valid;
    
    // For check the contact is full or not
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book Full\n");                                                        
        return;
    }

    //for validation of name.
    do
    {
        valid=1;
        printf("Press 0 to Cancelle the operation\n");
        printf("Enter the name :");
        scanf(" %[^\n]",name);
        if (strcmp(name, "0") == 0)
        {
            printf("Operation cancelled.\n");
            return;
        }
        for(int i=0;name[i];i++)
        {
            if(!((name[i]>='A'&& name[i]<='Z')||
                (name[i]>='a'&& name[i]<='z')||
                (name[i]==' ')))
                {
                    printf("Error: Name should contain only alphabets\n ");
                    valid=0;
                    break;
                }

        }
        if(strlen(name)<3)
        {
            printf("Error: Name must contain atleast 3 characters\n");
            valid=0;
        }
    }while(valid==0);


    //for validation of number.
    do
    {
        valid=1;
        printf("Enter the number:");
        scanf(" %[^\n]",phone);
        for(int i=0;phone[i];i++)
        {
            if(!(phone[i]>='0' && phone[i]<='9'))
            {
                printf("Other than Digits any other Character not allowed in phone number\n");
                valid=0;
                break;
            }
        }
        if(strlen(phone)!=10)
        {
            printf("Phone number must contain exactly 10 digits\n");
            valid=0;
       
        }
        if(!(phone[0]>='6'&& phone[0]<='9'))// this condtion for the first number should be  6 to 9
        {
            printf("First digit must be between 6 and 9\n");
            valid=0;
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!(strcmp(addressBook->contacts[i].phone,phone)))// in this condition we check the phone number already register or not
            {
                printf("Phone number already exists\n");
                valid=0;
                break;
            }
        }
    }while(valid==0);
     

    //for validation of email.
    do
    {
        valid = 1;

        int at = 0, dot = 0;
        int atPos = -1, dotPos = -1;

        printf("Enter the Email: ");
        scanf(" %[^\n]", email);

        // Check lowercase letters, digits, @ and.
        for(int i = 0; email[i] != '\0'; i++)
        {
            if(email[i] >= 'A' && email[i] <= 'Z')
            {
                printf("Error: Email should contain only lowercase letters and digits\n");
                valid = 0;
                break;
            }
            if((email[i] >= 'a' && email[i] <= 'z') ||
                 (email[i] >= '0' && email[i] <= '9'))
                continue;

            if(email[i] == '@')
            {
                at++;
                atPos = i;
            }
            else if(email[i] == '.')
            {
                dot++;
                dotPos = i;
            }
            else
            {
                printf("Error: Invalid symbol\n");
                valid = 0;
                break;
            }
        }
        if(valid == 0)
        continue;
        // Exactly one @
        if(at == 0)
        {
            printf("Error: Missing @\n");
            valid = 0;
            continue;
        }
        if(at > 1)
        {
            printf("Error: Multiple @ symbols are not allowed\n");
            valid = 0;
            continue;
        }
        // Exactly one dot
        if(dot == 0)
        {
            printf("Error: Missing .\n");
            valid = 0;
            continue;
        }
        if(dot > 1)
        {
            printf("Error: Multiple dots are not allowed\n");
            valid = 0;
            continue;
        }
        // Dot must come after @
        if(dotPos < atPos)
        {
            printf("Error: . must appear after @\n");
            valid = 0;
            continue;
        }
        // At least one character between @ and .
        if(dotPos - atPos <= 1)
        {
            printf("Error: There must be at least one character between @ and .\n");
            valid = 0;
            continue;
        }
        // Must end with .com
        if(strcmp(email + dotPos, ".com") != 0)
        {
            printf("Error: Extra characters after the domain or invalid domain\n");
            valid = 0;
            continue;
        }
        // Email uniqueness
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(email, addressBook->contacts[i].email) == 0)
            {
                printf("Error: Email already exists\n");
                valid = 0;
                break;
            }
        }

    }while(valid == 0);


    int i=addressBook->contactCount;
    sscanf(name,"%s",addressBook->contacts[i].name);
    sscanf(phone,"%s",addressBook->contacts[i].phone);
    sscanf(email,"%s",addressBook->contacts[i].email);

    printf("----------------------------------------------------------------------\n");
    printf("%d\t%s\t%s\t%s\n",i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    printf("----------------------------------------------------------------------\n");

    addressBook->contactCount++;
    printf("Contact created Successfully");
    printf("\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    int SearchChoice;
    printf("1. Search by name: \n");
    printf("2. Search by phone: \n");
    printf("3. Search by email: \n");
    printf("4. exit\n");
    printf("Enter the choice:");
    scanf("%d",&SearchChoice);
    int count =0;
    char str[100];
    switch(SearchChoice)
    {
        //validation for name.
        case 1:
            printf("Enter the name :");
            scanf(" %[^\n]",str);
            for(int i=0;i<addressBook->contactCount;i++)
            {
            if((strcasestr(addressBook->contacts[i].name,str))!=NULL)
            {
                printf("----------------------------------------------------------------------\n");
                printf("%d\t%s\t%s\t%s\n",i+1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                printf("----------------------------------------------------------------------\n");
                count=1;
            }
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;

        //validation for number.
        case 2:
            printf("Enter the Phone Number :");
            scanf(" %[^\n]",str);
            if(strlen(str) != 10)
            {
                printf("Invalid Phone Number.\n");
                break;
            }
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if((strcasestr(addressBook->contacts[i].phone,str))!=NULL)
                {
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");  
                    count=1;
                }
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;

        //validation for mail.
        case 3:
            printf("Enter the Email :");
            scanf(" %[^\n]",str);
            if(strchr(str, '@') == NULL)
            {
                printf("Invalid Email ID.\n");
                break;
            }
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if((strcasestr(addressBook->contacts[i].email,str))!=NULL)  //for uppercase or lowercase.
                {
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    count=1;
                }
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;

        //exiting the search contact.
        case 4:
            printf("Exiting Search.\n");
            return;
        default:
         printf("Invalid choice. Please try again.\n"); 
    }
}

void editContact(AddressBook *addressBook)
{
	int count =0,choice;
    char str[100];
    char ename[50];
    char ephone[50];
    char eemail[50];
    printf("1.Edit by name:\n");
    printf("2.Edit by Phonenumber:\n");
    printf("3.Edit by email:\n");
    printf("4.Exit\n");
    
    printf("Enter the choice:");
    scanf(" %d",&choice);
    switch(choice)
    {
        //validation for name.
        case 1:
            printf("Enter the name :");
            scanf(" %[^\n]",str);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if((strcasestr(addressBook->contacts[i].name,str))!=NULL)
                {
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                                            addressBook->contacts[i].phone,
                                            addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Enter the name for Edit:");
                    scanf(" %[^\n]",ename);
                    for(int i=0;ename[i];i++)
                    {
                        if(!((ename[i]>='A'&& ename[i]<='z')||(ename[i]>='a'&& ename[i]<='z') ||(ename[i]==' ')))
                        {
                            printf("Error: Name should contain only alphabets\n ");
                            return;
                        }
                    }
                    if(strlen(ename)<4)
                    {
                        printf("Error  : Name must contain atleast 4 characters\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].name,ename);
                    count=1;
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                                            addressBook->contacts[i].phone,
                                            addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Contact edited successfully !\n");
                    break;
                }
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;

        //validation for number.
        case 2:
            printf("Enter the Phone Number :");
            scanf(" %[^\n]",str);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if((strcasestr(addressBook->contacts[i].phone,str))!=NULL)
                {
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                                            addressBook->contacts[i].phone,
                                            addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Enter the name for Edit:");
                    scanf(" %[^\n]",ephone);
                    for(int i=0;ephone[i];i++)
                    {
                        if(!(ephone[i]>='0' && ephone[i]<='9'))
                        {
                            printf("Other than Digits any other Character not allowed in phone number\n");
                            return ;
                        }
                    }
                    if(strlen(ephone)!=10)
                    {
                        printf("Phone number must contain exactly 10 digits");
                        return;
                    }
                    if(!(ephone[0]>='6'&& ephone[0]<='9'))// this condtion for the first number should be  6 to 9
                    {
                        printf("First digit must be between 6 and 9\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].phone,ephone);
                    count=1;
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                                            addressBook->contacts[i].phone,
                                            addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Contact edited successfully !\n");
                    break;
                }  
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;

        //validation for mail.
        case 3:
            printf("Enter the Email :");
            scanf(" %[^\n]",str);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if((strcasestr(addressBook->contacts[i].email,str))!=NULL)
                {
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Enter the mail for Edit:");
                    scanf(" %[^\n]",eemail);
                    strcpy(addressBook->contacts[i].name,eemail);
                    count=1;
                    printf("----------------------------------------------------------------------\n");
                    printf("%d\t%s\t%s\t%s\n",i+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    printf("----------------------------------------------------------------------\n");
                    printf("Contact edited successfully !\n");
                    break;
                }
            }
            if(!(count))
            {
                printf("Result Not Found");
            }
        break;
        case 4:
            printf("exiting from edit !");
            return;
        default:
        printf("Invalid choice. Please try again.\n");
    }

}

void deleteContact(AddressBook *addressBook)
{
    int choice, count = 0;
    char str[100];
    char confirm;

    printf("1. Delete by Name\n");
    printf("2. Delete by Phone Number\n");
    printf("3. Delete by Email\n");
    printf("4. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        //for name.
        case 1:
            printf("Enter the Name: ");
            scanf(" %[^\n]", str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].name, str) != NULL)
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    printf("\nDelete this contact? (y/n): ");
                    scanf(" %c", &confirm);

                    if(confirm == 'y' || confirm == 'Y')
                    {
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }

                    count = 1;
                    break;
                }
            }
        break;

        //for number.
        case 2:
            printf("Enter the Phone Number: ");
            scanf(" %[^\n]", str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, str) == 0)
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    printf("\nDelete this contact? (y/n): ");
                    scanf(" %c", &confirm);

                    if(confirm == 'y' || confirm == 'Y')
                    {
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }

                        addressBook->contactCount--;
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }

                    count = 1;
                    break;
                }
            }
        break;

        //for mail.
        case 3:
            printf("Enter the Email: ");
            scanf(" %[^\n]", str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, str) == 0)
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    printf("\nDelete this contact? (y/n): ");
                    scanf(" %c", &confirm);

                    if(confirm == 'y' || confirm == 'Y')
                    {
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }

                        addressBook->contactCount--;
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }

                    count = 1;
                    break;
                }
            }
            break;

        case 4:
            printf("Exiting from delete !");
            return;
        default:
            printf("Invalid Choice\n");
            return;
    }
    if(count == 0)
    {
        printf("Contact not found.\n");
    }
}