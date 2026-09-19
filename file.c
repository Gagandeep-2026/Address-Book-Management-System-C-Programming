#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;
    if((fptr=fopen("contact.csv","w"))==NULL)
    {
        fprintf(stderr,"file not found");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s %s %s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    if((fptr=fopen("contact.csv","r"))==NULL)
    {
        fprintf(stderr,"file not found");
        return;
    }
    while((fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email))==3)
    {
        addressBook->contactCount++;
    }
    fclose(fptr);
}
