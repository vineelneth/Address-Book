#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<string.h>
#include<ctype.h>
int isvalidphone(char* mob)
{
		int i=0,len=0;
		int isnotvalidphone=0;
		while(mob[i]!='\0')
		{
			if(mob[i]>='0'&&mob[i]<='9')
			{
				len++;
			}
			i++;
		}
		if(len==10&&i==10)
		{
			isnotvalidphone=0;
		}
		else
		{
			isnotvalidphone=1;
		}
		if(isnotvalidphone)
		{
			return 0;
		}
		else{
			return 1;
		}
}
int isvalidemail(char* email)
{
		int i=0;
		int isnotvalidemail =0;
		int len = strlen(email);
		while(email[i]!='\0')
		{
			if(email[i]>='a'&&email[i]<='z'||
				email[i]>='0'&&email[i]<='9')
				if(len>=10&&strcmp(email+len-10,"@gmail.com")==0)
				{
					isnotvalidemail=0;					
				}
			else
			{
				isnotvalidemail=1;
			}
			i++;
		}
		if(isnotvalidemail)
		{
			return 0;
		}	
		else
		{
			return 1;
		}
}
int isvalidname(char* name)
{
		int isnotvalidname=0;
		int i=0;	
  		while(name[i]!='\0')
		{
			if(name[i]>='a'&&name[i]<='z'||
				name[i]>='A'&&name[i]<='Z'||
				name[i]==' '||name[i]=='.')
			{
				isnotvalidname =0;
			}
			else
			{
				isnotvalidname=1;
				break;
			}
			i++;
		}
		if(isnotvalidname)
		{
			return 0;
		}
		else
		{
			return 1;
		}
}
void listContacts(AddressBook *addressBook)
{
    printf("\n%-20s %-20s %-20s\n", "Name", "Mobile Number", "Email ID");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-20s %-20s %-20s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
  	getchar();
	int isnotvalidname=0;
	do
	{
		printf("Enter name: ");
      		scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].name);
		int i=0;	
  		while(addressBook->contacts[addressBook->contactCount].name[i]!='\0')
		{
			if(addressBook->contacts[addressBook->contactCount].name[i]>='a'&&addressBook->contacts[addressBook->contactCount].name[i]<='z'||
				addressBook->contacts[addressBook->contactCount].name[i]>='A'&&addressBook->contacts[addressBook->contactCount].name[i]<='Z'||
				addressBook->contacts[addressBook->contactCount].name[i]==' '||addressBook->contacts[addressBook->contactCount].name[i]=='.')
			{
				isnotvalidname =0;
			}
			else
			{
				isnotvalidname=1;
				break;
			}
			i++;
		}
		if(isnotvalidname)
		{
			printf("Please try again with valid name.\n");
			getchar();
		}
	
	}while(isnotvalidname);
	getchar();
	int isnotvalidphone=0;
	char mobilenum[20];
	do
	{
		printf("Enter mobile number: ");
      	scanf("%[^\n]",mobilenum);
			int i=0,len=0;
			while(mobilenum[i]!='\0')
			{
				if(mobilenum[i]>='0'&&mobilenum[i]<='9')
				{
					len++;
				}
				i++;
			}
			if(len==10&&i==10)
			{
				isnotvalidphone=0;
			}
			else
			{
				printf("Please enter a valid mobile number.\n");
				isnotvalidphone=1;
				getchar();
			}
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,mobilenum)==0)
				{
					isnotvalidphone=1;
					printf("Mobile number is already in the database\n");
					getchar();
					break;
				}
			}
	}while(isnotvalidphone);
	strcpy(addressBook->contacts[addressBook->contactCount].phone,mobilenum);
	getchar();	
	int isnotvalidemail=0;
	char Email[100];
  	do{
			printf("Enter email: ");
      		scanf("%[^\n]",Email);
		int i=0;
		int len = strlen(Email);
		if(len>=10&&strcmp(Email+len-10,"@gmail.com")==0)
		{
			isnotvalidemail=0;					
		}
		else
		{
			isnotvalidemail=1;
		}
		if(isnotvalidemail==0)
		{
			while(Email[i]!='@')
			{
				if(Email[i]>='a'&&Email[i]<='z'||
					Email[i]>='0'&&Email[i]<='9')
				{	
					
				}
				else
				{
					isnotvalidemail=1;
					break;
				}
				i++;
			}
		}
		if(isnotvalidemail==0)
		{
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(strcmp(addressBook->contacts[i].email,Email)==0)
					{
						isnotvalidemail=1;
						printf("Email is already in the database\n");
						getchar();
						break;
					}
				}
		}	
			if(isnotvalidemail)
			{
				printf("Please enter a valid email.\n");
				getchar();
			}
	}while(isnotvalidemail);
	strcpy(addressBook->contacts[addressBook->contactCount].email,Email);
	addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
	int opt;
	printf("Based on what do you want to search\n1.Name\n2.Mobile Number\n3.Email\n");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1:{
			char name[60];
			getchar();
			printf("Enter name: ");
			scanf("%[^\n]",name);
			printf("---------------------------------------------------------------------\n");
			int found=0;
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(strstr(addressBook->contacts[i].name,name)!=NULL)
				{
					printf("Name: %s\nMobile: %s\nEmail: %s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					found =1;
				}
			}
			if(found==0)
			{
				printf("Contact not found\n");
			}
			printf("----------------------------------------------------------------------\n");
			}
			break;
		case 2:{
                        char mobnum[15];
                        getchar();
                        printf("Enter mobilenumber: ");
                        scanf("%[^\n]",mobnum);
                        int found=0;
						printf("---------------------------------------------------------------------\n");
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                                if(strcmp(addressBook->contacts[i].phone,mobnum)==0)
                                {
                                        printf("Name: %s\nMobile: %s\nEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                        found=1;
                                }
                        }
                        if(found==0)
                        {
                                printf("No contact found\n");	
								break;
                        }
						printf("---------------------------------------------------------------------\n");
			break;
                        }
		case 3:{
                        char email[15];
                        getchar();
                        printf("Enter email: ");
                        scanf("%[^\n]",email);
                        int flag=0;
						printf("---------------------------------------------------------------------\n");
                        for(int i=0;i<addressBook->contactCount;i++) 
						{
                                if(strcmp(addressBook->contacts[i].email,email)==0)
                                {
                                        printf("Name: %s\nMobile: %s\nEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);                                                                                                                                    flag=1;
                                }
                        }    
						if(flag==0)
                        {
                                printf("No contact found\n");
                        }
						printf("---------------------------------------------------------------------\n");
                        }       
		       break;
		 default: printf("Invalid input\n");
	}
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int opt;
    printf("Based on what do you want to edit the contact\n1.Name\n2.Mobile\n3.Email\n");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1: {
			char name[100];
			getchar();
			printf("Name: ");
			scanf("%[^\n]",name);
			int found=0;
			int subopt;
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strstr(addressBook->contacts[i].name,name)!=NULL)
				{
					found=1;
				}
			}
			if(found)
			{
				printf("What do you want to change\n1.Name\n2.Mobile number\n3.Email\n");
				scanf("%d",&subopt);
				switch(subopt)
				{
					case 1:{ 
						int again=0;
						char newname[100];
						getchar();
						do
						{
							printf("Enter new name: ");
							scanf("%[^\n]",newname);
							if(isvalidname(newname))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].name,name)==0)
									{
										strcpy(addressBook->contacts[i].name,newname);
										printf("New name: %s\n",addressBook->contacts[i].name);
									}
								}
								again =0;
							}
							else{
								again=1;
								printf("Please enter valid name\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 2:{ 
						int again=0;
						getchar();
						char newmob[100];
						do
						{
							printf("Enter new mobile number: ");
							scanf("%[^\n]",newmob);
							if(isvalidphone(newmob))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].name,name)==0)
									{
										strcpy(addressBook->contacts[i].phone,newmob);
									}
								}
								again=0;
							}
							else
							{
								again =1;
								printf("Please enter a valid mobile number\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 3:{ 
						int again=0;
						getchar();
						char newemail[100];
						do
						{
							printf("Enter new email: ");
							scanf("%[^\n]",newemail);
							if(isvalidemail(newemail))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].name,name)==0)
									{
										strcpy(addressBook->contacts[i].email,newemail);
									}
								}
								again = 0;
							}
							else
							{
								again =1;
								printf("Please enter valid email\n");
								getchar();
							}
						}while(again);
						break;
					}
					default:printf("Invalid input\n");
				}
				
			}
			else
			{
				printf("Contact not found\n");
			}
		}
		break;
	case 2: {
			char mob[100];
			getchar();
			printf("Mobile number: ");
			scanf("%[^\n]",mob);
			int found=0;
			int subopt;
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,mob)==0)
				{
					found=1;
				}
			}
			if(found)
			{
				printf("What do you want to change\n1.Name\n2.Mobile number\n3.Email\n");
				scanf("%d",&subopt);
				switch(subopt)
				{
					case 1:{ 
						int again=0;
						char newname[100];
						getchar();
						do
						{
							printf("Enter new name: ");
							scanf("%[^\n]",newname);
							if(isvalidname(newname))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].phone,mob)==0)
									{
										strcpy(addressBook->contacts[i].name,newname);
										printf("New name: %s\n",addressBook->contacts[i].name);
									}
								}
								again =0;
							}
							else{
								again=1;
								printf("Please enter valid name\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 2:{ 
						int again=0;
						getchar();
						char newmob[100];
						do
						{
							printf("Enter new mobile number: ");
							scanf("%[^\n]",newmob);
							if(isvalidphone(newmob))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].phone,mob)==0)
									{
										strcpy(addressBook->contacts[i].phone,newmob);
									}
								}
								again=0;
							}
							else
							{
								again =1;
								printf("Please enter a valid mobile number\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 3:{ 
						int again=0;
						getchar();
						char newemail[100];
						do
						{
							printf("Enter new email: ");
							scanf("%[^\n]",newemail);
							if(isvalidemail(newemail))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].phone,mob)==0)
									{
										strcpy(addressBook->contacts[i].email,newemail);
									}
								}
								again = 0;
							}
							else
							{
								again =1;
								printf("Please enter valid email\n");
								getchar();
							}
						}while(again);
						break;
					}
					default:printf("Invalid input\n");
				}
				
			}
			else
			{
				printf("Contact not found\n");
			}
		}
		break;
	case 3: {
			char email[100];
			getchar();
			printf("Email: ");
			scanf("%[^\n]",email);
			int found=0;
			int subopt;
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].email,email)==0)
				{
					found=1;
				}
			}
			if(found)
			{
				printf("What do you want to change\n1.Name\n2.Mobile number\n3.Email\n");
				scanf("%d",&subopt);
				switch(subopt)
				{
					case 1:{ 
						int again=0;
						char newname[100];
						getchar();
						do
						{
							printf("Enter new name: ");
							scanf("%[^\n]",newname);
							if(isvalidname(newname))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].email,email)==0)
									{
										strcpy(addressBook->contacts[i].name,newname);
										printf("New name: %s\n",addressBook->contacts[i].name);
									}
								}
								again =0;
							}
							else{
								again=1;
								printf("Please enter valid name\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 2:{ 
						int again=0;
						getchar();
						char newmob[100];
						do
						{
							printf("Enter new mobile number: ");
							scanf("%[^\n]",newmob);
							if(isvalidphone(newmob))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].email,email)==0)
									{
										strcpy(addressBook->contacts[i].phone,newmob);
									}
								}
								again=0;
							}
							else
							{
								again =1;
								printf("Please enter a valid mobile number\n");
								getchar();
							}
						}while(again);
						break;
					}
					case 3:{ 
						int again=0;
						getchar();
						char newemail[100];
						do
						{
							printf("Enter new email: ");
							scanf("%[^\n]",newemail);
							if(isvalidemail(newemail))
							{
								for(int i=0;i<addressBook->contactCount;i++)
								{
									if(strcmp(addressBook->contacts[i].email,email)==0)
									{
										strcpy(addressBook->contacts[i].email,newemail);
									}
								}
								again = 0;
							}
							else
							{
								again =1;
								printf("Please enter valid email\n");
								getchar();
							}
						}while(again);
						break;
					}
					default:printf("Invalid input\n");
				}
			}
			else
			{
				printf("Contact not found\n");
			}
		}
		break;
		default: printf("Invalid\n");
}
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int opt;
	printf("Delete contact based on\n1.Name\n2.Mobile\n3.Email\n");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1:{
			char name1[100];
			getchar();
			printf("Enter name: ");
			scanf("%[^\n]",name1);
			int found=0;
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(strstr(addressBook->contacts[i].name,name1)!=NULL)
				{
					printf("Name: %s\nMobile: %s\nEmail: %s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					found =1;
				}
			}
			if(found==0)
			{
				printf("Contact not found\n");
				break;
			}
			printf("----------------------------------------------------------------------\n");
			int num;
			char name[100];
			getchar();
			printf("Enter name to be deleted: ");
			scanf("%[^\n]",name);
			printf("Do you want to delete the contact(1-Yes/0-No): ");
			scanf("%d",&num);
			if(num)
			{
				int newind=0;
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(strcmp(addressBook->contacts[i].name,name)!=0)
						{
							addressBook->contacts[newind] = addressBook->contacts[i];
							newind++;   
						}
				}
				addressBook->contactCount = newind;
			}
		}
		break;
		case 2:{
			char mob[15];
			getchar();
			printf("Enter mobile: ");
			scanf("%[^\n]",mob);
			int found=0;
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(strstr(addressBook->contacts[i].phone,mob)!=NULL)
				{
					printf("Name: %s\nMobile: %s\nEmail: %s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					found =1;
				}
			}
			if(found==0)
			{
				printf("Contact not found\n");
				break;
			}
			printf("----------------------------------------------------------------------\n");
			int num;
			char name[100];
			getchar();
			printf("Enter name to be deleted: ");
			scanf("%[^\n]",name);
			printf("Do you want to delete the contact(1-Yes/0-No): ");
			scanf("%d",&num);
			if(num)
			{
				int newind=0;
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(strcmp(addressBook->contacts[i].name,name)!=0)
						{
							addressBook->contacts[newind] = addressBook->contacts[i];
							newind++;   
						}
				}
				addressBook->contactCount = newind;
			}
		}
		break;
		case 3:{
			char email[100];
			getchar();
			printf("Enter email: ");
			scanf("%[^\n]",email);
			int found=0;
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(strstr(addressBook->contacts[i].email,email)!=NULL)
				{
					printf("Name: %s\nMobile: %s\nEmail: %s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					found =1;
				}
			}
			if(found==0)
			{
				printf("Contact not found\n");
				break;
			}
			printf("----------------------------------------------------------------------\n");
			int num;
			char name[100];
			getchar();
			printf("Enter name to be deleted: ");
			scanf("%[^\n]",name);
			printf("Do you want to delete the contact(1-Yes/0-No): ");
			scanf("%d",&num);
			if(num)
			{
				int newind=0;
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(strcmp(addressBook->contacts[i].name,name)!=0)
						{
							addressBook->contacts[newind] = addressBook->contacts[i];
							newind++;   
						}
				}
				addressBook->contactCount = newind;
			}
		}
		break;
		default: printf("Invalid input\n");
	}
}