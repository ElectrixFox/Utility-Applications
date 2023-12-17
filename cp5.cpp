/******************************************************************************
Program:        Prototype
File:           Prototype.cpp
Functions:      				ChangeDJEmailAddress, ChangeDJMusicStyle, 
				ChangeDJPerformanceName, ChangeDJPhoneNumber, 
ChangeDJ, ChangeDJMenu, ChangeDJName, 
Description:    
Author:         Luke Phillips
Environment:    Borland C++ Pro 6.0
Notes:			
Revisions:      18/07/2023
******************************************************************************/

int ChangeDJ();
int ChangeDJMenu();
int ChangeDJName();
int ChangeDJPerformanceName();
int ChangeDJPhoneNumber();
int ChangeDJEmailAddress();
int ChangeDJMusicStyle();

int GenerateDJNumber()
{
int count;
int compife;

for (count = 1; count < 52; count++)
    {
	compife = 2;

	if(compife == 0)
		{
		return count;
		}

    }

// return -1 value if empty slot hasn't been found
return -1;
}

void LocateDJ(int idjno)
{
// opens the file
ifstream fin(FileName6, ios::binary);

// finds the DJ at idjno
fin.seekg(idjno * sizeof(a_dj));
fin.get((char*)&a_dj, sizeof(a_dj));
fin.close();
}

int RemoveGuest()
{
char innum[10];
int find = 0;
int del = 0;
char guestname[32];
char choice;

ReadBackGuestFile();

clrscr();
cout << "\nRemove Guest";
cout << "\n============\n";

// get guest name
cout << "\nEnter Guest Number: ";
cin.getline(innum, 10);

find = FindInArray10(guestno, innum, ngi);

strcpy(guestname, gunam[find]);

// confirmaiton required to reduce mistakes
cout << "\nAre you sure you want to Delete " << guestname << " (y/n): ";

// getting the choice
choice = cin.get();
cin.get();

// quick bit of validation to make sure that nothing accidental is done during testing
if(find == -1)
	return 0;

// if the choice is not yes return as not needed to keep going
if(choice != 'y')
	{
	cout << "\nDeletion has been cancelled" << "\nPress any key to return";
	getch();

	return 0;
	}

// shuffle all the guests back one space
for (del = find; del < ngi; del++)
	{
	strcpy(guestno[del], guestno[del+1]);
	strcpy(gunam[del], gunam[del+1]);
	strcpy(gucontactnam[del], gucontactnam[del+1]);
	strcpy(guconttelenum[del], guconttelenum[del+1]);
	strcpy(guemailaddr[del], guemailaddr[del+1]);
	} 

// insert check here
cout << "\nSuccess - " << guestname << " has been deleted\n";

ngi = ngi - 1;
itoa(ngi, ngc, 10);
ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}