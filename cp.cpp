/******************************************************************************
Program:        Prototype
File:           Prototype.cpp
Functions:      main 
Description:    
Author:         Luke Phillips
Environment:    Borland C++ Pro 6.0
Notes:			
Revisions:      18/07/2023
******************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <time.h>

//#include <vcl.h>

#define HOME
#ifdef HOME
using namespace std;
#define clrscr() system("CLS")
#define getch() cin.get();
#define out(x) cout << '\n' << #x << ": " << x << '\n'
#endif

char pound = 156;

char FileName1[80] = "GuestFile";
int ngi;
char ngc[3];

char FileName2[80] = "EventsFile";
int nei;
char nec[3];

char FileName3[80] = "MusicFile";
int nmi;
char nmc[3];

char FileName4[80] = "EventsLinksFile";
int nli;
char nlc[3];

char FileName5[80] = "PlaylistsLinksFile";
int npi;
char npc[3];

typedef struct tag_cr
	{
	char djnam[32];
	char djtelenum[12]; 
	char djemailaddr[32]; 
	char performnam[32]; 
	char musstyle[24]; 
	char flag[2];
	} DJ_RECORD;

char FileName6[80] = "DJFile";
int djno;
DJ_RECORD a_dj;

char FileName7[80] = "ScheduleFile";

char guestno[128][10]; 
char gunam[128][32]; 
char gucontactnam[128][32]; 
char guconttelenum[128][12]; 
char guemailaddr[128][32]; 

char mucatno[500][10]; 
char mutitle[500][48];
char muartist[500][32]; 
char mugenre[500][24]; 
char mupub[500][64]; 
char muplaytime[500][6]; 
char mucheck[500][2]; 
char mufreq[500][10]; 

char eventno[128][10]; 
char evdate[128][11]; 
char evtime[128][6]; 
char evdur[128][10]; 
char evlocation[128][32]; 
char evdescription[128][128]; 
char evtitle[128][64]; 
char evcost[128][6]; 
char evcont[128][32]; 
char evcontemail[128][32]; 
char evcontnum[128][12]; 

char evlinkevno[128][10];
char evlinkdjno[128][10];

char pllinkcatno[128][10];
char pllinkevno[128][10];

// [dj][day][time]
char sch[52][367][24][32];

/* To-Do:
 [*] change all gen refs
 [*] validation only 1 internal event is happening at once
 [*] update the setting of the schedule to use the character inputs
 [*] using the leap day on the schedule to show the start date of the schedule

 Issues:
 [*] remove music is incorrect
 [*] allocate DJs not allocating DJs
*/

int MainMenu();

#pragma region DJs

int InitialiseDJFile();

// loads the DJ at the inputted number
void LocateDJ(int idjno);

// sets the flag to the state for the current DJ
void SetDJFlag(int state);

// writes the DJ at idjno to the file
void WriteDJ(int idjno);

// finds first empty slot and returns it as an integer
int GenerateDJNumber();


int DJs();
int DJMenu();

int AddDJ();
int RemoveDJ();

int ViewDJ();
int ViewDJMenu();
int ViewDJByName();
int ViewByDJNumber();
int ViewDJByMusicStyle();

int ChangeDJ();
int ChangeDJMenu();
int ChangeDJName();
int ChangeDJPerformanceName();
int ChangeDJPhoneNumber();
int ChangeDJEmailAddress();
int ChangeDJMusicStyle();

#pragma endregion

#pragma region Guests

int ReadBackGuestFile();
int ReWriteGuestFile();

// outputs the details of the guest
void OutputGuest(int loc);

// generates the guest number
int GenerateGuestNumber(char inguno[10]);

int Guests();
int GuestsMenu();

int ViewGuest();
int ViewGuestMenu();
int ViewGuestByName();
int ViewGuestByGuestNumber();
int ViewGuestNextAppearance();
int ViewGuestByNextAppearance();

int AddGuest();

int ChangeGuest();
int ChangeGuestMenu();
int ChangeGuestName();
int ChangeGuestContactName();
int ChangeGuestContactPhoneNumber();
int ChangeGuestContactEmailAddress();

int RemoveGuest();

#pragma endregion

#pragma region Music

int ReadBackMusicFile();
int ReWriteMusicFile();

int Music();
int MusicMenu();


int Catalogue();
int CatalogueMenu();

int ViewCatalogue();
int ViewCatalogueMenu();
int ViewCatalogueByCatalogueNumber();
int ViewCatalogueByTitle();
int ViewCatalogueByArtist();
int ViewCatalogueByGenre();
int ViewCatalogueByPopularity();


int CatalogueAddMusic();

// finds the song with the longest entry and returns that field length, also copies the data for that field into the outvalues
int MusicLongestLength(char title[], int songids[], int size, char outvalues[][256]);

// generates the catalogue number
int GenerateCatalogueNumber(char incatno[10]);

// outputs the song at the location with the headers
void OutputSong(int location, char heads[32] = "IdTiPlArGePuCh");

// outputs all of the songs with the song ids (size is the number of ids), heads are the first two letters of the header
// an example would be "TiId" for the title and the ID
void OutputSongs(int songids[], char heads[32], int size);

// outputs the song at the location in a linear layout
void OutputSongLinear(int location);

// converts the playtime into seconds
int ConvertPlaytimeToSecconds(char playtime[6]);

int CatalogueChangeMusic();
int CatalogueChangeMusicMenu();
int ChangeMusicTitle();
int ChangeMusicArtist();
int ChangeMusicPlaytime();
int ChangeMusicGenre();
int ChangeMusicCheck();

int CatalogueRemoveMusic();

int ReadBackPlaylistFile();
int ReWritePlaylistFile();

// returns the duration of the playlist (in seconds) at inevno
int CalculatePlaylistDuration(char inevno[10]);

// creates the output message for the duration calc (diff in mins)
void DurationEnding(char output[64], int durdiff);

// gives an output for if the duration of the playlist is incorrect (returns the duration), allows for playlist duration to be passed in
// if -1 is passed in to the duration it suppresses the output message if correct length
// returns negative if the duration of the playlist fails the check
int PlaylistDurationCheck(char evno[10], int pldur = 0);

// adds a new song (incatno) to the playlist on inevno 
void AddPlaylistEntry(char inevno[10], char incatno[10]);

// removes all songs according to their catalogue number
void RemovePlaylistEntriesBySong(char incatno[10]);

// removes all songs according to their event number
void RemovePlaylistEntriesByEvent(char inevno[10]);

// removes an entry from the playlist on inevno with songid incatno
void RemovePlaylistEntry(char inevno[10], char incatno[10]);


int Playlists();
int PlaylistsMenu();

int ViewPlaylist();

int CreatePlaylist();

int EditPlaylist();
int EditPlaylistMenu();
int AddMusic();
int RemoveMusic();

int RemovePlaylist();

#pragma endregion

#pragma region Admin

int Admin();
int AdminMenu();

int AddUser();

int ChangeUser();
int ChangeUserMenu();
int ChangeUserUsername();
int ChangeUserPassword();
int ChangeUserAccessLevel();

int RemoveUser();
int Backup();
int Recovery();

#pragma endregion

#pragma region Events

int ReadBackEventLinksFile();
int ReWriteEventLinksFile();

// gets the type of event from the characteristics of the event
char GetBaseType(char evnoc[10]);

// finds the event with the longest entry and returns that field length, also copies the data for that field into the outvalues
int EventsLongestLength(char title[], int eventids[], int size, char outvalues[][256]);

// finds the guest event with the longest entry and returns that field length, also copies the data for that field into the outvalues
int GuestEventLongestLength(char title[], int eventids[], int gunos[], int size, char outvalues[][256]);

// adds an entry to the links file 
void AddLinksEntry(char inevno[10], char indjno[10]);

// removes the link entry with the passed fields
void RemoveLinksEntry(char inevno[10], char indjno[10]);

// removes all links with a DJ
void RemoveDJLinksEntries(char indjno[10]);

// removes all links with an event
void RemoveEventLinksEntries(char inevno[10]);

int ReadBackEventFile();
int ReWriteEventFile();

int GenerateEventNumber(char inevno[10]);

// outputs size number of events (with evids) in a tabular form with the specified headers
void OutputEventsTabular(int evids[], char heads[32], int size);

// outputs size number of guest events (with evids) in a tabular form with the specified headers
void OutputGuestEventsTabular(int evids[], int gunos[], char heads[32], int size);

// outputs the event at the date and time
void OutputEvent(char evno[10]);

// outputs the event at the date and time for djid  
void OutputEvent(int date, int time, int djid);

// gets the first attending DJ and returns their number as an int (-1 if no DJs), outputs them if output is 1
int GetAttendingDJ(char inevno[10], int output = 0);

// gets all of the attending DJs and copies them into attdjs, outputs them if output is 1, returns num of DJs
int GetAttendingDJs(char inevno[10], int outdjids[50], int output = 0);

// swaps the event at index and the following event
void SwapEvents(int index);

// removes the event at the location in the events file
void RemoveEvent(int location);

// bubble sorts the dates in the events
void BubbleEventSortDates(int size);

int Events();
int EventsMenu();

int ViewEvents();
int ViewEventsMenu();
int ViewEventsByEventReference();
int ViewEventsByDate();
int ViewEventsByTitle();

int AddEvent();
int AddEventMenu();
int DJSession();
int GuestAppearance();
int ExternalEvent();
int Replay();

int ChangeEvents();
int ChangeEventsMenu();
int ChangeEventsTitle();
int ChangeEventsDate();
int ChangeEventsTime();
int ChangeEventsLocation();
int ChangeEventsDescription();
int ChangeEventsCost();
int ChangeEventsContact();
int ChangeEventsPlaylist();

int ChangeEventsContact();
int ChangeEventsContactMenu();
int ChangeEventsContactName();
int ChangeEventsContactEmailAddress();
int ChangeEventsContactPhoneNumber();

int AllocateDJs();

int RemoveEvents();

#pragma endregion

#pragma region Scheduling

int ReadBackScheduleFile();
int ReWriteScheduleFile();

// gets the year of the schedule
int GetScheduleYear();

// gets the start date of the schedule
void GetScheduleStartDate(char* outdate);

// checks if an event is on the schedule (returns 0 if not on schedule)
int IsEventOnSchedule(char evno[10]);

void SetScheduleSlot(char value[32], int date, int time, int djid);
void SetScheduleSlot(char value[32], char date[11], char time[6], int djid);

// gets the schedule slot at date and time with djid and copies it into output 
void GetScheduleSlot(char output[32], int date, int time, int djid);

// gets the schedule slot for evnoc with djid and copies it into output 
void GetScheduleSlot(char output[32], char evnoc[10], int djid);

// searches the schedule for the slot at the event date and time with the event ID and then returns the type
char GetEventType(char evnoc[10]);

// generates the token for the schedule and returns it as output
void GenerateScheduleToken(char output[32], char type[3], char inevno[10], char guno[10] = " ");

// finds if there is an active guest slot on that day and time, returns the DJ who it is with
int FindScheduleGuestSlot(int date, int time);

// outputs the formatted date from a date index in the schedule 
void CalculateDateFromSchedule(char outdate[11], int schedindex);

// gets the index of the input date in the schedule
int CalculateScheduleDateIndex(char date[11]);

// gets the index of the input time in the schedule
int CalculateScheduleTimeIndex(char time[6]);

// gets the type of slot at date and time with djid
char GetScheduleType(int date, int time, int djid);

// gets the guest number at the date and time for djid
int GetScheduleGuestNumber(int date, int time, int djid);

// gets the guest number for the guest appearance ref (guappno)
int GetScheduleGuestNumber(char guappno[10]);

// gets the schedule number of the slot at date, time and with djid
int GetScheduleEventNumber(int date, int time, int djid);

// adds the event to the schedule and creates a link for the DJ and event
void AddEventToSchedule(char inevno[10], char type, int indjno, char inguno[10] = "");

// adds a guest event to the schedule creating a link between the in DJ and the event
void AddGuestEventToSchedule(char inevno[10], char inguno[10], int indjno);

// adds the event to the DJ's schedule and creates a link for it 
void AddDJToEvent(char inevno[10], int idjno);

// removes the event from the schedule for all DJs
void RemoveEventFromSchedule(char evno[10]);

// clears the event on the DJ's schedule and removes all links for them
void RemoveDJFromEvent(char evno[10], int indjno);

// changes all of the slots ocupied by an event for all attending DJs
void ChangeEventSlot(char evnoc[10], char slot[32]);

// output function for a DJ availability since it is used a few times
void OutputDJAvailability(int idjno);

// gets the day in the month from the schedule date index
int GetDayInMonth(int dtindex);

int Scheduling();
int SchedulingMenu();

int Schedule();
int ScheduleMenu();

int ViewSchedule();
int ViewScheduleMenu();
int ViewScheduleByDJ();
int ViewScheduleAvailabilityByDJ();
int ViewScheduleGuestSlots();

int CreateSchedule();
int ClearSchedule();

int EditSchedule();
int EditScheduleMenu();
int ChangeDJAvailability();
int GuestSlots();

// checks if the holiday is approved and returns 1 if it is approved
int IsHolidayApproved(char holref[10]);

// outputs the size number of holidays with holiday references holids and outputs if they are approved if check = 1
void OutputHolidays(int holids[], int size, int check = 0);

int Holidays();
int HolidaysMenu();

int ViewHolidays();
int ViewHolidaysMenu();
int ViewHolidaysByDJ();
int ViewHolidaysByDate();
int ViewHolidaysByUnapproved();

int BookHolidays();

int ChangeHolidays();
int ChangeHolidaysMenu();
int ChangeHolidaysStartDate();
int ChangeHolidaysEndDate();


int RemoveHolidays();
int ApproveHolidays();

#pragma endregion

#pragma region Other

// Other functions

// finds an item in the array 64 bytes with default starting point at 0 
int FindInArray64(char array[][64], char item[], int size, int start = 0);

// finds an item in the array 48 bytes with default starting point at 0
int FindInArray48(char array[][48], char item[], int size, int start = 0);

// finds an item in the array 32 bytes with default starting point at 0
int FindInArray32(char array[][32], char item[], int size, int start = 0);

// finds an item in the array 24 bytes with default starting point at 0
int FindInArray24(char array[][24], char item[], int size, int start = 0);

// finds an item in the array 10 bytes with default starting point at 0
int FindInArray10(char array[][10], char item[], int size, int start = 0);

// finds an item in the array 4 bytes with default starting point at 0
int FindInArray04(char array[][4], char item[], int size, int start = 0);

// finds part of an item in the array 32 bytes with default starting point at 0
int FindPartialInArray32(char array[][32], char item[], int size, int start = 0);

// gets the location of the reference numbers in the array taking in the number of indecies, size of the array and the ids of the elements
void GetRefLocations(char array[][10], int indecies[], int size, int nindecies);

// finds the longest string in a list at the indecies and returns it's length, takes in size of array
template<int T>
int FindLongestInIndecies(char lst[][T], int indecies[], int size);

// finds the longest string in a list and returns it's length
template<int T>
int FindLongest(char lst[][T], int size);

// appends a character (item) to the string at index 
void AppendToStringAt32(char str[], char item, int index);

// appends a string to a string at a location
void AppendStrToStringAt32(char str[], char item[], int index);

// requires a password of a specific length, it must contain a number, mixed case and special character
int PasswordSecurityCheck(char inpass[32]);

// finds the next available ref number in the number array starting at testnumber
int FindNextReferenceNumber(int testnumber, char numberarr[][10], int size);

// finds the day on the date passed to the function
int FindDayOnDate(char date[11]);

// identifies the headers from their prefixes and outputs them in a list of headers (returns number of headers)
int GetHeaders(char headercombo[32], char output[][32], char prefixindex[][32], char lookupindex[][32], int indexsize);

// formats the alignment of the output and corrects the output format, taking len of longest entry and title
void FormatAlignment(char title[], int longest, char* outformat);

// output the array
void PrintArray(int array[], int size);
void PrintArray(char array[][11], int size);
void PrintArray(char array[][48], int size);

// print the array starting from start and ending at end (for whole it would be 0, array.length)
void PrintArray(char array[][11], int start, int end);

// convert the parts of the date into a string
void ConvertDateToStr(char date[11], int day, int month, int year);

// convert the parts of the time into a string
void ConvertTimeToStr(char time[6], int hours, int mins);

// get the date as an integer in the form yyyymmdd where each character is a digit
int CalculateNumericalDate(char date[11]);

// calculates the numerical date in the form yyyymmdd from the separate integers
int CalculateNumericalDateInt(int day, int month, int year);

// converts the month prefixes into numerical months
int ConvertMonth(char month[32]);

// gets the time difference between two times (returns in hours)
int CalculateDuration(char time1[6], char time2[6]);

// finds the end time of the duration added to the time (outputs to timeout) 
void CalculateEndTime(char time[6], char duration[10], char timeout[6]);

// gets the date of today in the form dd/mm/yyyy
void GetToday(char output[11]);

// gets the numerical date from the systems clock
int GetSystemsClock();

// subtracts the number of days from the date
void SubtractDays(char date[11], int days);

// adds the number of days to the date
void AddDays(char date[11], int days);

// adds hours to the time, returns the number of days if it goes over into the next day since it is mod 24
// if a negative hours is inputted gives a -ve result if it goes back days 
int AddTimes(char time[6], int hours);

// bubble sort
void BubbleSort(int array[], int size);

// bubble sort for dates
void BubbleSortDates(char dates[][11], int size);

// an extended bubble sort which uses another function as a parameter for swapping the values
void ExtendedBubbleSort(int array[], int size, void (*swapfunc)(int index));

// sorts the dates chronologically with the option to return the index of the first furture date
int SortDatesChronologically(char dates[][11], int nodates, int onlyfuture);

void BubbleSortMusicPopularity(int array[], int size);

// checks that the date is in the range of the two dates
// returns -1 if before min
// returns 1 if after max
// returns 0 if correct
int DateRangeCk(char date[11], char mindate[11], char maxdate[11]);

#pragma endregion

/* ------------------------------
 *          Main Menu
 * ------------------------------ 
 */

int main(int argc, char* argv[])
{
int mainstatus = 0;
while (mainstatus != 7)
        {
        mainstatus = MainMenu();
        clrscr();
        } //endwhile

getch();
return 0;
}

int MainMenu()
{
int choice;

clrscr();

cout << "\n\tMain Menu";
cout << "\n\t=========\n";
cout << "\n\t1. DJs";
cout << "\n\t2. Guests";
cout << "\n\t3. Music";
cout << "\n\t4. Admin";
cout << "\n\t5. Events";
cout << "\n\t6. Scheduling";
cout << "\n\t7. Quit";

cout << "\n\nEnter Choice: ";
cin >> choice;

switch(choice)
        {
        case 1:
                {
                DJs();
                clrscr();
                break;
                } // endcase
        case 2:
                {
                Guests();
                clrscr();
                break;
                } // endcase
        case 3:
                {
                Music();
                clrscr();
                break;
                } // endcase
        case 4:
                {
                Admin();
                clrscr();
                break;
                } // endcase
        case 5:
                {
                Events();
                clrscr();
                break;
                } // endcase
        case 6:
                {
                Scheduling();
                clrscr();
                break;
                } // endcase
        case 7:
                {
                clrscr();
                break;
                } // endcase
        }

return choice;
}


#pragma region DJs


int InitialiseDJFile()
{
int count;
ofstream fout(FileName6, ios::binary);
strcpy(a_dj.flag, "0");
for(count = 0; count < 52; count++)
        {
        fout.write((char*)&a_dj, sizeof(a_dj));
        } //endfor

fout.close();
return 0;
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

void SetDJFlag(int state)
{
if(state == 1)
	{
	strcpy(a_dj.flag, "1");
	} //endif set to here
else if(state == 0)
	{
	strcpy(a_dj.flag, "0");
	} //endelseif
}

void WriteDJ(int idjno)
{
// opens the DJ file to write
ofstream fout(FileName6, ios::in);

// goes to the DJ's position in the file
fout.seekp(idjno * sizeof(a_dj));

// writes the DJ to the file
fout.write((char*)&a_dj, sizeof(a_dj));
fout.close();
}

int GenerateDJNumber()
{
int count;
int comp;

for (count = 1; count < 52; count++)
    {
	LocateDJ(count);

	comp = strcmpi(a_dj.flag, "0");
	
	if(comp == 0)
		{
		return count;
		} //endif

    } //endfor loop through all DJs to find empty DJ slot

// return -1 value if empty slot hasn't been found
return -1;
}

/* ------------------------------
 *           DJ Menu
 * ------------------------------ 
 */

int DJs()
{
int djstatus = 0;
while (djstatus != 5)
        {
        djstatus = DJMenu();
        clrscr();
        } //endwhile

return 0;
}

int DJMenu()
{
int djchoice;

clrscr();

cout << "\n\tDJ Menu";
cout << "\n\t=======\n";
cout << "\n\t1. View DJ";
cout << "\n\t2. Add DJ";
cout << "\n\t3. Change DJ";
cout << "\n\t4. Remove DJ";
cout << "\n\t5. Return";

cout << "\n\nEnter Choice: ";
cin >> djchoice;

// takes '\n' as input preventing input skipping
cin.get();

// there'll be some validation about access levels here

switch(djchoice)
	{
	case 1:
		{
		ViewDJ();
		clrscr();
		break;
		} // endcase
	case 2:
		{
		AddDJ();
		clrscr();
		break;
		} // endcase
	case 3:
		{
		ChangeDJ();
		clrscr();
		break;
		} // endcase
	case 4:
		{
		RemoveDJ();
		clrscr();
		break;
		} // endcase
	case 5:
		{
		clrscr();
		break;
		} // endcase
	} //endswitch

return djchoice;
}


/* ------------------------------
 *           View DJ
 * ------------------------------ 
 */


int ViewDJ()
{
int vistat = 0;
while (vistat != 4)
	{
	vistat = ViewDJMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewDJMenu()
{
int vidjch;

clrscr();

cout << "\n\tView DJ Menu";
cout << "\n\t============\n";
cout << "\n\t1. By Name";
cout << "\n\t2. By DJ Number";
cout << "\n\t3. By Music Style";
cout << "\n\t4. Return";

cout << "\nEnter Choice: ";
cin >> vidjch;

// ignores the new line
cin.ignore(1, '\n');

switch(vidjch)
	{
	case 1: 
		{
		ViewDJByName();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewByDJNumber();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewDJByMusicStyle();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return vidjch;
}

int ViewDJByName()
{
char djname[32];
char tnam[32];
int count = 0;
int compare = 0;

clrscr();
cout << "\nView DJ By Name";
cout << "\n===============\n";

// getting the name of the DJ
cout << "\nEnter DJ Name: ";
cin.getline(djname, 32);

// opens the file
ifstream fin(FileName6, ios::binary);

//  looping through all DJs in file
for (count = 1; count < 52; count++)
	{
	// getting the DJ name
	fin.seekg(count * sizeof(a_dj));
	fin.get((char*)&tnam, sizeof(tnam));

	// compares the inputted name to the name in the record
	compare = strcmpi(tnam, djname);

	// if the DJ has been found then load in the rest of the DJ
	if(compare == 0) 
		{
		// goes back to the position and loads in the full DJ
		fin.seekg(count * sizeof(a_dj));
		fin.get((char*)&a_dj, sizeof(a_dj));

		// break out of the loop to output everything
		break;
		} //endif the DJ is found
	} //endfor

fin.close();

// outputting DJ details
cout << "\nNumber: " << count;
cout << "\nName: " << a_dj.djnam;
cout << "\nPerformance Name: " << a_dj.performnam;
cout << "\nMusic Style: " << a_dj.musstyle;
cout << "\nPhone Number: " << a_dj.djtelenum;
cout << "\nEmail Address: " << a_dj.djemailaddr;

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewByDJNumber()
{
char indjno[10];
int idjno;

clrscr();
cout << "\nView By DJ Number";
cout << "\n=================\n";

// getting the DJ number
cout << "\nEnter DJ Number: ";
cin.getline(indjno, 32);

// converting the number into an integer
idjno = atoi(indjno);

// finds the DJ
LocateDJ(idjno);

// allow for some error correction here in the future

cout << "\nName: " << a_dj.djnam;
cout << "\nPerformance Name: " << a_dj.performnam;
cout << "\nMusic Style: " << a_dj.musstyle;
cout << "\nPhone Number: " << a_dj.djtelenum;
cout << "\nEmail Address: " << a_dj.djemailaddr;

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewDJByMusicStyle()
{
char inpstyle[24];
char tstyle[24];
int count = 0;
int compare = 0;
int jumpsize = 0;

clrscr();
cout << "\nView DJ By Music Style";
cout << "\n======================\n";

// this will need changing to a dropdown list
cout << "\nEnter Music Style: ";
cin.getline(inpstyle, 24);

// opens the file
ifstream fin(FileName6, ios::binary);

//  looping through all DJs in file
for (count = 1; count < 52; count++)
	{
	// getting the size of the jump this is the size of the DJ record - the size of the fields after the style
	jumpsize = ((count + 1) * sizeof(a_dj)) - (sizeof(a_dj.musstyle) + sizeof(a_dj.flag));

	// getting the style field in the record
	fin.seekg(jumpsize);
	fin.get((char*)&tstyle, sizeof(tstyle));

	// compares the inputted style to the style in the record
	compare = strcmpi(tstyle, inpstyle);

	// if the style has been found then load in the rest of the DJ
	if(compare == 0) 
		{
		// goes back to the position and loads in the full DJ
		fin.seekg(count * sizeof(a_dj));
		fin.get((char*)&a_dj, sizeof(a_dj));
	
		// outputting DJ details
        cout << "\n\nNumber: " << count;
		cout << "\nName: " << a_dj.djnam;
		cout << "\nPerformance Name: " << a_dj.performnam;
		cout << "\nMusic Style: " << a_dj.musstyle;
		cout << "\nPhone Number: " << a_dj.djtelenum;
		cout << "\nEmail Address: " << a_dj.djemailaddr;
		} //endif
	} //endfor

fin.close();



cout << "\n\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *           Add DJ
 * ------------------------------ 
 */

int AddDJ()
{
char tmpnam[32];
char tmpperf[32];
char tmpstyle[32];
char tmptelno[32];
char tmpemail[32];
int idjno;

clrscr();
cout << "\nAdd DJ";
cout << "\n======\n";

idjno = GenerateDJNumber();
LocateDJ(idjno);

// inputting the DJ's name
cout << "\nEnter DJ Name: ";
cin.getline(tmpnam, 32);

// inputting the email address
cout << "\nEmail Address: ";
cin.getline(tmpemail, 32);

// inputting the phone number
cout << "\nPhone Number: ";
cin.getline(tmptelno, 12);

// inputting the performance name
cout << "\nEnter DJ Performance Name: ";
cin.getline(tmpperf, 12);

// inputting the music style
cout << "\nEnter Music Style: ";
cin.getline(tmpstyle, 12);

cout << "\nDJ Number: " << idjno;

// copying across all relavent information
strcpy(a_dj.djnam, tmpnam);
strcpy(a_dj.performnam, tmpperf);
strcpy(a_dj.djtelenum, tmptelno);
strcpy(a_dj.musstyle, tmpstyle);
strcpy(a_dj.djemailaddr, tmpemail);

SetDJFlag(1);
WriteDJ(idjno);

cout << "\n\nPress any key to return";

getch();

return 0;
}


/* ------------------------------
 *           Change DJ
 * ------------------------------ 
 */

int ChangeDJ()
{
int chstat = 0;
while (chstat != 6)
	{
	chstat = ChangeDJMenu();
	clrscr();
	} //endwhile

return 0;
}


int ChangeDJMenu()
{
int chandjch;

clrscr();

cout << "\n\tChange DJ Menu";
cout << "\n\t==============\n";
cout << "\n\t1. Name";
cout << "\n\t2. Performance Name";
cout << "\n\t3. Phone Number";
cout << "\n\t4. Email Address";
cout << "\n\t5. Music Style";;
cout << "\n\t6. Return";

cout << "\n\nEnter Choice: ";
cin >> chandjch;

// ignores the new line
cin.ignore(1, '\n');

switch(chandjch)
	{
	case 1: 
		{
		ChangeDJName();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeDJPerformanceName();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeDJPhoneNumber();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ChangeDJEmailAddress();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		ChangeDJMusicStyle();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return chandjch;
}

int ChangeDJName()
{
char tmpdjno[10];
char tmpdjnam[32];
int idjno;

clrscr();
cout << "\nChange DJ Name";
cout << "\n==============\n";

// getting the name of the DJ
cout << "\nEnter DJ Number: ";
cin.getline(tmpdjno, 10);

// setting the current DJ as the inputted number
idjno = atoi(tmpdjno);

// loading the DJ into the DJ struct
LocateDJ(idjno);

// find the old details to display them just to make sure they have the right thing
cout << "\nDJ Name: " << a_dj.djnam;

// gets the new DJ name
cout << "\nNew DJ Name: ";
cin.getline(tmpdjnam, 32);

// copying the new DJ name into the DJ
strcpy(a_dj.djnam, tmpdjnam);

// updating the DJ record in the file
WriteDJ(idjno);

// output message if the changes have been made (a selection statement here to check)
cout << "\n\nSuccess - Name has been changed\n";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJPerformanceName()
{
char tmpdjno[10];
char tmpdjperfnam[32];
int idjno;

clrscr();
cout << "\nChange DJ Performance Name";
cout << "\n==========================\n";

// getting the number of the DJ
cout << "\nEnter DJ Number: ";
cin.getline(tmpdjno, 10);

// setting the current DJ as the inputted number
idjno = atoi(tmpdjno);

// loading the DJ into the DJ struct
LocateDJ(idjno);

// find the old details to display them just to make sure they have the right thing
cout << "\nCurrent DJ Performance Name: " << a_dj.performnam;

// entering the new performance name
cout << "\nNew Performance Name: ";
cin.getline(tmpdjperfnam, 32);

// copying the new DJ performance name into the DJ
strcpy(a_dj.performnam, tmpdjperfnam);

// updating the DJ record in the file
WriteDJ(idjno);

// a check would be needed here
cout << "\n\nSuccess - Performance Name has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJPhoneNumber()
{
char tmpdjno[10];
char tmptelno[32];
int idjno;

clrscr();
cout << "\nChange DJ Phone Number";
cout << "\n======================\n";

// getting the name of the DJ
cout << "\nEnter DJ Number: ";
cin.getline(tmpdjno, 10);

// setting the current DJ as the inputted number
idjno = atoi(tmpdjno);

// loading the DJ into the DJ struct
LocateDJ(idjno);

// find the old details to display them just to make sure they have the right thing
cout << "\nCurrent Phone Number: " << a_dj.djtelenum;

cout << "\nNew Phone Number: ";
cin.getline(tmptelno, 12);

// copying the new DJ phone number into the DJ
strcpy(a_dj.djtelenum, tmptelno);

// updating the DJ record in the file
WriteDJ(idjno);

// another check would be needed here
cout << "\n\nSuccess - Phone Number has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJEmailAddress()
{
char tmpdjno[10];
char tmpdjemail[32];
int idjno;

clrscr();
cout << "\nChange DJ Email Address";
cout << "\n=======================\n";

// getting the DJ number
cout << "\nEnter DJ Number: ";
cin.getline(tmpdjno, 10);

// setting the current DJ as the inputted number
idjno = atoi(tmpdjno);

// loading the DJ into the DJ struct
LocateDJ(idjno);

// find the old details to display them just to make sure they have the right thing
cout << "\nDJ Name: " << a_dj.djnam;
cout << "\nCurrent Email Address: " << a_dj.djemailaddr;

// getting the new email address
cout << "\nNew Email Address: ";
cin.getline(tmpdjemail, 32);

// copying the new DJ email into the DJ
strcpy(a_dj.djemailaddr, tmpdjemail);

// updating the DJ record in the file
WriteDJ(idjno);

// insert check here
cout << "\n\nSuccess - Email Address has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJMusicStyle()
{
char tmpdjno[10];
char tmpstyle[24];
int idjno;

clrscr();
cout << "\nChange DJ Music Style";
cout << "\n=====================\n";

// getting the DJ number
cout << "\nEnter DJ Number: ";
cin.getline(tmpdjno, 10);

// setting the current DJ as the inputted number
idjno = atoi(tmpdjno);

// loading the DJ into the DJ struct
LocateDJ(idjno);

// find the old details to display them just to make sure they have the right thing
cout << "\nDJ Name: " << a_dj.djnam;
cout << "\nCurrent Music Style: " << a_dj.musstyle;

// getting the new style
cout << "\nNew Music Style: ";
cin.getline(tmpstyle, 24);

// copying the new DJ style into the DJ
strcpy(a_dj.musstyle, tmpstyle);

// updating the DJ record in the file
WriteDJ(idjno);

// insert check here
cout << "\n\nSuccess - Music Style has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *           Remove DJ
 * ------------------------------ 
 */

int RemoveDJ()
{
char djnoc[10];
int idjno;
char choice;
int del = 1;
char tdjnam[32];

clrscr();
cout << "\nRemove DJ";
cout << "\n=========\n";

// gets the DJ number as an input
cout << "\nEnter DJ Number: ";
cin.getline(djnoc, 10);

// converts the DJ number to an integer
idjno = atoi(djnoc);

// finding the DJ
LocateDJ(idjno);

// needs to be here to stop incorrect deletion
if(strcmpi(a_dj.flag, "0") == 0)
	{
	cout << "\nError: DJ doesn't exist";
	
	cout << "\n\nPress any key to return";
	getch();
	return 0;
	} //endif the DJ doesn't exist

// copying in the djname at idjno into the temporary DJ name
strcpy(tdjnam, a_dj.djnam);

// find the old details to display them just to make sure they have the right thing
cout << "\nDJ to Remove: " << tdjnam;

// checking before it get removes the DJ
cout << "\nAre you sure you want to Delete " << tdjnam << " (y/n): ";
choice = cin.get();

if(choice == 'y')
	{
	del = 1;
	} //endif
else if(choice == 'n')
	{
	del = 0;
	} //endif

if(del == 1)
	{
	SetDJFlag(0);

	// insert check here
	cout << "\n\nSuccess - " << tdjnam << " has been deleted";

	WriteDJ(idjno);
	} //endif

cout << "\n\nPress any key to return";
getch();

return 0;
}


#pragma endregion


#pragma region Guests


/* ------------------------------
 *            Guests
 * ------------------------------ 
 */

int ReadBackGuestFile()
{
int count;
ifstream fin(FileName1, ios::binary);
fin.read((char*)&ngc, sizeof(ngc));
sscanf(&ngc[0], "%d", &ngi);

for (count = 0; count < ngi; count++)
	{
	fin.getline(guestno[count], sizeof(guestno[count]));
	fin.getline(gunam[count], sizeof(gunam[count]));
	fin.getline(gucontactnam[count], sizeof(gucontactnam[count]));
	fin.getline(guconttelenum[count], sizeof(guconttelenum[count]));
	fin.getline(guemailaddr[count], sizeof(guemailaddr[count]));
	} //endfor

fin.close();

return 0;
}

int ReWriteGuestFile()
{
int count;
ofstream fout(FileName1, ios::binary);

fout.write((char*)&ngc, sizeof(ngc));

for(count = 0; count < ngi; count++)
	{
	fout.write((char*)&guestno[count], strlen(guestno[count]));
	fout.write("\n", 1);
	fout.write((char*)&gunam[count], strlen(gunam[count]));
	fout.write("\n", 1);
	fout.write((char*)&gucontactnam[count], strlen(gucontactnam[count]));
	fout.write("\n", 1);
	fout.write((char*)&guconttelenum[count], strlen(guconttelenum[count]));
	fout.write("\n", 1);
	fout.write((char*)&guemailaddr[count], strlen(guemailaddr[count]));
	fout.write("\n", 1);
	} //endfor

fout.close();

return 0;
}

int GenerateGuestNumber(char inguno[10])
{
int result = ngi;

result = FindNextReferenceNumber(result, guestno, ngi);
itoa(result, inguno, 10);

return result;
}

void OutputGuest(int loc)
{
cout << "\nGuest Number: " << guestno[loc];
cout << "\nGuest Name: " << gunam[loc];
cout << "\nContact Name: " << gucontactnam[loc];
cout << "\nContact Phone Number: " << guconttelenum[loc];
cout << "\nContact Email Address: " << guemailaddr[loc];
}

/* ------------------------------
 *             Guests
 * ------------------------------ 
 */

int Guests()
{
int gustat = 0;
while (gustat != 5)
	{
	gustat = GuestsMenu();
	clrscr();
	} //endwhile

return 0;
}


int GuestsMenu()
{
int guch;

clrscr();

cout << "\n\tGuests Menu";
cout << "\n\t===========\n";
cout << "\n\t1. View Guest";
cout << "\n\t2. Add Guest";
cout << "\n\t3. Change Guest";
cout << "\n\t4. Remove Guest";
cout << "\n\t5. Return";

cout << "\n\nEnter Choice: ";
cin >> guch;

// ignores the new line
cin.get();

switch(guch)
	{
	case 1: 
		{
		ViewGuest();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		AddGuest();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeGuest();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		RemoveGuest();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return guch;
}

/* ------------------------------
 *          View Guests
 * ------------------------------ 
 */

int ViewGuest()
{
int vistat = 0;
while (vistat != 5)
	{
	vistat = ViewGuestMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewGuestMenu()
{
int viguch;

clrscr();

cout << "\n\tView Guest Menu";
cout << "\n\t===============\n";
cout << "\n\t1. By Name";
cout << "\n\t2. By Guest Number";
cout << "\n\t3. Guest Next Appearance";
cout << "\n\t4. By Next Appearance";
cout << "\n\t5. Return";

cout << "\nEnter Choice: ";
cin >> viguch;

// ignores the new line
cin.ignore(1, '\n');

switch(viguch)
	{
	case 1: 
		{
		ViewGuestByName();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewGuestByGuestNumber();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewGuestNextAppearance();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ViewGuestByNextAppearance();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return viguch;
}

int ViewGuestByName()
{
char ingunam[32];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nView Guest By Name";
cout << "\n==================\n";

// input for the guest number 
cout << "Enter Guest Name: ";
cin.getline(ingunam, 32);

// find the guest number in the guest numbers array
loc = FindInArray32(gunam, ingunam, ngi);

// outputs the details of the guest at that location
OutputGuest(loc);

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewGuestByGuestNumber()
{
char inguno[10];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nView Guest By Guest Number";
cout << "\n==========================\n";

// input for the guest number 
cout << "Enter Guest Number: ";
cin.getline(inguno, 10);

// find the guest number in the guest numbers array
loc = FindInArray10(guestno, inguno, ngi);

// outputs the details of the guest at that location
OutputGuest(loc);

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewGuestNextAppearance()
{
char inguno[10];
int tguno;
int guno;
int count;
char type;
int gunos[500];
int evids[500];
int top = 0;

ReadBackEventLinksFile();
ReadBackScheduleFile();
ReadBackEventFile();
ReadBackGuestFile();

clrscr();
cout << "\nView Guest Next Appearance";
cout << "\n==========================\n";

cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

guno = atoi(inguno);

// sort the events so that it outputs chronologically
BubbleEventSortDates(nei);

for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	if(type == 'G')
		{
		tguno = GetScheduleGuestNumber(eventno[count]);

		if(tguno == guno)
			{
			evids[top] = atoi(eventno[count]);
			gunos[top++] = GetScheduleGuestNumber(eventno[count]);
			} //endif the guest number found is equal to the input 
		} //endif found a guest slot
	} //endfor

OutputGuestEventsTabular(evids, gunos, "GNDaTmCN", top);

ReadBackEventFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewGuestByNextAppearance()
{
int count;
char type;
int gunos[500];
int evids[500];
int top = 0;

ReadBackEventLinksFile();
ReadBackScheduleFile();
ReadBackEventFile();
ReadBackGuestFile();

clrscr();
cout << "\nView Guest By Next Appearance";
cout << "\n=============================\n";

BubbleEventSortDates(nei);

for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	if(type == 'G')
		{
		evids[top] = atoi(eventno[count]);
		gunos[top++] = GetScheduleGuestNumber(eventno[count]);
		} //endif found a guest slot
	} //endfor

OutputGuestEventsTabular(evids, gunos, "GNDaTmCN", top);

ReadBackEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *           Add Guests
 * ------------------------------ 
 */

int AddGuest()
{
char tmpgunam[32];
char tmpgucontnam[32];
char tmpguconttel[12];
char tmpgucontemail[32];
char tmpguno[10];

ReadBackGuestFile();

clrscr();
cout << "\nAdd Guest";
cout << "\n=========\n";

// entering the guest name
cout << "\nEnter Guest Name: ";
cin.getline(tmpgunam, 32);

// entering the name of the contact
cout << "\nEnter Contact Name: ";
cin.getline(tmpgucontnam, 32);

// entering the phone number of the contact
cout << "\nEnter Contact Phone Number: ";
cin.getline(tmpguconttel, 12);

// entering the email address of the contact
cout << "\nEnter Contact Email Address: ";
cin.getline(tmpgucontemail, 32);

GenerateGuestNumber(tmpguno);

// copying the temporary variables into the global file variables
strcpy(guestno[ngi], tmpguno);
strcpy(gunam[ngi], tmpgunam);
strcpy(gucontactnam[ngi], tmpgucontnam);
strcpy(guconttelenum[ngi], tmpguconttel);
strcpy(guemailaddr[ngi], tmpgucontemail);

ngi = ngi + 1;
itoa(ngi, ngc, 10);
ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Change Guests
 * ------------------------------ 
 */

int ChangeGuest()
{
int chstat = 0;
while (chstat != 5)
	{
	chstat = ChangeGuestMenu();
	clrscr();
	} //endwhile

return 0;
}


int ChangeGuestMenu()
{
int changeguch;

clrscr();

cout << "\n\tChange Guest Menu";
cout << "\n\t=================\n";
cout << "\n\t1. Name";
cout << "\n\t2. Contact Name";
cout << "\n\t3. Contact Phone Number";
cout << "\n\t4. Contact Email Address";
cout << "\n\t5. Return";

cout << "\nEnter Choice: ";
cin >> changeguch;

// ignores the new line
cin.get();

switch(changeguch)
	{
	case 1: 
		{
		ChangeGuestName();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeGuestContactName();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeGuestContactPhoneNumber();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ChangeGuestContactEmailAddress();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return changeguch;
}

int ChangeGuestName()
{
char inguno[10];
char ingunam[32];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Name";
cout << "\n=================\n";

cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

loc = FindInArray10(guestno, inguno, ngi);

// effectively the same thing as the DJ equivalent
cout << "\nCurrent Guest Name: " << gunam[loc];

cout << "\nNew Guest Name: ";
cin.getline(ingunam, 32);

// here is where we could check that the new guest name is unique
strcpy(gunam[loc], ingunam);

// check it was actually successful
cout << "\nSuccess - Name has been changed\n";

ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeGuestContactName()
{
char inguno[10];
char ingucontnam[32];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Contact Name";
cout << "\n=========================\n";

// gets the guest number
cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

// finds the guest number in the file
loc = FindInArray10(guestno, inguno, ngi);

// effectively the same thing as the DJ equivalent
cout << "\nCurrent Contact Name: " << gucontactnam[loc];

// inputting the new contact name
cout << "\nNew Contact Name: ";
cin.getline(ingucontnam, 32);

// copying across the new contact name
strcpy(gucontactnam[loc], ingucontnam);

// check here
cout << "\nSuccess - Contact Name has been changed\n";

ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeGuestContactPhoneNumber()
{
char inguno[10];
char inguphonenum[12];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Contact Phone Number";
cout << "\n=================================\n";

// gets the guest number
cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

// finds the guest number in the file
loc = FindInArray10(guestno, inguno, ngi);

cout << "\nCurrent Phone Number: " << guconttelenum[loc];

cout << "\nNew Phone Number: ";
cin.getline(inguphonenum, 12);

// copies input into file
strcpy(guconttelenum[loc], inguphonenum);

// another check would be needed here
cout << "\nSuccess - Phone Number has been changed\n";

ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeGuestContactEmailAddress()
{
char inguno[10];
char inguemail[32];
int loc = 0;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Email Address";
cout << "\n==========================\n";

// gets the guest number
cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

// finds the guest number in the file
loc = FindInArray10(guestno, inguno, ngi);

// outputs the current email address
cout << "\nCurrent Email Address: " << guemailaddr[loc];

// gets the new email address
cout << "\nNew Email Address: ";
cin.getline(inguemail, 32);

// copies input into file
strcpy(guemailaddr[loc], inguemail);

// insert check here
cout << "\nSuccess - Email Address has been changed\n";

ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Remove Guests
 * ------------------------------ 
 */

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
	} //endfor

// insert check here
cout << "\nSuccess - " << guestname << " has been deleted\n";

ngi = ngi - 1;
itoa(ngi, ngc, 10);
ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

#pragma endregion


#pragma region Music

/* ----------------------------
 *            Music
 * ---------------------------- 
 */

int ReadBackMusicFile()
{
int count;
ifstream fin(FileName3, ios::binary);
fin.read((char*)&nmc, sizeof(nmc));
sscanf(&nmc[0], "%d", &nmi);

for (count = 0; count < nmi; count++)
        {
        fin.getline(mucatno[count], sizeof(mucatno[count]));
        fin.getline(mutitle[count], sizeof(mutitle[count]));
        fin.getline(muartist[count], sizeof(muartist[count]));
        fin.getline(mugenre[count], sizeof(mugenre[count]));
        fin.getline(mupub[count], sizeof(mupub[count]));
        fin.getline(muplaytime[count], sizeof(muplaytime[count]));
        fin.getline(mucheck[count], sizeof(mucheck[count]));
        fin.getline(mufreq[count], sizeof(mufreq[count]));
        } //endfor

fin.close();

return 0;
}

int ReWriteMusicFile()
{
int count;
ofstream fout(FileName3, ios::binary);

fout.write((char*)&nmc, sizeof(nmc));

for(count = 0; count < nmi; count++)
        {
        fout.write((char*)&mucatno[count], strlen(mucatno[count]));
        fout.write("\n", 1);
        fout.write((char*)&mutitle[count], strlen(mutitle[count]));
        fout.write("\n", 1);
        fout.write((char*)&muartist[count], strlen(muartist[count]));
        fout.write("\n", 1);
        fout.write((char*)&mugenre[count], strlen(mugenre[count]));
        fout.write("\n", 1);
        fout.write((char*)&mupub[count], strlen(mupub[count]));
        fout.write("\n", 1);
        fout.write((char*)&muplaytime[count], strlen(muplaytime[count]));
        fout.write("\n", 1);
        fout.write((char*)&mucheck[count], strlen(mucheck[count]));
        fout.write("\n", 1);
        fout.write((char*)&mufreq[count], strlen(mufreq[count]));
        fout.write("\n", 1);
        } //endfor

fout.close();

return 0;
}

int GenerateCatalogueNumber(char incatno[10])
{
int result = nmi;

result = FindNextReferenceNumber(result, mucatno, nmi);
itoa(result, incatno, 10);

return result;
}

int MusicLongestLength(char title[], int songids[], int size, char outvalues[][256])
{
int loc;
int maxlen;
int count;
char countc[10];

char lookupindex[][32] = { "Title", "Playtime", "Artist", "Genre", "Publisher", "Checked", "Frequency", "ID", "Rank" };
int notitles;

notitles = sizeof(lookupindex) / sizeof(lookupindex[0]);

loc = FindInArray32(lookupindex, title, notitles);

// uses this switch to determine which array should be used for the lonest search
switch (loc)
	{
	case 0:
		{
		maxlen = FindLongestInIndecies(mutitle, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mutitle[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 1:
		{
		maxlen = strlen(title);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], muplaytime[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 2:
		{
		maxlen = FindLongestInIndecies(muartist, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], muartist[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 3:
		{
		maxlen = FindLongestInIndecies(mugenre, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mugenre[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 4:
		{
		maxlen = FindLongestInIndecies(mupub, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mupub[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 5:
		{
		maxlen = strlen(title);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mucheck[songids[count]]);
			} //endfor
		} //endcase
	case 6:
		{
		maxlen = FindLongestInIndecies(mufreq, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mufreq[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 7:
		{
		maxlen = FindLongestInIndecies(mucatno, songids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], mucatno[songids[count]]);
			} //endfor
		break;
		} //endcase
	case 8:
		{
		maxlen = strlen(title);
		for(count = 0; count < size; count++)
			{
			// copies the index into the output value
			itoa((count+1), countc, 10);
			strcpy(outvalues[count], countc);
			} //endfor
		break;
		} //endcase
	default:
		{
		maxlen = strlen(title);
		break;
		} //enddefaultcase
	} //endswitch

return maxlen;
}

void OutputSong(int location, char heads[32])
{
int locs[1];

// setting the locs to loc
locs[0] = atoi(mucatno[location]);

OutputSongs(locs, heads, 1);
}

void OutputSongs(int songids[], char heads[32], int size)
{
int count;
int index;
int maxlens[512];

char outdata[512][256];

char fmtbump[32][32];
char titles[128][32];
int notitles;

char lookupindex[][32] = { "Title", "Playtime", "Artist", "Genre", "Publisher", "Checked", "Frequency", "ID", "Rank" };
char prefs[][32] = { "Ti", "Pl", "Ar", "Ge", "Pu", "Ch", "Fr", "ID", "Ra" };
int lookupsize;

lookupsize = sizeof(lookupindex) / sizeof(lookupindex[0]);

// gets all of the corresponding headers
notitles = GetHeaders(heads, titles, prefs, lookupindex, lookupsize);

// gets the locations of the songs in the catalogue and saves it to the file
GetRefLocations(mucatno, songids, nmi, size);

// getting the maximum length for all of the fields to show
for(count = 0; count < notitles; count++)
	{
	// gets the longest entry and adds the data for that field to the outdata
	maxlens[count] = MusicLongestLength(titles[count], songids, size, &outdata[size * count]);

	// adding the default bumper to the bumpers
	strcpy(fmtbump[count], "%s\t");
	} //endif

// getting the final alignment of the format
for(count = 0; count < notitles; count++)
	{
	FormatAlignment(titles[count], maxlens[count], fmtbump[count]);
	} //endfor

// looping through all of the headers and outputting them
for(count = 0; count < notitles; count++)
	{
	printf(fmtbump[count], titles[count]);
	} //endfor
cout << '\n';

// outputting all of the song details
for(count = 0; count < size; count++)
	{
	for(index = 0; index < notitles; index++)
		{
		printf(fmtbump[index], outdata[count + size * index]);
		} //endfor
	cout << '\n';
	} //endfor
}

void OutputSongLinear(int location)
{
cout << "\n\nFrequency: "<< mufreq[location];
cout << "\nCatalogue Number: "<< mucatno[location];
cout << "\nTitle: "<< mutitle[location];
cout << "\nPlaytime: "<< muplaytime[location];
cout << "\nArtist: "<< muartist[location];
cout << "\nGenre: "<< mugenre[location];
cout << "\nPublisher: "<< mupub[location];
cout << "\nChecked: "<< mucheck[location];
}

void SwapSongs(int index)
{
swap(mucatno[index], mucatno[index + 1]);
swap(mutitle[index], mutitle[index + 1]);
swap(muartist[index], muartist[index + 1]);
swap(mugenre[index], mugenre[index + 1]);
swap(mupub[index], mupub[index + 1]);
swap(muplaytime[index], muplaytime[index + 1]);
swap(mucheck[index], mucheck[index + 1]);
swap(mufreq[index], mufreq[index + 1]);
}

int ConvertPlaytimeToSecconds(char playtime[6])
{
int sec, min;
int res = 0;

// getting the mins and seconds
sscanf(playtime, "%d:%d", &min, &sec);

// converting min to seconds and adding to secs
res = sec + (60 * min);

return res;
}

/* ------------------------------
 *          Music Menu
 * ------------------------------ 
 */

int Music()
{
int musistatus = 0;
while (musistatus != 3)
	{
	musistatus = MusicMenu();
	clrscr();
	} //endwhile

return 0;
}


int MusicMenu()
{
int musicchoice;

clrscr();

cout << "\n\tMusic Menu";
cout << "\n\t==========\n";
cout << "\n\t1. Catalogue";
cout << "\n\t2. Playlists";
cout << "\n\t3. Return";

cout << "\n\nEnter Choice: ";
cin >> musicchoice;

switch(musicchoice)
	{
	case 1: 
		{
		Catalogue();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		Playlists();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		clrscr();
		break;
		} // endcase
	}

return musicchoice;
}

/* ------------------------------
 *          Catalogue
 * ------------------------------ 
 */

int Catalogue()
{
int catstat = 0;
while (catstat != 5)
	{
	catstat = CatalogueMenu();
	clrscr();
	} //endwhile

return 0;
}


int CatalogueMenu()
{
int catchoice;

clrscr();

cout << "\n\tCatalogue Menu";
cout << "\n\t==============\n";
cout << "\n\t1. View Catalogue";
cout << "\n\t2. Add Music";
cout << "\n\t3. Change Music";
cout << "\n\t4. Remove Music";
cout << "\n\t5. Return";

cout << "\n\nEnter Choice: ";
cin >> catchoice;

// ignores the new line
cin.ignore(1, '\n');

switch(catchoice)
	{
	case 1: 
		{
		ViewCatalogue();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		CatalogueAddMusic();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		CatalogueChangeMusic();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		CatalogueRemoveMusic();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return catchoice;
}

/* ------------------------------
 *        View Catalogue
 * ------------------------------ 
 */


int ViewCatalogue()
{
int viewstatus = 0;
while (viewstatus != 6)
	{
	viewstatus = ViewCatalogueMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewCatalogueMenu()
{
int viewcatch;

clrscr();

cout << "\n\tView Catalogue Music Menu";
cout << "\n\t=========================\n";
cout << "\n\t1. By Catalogue Number";
cout << "\n\t2. By Title";
cout << "\n\t3. By Artist";
cout << "\n\t4. By Genre";
cout << "\n\t5. By Popularity";
cout << "\n\t6. Return";

cout << "\nEnter Choice: ";
cin >> viewcatch;

// ignores the new line
cin.get();

switch(viewcatch)
	{
	case 1: 
		{
		ViewCatalogueByCatalogueNumber();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewCatalogueByTitle();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewCatalogueByArtist();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ViewCatalogueByGenre();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		ViewCatalogueByPopularity();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return viewcatch;
}

int ViewCatalogueByCatalogueNumber()
{
char tmpcatno[10];
int loc = 0;

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue Music By Catalogue Number";
cout << "\n========================================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

OutputSongLinear(loc);

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewCatalogueByTitle()
{
char tmptitle[48];
int songs[500];
int top = 0;
int loc = 0;

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue By Title";
cout << "\n=======================\n";

cout << "\nEnter Song Title: ";
cin.getline(tmptitle, 48);

// finds the title in the array
loc = FindInArray48(mutitle, tmptitle, nmi);
songs[top++] = atoi(mucatno[loc]);

while(loc >= 0)
        {
        // finds the title in the array from the starting location of loc + 1
        loc = FindInArray48(mutitle, tmptitle, nmi, loc + 1);

		// break if a song hasn't been found
		if(loc == -1)
			break;
		
		// adding the song ID to the stack
		songs[top++] = atoi(mucatno[loc]);
        } //endwhile

OutputSongs(songs, "IdTiPlArGePuCh", top);

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewCatalogueByArtist()
{
char tmpartist[48];
int songs[500];
int top = 0;
int loc = 0;

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue By Artist";
cout << "\n========================\n";

cout << "\nEnter Song Artist: ";
cin.getline(tmpartist, 48);

// finds the first song by that artist
loc = FindInArray32(muartist, tmpartist, nmi);
songs[top++] = atoi(mucatno[loc]);

while(loc >= 0)
        {
        // finds the artist in the array from the starting location of loc + 1
        loc = FindInArray32(muartist, tmpartist, nmi, loc + 1);
		
		// break if a song hasn't been found
		if(loc == -1)
			break;
		
		// adding the song ID to the stack
		songs[top++] = atoi(mucatno[loc]);
        } //endwhile

OutputSongs(songs, "IdTiPlArGePuCh", top);

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewCatalogueByGenre()
{
char tmpgenre[24];
int songs[500];
int loc = 0;
int top = 0;

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue By Genre";
cout << "\n=======================\n";

cout << "\nEnter Song Genre: ";
cin.getline(tmpgenre, 24);

// finds the first song in the inputted genre
loc = FindInArray24(mugenre, tmpgenre, nmi);
songs[top++] = atoi(mucatno[loc]);

while(loc >= 0)
        {
        // finds the genre in the array from the starting location of loc + 1
        loc = FindInArray24(mugenre, tmpgenre, nmi, loc + 1);
		
		// break if a song hasn't been found
		if(loc == -1)
			break;
		
		songs[top++] = atoi(mucatno[loc]);
        } //endwhile

// outputting the title, playtime, artist, genre, publisher, check and ID of songs
OutputSongs(songs, "TiPlArGePuChId", top);

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewCatalogueByPopularity()
{
int count;
int outcatnos[50];

// creating a pointer to the first part of the array
int* ifreqs;

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue By Popularity";
cout << "\n============================\n";

// creating the new array
ifreqs = new int[nmi];

// looping throught the frequencies and adding them to a list
for(count = 0; count < nmi; count++)
	{
	ifreqs[count] = atoi(mufreq[count]);
	} //endfor

// sorting the music
ExtendedBubbleSort(ifreqs, nmi, SwapSongs);

// maybe add something here to not include unchecked songs

// adding the top 50 songs (or until end of catalogue) to an array to be outputted
for(count = 0; (count < nmi) && (count < 50); count++)
	{
	// sorts smallest to largest therefore reverse the list
	outcatnos[nmi - 1 - count] = atoi(mucatno[count]);
	} //endfor

// outputting all of the songs
OutputSongs(outcatnos, "RaFrTiPlArGeId", count);

// reading back again to restore the file back to it's origional state
ReadBackMusicFile();

cout << "\n\nPress any key to return";
getch();

// deleting the array after usage
delete ifreqs;

return 0;
}

/* ------------------------------
 *        Add To Catalogue
 * ------------------------------ 
 */

int CatalogueAddMusic()
{
char tmpcatno[10];
char tmptitle[48];
char tmpartist[32];
char tmpgenre[24];
char tmppub[64];
char tmpplaytime[6];

ReadBackMusicFile();

clrscr();
cout << "\nAdd Music";
cout << "\n=========\n";

// entering the song details
cout << "\nEnter Song Title: ";
cin.getline(tmptitle, 48);

cout << "\nEnter Artist: ";
cin.getline(tmpartist, 32);

cout << "\nEnter Playtime: ";
cin.getline(tmpplaytime, 6);

cout << "\nEnter Publisher: ";
cin.getline(tmppub, 64);

cout << "\nEnter Genre: ";
cin.getline(tmpgenre, 24);

// generating the catalogue number
GenerateCatalogueNumber(tmpcatno);

// copying the temporary variables into the global file variables
strcpy(mucatno[nmi], tmpcatno);
strcpy(mutitle[nmi], tmptitle);
strcpy(muartist[nmi], tmpartist);
strcpy(mugenre[nmi], tmpgenre);
strcpy(muplaytime[nmi], tmpplaytime);
strcpy(mupub[nmi], tmppub);

// the default values for the frequency and the check will be 0 and 'N'
strcpy(mufreq[nmi], "0\0");
strcpy(mucheck[nmi], "N\0");

nmi = nmi + 1;
itoa(nmi, nmc, 10);
ReWriteMusicFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *      Change In Catalogue
 * ------------------------------ 
 */

int CatalogueChangeMusic()
{
int changestatus = 0;
while (changestatus != 6)
	{
	changestatus = CatalogueChangeMusicMenu();
	clrscr();
	} //endwhile

return 0;
}

int CatalogueChangeMusicMenu()
{
int changemusicchoice;

clrscr();

cout << "\n\tChange Music Menu";
cout << "\n\t=================\n";
cout << "\n\t1. Title";
cout << "\n\t2. Artist";
cout << "\n\t3. Playtime";
cout << "\n\t4. Genre";
cout << "\n\t5. Check";
cout << "\n\t6. Return";

cout << "\n\nEnter Choice: ";
cin >> changemusicchoice;

// ignores the new line
cin.get();

switch(changemusicchoice)
	{
	case 1: 
		{
		ChangeMusicTitle();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeMusicArtist();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeMusicPlaytime();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ChangeMusicGenre();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		ChangeMusicCheck();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return changemusicchoice;
}

int ChangeMusicTitle()
{
char tmpcatno[10];
int loc = 0;
char ntitle[64];

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Title";
cout << "\n==================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

cout << "\nCurrent Title: " << mutitle[loc];

cout << "\nNew Title: ";
cin.getline(ntitle, 64);

// there'll be some future validation here

// copying new title into old title
strcpy(mutitle[loc], ntitle);

ReWriteMusicFile();

// insert check here
cout << "\nSuccess - Title has been Changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicArtist()
{
char nartist[64];
char tmpcatno[10];
int loc = 0;

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Artist";
cout << "\n===================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

cout << "\nCurrent Artist: " << muartist[loc];

cout << "\nNew Artist: ";
cin.getline(nartist, 64);

// there'll be some future validation here

// copying new title into old artist
strcpy(muartist[loc], nartist);

ReWriteMusicFile();

// insert check here
cout << "\nSuccess - Artist has been Changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicPlaytime()
{
char tmpcatno[10];
int loc = 0;
char nplaytim[6];

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Playtime";
cout << "\n=====================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

cout << "\nCurrent Playtime: " << muplaytime[loc];

cout << "\nNew Playtime: ";
cin.getline(nplaytim, 6);

// there'll be some future validation here

// copying new playtime into old playtime
strcpy(muplaytime[loc], nplaytim);

ReWriteMusicFile();

// insert check here
cout << "\nSuccess - Playtime has been Changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicGenre()
{
char tmpcatno[10];
int loc = 0;
char ngenre[24];

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Genre";
cout << "\n==================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

cout << "\nCurrent Genre: " << mugenre[loc];

// getting new genre
cout << "\nNew Genre: ";
cin.getline(ngenre, 24);

// one in list validation here

// writing the variable
strcpy(mugenre[loc], ngenre);

ReWriteMusicFile();

// insert check here
cout << "\nSuccess - Genre has been Changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicCheck()
{
char tmpcatno[10];
int loc = 0;
char choice[2];

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Check";
cout << "\n==================\n";

cout << "\nEnter Catalogue Number: ";
cin.getline(tmpcatno, 10);

// finds the catalogue number in the array
loc = FindInArray10(mucatno, tmpcatno, nmi);

cout << "\nCurrent Check: " << mucheck[loc];

cout << "\nNew Check: ";
cin.getline(choice, 2);

// writing the variable
strcpy(mucheck[loc], choice);

ReWriteMusicFile();

// insert check here
cout << "\nSuccess - The check has been Changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *      Remove From Catalogue
 * ------------------------------ 
 */

int CatalogueRemoveMusic()
{
char innum[10];
int find = 0;
int del = 0;
char songtitle[32];
char choice;

strcpy(songtitle, gunam[find]);
ReadBackMusicFile();

clrscr();
cout << "\nRemove Music";
cout << "\n============\n";

// get song name
cout << "\nEnter Catalogue Number: ";
cin.getline(innum, 9);

find = FindInArray10(mucatno, innum, nmi);

// another warning to highlight changes
cout << "\nWarning: Deleting will remove this song from all playlists it is in";

// confirmaiton required to reduce mistakes
cout << "\nAre you sure you want to Delete " << songtitle << " (y/n): ";
choice = cin.get();
cin.get();

if(choice != 'y')
	{
	cout << "\nDeletion cancelled";

	cout << "\nPress any key to return";
	getch();

	return 0;
	} //endif shouldn't remove

// quick bit of validation to make sure that nothing accidental is done during testing
if(find == -1)
	return 0;

RemovePlaylistEntriesBySong(mucatno[find]);

for (del = find; del < nmi; del++)
	{
	strcpy(mucatno[del], mucatno[del+1]);
	strcpy(mutitle[del], mutitle[del+1]);
	strcpy(muartist[del], muartist[del+1]);
	strcpy(mugenre[del], mugenre[del+1]);
	strcpy(mupub[del], mupub[del+1]);
	strcpy(muplaytime[del], muplaytime[del+1]);
	strcpy(mucheck[del], mucheck[del+1]);
	strcpy(mufreq[del], mufreq[del+1]);
	} //endfor

// insert check here
cout << "\nSuccess - " << songtitle << " has been deleted\n";

nmi = nmi - 1;
itoa(nmi, nmc, 10);
ReWriteMusicFile();
ReWritePlaylistFile();

cout << "\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *          Playlists
 * ------------------------------ 
 */


int ReadBackPlaylistFile()
{
int count;
ifstream fin(FileName5, ios::binary);
fin.read((char*)&npc, sizeof(npc));
sscanf(&npc[0], "%d", &npi);

for (count = 0; count < npi; count++)
        {
        fin.getline(pllinkcatno[count], sizeof(pllinkcatno[count]));
        fin.getline(pllinkevno[count], sizeof(pllinkevno[count]));
        } //endfor

fin.close();

return 0;
}

int ReWritePlaylistFile()
{
int count;
ofstream fout(FileName5, ios::binary);

fout.write((char*)&npc, sizeof(npc));

for(count = 0; count < npi; count++)
        {
        fout.write((char*)&pllinkcatno[count], strlen(pllinkcatno[count]));
        fout.write("\n", 1);
        fout.write((char*)&pllinkevno[count], strlen(pllinkevno[count]));
        fout.write("\n", 1);
        } //endfor

fout.close();

return 0;
}

void AddPlaylistEntry(char inevno[10], char incatno[10])
{
int muloc = 0;
int curcount = 0;

ReadBackPlaylistFile();
ReadBackMusicFile();

// finds song index
muloc = FindInArray10(mucatno, incatno, nmi);

// converting the count to and integer
curcount = atoi(mufreq[muloc]);

// increasing the frequency of the song by 1
curcount += 1;

// writing the new count
itoa(curcount, mufreq[muloc], 10);

strcpy(pllinkevno[npi], inevno);
strcpy(pllinkcatno[npi], incatno);

npi = npi + 1;
itoa(npi, npc, 10);
ReWritePlaylistFile();
}

void RemovePlaylistEntriesBySong(char incatno[10])
{
int count;

for(count = 0; count < npi; count++)
	{
	RemovePlaylistEntry(pllinkevno[count], incatno);
	} //endfor
}

void RemovePlaylistEntriesByEvent(char inevno[10])
{
int count;

for(count = 0; count < nmi; count++)
	{
	// removes the link with that event number and catalogue number
	RemovePlaylistEntry(inevno, mucatno[count]);
	} //endfor
}

void RemovePlaylistEntry(char inevno[10], char incatno[10])
{
int muloc = 0;
int curcount;
int find = 0;
int del = 0;
int compare = 0;

// find the event number in the array
find = FindInArray10(pllinkevno, inevno, npi);

// if the event isn't in the file return early
if(find == -1)
	return;

// check if the catalogue number at find is correct
compare = strcmpi(pllinkcatno[find], incatno);

// if not correct repeat
while(compare != 0 && find != -1)
	{
	// find the event number in the array
	find = FindInArray10(pllinkevno, inevno, npi, find + 1);

	// check if the catalogue number at find is correct
	compare = strcmpi(pllinkcatno[find], incatno);
	} //endwhile loop through the entries in the playlist to find the song

// return early if there isn't an entry with the correct details
if(find == -1)
	return;

// finds song index
muloc = FindInArray10(mucatno, incatno, nmi);

// converting the frequency to an integer and decreasing the frequency of the song by 1
curcount = atoi(mufreq[muloc]) - 1;

// writing the new count
itoa(curcount, mufreq[muloc], 10);

for (del = find; del < npi; del++)
	{
	strcpy(pllinkevno[del], pllinkevno[del+1]);
	strcpy(pllinkcatno[del], pllinkcatno[del+1]);
	} //endfor

npi = npi - 1;
itoa(npi, npc, 10);
}

int CalculatePlaylistDuration(char inevno[10])
{
int count;
int dur = 0;
int loc;
int tdur;

for (count = 0; count < npi; count++)
	{
	if(strcmpi(pllinkevno[count], inevno) == 0)
		{
		// finds the song in the catalogue
		loc = FindInArray10(mucatno, pllinkcatno[count], nmi);

		// looks up the duration and saves it to a temp variable
		tdur = ConvertPlaytimeToSecconds(muplaytime[loc]);

		dur += tdur;
		} //endif the event num is equal to the inputted number
	} //endfor

return dur;
}

int Playlists()
{
int playliststatus = 0;
while (playliststatus != 5)
	{
	playliststatus = PlaylistsMenu();
	clrscr();
	} //endwhile

return 0;
}

int PlaylistsMenu()
{
int playlistschoice;

clrscr();

cout << "\n\tPlaylists Menu";
cout << "\n\t==============\n";
cout << "\n\t1. View Playlist";
cout << "\n\t2. Create Playlist";
cout << "\n\t3. Edit Playlist";
cout << "\n\t4. Remove Playlist";
cout << "\n\t5. Return";

cout << "\nEnter Choice: ";
cin >> playlistschoice;

// ignores the new line
cin.ignore(1, '\n');

switch(playlistschoice)
	{
	case 1: 
		{
		ViewPlaylist();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		CreatePlaylist();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		EditPlaylist();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		RemovePlaylist();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return playlistschoice;
}

/* ------------------------------
 *         View Playlists
 * ------------------------------ 
 */

int ViewPlaylist()
{
char inevref[10];
int loc = 0;
int muloc;
int top = 0;
int plids[1024];
int pldur;

ReadBackPlaylistFile();
ReadBackMusicFile();
ReadBackEventFile();

clrscr();
cout << "\nView Playlist";
cout << "\n=============\n";

cout << "\nEnter Event Reference: ";
cin.getline(inevref, 10);

// finds the event in the event file
loc = FindInArray10(eventno, inevref, nei);
cout << "Event Title: " << evtitle[loc] << '\n';

pldur = CalculatePlaylistDuration(inevref);

// finding the playlist
loc = FindInArray10(pllinkevno, inevref, npi);

// here is an ideal place to validate

// finding the song
muloc = FindInArray10(mucatno, pllinkcatno[loc], nmi);

printf("\nPlaylist Duration: %d:%d\n", pldur/60, pldur % 60);

// while songs can be found add them to the songidlist
while(loc != -1)
	{
	// starts at loc + 1 so it doesn't repeat itself
	loc = FindInArray10(pllinkevno, inevref, npi, loc + 1);

	// adds the catno to the list of catnos
	plids[top] = atoi(pllinkcatno[loc]);
	top += 1;
	} //endwhile

// outputs all of the songs
OutputSongs(plids, "TiArPlId", top);

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *        Create Playlists
 * ------------------------------ 
 */

void DurationEnding(char output[64], int durdiff)
{
char tmpminstr[9] = "minutes";

if(abs(durdiff) == 1)
		{
		strcpy(tmpminstr, "minute");
		} //endif the difference is 1 minute

if(durdiff < 0)
	{
	sprintf(output, "%d %s over", abs(durdiff), tmpminstr);
	} //endif the difference is negative
else if(durdiff > 0)
	{
	sprintf(output, "%d %s under", abs(durdiff), tmpminstr);
	} //endif the difference is positive
else if(durdiff == 0)
	{
	sprintf(output, "Playlist correct duration");
	} //endif is exactly on
}

int PlaylistDurationCheck(char evno[10], int pldur)
{
char ending[64];
int evloc;
int evduri;
int durdiff;
int curdur = pldur;
int cdurmin;

evloc = FindInArray10(eventno, evno, nei);

evduri = atoi(evdur[evloc]) * 60;

if(pldur <= 0)
	{
	curdur = CalculatePlaylistDuration(evno);
	} //endif there is no input duration

// gets the difference in the duration of the playlist and the event
cdurmin = curdur / 60;
durdiff = evduri - cdurmin;

if(durdiff == 0 && pldur == -1)
	{
	return -curdur;
	} //endif there should be no output

DurationEnding(ending, durdiff);

printf("\nPlaylist Duration: %.2d:%.2d\nRequired Duration: %d:00\n%s\n", cdurmin, curdur % 60, evduri, ending);


return curdur;
}

int CreatePlaylist()
{
char inevref[10];
char incatno[10];
char ending[64];
char choice;

int evduri;
int durdiff;
int muloc = 0;
int evloc = 0;
int curdur = 0;
int cdurmin;

ReadBackPlaylistFile();
ReadBackMusicFile();
ReadBackEventFile();

clrscr();
cout << "\nCreate Playlist";
cout << "\n===============\n";

cout << "\nEnter Event Number: ";
cin.getline(inevref, 10);

// finds the event
evloc = FindInArray10(eventno, inevref, nei);

// validate the event exists here and that there isn't already a playlist

// convert dur to mins
evduri = atoi(evdur[evloc]) * 60;

curdur = CalculatePlaylistDuration(inevref);

// gets the difference in the duration of the playlist and the event
cdurmin = curdur / 60;
durdiff = evduri - cdurmin;
DurationEnding(ending, durdiff);

printf("\nPlaylist Duration: %.2d:%.2d\nRequired Duration: %d:00\n%s\n", cdurmin, curdur % 60, evduri, ending);

cout << "\nEnter Catalogue Number: ";
cin.getline(incatno, 10);

// finds the song
muloc = FindInArray10(mucatno, incatno, nmi);

// validate the song exists here

// adding the new song's duration to the current playlist duration
curdur += ConvertPlaytimeToSecconds(muplaytime[muloc]);

// adds the song to the playlist
AddPlaylistEntry(inevref, incatno);

cdurmin = curdur / 60;
durdiff = evduri - cdurmin;
DurationEnding(ending, durdiff);

cout << "\nContinue adding songs (y/n): ";
choice = cin.get();
cin.get();

// if should continue adding
while(choice == 'y')
	{
	printf("\nPlaylist Duration: %.2d:%.2d\nRequired Duration: %d:00\n%s\n", cdurmin, curdur % 60, evduri, ending);
	cout << "\nEnter Catalogue Number: ";
	cin.getline(incatno, 10);

	// adding the new song's duration to the current playlist duration
	curdur += ConvertPlaytimeToSecconds(muplaytime[muloc]);

	cdurmin = curdur / 60;
	durdiff = evduri - cdurmin;
	DurationEnding(ending, durdiff);

	// adds the song to the playlist
	AddPlaylistEntry(inevref, incatno);

	cout << "\nContinue adding songs (y/n): ";
	choice = cin.get();
	cin.get();
	} //endwhile

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *        Edit Playlists
 * ------------------------------ 
 */

int EditPlaylist()
{
int editstatus = 0;
while (editstatus != 3)
	{
	editstatus = EditPlaylistMenu();
	clrscr();
	} //endwhile

return 0;
}

int EditPlaylistMenu()
{
int editplaylistchoice;

clrscr();

cout << "\n\tEdit Playlist Menu";
cout << "\n\t==================\n";
cout << "\n\t1. Add Music";
cout << "\n\t2. Remove Music";
cout << "\n\t3. Return";

cout << "\nEnter Choice: ";
cin >> editplaylistchoice;

// ignores the new line
cin.get();

switch(editplaylistchoice)
	{
	case 1: 
		{
		AddMusic();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		RemoveMusic();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		clrscr();
		break;
		} // endcase
	}

return editplaylistchoice;
}

int AddMusic()
{
char inevref[10];
char incatno[10];
char choice;

ReadBackMusicFile();
ReadBackEventFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nAdd Music";
cout << "\n=========\n";

cout << "\nEnter Event Number: ";
cin.getline(inevref, 10);

// validate the event and playlist exists here 

cout << "\nEnter Catalogue Number: ";
cin.getline(incatno, 10);

// adds the song to the playlist
AddPlaylistEntry(inevref, incatno);

cout << "\nContinue adding songs (y/n): ";
choice = cin.get();

// if should continue adding
while(choice == 'y')
	{
	cout << "\nEnter Catalogue Number: ";
	cin.getline(incatno, 10);

	// adds the song to the playlist
	AddPlaylistEntry(inevref, incatno);

	cout << "\nContinue adding songs (y/n): ";
	choice = cin.get();
	} //endwhile

ReWritePlaylistFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int RemoveMusic()
{
char inevref[10];
char incatno[10];

ReadBackMusicFile();
ReadBackEventFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nRemove Music";
cout << "\n============\n";

cout << "\nEnter Event Number: ";
cin.getline(inevref, 10);

// validate event exists  

cout << "\nEnter Catalogue Number: ";
cin.getline(incatno, 10);

// validate song exists

RemovePlaylistEntry(inevref, incatno);

ReWritePlaylistFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *       Remove Playlists
 * ------------------------------ 
 */

int RemovePlaylist()
{
char evno[10];

ReadBackMusicFile();
ReadBackEventFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nRemove Playlist";
cout << "\n===============\n";

cout << "\nEnter Event Number: ";
cin.getline(evno, 10);

// validate the event number here

RemovePlaylistEntriesByEvent(evno);

ReWritePlaylistFile();

cout << "\nPress any key to return";
getch();

return 0;
}


#pragma endregion


#pragma region Admin


/* ------------------------------
 *          Admin Menu
 * ------------------------------ 
 */


int Admin()
{
int admistatus = 0;
while (admistatus != 6)
	{
	admistatus = AdminMenu();
	clrscr();
	} //endwhile

return 0;
}


int AdminMenu()
{
int adminchoice;

clrscr();

cout << "\n\tAdmin Menu";
cout << "\n\t==========\n";
cout << "\n\t1. Add User";
cout << "\n\t2. Change User";
cout << "\n\t3. Remove User";
cout << "\n\t4. Backup";
cout << "\n\t5. Recovery";
cout << "\n\t6. Return";

cout << "\n\nEnter Choice: ";
cin >> adminchoice;

// ignores the new line
cin.ignore(1, '\n');

switch(adminchoice)
	{
	case 1: 
		{
		AddUser();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeUser();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		RemoveUser();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		Backup();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		Recovery();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return adminchoice;
}

/* ------------------------------
 *          Add User
 * ------------------------------ 
 */


int AddUser()
{
clrscr();
cout << "\nAdd User";
cout << "\n========\n";

cout << "\nEnter Username: ";
cout << "ThomasC";

cout << "\nEnter Password: ";
cout << "Password!23\n";

cout << "\nEnter Access Level: ";
cout << "2\n";

// add in the linking to the DJs

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *         Change User
 * ------------------------------ 
 */


int ChangeUser()
{
int changestatus = 0;
while (changestatus != 4)
	{
	changestatus = ChangeUserMenu();
	clrscr();
	} //endwhile

return 0;
}

int ChangeUserMenu()
{
int changeuserchoice;

clrscr();

cout << "\n\tChange User Menu";
cout << "\n\t================\n";
cout << "\n\t1. Username";
cout << "\n\t2. Password";
cout << "\n\t3. Access Level";
cout << "\n\t4. Return";

cout << "\n\nEnter Choice: ";
cin >> changeuserchoice;

// ignores the new line
cin.get();

switch(changeuserchoice)
	{
	case 1: 
		{
		ChangeUserUsername();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeUserPassword();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeUserAccessLevel();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return changeuserchoice;
}

int ChangeUserUsername()
{
clrscr();
cout << "\nChange Username";
cout << "\n====================\n";

cout << "\nEnter Username: ";
cout << "ThomasC\n";

cout << "\nCurrent Username: " << "ThomasC";

cout << "\nEnter New Username: ";
cout << "TomC";

cout << "\n\nSuccess - Username has been changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeUserPassword()
{
clrscr();
cout << "\nChange Password";
cout << "\n====================\n";

cout << "\nEnter Username: ";
cout << "TomC\n";

// enter current password for security
cout << "\nEnter Current Password: ";
cout << "Password!23";

cout << "\nEnter New Password: ";
cout << "Password!123";

// double entry for security
cout << "\nEnter New Password Again: ";
cout << "Password!123";

cout << "\n\nSuccess - Password has been changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeUserAccessLevel()
{
clrscr();
cout << "\nChange User Access Level";
cout << "\n========================\n";

cout << "\nEnter Username: ";
cout << "TomC\n";

cout << "\nAccess Level: " << "2";

cout << "\nEnter New Access Level: ";
cout << "1";

cout << "\n\nSuccess - Access Level has been changed\n";

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Remove User
 * ------------------------------ 
 */

int RemoveUser()
{
clrscr();
cout << "\nRemove User";
cout << "\n===========\n";

cout << "\nEnter the username of the user to remove: ";
cout << "TomC\n";

cout << "\nAre you sure you want to remove " << "TomC" << " (y/n): ";
cout << "y";

// outputting which user at the end just as another check to make sure it is clear who has been removed
cout << "\nSuccess - the user " << "TomC" << " has been removed";

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *             Backup
 * ------------------------------ 
 */

int Backup()
{
clrscr();
cout << "\nBackup";
cout << "\n======\n";

cout << "Would you like to make a new backup (y/n): ";
cout << "y";

cout << "\nBacking up all data";

cout << "\nSuccess - A new backup has been created";

cout << "\n\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *           Recovery
 * ------------------------------ 
 */

int Recovery()
{
clrscr();
cout << "\nRecovery";
cout << "\n========\n";

cout << "Would you like to recover to a previous version (y/n): ";
cout << "y";

cout << "\n1. 12/12/2023";
cout << "\n2. 10/12/2023";
cout << "\n3. 29/11/2023";
cout << "\n4. Return";

cout << "\nSelect which version to recover to: ";
cout << "2";

cout << "\nAre you sure you want to recover to " << "10/12/2023" << " data after " << "10/12/2023" << " will be inaccessible (y/n): ";
cout << "y";

cout << "\n\nSuccess - The system has been recovered to the backup made on " << "10/12/2023";

cout << "\nPress any key to return";
getch();

return 0;
}


#pragma endregion


#pragma region Events

/* ------------------------------
 *         Event Links
 * ------------------------------ 
 */

int ReadBackEventLinksFile()
{
int count;
ifstream fin(FileName4, ios::binary);
fin.read((char*)&nlc, sizeof(nlc));
sscanf(&nlc[0], "%d", &nli);

for (count = 0; count < nli; count++)
	{
	fin.getline(evlinkevno[count], sizeof(evlinkevno[count]));
	fin.getline(evlinkdjno[count], sizeof(evlinkdjno[count]));
	} //endfor

fin.close();

return 0;
}

int ReWriteEventLinksFile()
{
int count;
ofstream fout(FileName4, ios::binary);

fout.write((char*)&nlc, sizeof(nlc));

for(count = 0; count < nli; count++)
	{
	fout.write((char*)&evlinkevno[count], strlen(evlinkevno[count]));
	fout.write("\n", 1);
	fout.write((char*)&evlinkdjno[count], strlen(evlinkdjno[count]));
	fout.write("\n", 1);
	} //endfor

fout.close();

return 0;
}

void OutputEventsTabular(int evids[], char heads[32], int size)
{
int count;
int index;
int maxlens[512];

char outdata[512][256];

char fmtbump[32][32];
char titles[128][32];
int notitles;

char lookupindex[][32] = { "ID", "Date", "Time", "Duration", "Location", "Description", "Title", "Cost", "Contact Name", "Contact Email", "Contact Phone Number", "Rank" };
char prefsindx[][32] = { "ID", "Da", "Tm", "Du", "Lo", "De", "Ti", "Co", "CN", "CE", "CP", "Ra" };
int lookupsize;

lookupsize = sizeof(lookupindex) / sizeof(lookupindex[0]);

// gets all of the corresponding headers
notitles = GetHeaders(heads, titles, prefsindx, lookupindex, lookupsize);

// gets the locations of the events in the files
GetRefLocations(eventno, evids, nei, size);

// getting the maximum length for all of the fields to show
for(count = 0; count < notitles; count++)
	{
	// gets the longest entry and adds the data for that field to the outdata
	maxlens[count] = EventsLongestLength(titles[count], evids, size, &outdata[size * count]);

	// adding the default bumper to the bumpers
	strcpy(fmtbump[count], "%s\t");
	} //endif

// getting the final alignment of the format
for(count = 0; count < notitles; count++)
	{
	FormatAlignment(titles[count], maxlens[count], fmtbump[count]);
	} //endfor

// looping through all of the headers and outputting them
for(count = 0; count < notitles; count++)
	{
	printf(fmtbump[count], titles[count]);
	} //endfor
cout << '\n';

// outputting all of the event details
for(count = 0; count < size; count++)
	{
	for(index = 0; index < notitles; index++)
		{
		printf(fmtbump[index], outdata[count + size * index]);
		} //endfor
	cout << '\n';
	} //endfor
}

void OutputGuestEventsTabular(int evids[], int gunos[], char heads[32], int size)
{
int count;
int index;
int maxlens[512];

char outdata[512][256];

char fmtbump[32][32];
char titles[128][32];
int notitles;

char lookupindex[][32] = { "ID", "Date", "Time", "Duration", "Title", "Contact Name", "Contact Email", "Contact Phone Number", "Guest Name", "Rank" };
char prefsindx[][32] = { "ID", "Da", "Tm", "Du", "Ti", "CN", "CE", "CP", "GN", "Ra" };
int lookupsize;

lookupsize = sizeof(lookupindex) / sizeof(lookupindex[0]);

// gets all of the corresponding headers
notitles = GetHeaders(heads, titles, prefsindx, lookupindex, lookupsize);

// gets the locations of the events in the files
GetRefLocations(eventno, evids, nei, size);

// getting the maximum length for all of the fields to show
for(count = 0; count < notitles; count++)
	{
	// gets the longest entry and adds the data for that field to the outdata
	maxlens[count] = GuestEventLongestLength(titles[count], evids, gunos, size, &outdata[size * count]);

	// adding the default bumper to the bumpers
	strcpy(fmtbump[count], "%s\t");
	} //endif

// getting the final alignment of the format
for(count = 0; count < notitles; count++)
	{
	FormatAlignment(titles[count], maxlens[count], fmtbump[count]);
	} //endfor

// looping through all of the headers and outputting them
for(count = 0; count < notitles; count++)
	{
	printf(fmtbump[count], titles[count]);
	} //endfor
cout << '\n';

// outputting all of the event details
for(count = 0; count < size; count++)
	{
	for(index = 0; index < notitles; index++)
		{
		printf(fmtbump[index], outdata[count + size * index]);
		} //endfor
	cout << '\n';
	} //endfor
}

int EventsLongestLength(char title[], int eventids[], int size, char outvalues[][256])
{
int loc;
int maxlen;
int count;
char countc[10];
char lookupindex[][32] = { "ID", "Date", "Time", "Duration", "Location", "Description", "Title", "Cost", "Contact Name", "Contact Email", "Contact Phone Number", "Rank" };
int lookupsize;

lookupsize = sizeof(lookupindex) / sizeof(lookupindex[0]);

loc = FindInArray32(lookupindex, title, lookupsize);

// uses this switch to determine which array should be used for the lonest search
switch (loc)
	{
	case 0:
		{
		maxlen = FindLongestInIndecies(eventno, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], eventno[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 1:
		{
		maxlen = FindLongestInIndecies(evdate, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evdate[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 2:
		{
		maxlen = FindLongestInIndecies(evtime, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evtime[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 3:
		{
		maxlen = FindLongestInIndecies(evdur, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evdur[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 4:
		{
		maxlen = FindLongestInIndecies(evlocation, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evlocation[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 5:
		{
		maxlen = FindLongestInIndecies(evdescription, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evdescription[eventids[count]]);
			} //endfor
		} //endcase
	case 6:
		{
		maxlen = FindLongestInIndecies(evtitle, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evtitle[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 7:
		{
		maxlen = FindLongestInIndecies(evcost, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evcost[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 8:
		{
		maxlen = FindLongestInIndecies(evcont, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evcont[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 9:
		{
		maxlen = FindLongestInIndecies(evcontemail, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evcontemail[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 10:
		{
		maxlen = FindLongestInIndecies(evcontnum, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evcontnum[eventids[count]]);
			} //endfor
		break;
		} //endcase	
	case 11:
		{
		maxlen = strlen(title);
		for(count = 0; count < size; count++)
			{
			// copies the index into the output value
			itoa((count+1), countc, 10);
			strcpy(outvalues[count], countc);
			} //endfor
		break;
		} //endcase
	default:
		{
		maxlen = strlen(title);
		break;
		} //enddefaultcase
	} //endswitch

return maxlen;
}

int GuestEventLongestLength(char title[], int eventids[], int gunos[], int size, char outvalues[][256])
{
int loc;
int maxlen;
int count;
char countc[10];

char lookupindex[][32] = { "ID", "Date", "Time", "Duration", "Title", "Contact Name", "Contact Email", "Contact Phone Number", "Guest Name", "Rank" };
int lookupsize;

lookupsize = sizeof(lookupindex) / sizeof(lookupindex[0]);

// finds the title in the lookup index
loc = FindInArray32(lookupindex, title, lookupsize);

// uses this switch to determine which array should be used for the lonest search
switch (loc)
	{
	case 0:
		{
		maxlen = FindLongestInIndecies(eventno, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], eventno[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 1:
		{
		maxlen = FindLongestInIndecies(evdate, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evdate[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 2:
		{
		maxlen = FindLongestInIndecies(evtime, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evtime[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 3:
		{
		maxlen = FindLongestInIndecies(evdur, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evdur[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 4:
		{
		maxlen = FindLongestInIndecies(evtitle, eventids, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], evtitle[eventids[count]]);
			} //endfor
		break;
		} //endcase
	case 5:
		{
		maxlen = FindLongestInIndecies(gucontactnam, gunos, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], gucontactnam[gunos[count]]);
			} //endfor
		break;
		} //endcase
	case 6:
		{
		maxlen = FindLongestInIndecies(guemailaddr, gunos, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], guemailaddr[gunos[count]]);
			} //endfor
		break;
		} //endcase
	case 7:
		{
		maxlen = FindLongestInIndecies(guconttelenum, gunos, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], guconttelenum[gunos[count]]);
			} //endfor
		break;
		} //endcase
	case 8:
		{
		maxlen = FindLongestInIndecies(gunam, gunos, size);
		for(count = 0; count < size; count++)
			{
			strcpy(outvalues[count], gunam[gunos[count]]);
			} //endfor
		break;
		} //endcase
	case 9:
		{
		maxlen = strlen(title);
		for(count = 0; count < size; count++)
			{
			// copies the index into the output value
			itoa((count+1), countc, 10);
			strcpy(outvalues[count], countc);
			} //endfor
		break;
		} //endcase
	default:
		{
		maxlen = strlen(title);
		break;
		} //enddefaultcase
	} //endswitch

return maxlen;
}

char GetBaseType(char evnoc[10])
{
int loc;
char type;

// finds location of event in event file
loc = FindInArray10(eventno, evnoc, nei);

if(strstr(evtitle[loc], "Replay") != NULL)
	{
	type = 'R';
	} //endif replay is in the title
else if(strcmpi(evlocation[loc], "Station") == 0)
	{
	// if it is station then it is likely to be a show
	type = 'S';
	} //endelseif checking if it is at the station
else if(strstr(evtitle[loc], "Appearance") != NULL)
	{
	type = 'G';
	} //endelseif the word appearance has been mentioned in the title
else if(strcmpi(evlocation[loc], "Holiday") == 0)
	{
	type = 'H';
	} //endelseif the location is holiday
else
	{
	// if there isn't a default location then it will most likely be an external
	type = 'E';
	} //endelse if it is none of the others then it will be external

return type;
}

void AddLinksEntry(char inevno[10], char indjno[10])
{
strcpy(evlinkevno[nli], inevno);
strcpy(evlinkdjno[nli], indjno);

nli = nli + 1;
itoa(nli, nlc, 10);
ReWriteEventLinksFile();
}

void RemoveDJLinksEntries(char indjno[10])
{
int count = 0;

for(count = 0; count < nli; count++)
        {
	RemoveLinksEntry(evlinkevno[count], indjno);
	} //endfor
}

void RemoveEventLinksEntries(char inevno[10])
{
char tmpdjno[10];
int count = 0;

for(count = 0; count < 50; count++)
	{
	// converts the count into a string
	itoa(count, tmpdjno, 10);

	// removes that link
	RemoveLinksEntry(inevno, tmpdjno);
	} //endfor
}

void RemoveLinksEntry(char inevno[10], char indjno[10])
{
int find = 0;
int del = 0;
int compare = 0;

// find the event number in the array
find = FindInArray10(evlinkevno, inevno, nli);

// if the event isn't in the file return early
if(find == -1)
	{
	return;
	} //endif

// check if the DJ number at find is correct
compare = strcmpi(evlinkdjno[find], indjno);

// if not correct repeat
while(compare != 0 && find != -1)
	{
	// find the event number in the array
	find = FindInArray10(evlinkevno, inevno, nli, find + 1);

	// check if the DJ number at find is correct
	compare = strcmpi(evlinkdjno[find], indjno);
	} //endwhile

for (del = find; del < nli; del++)
	{
	strcpy(evlinkevno[del], evlinkevno[del+1]);
	strcpy(evlinkdjno[del], evlinkdjno[del+1]);
	} //endfor


nli = nli - 1;
itoa(nli, nlc, 10);
ReWriteEventLinksFile();
}

int GetAttendingDJs(char inevno[10], int outdjids[50], int output)
{
int count;
int compare;
int top = 0;
int tmptop;
char attdjs[50][32];

// iterates through the array of djs and finds the event number 
for(count = 0; count < nli; count++)
	{
	// checks if there is an event with that event number in the links file
	compare = strcmpi(evlinkevno[count], inevno);

	if(compare == 0)
		{
		djno = atoi(evlinkdjno[count]);

		// finds the DJ
		LocateDJ(djno);

		// setting the output array of IDs to have the dj number in it
		outdjids[top] = djno;

		// copies the name into the attending DJs
		strcpy(attdjs[top], a_dj.djnam);

		// increments the top of the stack
		top = top + 1;
		} //endif
	} //endfor

tmptop = top;

if(output == 1 && tmptop > 0)
	{
	cout << "\nDJs Attending: ";

	while(tmptop > 0)
		{
		// decrement the top pointer
		tmptop = tmptop - 1;

		// output the DJ
		cout << attdjs[tmptop];

		if(tmptop > 0)
			{
			// add a comma
			cout << ", ";
			} //endif not the last item
		} //endwhile
	} //endif


return top;
}

int GetAttendingDJ(char inevno[10], int output)
{
int loc = 0;
int idjno = -1;
char djnam[32];

loc = FindInArray10(evlinkevno, inevno, nli);

if(loc != -1)
	{
	// gets the DJ no as an int
	idjno = atoi(evlinkdjno[loc]);

	// finds the DJ
	LocateDJ(idjno);

	// copies the name into the attending DJs
	strcpy(djnam, a_dj.djnam);
	} //endif

if(output == 1)
	{
	if(idjno == -1)
		{
		strcpy(djnam, "None");
		} //endif no DJs found

	cout << "\nDJs Attending: " << djnam;
	} //endif should output the DJ

return idjno;
}

void OutputEvent(int date, int time, int djid)
{
int evno;
char evnoc[10];

evno = GetScheduleEventNumber(date, time, djid);

itoa(evno, evnoc, 10);

OutputEvent(evnoc);
}

void OutputEvent(char evno[10])
{
int loc;
int lnkdjno;
int linkloc;
int guloc;
int duri;
int durday;
int guno;
char gunoc[10];
char edate[11];
char etime[6];
int attdjs[50];
char slottype;

loc = FindInArray10(eventno, evno, nei);

// finds one of the DJs attending the event
linkloc = FindInArray10(evlinkevno, evno, nli);

// gets the DJ number as an integer
lnkdjno = atoi(evlinkdjno[linkloc]);

// gets the slot type for the switch
slottype = GetEventType(evno);

// assume the type is external event if it isn't on the schedule
if(slottype == '*' && strcmpi(evlocation[loc], "") != 0)
	{
	slottype = 'E';
	} //endif there is a null slot and a specific location

switch (slottype)
	{
	case 'S':
		{
		cout << "\nShow Title: " << evtitle[loc];
		cout << "\nDate: " << evdate[loc];
		cout << "\nStart Time: " << evtime[loc];

		// calculates the end time of the show
		CalculateEndTime(evtime[loc], evdur[loc], etime);
		
		cout << "\nEnd Time: " << etime;

		// outputs the attending DJs
		GetAttendingDJs(eventno[loc], attdjs, 1);

		break;
		} //endcase
	case 'G':
		{
		guno = GetScheduleGuestNumber(evno);

		// convert the guest number to str
		itoa(guno, gunoc, 10);

		guloc = FindInArray10(guestno, gunoc, ngi);

		cout << "\nGuest Name: " << gunam[guloc];
		cout << "\nDate: " << evdate[loc];
		cout << "\nStart Time: " << evtime[loc];
		
		// calculates the end time of the event
		CalculateEndTime(evtime[loc], evdur[loc], etime);
		
		cout << "\nEnd Time: " << etime;

		// outputs the attending DJs
		GetAttendingDJs(eventno[loc], attdjs, 1);

		break;
		} //endcase
	case 'E':
		{
		cout << "\nEvent Title: " << evtitle[loc];
		cout << "\nDescription: " << evdescription[loc];
		cout << "\nDate: " << evdate[loc];
		cout << "\nStart Time: " << evtime[loc];

		// calculates the end time of the event
		CalculateEndTime(evtime[loc], evdur[loc], etime);
		
		cout << "\nEnd Time: " << etime;
		cout << "\nLocation: " << evlocation[loc];

		cout << "\nCost: ";
		
		// add the pound if the event isn't free
		if(strcmpi(evcost[loc], "free") != 0)
			{
			cout << pound;
			} //endif the event isn't free

		cout << evcost[loc];
		
		// these are only outputted if the fields are filled as it would be useless otherwise
		if(strcmpi(evcont[loc], "na") != 0)
			{
			cout << "\nContact Name: " << evcont[loc];
			} //endif the contact name isn't empty
		if(strcmpi(evcontemail[loc], "na") != 0)
			{
			cout << "\nContact Email Address: " << evcontemail[loc];
		    } //endif the contact email isn't empty
		if(strcmpi(evcontnum[loc], "na") != 0)
			{
			cout << "\nContact Phone Number: " << evcontnum[loc];
		    } //endif the contact number isn't empty
			
		// outputs the attending DJs
		GetAttendingDJs(eventno[loc], attdjs, 1);
		break;
		} //endcase
	case 'R':
		{
		
		break;
		} //endcase
	case 'H':
		{
		strcpy(edate, evdate[loc]);

		duri = atoi(evdur[loc]);
		durday = floor(duri/24);

		AddDays(edate, durday);

		cout << "\nStart Date: " << evdate[loc];
		cout << "\nEnd Date: " << edate;
		cout << "\nApproved: ";

		if(IsHolidayApproved(evno) == 1)
			{
			cout << "Y";
			} //endif
		else
			{
			cout << "N";
			} //endelse

		cout << '\n';
		break;
		} //encase
	case '*':
		{
		cout << "\nUndefined Type";
		break;
		} //endcase
	// allows for validation
	default:
		{
		break;
		} //endcase
	} //endswitch

}

void SwapEvents(int index)
{
swap(eventno[index], eventno[index + 1]);
swap(evdate[index], evdate[index + 1]);
swap(evtime[index], evtime[index + 1]);
swap(evdur[index], evdur[index + 1]);
swap(evlocation[index], evlocation[index + 1]);
swap(evdescription[index], evdescription[index + 1]);
swap(evtitle[index], evtitle[index + 1]);
swap(evcost[index], evcost[index + 1]);
swap(evcont[index], evcont[index + 1]);
swap(evcontemail[index], evcontemail[index + 1]);
swap(evcontnum[index], evcontnum[index + 1]);
}

void RemoveEvent(int location)
{
int find = location;
int del;

for (del = find; del < nei; del++)
	{
	strcpy(eventno[del], eventno[del+1]);
	strcpy(evdate[del], evdate[del+1]);
	strcpy(evtime[del], evtime[del+1]);
	strcpy(evdur[del], evdur[del+1]);
	strcpy(evlocation[del], evlocation[del+1]);
	strcpy(evdescription[del], evdescription[del+1]);
	strcpy(evtitle[del], evtitle[del+1]);
	strcpy(evcost[del], evcost[del+1]);
	strcpy(evcont[del], evcont[del+1]);
	strcpy(evcontemail[del], evcontemail[del+1]);
	strcpy(evcontnum[del], evcontnum[del+1]);
	} //endfor

nei = nei - 1;
itoa(nei, nec, 10);
}

/* ------------------------------
 *            Events
 * ------------------------------ 
 */

int ReadBackEventFile()
{
int count;
ifstream fin(FileName2, ios::binary);
fin.read((char*)&nec, sizeof(nec));
sscanf(&nec[0], "%d", &nei);

for (count = 0; count < nei; count++)
	{
	fin.getline(eventno[count], sizeof(eventno[count]));
	fin.getline(evdate[count], sizeof(evdate[count]));
	fin.getline(evtime[count], sizeof(evtime[count]));
	fin.getline(evdur[count], sizeof(evdur[count]));
	fin.getline(evlocation[count], sizeof(evlocation[count]));
	fin.getline(evdescription[count], sizeof(evdescription[count]));
	fin.getline(evtitle[count], sizeof(evtitle[count]));
	fin.getline(evcost[count], sizeof(evcost[count]));
	fin.getline(evcont[count], sizeof(evcont[count]));
	fin.getline(evcontemail[count], sizeof(evcontemail[count]));
	fin.getline(evcontnum[count], sizeof(evcontnum[count]));
	} //endfor

fin.close();

return 0;
}

int ReWriteEventFile()
{
int count;
ofstream fout(FileName2, ios::binary);
fout.write((char*)&nec, sizeof(nec));

for(count = 0; count < nei; count++)
	{
	fout.write((char*)&eventno[count], strlen(eventno[count]));
	fout.write("\n", 1);
	fout.write((char*)&evdate[count], strlen(evdate[count]));
	fout.write("\n", 1);
	fout.write((char*)&evtime[count], strlen(evtime[count]));
	fout.write("\n", 1);
	fout.write((char*)&evdur[count], strlen(evdur[count]));
	fout.write("\n", 1);
	fout.write((char*)&evlocation[count], strlen(evlocation[count]));
	fout.write("\n", 1);
	fout.write((char*)&evdescription[count], strlen(evdescription[count]));
	fout.write("\n", 1);
	fout.write((char*)&evtitle[count], strlen(evtitle[count]));
	fout.write("\n", 1);
	fout.write((char*)&evcost[count], strlen(evcost[count]));
	fout.write("\n", 1);
	fout.write((char*)&evcont[count], strlen(evcont[count]));
	fout.write("\n", 1);
	fout.write((char*)&evcontemail[count], strlen(evcontemail[count]));
	fout.write("\n", 1);
	fout.write((char*)&evcontnum[count], strlen(evcontnum[count]));
	fout.write("\n", 1);
	} //endfor

fout.close();

return 0;
}

int GenerateEventNumber(char inevno[10])
{
int result = nei;

result = FindNextReferenceNumber(result, eventno, nei);
itoa(result, inevno, 10);

return result;
}

void BubbleEventSortDates(int size)
{
int index;
int numdate1;
int numdate2;

if(size == 1)
        {
        return;
        } //endif

for(index = 0; index < size-1; index++)
        {
        numdate1 = CalculateNumericalDate(evdate[index]);
        numdate2 = CalculateNumericalDate(evdate[index + 1]);

        if(numdate1 > numdate2)
                {
                SwapEvents(index);
                } //endif
        } //endfor

// recursively calling the sort
BubbleEventSortDates(size - 1);
}

/* ------------------------------
 *          Events Menu
 * ------------------------------ 
 */

int Events()
{
int eventstatus = 0;
while (eventstatus != 6)
	{
	eventstatus = EventsMenu();
	clrscr();
	} //endwhile

return 0;
}


int EventsMenu()
{
int eventschoice;

clrscr();

cout << "\n\tEvents Menu";
cout << "\n\t===========\n";
cout << "\n\t1. View Events";
cout << "\n\t2. Add Event";
cout << "\n\t3. Change Events";
cout << "\n\t4. Remove Events";
cout << "\n\t5. Allocate DJs";
cout << "\n\t6. Return";

cout << "\n\nEnter Choice: ";
cin >> eventschoice;

// ignores the new line
cin.ignore(1, '\n');

switch(eventschoice)
	{
	case 1: 
		{
		ViewEvents();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		AddEvent();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeEvents();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		RemoveEvents();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		AllocateDJs();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return eventschoice;
}


/* ------------------------------
 *          View Events
 * ------------------------------ 
 */


int ViewEvents()
{
int viewstatus = 0;
while (viewstatus != 4)
	{
	viewstatus = ViewEventsMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewEventsMenu()
{
int vieweventschoice;

clrscr();

cout << "\n\tView Events Menu";
cout << "\n\t================\n";
cout << "\n\t1. By Event Reference";
cout << "\n\t2. By Date";
cout << "\n\t3. By Title";
cout << "\n\t4. Return";

cout << "\nEnter Choice: ";
cin >> vieweventschoice;

// ignores the new line
cin.get();

switch(vieweventschoice)
	{
	case 1: 
		{
		ViewEventsByEventReference();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewEventsByDate();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewEventsByTitle();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return vieweventschoice;
}

int ViewEventsByEventReference()
{
char inevno[10];
int find;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Event Reference";
cout << "\n==============================\n";

cout << "\nEnter Event Reference: ";
cin.getline(inevno, 10);

// this needs to stay here regardless as it'll be used in validation later

// finds the event in the array of events
find = FindInArray10(eventno, inevno, nei);

if(find != -1)
	{
	OutputEvent(inevno);
	} //endif found an event
else
	{
	cout << "\nError: Event not found";
	} //endelse


cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewEventsByDate()
{
int count;
int evid[500];
int top = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Date";
cout << "\n===================\n";

BubbleEventSortDates(nei);

// gets the closest events
for(count = 0; count < nei; count++)
	{
	// if there is no title then skip the event
	if(evtitle[count][0] == '\0')
		{
		continue;
		} //endif

	evid[top++] = atoi(eventno[count]);
	} //endfor

OutputEventsTabular(evid, "TiDaTmLo", top);

ReadBackEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewEventsByTitle()
{
char title[64];
int find;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Title";
cout << "\n====================\n";

cout << "\nEnter Event Title: ";
cin.getline(title, 64);

find = FindInArray64(evtitle, title, nei);

if(find != -1)
	{
	OutputEvent(eventno[find]);
	} //endif finds an event

cout << "\n\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Add Events
 * ------------------------------ 
 */

int AddEvent()
{
int addstatus = 0;
while (addstatus != 5)
	{
	addstatus = AddEventMenu();
	clrscr();
	} //endwhile

return 0;
}

int AddEventMenu()
{
int addeventchoice;

clrscr();

cout << "\n\tAdd Event Menu";
cout << "\n\t==============\n";
cout << "\n\t1. DJ Session";
cout << "\n\t2. Guest Appearance";
cout << "\n\t3. External Event";
cout << "\n\t4. Replay";
cout << "\n\t5. Return";

cout << "\nEnter Choice: ";
cin >> addeventchoice;

// ignores the new line
cin.get();

switch(addeventchoice)
	{
	case 1: 
		{
		DJSession();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		GuestAppearance();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ExternalEvent();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		Replay();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return addeventchoice;
}

int DJSession()
{
char indjno[10];
char indate[11];
char instime[6];
char inetime[6];
char intitle[64];
char evno[10];
int ievno;
int idjno;

// in hours
int duration;

char durc[10];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nDJ Session";
cout << "\n==========\n";

ievno = GenerateEventNumber(evno);

cout << "\nEnter DJ Number: ";
cin.getline(indjno, 10);

cout << "\nEnter Title: ";
cin.getline(intitle, 64);

cout << "\nEnter Date: ";
cin.getline(indate, 11);

cout << "\nEnter Start Time: ";
cin.getline(instime, 6);

cout << "\nEnter End Time: ";
cin.getline(inetime, 6);

// gets the DJ number as an integer
idjno = atoi(indjno);

duration = CalculateDuration(instime, inetime);

itoa(duration, durc, 10);

// copies locals into their respective globals 
strcpy(eventno[nei], evno);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], instime);
strcpy(evdur[nei], durc);
strcpy(evlocation[nei], "Station");
strcpy(evtitle[nei], intitle);


nei = nei + 1;
itoa(nei, nec, 10);

AddEventToSchedule(evno, 'S', idjno);

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "Success - DJ session has been added to the schedule";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int GuestAppearance()
{
char indjno[10];
char inguno[64];
char indate[11];
char instime[6];
char inetime[6];
char evno[10];
char evtit[64];
int ievno;
int idjno;
int guloc;

int day;
int time;

char vgslotsch;

char dttoday[11];
int tday;

int hasguest;

// in hours
int duration;

char durc[10];

char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

ReadBackGuestFile();
ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nGuest Appearance";
cout << "\n================\n";

ievno = GenerateEventNumber(evno);

// if not or if the time isn't available then asks if the available slots should be shown
cout << "\n\nWould you like to see all of the available guest slots (y/n): ";
vgslotsch = cin.get();

// this stops the input skipping
cin.get();

// setting today to that date
GetToday(dttoday);

// getting the day of today
tday = FindDayOnDate(dttoday);

// if today is not 1 then the day is not a Monday
if(tday != 1)
	{
	SubtractDays(dttoday, tday - 1);
	} //endif

cout << "\nClosest Monday: " << dttoday << "\n\n";

if(vgslotsch == 'y')
	{
	cout << "    ";
	for(time = 0; time < 24; time++)
		{
		if(time < 10)
				{
				cout << "0";
				} //endif
		
		cout << time << " ";
		}

	for(day = 0; day < 7; day++)
		{
		cout << '\n' << daysofweek[day];
		for(time = 0; time < 24; time++)
			{
			// finds if there is a guest at that day and time
			hasguest = FindScheduleGuestSlot(day, time);

			if(hasguest == 0)
				{	
				cout << "  " << sch[0][day][time];
				} //endif
			else
				{
				cout << "  " << "*";
				} //endelse
			}
		}
	} //endif view guest slots

cout << "\nEnter Guest Number: ";
cin.getline(inguno, 10);

guloc = FindInArray10(guestno, inguno, ngi);

cout << "\nEnter Assisting DJ's Number: ";
cin.getline(indjno, 64);

cout << "\nEnter Date: ";
cin.getline(indate, 11);

// some validation here to make sure that one of the slots have been selected

cout << "\nEnter Start Time: ";
cin.getline(instime, 6);

cout << "\nEnter End Time: ";
cin.getline(inetime, 6);

// gets the DJ number as an integer
idjno = atoi(indjno);

duration = CalculateDuration(instime, inetime);

// converts the duration into a string
itoa(duration, durc, 10);

// creating the title of the appearance
strcpy(evtit, gunam[guloc]);
strcat(evtit, " Appearance");

// copies locals into their respective globals 
strcpy(eventno[nei], evno);
strcpy(evtitle[nei], evtit);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], instime);
strcpy(evdur[nei], durc);

nei = nei + 1;
itoa(nei, nec, 10);

AddEventToSchedule(evno, 'G', idjno, inguno);

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\n\nSuccess - Slot on " << indate << " at " << instime << " has been booked for " << gunam[guloc] << "\n";

cout << "\nPress any key to return";
getch();

return 0;
}

int ExternalEvent()
{
char intitle[64];
char indesc[128];
char indate[11];
char instime[6];
char inetime[6];
char inloc[32];
char inprice[7];
char incontnam[32];
char inemail[32];
char intelno[12];
char indjno[10];
char evno[10];
int idjno;
int duri;
char durc[10];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nExternal Event";
cout << "\n==============\n";

// generates the event number for the event
GenerateEventNumber(evno);

cout << "\nEnter Event Title: ";
cin.getline(intitle, 64);

cout << "\nEnter Event Description: ";
cin.getline(indesc, 128);

cout << "\nEnter Event Date: ";
cin.getline(indate, 11);

cout << "\nEnter Start Time: ";
cin.getline(instime, 6);

// range check that this is not over a day

cout << "\nEnter End Time: ";
cin.getline(inetime, 6);

cout << "\nEnter Event Location: ";
cin.getline(inloc, 32);

cout << "\nEnter Event Cost (free if free): ";
cin.getline(inprice, 7);

// acounting for the pound symbol
if(inprice[0] == pound)
	{
	// copies the price into the price but ignoring the 1st char which would be the £
	strcpy(inprice, &inprice[1]);
	} //endif pound

cout << "\nEnter Event Contact name (na if none): ";
cin.getline(incontnam, 32);

cout << "\nEnter Event Contact Email Address (na if none): ";
cin.getline(inemail, 32);

cout << "\nEnter Event Contact Phone Number (na if none): ";
cin.getline(intelno, 12);

cout << "\nEnter Attending DJ Number: ";
cin.getline(indjno, 10);

cout << "Success - Event has been added to the schedule";

// calculates the duration of the event in hours
duri = CalculateDuration(instime, inetime);

// converts the duration to a str
itoa(duri, durc, 10);

strcpy(eventno[nei], evno);
strcpy(evtitle[nei], intitle);
strcpy(evdescription[nei], indesc);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], instime);
strcpy(evdur[nei], durc);
strcpy(evlocation[nei], inloc);
strcpy(evcost[nei], inprice);
strcpy(evcont[nei], incontnam);
strcpy(evcontemail[nei], inemail);
strcpy(evcontnum[nei], intelno);

nei = nei + 1;
itoa(nei, nec, 10);

AddEventToSchedule(evno, 'E', idjno);

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int Replay()
{
char inevno[10];
char token[32];
char indate[11];
char intime[6];
char evnoc[10];
char etitle[64];
int loc;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nReplay";
cout << "\n======\n";

cout << "\nEnter Replay Show Event Number: ";
cin.getline(inevno, 10);

// finding the event number
loc = FindInArray10(eventno, inevno, nei);

// validation the event exists here

cout << "\nEnter Date: ";
cin.getline(indate, 11);

cout << "\nEnter Start Time: ";
cin.getline(intime, 6);

GenerateEventNumber(evnoc);

// validation of the details here

// creating the token
GenerateScheduleToken(token, "R", evnoc, "");

// creating the title
strcpy(etitle, "Replay ");
strcat(etitle, evtitle[loc]);

strcpy(eventno[nei], evnoc);
strcpy(evtitle[nei], evtitle[loc]);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], intime);
strcpy(evdur[nei], evdur[loc]);
strcpy(evlocation[nei], evlocation[loc]);

nei = nei + 1;
itoa(nei, nec, 10);

// setting the schedule slot for the very last DJ as it won't be used
// therefore the event has somewhere to be stored if being viewed
AddEventToSchedule(evnoc, 'R', 52);

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Change Events
 * ------------------------------ 
 */


int ChangeEvents()
{
int changestatus = 0;
while (changestatus != 9)
	{
	changestatus = ChangeEventsMenu();
	clrscr();
	} //endwhile

return 0;
}


int ChangeEventsMenu()
{
int changeeventchoice;

clrscr();

cout << "\n\tChange Event Menu";
cout << "\n\t=================\n";
cout << "\n\t1. Title";
cout << "\n\t2. Date";
cout << "\n\t3. Time";
cout << "\n\t4. Location";
cout << "\n\t5. Description";
cout << "\n\t6. Cost";
cout << "\n\t7. Contact";
cout << "\n\t8. Playlist";
cout << "\n\t9. Return";

cout << "\nEnter Choice: ";
cin >> changeeventchoice;

// ignores the new line
cin.get();

switch(changeeventchoice)
	{
	case 1: 
		{
		ChangeEventsTitle();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeEventsDate();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeEventsTime();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		ChangeEventsLocation();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		ChangeEventsDescription();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		ChangeEventsCost();
		clrscr();
		break;
		} // endcase
	case 7: 
		{
		ChangeEventsContact();
		clrscr();
		break;
		} // endcase
	case 8: 
		{
		ChangeEventsPlaylist();
		clrscr();
		break;
		} // endcase
	case 9: 
		{
		clrscr();
		break;
		} // endcase
	}

return changeeventchoice;
}


int ChangeEventsTitle()
{
char evnoc[10];
char ntitle[64];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Events Title";
cout << "\n===================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nCurrent Title: " << evtitle[loc];

cout << "\nNew Title: ";
cin.getline(ntitle, 32);

// validation here

strcpy(evtitle[loc], ntitle);

// insert check here
cout << "\n\nSuccess - Title has been Changed\n";

ReWriteEventFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeEventsDate()
{
char evnoc[10];
char ndate[11];
char slot[32];
int attdjs[52];
int count;
char gunoc[10];
char type;
int nodjs;
int loc;
     
ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nChange Events Date";
cout << "\n==================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];

cout << "\nDate: " << evdate[loc];

cout << "\nNew Date: ";
cin.getline(ndate, 11);

nodjs = GetAttendingDJs(evnoc, attdjs);

// gets the first slot for each attending DJ
GetScheduleSlot(slot, evnoc, attdjs[0]);

type = slot[0];

RemoveEventFromSchedule(evnoc);

// change the date here
strcpy(evdate[loc], ndate);
                         
// add back all of the DJs
if(type == 'G')
        {
        GetScheduleGuestNumber(gunoc);

        AddGuestEventToSchedule(evnoc, gunoc, attdjs[0]);
        } //endif is a guest event

AddEventToSchedule(evnoc, type, attdjs[0]);

for(count = 1; count < nodjs; count++)
        {
        AddDJToEvent(evnoc, attdjs[count]);
        } //endfor


// insert check here
cout << "\nSuccess - Date has been Changed\n";

cout << "\nPress any key to return";
getch();

ReWriteEventFile();
ReWriteScheduleFile();

return 0;
}

int ChangeEventsTime()
{
char evnoc[10];
char ntime[6];
char etime[6];
char netime[6];
int attdjs[50];
int count;
int nodjs;
int duri;
int loc;

ReadBackEventFile();
ReadBackScheduleFile();

clrscr();
cout << "\nChange Events Time";
cout << "\n==================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];

cout << "\nStart Time: " << evtime[loc];

strcpy(etime, evtime[loc]);

// convert the duration to an integer and then add it to the start time to get the end time
AddTimes(etime, atoi(evdur[loc]));

cout << "\nEnd Time: " << etime;

// here there needs validation that there is no overlap with the DJs

cout << "\nNew Start Time: ";
cin.getline(ntime, 6);

// validate one is after the other

cout << "\nNew End Time: ";
cin.getline(netime, 6);

duri = CalculateDuration(ntime, netime);

/*
 * need to get a list of all attending DJs
 * clear those slots in the DJ's schedule
 * add the new ones in
 * this only works if the DJ exists
*/

nodjs = GetAttendingDJs(evnoc, attdjs);

// removing the event from all attending DJs
for (count = 0; count < nodjs; count++)
	{
	RemoveDJFromEvent(evnoc, attdjs[count]);
	} //endfor

// writing the new event details to the variables

// write the duration to the duration variable
itoa(duri, evdur[loc], 10);

strcpy(evtime[loc], ntime);

// adding the event back after the editations
for (count = 0; count < nodjs; count++)
	{
	AddDJToEvent(evnoc, attdjs[count]);
	} //endfor

// insert check here
cout << "\nSuccess - Time has been Changed";

ReWriteEventFile();
ReWriteScheduleFile();

// then calc to find duration

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeEventsLocation()
{
char evnoc[10];
char nlocation[32];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Events Location";
cout << "\n======================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];
cout << "\nLocation: " << evlocation[loc];

cout << "\nNew Location: ";
cin.getline(nlocation, 32);

// validation here

strcpy(evlocation[loc], nlocation);

// another check would be needed here
cout << "\n\nSuccess - Location has been changed";

ReWriteEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeEventsDescription()
{
char evnoc[10];
char ndesc[128];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Events Description";
cout << "\n=========================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];
cout << "\nDescription: " << evdescription[loc];

cout << "\nNew Description: ";
cin.getline(ndesc, 128);

// validation here

strcpy(evdescription[loc], ndesc);

// check for success
cout << "\n\nSuccess - Description has been changed";

ReWriteEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeEventsCost()
{
char evnoc[10];
char nprice[7];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Events Cost";
cout << "\n==================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];

cout << "\nCost: ";

if(isdigit(evcost[loc][0]) == 0)
	{
	cout << pound;
	} //endif there is a digit

cout << evcost[loc];

cout << "\nNew Cost: ";
cin.getline(nprice, 7);

if(nprice[0] != pound)
	{
	strcpy(evcost[loc], &nprice[1]);
	} //endif there is a pound sign
else
	{
	strcpy(evcost[loc], nprice);
	} //endelse there isn't a pound sign

// check for success
cout << "\n\nSuccess - Cost has been changed";

ReWriteEventFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeEventsContact()
{
int changestatus = 0;
while (changestatus != 4)
	{
	changestatus = ChangeEventsContactMenu();
	clrscr();
	} //endwhile

getch();
return 0;
}

int ChangeEventsContactMenu()
{
int changeeventscontactchoice;

clrscr();

cout << "\n\tChange Contact Menu";
cout << "\n\t===================\n";
cout << "\n\t1. Name";
cout << "\n\t2. Email Address";
cout << "\n\t3. Phone Number";
cout << "\n\t4. Return";

cout << "\n\nEnter Choice: ";
cin >> changeeventscontactchoice;

switch(changeeventscontactchoice)
	{
	case 1: 
		{
		ChangeEventsContactName();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeEventsContactEmailAddress();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeEventsContactPhoneNumber();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return changeeventscontactchoice;
}

int ChangeEventsContactName()
{
char inevno[10];
char inevcontnam[32];
int loc = 0;

ReadBackEventFile();

clrscr();
cout << "\nChange Contact Name";
cout << "\n===================\n";

// gets the event number
cout << "\nEnter Event Number: ";
cin.getline(inevno, 10);

// finds the event number in the file
loc = FindInArray10(eventno, inevno, nei);

cout << "\nTitle: " << evtitle[loc];

// effectively the same thing guest equivalent
cout << "\nCurrent Contact Name: " << evcont[loc];

// inputting the new contact name
cout << "\nNew Contact Name: ";
cin.getline(inevcontnam, 32);

// copying across the new contact name
strcpy(evcont[loc], inevcontnam);

// check here
cout << "\nSuccess - Contact Name has been changed\n";

ReWriteEventFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeEventsContactEmailAddress()
{
char evnoc[10];
char nemail[32];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Email Address";
cout << "\n====================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];
cout << "\nContact Email Address: " << evcontemail[loc];

cout << "\nNew Email Address: ";
cin.getline(nemail, 32);

// copying across the new contact name
strcpy(evcontemail[loc], nemail);

// insert check here
cout << "\nSuccess - Email Address has been changed";

ReWriteEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeEventsContactPhoneNumber()
{
char evnoc[10];
char ntelno[32];
int loc;

ReadBackEventFile();

clrscr();
cout << "\nChange Phone Number";
cout << "\n===================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc, 10);

loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc];
cout << "\nContact Phone Number: " << evcontnum[loc];

cout << "\nNew Phone Number: ";
cin.getline(ntelno, 32);

// copying across the new contact name
strcpy(evcontnum[loc], ntelno);

// another check would be needed here
cout << "\nSuccess - Phone Number has been changed";

ReWriteEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeEventsPlaylist()
{
char evnoc1[10];
char evnoc2[10];
int evloc;
int lnkloc1;
int lnkloc2;

// temp catno
char tcatno[10];

// setting up the queue for the first event
int catnos1[500];
int back1 = 0;

// setting up the queue for the second event
int catnos2[500];
int back2 = 0;

int count;

ReadBackEventFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nChange Event Playlist";
cout << "\n=====================\n";

cout << "\nEnter Event Number: ";
cin.getline(evnoc1, 10);

evloc = FindInArray10(eventno, evnoc1, nei);

cout << "\nTitle: " << evtitle[evloc];

cout << "\nEnter Event Number of Playlist to Swap to: ";
cin.getline(evnoc2, 10);

// we can reuse variables here as we aren't using them again
evloc = FindInArray10(eventno, evnoc2, nei);
cout << "\nTitle: " << evtitle[evloc];

// here we will need validation of the length of playlist
// the playlist exists
// the events exist

// getting the first songs for both (allows for future validaion hence why not do while)
lnkloc1 = FindInArray10(pllinkevno, evnoc1, npi);
lnkloc2 = FindInArray10(pllinkevno, evnoc2, npi);

while(lnkloc1 != -1)
	{
	// writing the catno to the back as int and incrementing back
	catnos1[back1++] = atoi(pllinkcatno[lnkloc1]);

	// finding next entry
	lnkloc1 = FindInArray10(pllinkevno, evnoc1, npi);
	} //endwhile

while(lnkloc2 != -1)
	{
	catnos2[back2++] = atoi(pllinkcatno[lnkloc2]);

	lnkloc2 = FindInArray10(pllinkevno, evnoc2, npi);
	} //endwhile

// to enable swapping literally just add another one of these sections but swapping all 1s for 2s

// clearing the event to change's playlist
RemovePlaylistEntriesByEvent(evnoc1);

// starting from the front of the queue
for(count = 0; count < back2; count++)
	{
	// converting the tmpid into a str
	itoa(catnos2[count], tcatno, 10);

	// adding the song at the top of the queue from pl2 to pl1
	AddPlaylistEntry(evnoc1, tcatno);
	} //endfor

cout << "\n\nSuccess - Playlist has been changed";

ReWritePlaylistFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Allocate DJs
 * ------------------------------ 
 */

int AllocateDJs()
{
char indjno[10];
char inevno[10];
int djnos[50];
int idjno;
char choice;

ReadBackEventFile();
ReadBackEventLinksFile();
ReadBackScheduleFile();

clrscr();
cout << "\nAllocate DJs";
cout << "\n============\n";

cout << "\nEnter Event Number: ";
cin.getline(inevno, 10);

GetAttendingDJs(inevno, djnos, 1);

cout << "\nWould you like to add or remove a DJ (A/R): ";
choice = cin.get();
cin.get();

cout << "\nEnter DJ Number: ";
cin.getline(indjno, 10);

// converts the DJ number to an integer
itoa(idjno, indjno, 10);

LocateDJ(idjno);

if(choice == 'A')
	{
	// To-Do: put some validation here to stop the same DJ being added

	// allocates the DJ to the event
	AddDJToEvent(inevno, idjno);

	cout << "\nSuccess - " << a_dj.djnam << " has been allocated\n";
	} //endif choice is add
else if(choice == 'R')
	{
	// To-Do: put some validation here to stop a DJ being removed that doesn't exist

	// deallocates the DJ from the event
	RemoveDJFromEvent(inevno, idjno);	

	cout << "\nSuccess - " << a_dj.djnam << " has been deallocated\n";
	} //endif the choice is to remove

ReWriteEventFile();
ReWriteEventLinksFile();
ReWriteScheduleFile();

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *          Remove Events
 * ------------------------------ 
 */

int RemoveEvents()
{
int find = 0;
char choice;
char tmptitle[64];
char evno[10];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nRemove Events";
cout << "\n=============\n";

cout << "\nEnter Event Reference: ";
cin.getline(evno, 10);

// gets the event number
find = FindInArray10(eventno, evno, nei);

// copying the found title into the temp variable
strcpy(tmptitle, evtitle[find]);

// confirmaiton required to reduce mistakes
cout << "\nAre you sure you want to Delete " << tmptitle << " (y/n): ";
choice = cin.get();
getch();

// quick bit of validation to make sure that nothing accidental is done during testing
if(find == -1)
	return 0;

// remove only if yes
if(choice == 'y')
	{
	RemoveEventFromSchedule(evno);

	// removes all entries with this event
	RemoveEventLinksEntries(evno);

	// removes the event
	RemoveEvent(find);
	} //endif
else if(choice == 'n')
	{
	// return if not needed to delete
	return 0;
	} //endif

// insert check here
cout << "\nSuccess - " << tmptitle << " has been deleted\n";

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\nPress any key to return";
getch();

return 0;
}

#pragma endregion


#pragma region Scheduling

int ReadBackScheduleFile()
{
int day;
int time;
int djindex;
ifstream fin(FileName7, ios::in);

for (djindex = 0; djindex < 52; djindex++)
	{
	for(day = 0; day < 367; day++)
		{               
		for(time = 0; time < 24; time++)
			{
			fin.getline((char*)&sch[djindex][day][time], 32);
			} //endfor
		} //endfor
	} //endfor

fin.close();
return 0;
}

int ReWriteScheduleFile()
{
int day;
int time;
int djindex;

ofstream fout(FileName7, ios::binary);
for (djindex = 0; djindex < 52; djindex++)
	{
	for(day = 0; day < 367; day++)
		{               
		for(time = 0; time < 24; time++)
			{
			fout.write((char*)&sch[djindex][day][time], strlen(sch[djindex][day][time]));
			fout.write("\n ", 1);
			} //endfor
		}//endfor
	}//endfor

fout.close();
return 0;
}

void OutputHolidays(int holids[], int size, int check)
{
char djnams[500][64];
char approv[500][3];
int tdjid = 0;
char tref[10];
int count;
int maxlen;
int hollen;
char outformat[32] = "%s";
char sdate[11];
char edate[11];

for(count = 0; count < size; count++)
	{
	itoa(holids[count], tref, 10);
	tdjid = GetAttendingDJ(tref);

	LocateDJ(tdjid);

	strcpy(djnams[count], a_dj.djnam);
	} //endfor loop through all attending DJs and add them to a list of DJ names

// gets the locations of the events in the files
GetRefLocations(eventno, holids, nei, size);

if(check == 1)
	{
	for(count = 0; count < size; count++)
		{
		if(IsHolidayApproved(eventno[holids[count]]) == 1)
			{
			strcpy(approv[count], "Y");
			} //endif approved set the approved output to yes
		else
			{
			strcpy(approv[count], "N");
			} //endelse
		} //endfor loop through holidays to check if they are approved
	} //endif should show approved

maxlen = FindLongest(djnams, size);

// formatting the alignment
FormatAlignment("DJ", maxlen, outformat);

strcat(outformat, "\t%-11s\t%-10s");

if(check == 1)
	{
	strcat(outformat, "\t%-9s");

	printf(outformat, "DJ", "Start Date", "End Date", "Approved");
	} //endif should show if checked
else
	{
	printf(outformat, "DJ", "Start Date", "End Date");
	} //endelse

cout << '\n';

for(count = 0; count < size; count++)
	{
	// copy the date of the event into the start date column
	strcpy(sdate, evdate[holids[count]]);

	// copying the start date into the end date for the addition to work
	strcpy(edate, sdate);

	// getting length of holiday in days
	hollen = atoi(evdur[holids[count]]) / 24;

	// finds the end date by adding the duration number of days
	AddDays(edate, hollen);
	
	if(check == 1)
		{
		printf(outformat, djnams[count], sdate, edate, approv[count]);
		} //endif check they output approved or not
	else
		{
		printf(outformat, djnams[count], sdate, edate);
		} //endelse
	cout << '\n';
	} //endfor
}

int GetScheduleYear()
{
return 2023;
}

void GetScheduleStartDate(char* outdate)
{
strcpy(outdate, "01/01/2023");
}

char GetEventType(char evnoc[10])
{
int atdjno;
char slot[32];

atdjno = GetAttendingDJ(evnoc);

GetScheduleSlot(slot, evnoc, atdjno);

return slot[0];
}

void SetScheduleSlot(char value[32], int date, int time, int djid)
{
strcpy(sch[djid][date][time], value);
}

void SetScheduleSlot(char value[32], char date[11], char time[6], int djid)
{
int idate;
int itime;

// getting the location of the slot from the date and time
idate = CalculateScheduleDateIndex(date);

itime = CalculateScheduleTimeIndex(time);

// actually setting the slot
strcpy(sch[djid][idate][itime], value);
}

void GetScheduleSlot(char output[32], int date, int time, int djid)
{
if(djid == -1)
	{
	// copy in the default slot plus X to show error
	strcpy(output, "*X");
	return;
	} //endif there is no DJ

strcpy(output, sch[djid][date][time]);
}

void GetScheduleSlot(char output[32], char evnoc[10], int djid)
{
int itime;
int idate;
int loc;

loc = FindInArray10(eventno, evnoc, nei);

idate = CalculateScheduleDateIndex(evdate[loc]);
itime = CalculateScheduleTimeIndex(evtime[loc]);

GetScheduleSlot(output, idate, itime, djid);
}

void GenerateScheduleToken(char output[32], char type[3], char inevno[10], char guno[10])
{
// adding the type to the out token
strcat(output, type);

if(guno[0] != ' ')
	{
	// adding both the guest number and a separator to the token
	strcat(output, guno);	
	strcat(output, "/");	
	} //endif the first character of the guest number isn't empty

// addint the event number to the token
strcat(output, inevno);
}

int CalculateScheduleDateIndex(char date[11])
{
int day;
int month;
float year;
int count;
float yrcalc;
int iyears;
int daycount;

// number of days in each month
int daysinmon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// splits the date up into it's components
sscanf(date, "%d/%d/%f", &day, &month, &year);

// checks if is a leap year and updates accordingly
yrcalc = year / 4;
iyears = floor(yrcalc);

if(yrcalc == iyears)
	{
	daysinmon[1] = 29;
	} //endif

// gets the current day in the month
daycount = day;

// calculates the days passed in previous months
for(count = 0; count < month - 2; count++)
	{
	daycount += daysinmon[count];
	} //endfor


// -1 to account for 0 index
return daycount - 1;
}

int CalculateScheduleTimeIndex(char time[6])
{
int hour;
int min;

// separates the hours and minutes
sscanf(time, "%d:%d", &hour, &min);

// we only need the hour because we're working in hours
return hour;
}

void CalculateDateFromSchedule(char outdate[11], int schedindex)
{
int start;
int year;
int curday;
int iyears;
float yrcalc;

// number of days in each month
int daysinmon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

year = GetScheduleYear();
yrcalc = year / 4;
iyears = floor(yrcalc);

curday = schedindex;

if(yrcalc == iyears)
	{
	daysinmon[1] = 29;
	} //endif

for(start = 0; (curday - daysinmon[start]) > 0 && start < 12; start++)
	{
	curday -= daysinmon[start];
	} //endwhile the current day is greater than 0

ConvertDateToStr(outdate, curday, start + 1, year);
}

char GetScheduleType(int date, int time, int djid)
{
char val[32];

// gets the schedule slot
GetScheduleSlot(val, date, time, djid);

// returns the first character which is the type identifier
return val[0];
}

int GetScheduleGuestNumber(int date, int time, int djid)
{
char val[32];
int outguno;

// gets the schedule slot
GetScheduleSlot(val, date, time, djid);

// separate the guest number and event number
sscanf(val, "G%d", &outguno);

return outguno;
}

int GetScheduleGuestNumber(char guappno[10])
{
int idjno;
int guno;
char slot[32];
int evno;

idjno = GetAttendingDJ(guappno);

GetScheduleSlot(slot, guappno, idjno);

// extracting the guest number
sscanf(slot, "G%d/%d", &guno, &evno);

return guno;
}

int GetScheduleEventNumber(int date, int time, int djid)
{
char val[32];
int outevno;

// gets the schedule slot
GetScheduleSlot(val, date, time, djid);

// separate the type and event number
sscanf(&val[1], "%d", &outevno);

return outevno;
}

int FindScheduleGuestSlot(int date, int time)
{
int count;
char temptype;

// starting from 1 because DJ 0 is a null DJ for storage purposes
for(count = 1; count < 52; count++)
	{
	// getting the type of the slot at that date and time
	temptype = GetScheduleType(date, time, count);

	if(temptype == 'G')
		{
		return count;
		} //endif if the type is a guest slot
	} //endfor looping through the DJ schedule's

return 0;
}

void ChangeEventSlot(char evnoc[10], char slot[32])
{
int duri;
int count;
int evloc;
int dati;
int timi;
int djit;
int dayit = 0;
int attdjs[50];
int nodjs;

evloc = FindInArray10(eventno, evnoc, nei);

nodjs = GetAttendingDJs(evnoc, attdjs);

// if doesn't find event
if(evloc == -1)
	return;

duri = atoi(evdur[evloc]);

dati = CalculateScheduleDateIndex(evdate[evloc]);
timi = CalculateScheduleTimeIndex(evtime[evloc]);

for(djit = 0; djit < nodjs; djit++)
	{
	for(count = 0; count < duri; count++)
		{
		if((timi + count) == 24)
			{
			// increase the day iterator
			dayit += 1;

			// reset the time to 0
			timi = 0;

			// decrease the duration by count
			duri -= count;

			// reset count
			count = 0;
			} //endif the time goes onto the next day
		
		SetScheduleSlot(slot, dati + dayit, timi + count, attdjs[djit]);
		} //endfor
	} //endfor loop through every attending DJ
}

void AddEventToSchedule(char inevno[10], char type, int indjno, char inguno[10])
{
char schentry[32] = "";
int loc;
int count;
int duri;
int itim;
int idat;
int curhour;
char types[3] = { type, '\0' };

if(type == 'H')
	{
	// mark the holiday as unapproved
	types[1] = 'U';
	types[2] = '\0';
	} //endif the type is a holiday

loc = FindInArray10(eventno, inevno, nei);

if(strcmpi(inguno, "") == 0)
	{
	// generates the schedule token
	GenerateScheduleToken(schentry, types, inevno);
	} //endif there is not a guest number
else
	{
	GenerateScheduleToken(schentry, types, inevno, inguno);	
	} //endelse

duri = atoi(evdur[loc]);

itim = CalculateScheduleTimeIndex(evtime[loc]);
idat = CalculateScheduleDateIndex(evdate[loc]);

for(count = 0; count < duri; count++)
	{
	curhour = itim + count;

	if(count > 0 && curhour % 24 == 0)
		{
		// increment the date
		idat += 1;
		} //endif curhour is on new day

	// sets the schedule slot
	SetScheduleSlot(schentry, idat, curhour % 24, indjno);
	} //endfor loop though duration of event

// adds the DJ to the event
AddDJToEvent(inevno, indjno);
}

void AddGuestEventToSchedule(char inevno[10], char inguno[10], int indjno)
{
char schentry[32] = "";
int duri;
int curhour;
int loc;
int count;
int itim;
int idat;

loc = FindInArray10(eventno, inevno, nei);

// generates the schedule token
GenerateScheduleToken(schentry, "G", inevno, inguno);

// getting the duration an an int
duri = atoi(evdur[loc]);

// getting the position of the event in the schedule
itim = CalculateScheduleTimeIndex(evtime[loc]);
idat = CalculateScheduleDateIndex(evdate[loc]);

// setting all of the slots which should contain that event
for(count = 0; count < duri; count++)
	{
	curhour = itim + count;

	if(curhour == 24)
		{
		// reset the time
		itim = 0;

		// increment the date
		idat += 1;

		// remove the number of hours from the duration
		duri -= count;

		// reset the count
		count = 0;
		} //endif curhour is 24

	// sets the schedule slot
	SetScheduleSlot(schentry, idat, curhour, indjno);
	} //endfor loop though duration of event

// adds the DJ to the event
AddDJToEvent(inevno, indjno);
}

void AddDJToEvent(char inevno[10], int idjno)
{
int evloc;
int duri;
char djnoc[10];
char slot[32];
int count;
int itim;
int idat;
int curhour;

evloc = FindInArray10(eventno, inevno, nei);

duri = atoi(evdur[evloc]);

itim = CalculateScheduleTimeIndex(evtime[evloc]);
idat = CalculateScheduleDateIndex(evdate[evloc]);

GetScheduleSlot(slot, inevno, idjno);

// converting the DJ number to str
itoa(idjno, djnoc, 10);

AddLinksEntry(inevno, djnoc);

for(count = 0; count < duri; count++)
	{
	curhour = itim + count;

	if(curhour == 24)
		{
		// reset the time
		itim = 0;

		// increment the date
		idat += 1;

		// remove the number of hours from the duration
		duri -= count;

		// reset the count
		count = 0;
		} //endif curhour is 24

	// sets the schedule slot
	SetScheduleSlot(slot, idat, curhour, idjno);
	} //endfor loop though duration of event
}

void RemoveEventFromSchedule(char evno[10])
{
int count;
int djnos[50];
int nodjs;

nodjs = GetAttendingDJs(evno, djnos);

// loops through all of the DJs and removes them from the event
for(count = 0; count < nodjs; count++)
	{
	RemoveDJFromEvent(evno, djnos[count]);
	} //endfor
}

void RemoveDJFromEvent(char evno[10], int indjno)
{
int idate;
int itime;
int loc;
int duri;
char djnoc[10];

// getting the location of the event
loc = FindInArray10(eventno, evno, nei);

idate = CalculateScheduleDateIndex(evdate[loc]);
itime = CalculateScheduleTimeIndex(evtime[loc]);

// converts the inputted DJ no into a str
itoa(indjno, djnoc, 10);

// removes the DJ link in the links file
RemoveLinksEntry(evno, djnoc);

// getting the duration of the event
duri = atoi(evdur[loc]);

// going backwards from the end of the event to the start
for (; duri >= 0; duri--)
	{
	SetScheduleSlot("*", idate, itime + duri, indjno);
	} //endfor

}

int IsEventOnSchedule(char evno[10])
{
char slot[32];
int atdjno;
int pres = 1;

atdjno = GetAttendingDJ(evno);

if(atdjno == -1)
	{
	pres = 0;

	// if no DJs attending event won't be on any of their schedules
	return pres;
	} //endif the DJ number is -1

GetScheduleSlot(slot, evno, atdjno);

if(slot[0] == '*')
	{
	pres = 0;
	} //endif the slot has the null character

return pres;
}

void OutputDJAvailability(int idjno)
{
int time;
int day;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

cout << "    ";

// outputting the time
for(time = 0; time < 24; time++)
	{
	if(time < 10)
			{
			cout << "0";
			} //endif

	cout << time << " ";
	} //endfor

// outputting the actual slot
for(day = 0; day < 7; day++)
	{
	cout << '\n' << daysofweek[day];
	for(time = 0; time < 24; time++)
		{
		// calculates the starting index by getting the DJ number * 7
		cout << "  " << sch[0][day + 7 * idjno][time][0];
		} //endfor
	} //endfor
}

int GetDayInMonth(int dtindex)
{
char odate[11];
int day;
int month;
int year;

CalculateDateFromSchedule(odate, dtindex);

// separates the day out
sscanf(odate, "%d/%d/%d", &day, &month, &year);

return day;
}

/* ------------------------------
 *          Scheduling Menu
 * ------------------------------ 
 */

int Scheduling()
{
int schedulinstatus = 0;
while (schedulinstatus != 3)
	{
	schedulinstatus = SchedulingMenu();
	clrscr();
	} //endwhile

return 0;
}


int SchedulingMenu()
{
int schedulingchoice;

clrscr();

cout << "\n\tScheduling Menu";
cout << "\n\t===============\n";
cout << "\n\t1. Schedule";
cout << "\n\t2. Holidays";
cout << "\n\t3. Return";

cout << "\n\nEnter Choice: ";
cin >> schedulingchoice;

switch(schedulingchoice)
	{
	case 1: 
		{
		Schedule();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		Holidays();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		clrscr();
		break;
		} // endcase
	}

return schedulingchoice;
}

/* ------------------------------
 *        Schedule Menu
 * ------------------------------ 
 */

int Schedule()
{
int schedulstatus = 0;
while (schedulstatus != 5)
	{
	schedulstatus = ScheduleMenu();
	clrscr();
	} //endwhile

return 0;
}


int ScheduleMenu()
{
int schedulechoice;

clrscr();

cout << "\n\tSchedule Menu";
cout << "\n\t=============\n";
cout << "\n\t1. View Schedule";
cout << "\n\t2. Create Schedule";
cout << "\n\t3. Clear Schedule";
cout << "\n\t4. Edit Schedule";
cout << "\n\t5. Return";

cout << "\nEnter Choice: ";
cin >> schedulechoice;

// ignores the new line
cin.ignore(1, '\n');

switch(schedulechoice)
	{
	case 1: 
		{
		ViewSchedule();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		CreateSchedule();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ClearSchedule();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		EditSchedule();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		clrscr();
		break;
		} // endcase
	}

return schedulechoice;
}

/* ------------------------------
 *         View Schedule
 * ------------------------------ 
 */

int ViewSchedule()
{
int viewstatus = 0;
while (viewstatus != 4)
	{
	viewstatus = ViewScheduleMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewScheduleMenu()
{
int viewschedulechoice;

clrscr();

cout << "\n\tView Schedule Menu";
cout << "\n\t==================\n";
cout << "\n\t1. By DJ";
cout << "\n\t2. Availability By DJ";
cout << "\n\t3. Guest Slots";
cout << "\n\t4. Return";

cout << "\nEnter Choice: ";
cin >> viewschedulechoice;

// ignores the new line
cin.get();

switch(viewschedulechoice)
	{
	case 1: 
		{
		ViewScheduleByDJ();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewScheduleAvailabilityByDJ();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewScheduleGuestSlots();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return viewschedulechoice;
}

int ViewScheduleByDJ()
{
int time;
int day;
int dayofwk;
char startdt[11];
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
char indjno[10];
char slotit[32];
char spacer[24];
char indate[11];
int dayinmo;
int numlen;
int idjno;
int count;
int dtindex;

ReadBackEventLinksFile();
ReadBackScheduleFile();
ReadBackEventFile();

clrscr();
cout << "\nView Schedule By DJ";
cout << "\n===================\n";

cout << "\nEnter DJ Number: ";
cin.getline(indjno, 10);

cout << "\nEnter week to view or view next or current (N/C): ";
cin.getline(indate, 11);

if(indate[0] == 'C')
	{
	GetToday(startdt);
	} //endif view current
else if(indate[0] == 'N')
	{
	GetToday(startdt);
	AddDays(startdt, 7);
	} //endif view next
else
	{
	// probs some validation here

	// set the start date to the inputted date
	strcpy(startdt, indate);
	} //endelse

// gets the DJ number as int
idjno = atoi(indjno);

// gets the day of the week 'today'
dayofwk = FindDayOnDate(startdt);

// if the day of the week isn't a Monday
if(dayofwk != 1)
	{
	// goes back dayofwk - 1 days (e.g. day 5 is 4 days from Mon)
	SubtractDays(startdt, dayofwk - 1);
	} //endif

// getting the starting index for the loop
dtindex = CalculateScheduleDateIndex(startdt);

// adding the day abbr len to the spacer
strcpy(spacer, "   ");

// getting the number of 10's as num in base 10
// adding 1 for the 1st sig fig
// then adding 4 as two brackets and 2 for spacing 
numlen = floor(log10(dtindex)) + 1 + 4;

for(count = 0; count < numlen; count++)
	{
	strcat(spacer, " ");
	} //endfor

// adding the spacing
cout << '\n' << spacer;

// outputting the times
for(time = 0; time < 24; time++)
	{
	if(time < 10)
			{
			cout << "0";
			} //endif
	cout << time << " ";
	} //endfor

for(day = 0; day < 7; day++)
	{
	dayinmo = GetDayInMonth(day + dtindex);

	cout << '\n' << "" << daysofweek[day] << "(" << dayinmo << ") ";
	
	for(time = 0; time < 24; time++)
		{
		GetScheduleSlot(slotit, day + dtindex, time, idjno);
		
		cout << "  " << sch[idjno][day + dtindex][time][0];
		} //endfor
	} //endfor

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewScheduleAvailabilityByDJ()
{
char indjno[10];
int djid;

ReadBackScheduleFile();

clrscr();
cout << "\nView Schedule Availability By DJ";
cout << "\n================================\n";

cout << "Enter DJ Number: ";
cin.getline(indjno, 10);

djid = atoi(indjno);

OutputDJAvailability(djid);

cout << "\nPress any key to return";
getch();

return 0;
}

int ViewScheduleGuestSlots()
{
int time;
int day;
int dayofwk;
int loc;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
char inpdate[11];
int dtindex;

ReadBackScheduleFile();

clrscr();
cout << "\nView Schedule Guest Slots";
cout << "\n=========================\n";

cout << "Enter date to view from: ";
cin.getline(inpdate, 11);

if(strcmpi(inpdate, "") == 0)
	{
	GetToday(inpdate);
	} //endif nothing is entered

// getting the starting index for the loop
dtindex = CalculateScheduleDateIndex(inpdate);

cout << "\n    ";

// outputting the times
for(time = 0; time < 24; time++)
	{
	if(time < 10)
			{
			cout << "0";
			} //endif
	cout << time << " ";
	} //endfor

// gets the day of the week on inpdate
dayofwk = FindDayOnDate(inpdate);

// if the day of the week isn't a Monday
if(dayofwk != 1)
	{
	// goes back dayofwk - 1 days (e.g. day 5 is 4 days from Mon)
	SubtractDays(inpdate, dayofwk - 1);
	} //endif

cout << day;

for(day = 0; day < 7; day++)
	{
	cout << '\n' << "" << daysofweek[day] << "(" << day + dtindex << ") ";
	
	for(time = 0; time < 24; time++)
		{
		loc = FindScheduleGuestSlot(day + dtindex, time);

		if(loc > 0)
			{
			GetScheduleGuestNumber(day + dtindex, time, loc);

			// output a null slot and then go to the next time
			cout << "  " << "*";
			continue;
			} //endif
		
		cout << "  " << sch[0][day][time];
		} //endfor
	} //endfor

cout << "\n\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *         Create Schedule
 * ------------------------------ 
 */


int CreateSchedule()
{
char choice;
int count;
int onsch;
char type;
int plcheck;
int attdj;
char mindt[11];
char maxdt[11];
char slot[32];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nCreate Schedule";
cout << "\n===============\n";

cout << "\nShould The Events be added to the Schedule (y/n): ";
choice = cin.get();

if(choice == 'n')
	{
	return 0;
	} //endif choice is no
else if(choice != 'y')
	{
	// some validation message here
	return 0;
	} //endelseif

// loop through the events and check they have been added to the schedule
for(count = 0; count < nei; count++)
	{
	onsch = IsEventOnSchedule(eventno[count]);

	if(onsch == -1)
		{
		cout << "\n\nID: " << eventno[count];
		cout << "\nTitle: " << evtitle[count];
		cout << "\nHasn't been added to the schedule - Please allocate a DJ";
		} //endif no DJ assigned to the event
	else if(onsch == 0)
		{
		type = GetBaseType(eventno[count]);

		attdj = GetAttendingDJ(eventno[count]);

		AddEventToSchedule(eventno[count], type, attdj);
		} //endif event not on the schedule or not completely on schedule
	} //endfor

// loop through the events and check the playlists are of correct length
for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	// if the type is not a show go to the next event
	if(type != 'S')
		continue;
	
	plcheck = PlaylistDurationCheck(eventno[count], 0);

	if(plcheck < 0)
		{
		cout << "\n\nID: " << eventno[count];
		cout << "\nTitle: " << evtitle[count];
		cout << "\nPlaylist of incorrect length";
		} //endif the duration of the playlist is less than 
	} //endfor

// output any holidays which haven't been approved and are for the following week
for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	// if the type is not a holiday go to the next event
	if(type != 'H')
		continue;

	// do a range check to make sure the event is in range
	GetToday(mindt);
	strcpy(maxdt, mindt);

	// getting the maximum date as a week after the current date
	AddDays(maxdt, 7);

	// skips any events with dates not in the range
	if(DateRangeCk(evdate[count], mindt, maxdt) != 0)
		continue;

	attdj = GetAttendingDJ(eventno[count]);

	GetScheduleSlot(slot, eventno[count], attdj);	

	if(slot[1] == 'U')
		{
		cout << "\n\nHoliday Ref: " << eventno[count];
		cout << "\nHoliday for next week hasn't been approved";
		} //endif the holiday is unapproved 
	} //endfor

cout << "\nSuccess - All events have been added to the schedule";

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\n\nPress any key to return";
getch();
getch();

return 0;
}


/* ------------------------------
 *         Clear Schedule
 * ------------------------------ 
 */


int ClearSchedule()
{
int day;
int time;
int djindex;
char choice;

ReadBackScheduleFile();

clrscr();
cout << "\nClear Schedule";
cout << "\n==============\n";

cout << "\nClear Schedule (y/n): ";
choice = cin.get();

if(choice != 'y')
	{
	return 0;
	} //endif

for (djindex = 1; djindex < 52; djindex++)
	{
	for(day = 0; day < 366; day++)
		{               
		for(time = 0; time < 24; time++)
			{
			strcpy(sch[djindex][day][time], "*");
			} //endfor
		} //endfor
	} //endfor

ReWriteScheduleFile();

cout << "\nPress any key to return";
getch();
return 0;
}

/* ------------------------------
 *         Change Schedule
 * ------------------------------ 
 */

int EditSchedule()
{
int editstatus = 0;
while (editstatus != 3)
	{
	editstatus = EditScheduleMenu();
	clrscr();
	} //endwhile

return 0;
}

int EditScheduleMenu()
{
int editschedulechoice;

clrscr();

cout << "\n\tEdit Schedule Menu";
cout << "\n\t==================\n";
cout << "\n\t1. DJ Availability";
cout << "\n\t2. Guest Slots";
cout << "\n\t3. Return";

cout << "\nEnter Choice: ";
cin >> editschedulechoice;

// ignores the new line
cin.get();

switch(editschedulechoice)
	{
	case 1: 
		{
		ChangeDJAvailability();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		GuestSlots();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		clrscr();
		break;
		} // endcase
	}

return editschedulechoice;
}

int ChangeDJAvailability()
{
int time;
int day;

char intime[3];
char inday[4];

char indjno[10];
int idjno;

char choice;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

ReadBackScheduleFile();

do
	{
	clrscr();
	cout << "\nChange DJ Availability";
	cout << "\n======================\n";

	cout << "\nEnter DJ Number: ";
	cin.getline(indjno, 10);

	idjno = atoi(indjno);

	cout << "    ";

	// outputting the time
	for(time = 0; time < 24; time++)
		{
		if(time < 10)
				{
				cout << "0";
				} //endif
		

		cout << time << " ";
		} //endfor

	// outputting the actual slot
	for(day = 0; day < 7; day++)
		{
		cout << '\n' << daysofweek[day];
		for(time = 0; time < 24; time++)
			{
			cout << "  " << sch[0][day + 7*idjno][time][0];
			} //endfor
		} //endfor

	// while loop here to loop until no more changes should be made

	cout << "\n\nAdd or Remove Available Slot (A/R): ";
	choice = cin.get();
	cin.get();

	if(choice == 'A')
		{
		cout << "\nEnter Day: ";
		cin.getline(inday, 4);

		cout << "\nEnter Time: ";
		cin.getline(intime, 3);

		// getting the day
		day = FindInArray04(daysofweek, inday, 7);

		// getting the time
		time = atoi(intime);

		sch[0][day + 7*idjno][time][0] = 'A';
		} //endif
	else if(choice == 'R')
		{
		cout << "\nEnter Day: ";
		cin.getline(inday, 4);

		cout << "\nEnter Time: ";
		cin.getline(intime, 3);

		// getting the day
		day = FindInArray04(daysofweek, inday, 7);

		// getting the time
		time = atoi(intime);

		sch[0][day + 7*idjno][time][0] = '*';
		} //endif

	// insert some check here
	cout << "\nSuccess - Availability has been changed";

	ReWriteScheduleFile();

	cout << "\nContinue making changes (y/n): ";
	choice = cin.get();
	cin.get();

	} //enddowhile choice is yes 
	while(choice == 'y');

cout << "\n\nPress any key to return";
getch();

return 0;
}

int GuestSlots()
{
int time;
int day;

char intime[3];
char inday[4];

char choice;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

ReadBackScheduleFile();

clrscr();
cout << "\nGuest Slots";
cout << "\n===========\n";

cout << "\nCurrent Guest Slots:\n\n";

// technically does the correct thing as the guest slots are just the availability of DJ 0
OutputDJAvailability(0);

cout << "\n\nAdd or Remove a Guest Slot (A/R): ";
choice = cin.get();
cin.get();

if(choice == 'A')
	{
	cout << "\nEnter Day: ";
	cin.getline(inday, 4);

	cout << "\nEnter Time: ";
	cin.getline(intime, 3);

	// getting the day
	day = FindInArray04(daysofweek, inday, 7);

	// getting the time
	time = atoi(intime);

	sch[0][day][time][0] = 'G';
	} //endif
else if(choice == 'R')
	{
	cout << "\nEnter Day: ";
	cin.getline(inday, 4);

	cout << "\nEnter Time: ";
	cin.getline(intime, 3);

	// getting the day
	day = FindInArray04(daysofweek, inday, 7);

	// getting the time
	time = atoi(intime);

	sch[0][day][time][0] = '*';
	} //endif


ReWriteScheduleFile();

cout << "\nPress any key to return";
getch();

return 0;
}



/* ------------------------------
 *        Holidays Menu
 * ------------------------------ 
 */

int IsHolidayApproved(char holref[10])
{
char slot[32];
int approved = 0;
int djid;

djid = GetAttendingDJ(holref);

GetScheduleSlot(slot, holref, djid);

if(slot[1] == 'U')
	{
	approved = 0;
	} //endif the holiday is unapproved
else if(slot[1] == 'A')
	{
	approved = 1;
	} //endif the holiday is approved

return approved;
}


int Holidays()
{
int holidaystatus = 0;
while (holidaystatus != 6)
	{
	holidaystatus = HolidaysMenu();
	clrscr();
	} //endwhile

return 0;
}


int HolidaysMenu()
{
int holidayschoice;

clrscr();

cout << "\n\tHolidays Menu";
cout << "\n\t=============\n";
cout << "\n\t1. View Holidays";
cout << "\n\t2. Book Holidays";
cout << "\n\t3. Change Holidays";
cout << "\n\t4. Remove Holidays";
cout << "\n\t5. Approve Holidays";
cout << "\n\t6. Return";

cout << "\n\nEnter Choice: ";
cin >> holidayschoice;

// ignores the new line
cin.ignore(1, '\n');

switch(holidayschoice)
	{
	case 1: 
		{
		ViewHolidays();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		BookHolidays();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ChangeHolidays();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		RemoveHolidays();
		clrscr();
		break;
		} // endcase
	case 5: 
		{
		ApproveHolidays();
		clrscr();
		break;
		} // endcase
	case 6: 
		{
		clrscr();
		break;
		} // endcase
	}

return holidayschoice;
}


/* ------------------------------
 *         View Holidays
 * ------------------------------ 
 */

int ViewHolidays()
{
int viewstatus = 0;
while (viewstatus != 4)
	{
	viewstatus = ViewHolidaysMenu();
	clrscr();
	} //endwhile

return 0;
}

int ViewHolidaysMenu()
{
int vholch;

clrscr();

cout << "\n\tView Holidays Menu";
cout << "\n\t==================\n";
cout << "\n\t1. By DJ";
cout << "\n\t2. By Date";
cout << "\n\t3. By Unapproved";
cout << "\n\t4. Return";

cout << "\nEnter Choice: ";
cin >> vholch;

// ignores the new line
cin.get();

switch(vholch)
	{
	case 1: 
		{
		ViewHolidaysByDJ();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ViewHolidaysByDate();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		ViewHolidaysByUnapproved();
		clrscr();
		break;
		} // endcase
	case 4: 
		{
		clrscr();
		break;
		} // endcase
	}

return vholch;
}

int ViewHolidaysByDJ()
{
char indjno[10];
char today[11];
int holrefs[500];
int top = 0;
int dtindex;
int idjno;
int cevno;
int count;
char type;

ReadBackEventLinksFile();
ReadBackScheduleFile();
ReadBackEventFile();

clrscr();
cout << "\nView Holidays By DJ";
cout << "\n===================\n";

cout << "\nEnter DJ Number: ";
cin.getline(indjno, 10);

idjno = atoi(indjno);

LocateDJ(idjno);

GetToday(today);

dtindex = CalculateScheduleDateIndex(today);

cout << '\n';

// update this bit to use the output with case
for (count = dtindex; count < 367; count++)
	{
	type = GetScheduleType(count, 0, idjno);

	cevno = atoi(eventno[count]);
	
	if(type == 'H' && holrefs[top] != cevno)
		{
		holrefs[top++] = cevno;
		} //endif the type is a holiday and that it isn't already in the stack
	} //endfor

OutputHolidays(holrefs, top, 1);

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewHolidaysByDate()
{
int count;
char type;
int holrefs[500];
int top = 0;

ReadBackEventFile();
ReadBackEventLinksFile();
ReadBackScheduleFile();

clrscr();
cout << "\nView Holidays By Date";
cout << "\n=====================\n";

BubbleEventSortDates(nei);

for (count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);
	
	if(type == 'H')
		{
		holrefs[top++] = atoi(eventno[count]);
		} //endif the type is a holiday
	} //endfor

OutputHolidays(holrefs, top, 1);

ReadBackEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewHolidaysByUnapproved()
{
int count;
char type;
int idate;
int loc;
int idjno;
int holrefs[500];
int top = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Holidays By Unapproved";
cout << "\n===========================\n";

for (count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	if(type == 'H')
		{
		idate = CalculateScheduleDateIndex(evdate[loc]);

		// this gets if it is approved or not
		type = sch[0][idate][0][1];

		if(type == 'U')
			{
			holrefs[top++] = atoi(eventno[count]);
			} //endif not approved
		} //endif
	} //endfor

OutputHolidays(holrefs, top);

cout << "\nPress any key to return";
getch();

return 0;
}

/* ------------------------------
 *         Add Holidays
 * ------------------------------ 
 */

int BookHolidays()
{
int idjno;
char djnoc[10];
char sdate[11];
char edate[11];
int sdati;
int edati;
int dur;
char evno[10];
char durc[10];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nBook Holidays";
cout << "\n=============\n";

// validate DJ exists
cout << "\nEnter DJ Number: ";
cin.getline(djnoc, 10);

// validate day isn't already booked for something
cout << "\nEnter Start Date: ";
cin.getline(sdate, 11);

// validate the end is after start
cout << "\nEnter End Date: ";
cin.getline(edate, 11);

sdati = CalculateScheduleDateIndex(sdate);
edati = CalculateScheduleDateIndex(edate);

// calculating the diff in days * 24 so it is in hours
dur = 24 * (edati - sdati);
itoa(dur, durc, 10);

GenerateEventNumber(evno);

// copies locals into their respective globals 
strcpy(eventno[nei], evno);
strcpy(evdate[nei], sdate);
strcpy(evtime[nei], "00:00");
strcpy(evlocation[nei], "Holiday");
strcpy(evdur[nei], durc);

cout << "\nSuccess - Holiday has been requested\n";

// gets the DJ number as an integer
idjno = atoi(djnoc);

nei = nei + 1;
itoa(nei, nec, 10);

// automatically adds the unapproved bit to the schedule
AddEventToSchedule(evno, 'H', idjno);

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *         Change Holidays
 * ------------------------------ 
 */

int ChangeHolidays()
{
int changestatus = 0;
while (changestatus != 3)
	{
	changestatus = ChangeHolidaysMenu();
	clrscr();
	} //endwhile

return 0;
}

int ChangeHolidaysMenu()
{
int changeholidayschoice;

clrscr();

cout << "\n\tChange Holidays Menu";
cout << "\n\t====================\n";
cout << "\n\t1. Start Date";
cout << "\n\t2. End Date";
cout << "\n\t3. Return";

cout << "\n\nEnter Choice: ";
cin >> changeholidayschoice;

// ignores the new line
cin.get();

switch(changeholidayschoice)
	{
	case 1: 
		{
		ChangeHolidaysStartDate();
		clrscr();
		break;
		} // endcase
	case 2: 
		{
		ChangeHolidaysEndDate();
		clrscr();
		break;
		} // endcase
	case 3: 
		{
		clrscr();
		break;
		} // endcase
	}

return changeholidayschoice;
}

int ChangeHolidaysStartDate()
{
char holref[10];
char ndate[11];
char edate[11];
char sdate[11];
int duri;
int nduri;
int eindx;
int evloc;
int attdj;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nChange Holidays Start Date";
cout << "\n==========================\n";

cout << "\nEnter Holiday Reference: ";
cin.getline(holref, 10);

evloc = FindInArray10(eventno, holref, nei);

strcpy(sdate, evdate[evloc]);

cout << "\nCurrent Start Date: " << sdate;

cout << "\nNew Start Date: ";
cin.getline(ndate, 11);

attdj = GetAttendingDJ(holref);

RemoveEventFromSchedule(holref);

duri = atoi(evdur[evloc]);

// copying start date to end date
strcpy(edate, sdate);

// getting end date
AddDays(edate, duri / 24);

eindx = CalculateScheduleDateIndex(edate);

// calculates difference in days then multiplies by 24 to get duration in hours
nduri = (eindx - CalculateScheduleDateIndex(ndate)) * 24;

// copy new duration into duration field
itoa(nduri, evdur[evloc], 10);

// copy new start date into date
strcpy(evdate[evloc], ndate);

AddEventToSchedule(holref, 'H', attdj);

// insert check here
cout << "\nSuccess - Start Date has been Changed\n";

ReWriteEventFile();
ReWriteScheduleFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeHolidaysEndDate()
{
char holref[10];
char edate[11];
char ndate[11];
int nduri;
int eindx;
int evloc;
int attdj;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nChange Holidays End Date";
cout << "\n========================\n";

cout << "\nEnter Holiday Reference: ";
cin.getline(holref, 10);

evloc = FindInArray10(eventno, holref, nei);

AddDays(edate, atoi(evdur[evloc]) / 24);

cout << "\nCurrent End Date: " << edate;

cout << "\nNew End Date: ";
cin.getline(ndate, 11);

attdj = GetAttendingDJ(holref);

RemoveEventFromSchedule(holref);

eindx = CalculateScheduleDateIndex(ndate);

// calculates difference in days then multiplies by 24 to get duration in hours
nduri = (eindx - CalculateScheduleDateIndex(evdate[evloc])) * 24;

// copy new duration into duration field
itoa(nduri, evdur[evloc], 10);

AddEventToSchedule(holref, 'H', attdj);

// insert check here
cout << "\nSuccess - End Date has been Changed\n";

ReWriteEventFile();
ReWriteScheduleFile();

cout << "\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *         Remove Holidays
 * ------------------------------ 
 */


int RemoveHolidays()
{
int find = 0;
char holref[10];
char tdate[11];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nRemove Holidays";
cout << "\n===============\n";

cout << "\nEnter Holiday Reference: ";
cin.getline(holref, 10);

// gets the event number
find = FindInArray10(eventno, holref, nei);

// saving the date for the final output
strcpy(tdate, evdate[find]);

// quick bit of validation to make sure that nothing accidental is done during testing
if(find == -1)
	return 0;

// clears the holiday off the schedule
RemoveEventFromSchedule(holref);

// removes all entries with this event
RemoveEventLinksEntries(holref);

RemoveEvent(find);

// insert check here
cout << "\nSuccess - The holiday on " << tdate << " has been deleted\n";

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\nPress any key to return";
getch();

return 0;
}


/* ------------------------------
 *         Approve Holidays
 * ------------------------------ 
 */


int ApproveHolidays()
{
char holref[10];
int attdj;
int loc;
char slot[32];
char choice;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nApprove Holidays";
cout << "\n================\n";

cout << "\nEnter Holiday Reference: ";
cin.getline(holref, 10);

loc = FindInArray10(eventno, holref, nei);

attdj = GetAttendingDJ(holref);

GetScheduleSlot(slot, holref, attdj);

cout << "\nEnter to Approve or Unapprove Holiday (A/U): ";
choice = cin.get();
cin.get();

if(choice == 'A' || choice == 'U')
	{
	// updates the holiday status
	slot[1] = choice;

	// this only needs to happen if a valid input is entered
	SetScheduleSlot(slot, evdate[loc], evtime[loc], attdj);
	} //endif there is a valid choice


// To-Do: sort this out so it is correct

// insert check here
cout << "\nSuccess - The holiday on " << evdate[loc] << " has been approved\n";

cout << "\nPress any key to return";
getch();

ReWriteScheduleFile();

return 0;
}

#pragma endregion


#pragma region Other

int FindInArray64(char array[][64], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindInArray48(char array[][48], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindInArray10(char array[][10], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindInArray04(char array[][4], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindInArray24(char array[][24], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindInArray32(char array[][32], char item[], int size, int start)
{
int count = 0;
int compare = 0;

for (count = start; count < size; count++)
        {
        compare = strcmpi(array[count], item);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

int FindPartialInArray32(char array[][32], char item[], int size, int start)
{
int count = 0;
int compare = 0;
int itlen = strlen(item);

for (count = start; count < size; count++)
        {
        compare = strnicmp(array[count], item, itlen);
        if(compare == 0)
                {
                return count;
                } //endif
        } //endfor

return -1;
}

template<int T>
int FindLongestInIndecies(char lst[][T], int indecies[], int size)
{
int count;
int len;
int maxlen = 0;

// finds the longest string
for(count = 0; count < size; count++)
	{
	len = strlen(lst[indecies[count]]);

	if(maxlen < len)
		{
		maxlen = len;
		} //endif the max length is less than the current length	
	} //endfor

return maxlen;
}

template<int T>
int FindLongest(char lst[][T], int size)
{
int count;
int maxlen = 0;

int indecies[size];

for(count = 0; count < size; count++)
	{
	indecies[count] = count;
	} //endfor

maxlen = FindLongestInIndecies(lst, indecies, size);

return maxlen;
}

void GetRefLocations(char array[][10], int indecies[], int size, int nindecies)
{
int count;
char refnoc[10];
int loc;

for(count = 0; count < nindecies; count++)
	{
	// converts the song id to a string
	itoa(indecies[count], refnoc, 10);

	loc = FindInArray10(array, refnoc, size);

	indecies[count] = loc;
	} //endfor
}

void AppendToStringAt32(char str[], char item, int index)
{
int count;
int len;

len = strlen(str);

// starting at the end and moving every character forward a space until index
for (count = len; count > index - 1; count--)
	{
	// moving the char
	str[count + 1] = str[count];
	} //endfor

// if it should be appended to the start of the string
if(index == -1)
        {
        // setting the index to the item
        str[0] = item;
        return;
        } //endif

// setting the index to the item
str[index] = item;
swap(str[index], str[index + 1]);
}

void AppendStrToStringAt32(char str[], char item[], int index)
{
int count;
int len;

len = strlen(item);

for(count = 0; count < len; count++)
	{
	// appending the characters in the item to the string
	// at index + count as for each append the desired index moves +1 forward
	AppendToStringAt32(str, item[count], index + count);
	} //endfor

}

int GetHeaders(char headercombo[32], char output[][32], char prefixindex[][32], char lookupindex[][32], int indexsize)
{
int noprefixes;
int comlen;
int count;
int loc;
int top = 0;

char separated[20][3];

comlen = strlen(headercombo);

// number of headers is length / 2 because each ID is 2 chars long
noprefixes = comlen / 2;

for(count = -2; count < comlen; count += 2)
	{
	// separates out the prefixes into a list [ "AA", "AA", ... ]
	separated[top - 1][0] = headercombo[count];
	separated[top - 1][1] = headercombo[count + 1];
	
	// adding the null terminator to show end of str
	separated[top - 1][2] = '\0';

	top += 1;
	} //endfor extract all prefixes

for(count = 0; count < noprefixes; count++)
	{
	// finds the location of the prefix in the lookup index
	loc = FindPartialInArray32(prefixindex, separated[count], indexsize);

	// copies the located index into the output
	strcpy(output[count], lookupindex[loc]);
	} //endfor

return top - 1;
}

void FormatAlignment(char title[], int longest, char* outformat)
{
char valc[10];

if(longest < strlen(title))
	{
	longest = strlen(title);
	} //endif the longest entry is smaller than the title

itoa(longest, valc, 10);
AppendToStringAt32(valc, '-', -1);
AppendStrToStringAt32(outformat, valc, 0);
}

void ConvertDateToStr(char date[11], int day, int month, int year)
{
// sections for the outputting of the date
char dayc[3] = "";
char monc[3] = "";
char yerc[5] = "";

// converting the day into a string
itoa(day, dayc, 10);

if(day < 10)
	{
	// moving the digit into the second position of the string
	dayc[1] = dayc[0];

	// adding a 0 at the first position of the string
	dayc[0] = '0';
	} //endif

// converting the month into a string
itoa(month, monc, 10);

if(month < 10)
	{
	// moving the digit to the second position
	monc[1] = monc[0];

	// setting the first position equal to 0
	monc[0] = '0';
	} //endif the month is less than 10

// converting the year into a character
itoa(year, yerc, 10);

// putting it all together into the dd/mm/yyyy format
sprintf(date, "%s/%s/%s", dayc, monc, yerc);
}

void ConvertTimeToStr(char time[6], int hours, int mins)
{
// sections for the outputting of the time
char minc[3] = "";
char hrsc[3] = "";

// converting the minutes into a string
itoa(mins, minc, 10);

if(mins < 10)
	{
	// moving the digit into the second position of the string
	minc[1] = minc[0];

	// adding a 0 at the first position of the string
	minc[0] = '0';
	} //endif

// converting the hours into a string
itoa(hours, hrsc, 10);

if(hours < 10)
	{
	// moving the digit to the second position
	hrsc[1] = hrsc[0];

	// setting the first position equal to 0
	hrsc[0] = '0';
	} //endif the hours is less than 10

// putting it all together into the hh:mm format
sprintf(time, "%s:%s", minc, hrsc);
}

int FindNextReferenceNumber(int testnumber, char numberarr[][10], int size)
{
int count;
int result = testnumber;
int tmpnum;

for (count = 0; count < size; count++)
    {
    // converts the number to an integer
    tmpnum = atoi(numberarr[count]);

    // if the number is equal to the result
    if(tmpnum == result)
        {
        // increment the result
        result = result + 1;

        // test it again and return the new found value
        return FindNextReferenceNumber(result, numberarr, size);
        } //endif
    } //endfor

// return the value if it hasn't been found
return result;
}

int FindDayOnDate(char date[11])
{
int day, month, year;

int anchor = 2;
int yrcode = 0;
int endyr = 0;

int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int dooms[12] = { 3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12 };

sscanf(date, "%d/%d/%d", &day, &month, &year);

endyr = 100*(year/100 - floor(year/100));

if(year % 4 == 0)
        {
        daysmo[1] = 29;
        dooms[0] = 29;
        dooms[0] = 4;
        } //endif leap year

yrcode = (anchor + (int)floor(endyr/4) + endyr) % 7;

day = day - dooms[month - 1];

day = (((day % 7) + yrcode) % 7);

return day;
}

int PasswordSecurityCheck(char inpass[32])
{
// password miniumum length to be valid
int minlen = 10;
int count;
int count2;
int passlen;

int isvalid = 1;

int capcheck = 0;
int digcheck = 0;
int lowcheck = 0;
int specheck = 0;

int speciallen;

char specialchars[34] = "!\" $%^&*()`|\\{[]}:;@'~#<,>.?/_-+=";
specialchars[2] = pound;

passlen = strlen(inpass); // Gets length of password.
speciallen = strlen(specialchars); // Gets the number of special characters.

if(passlen < minlen)
        {
        cout << "\nError: Password is not greater than " << minlen << " characters long";

        // setting it not valid
	isvalid = 0;

	// returning early because there isn't any point in doing anything else to validate
	return isvalid;
        } //endif password length is less than the minimum

for(count = 0; count < passlen; count++)
        {
		if(isupper(inpass[count]))
				{
				capcheck = 1;
				} //endif is uppercase
		if(islower(inpass[count]))
				{
				lowcheck = 1;
				} //endif is lowercase
		if(isdigit(inpass[count]))
				{
				digcheck = 1;
				} //endif is a digit
        
		for(count2 = 0; count2 < speciallen; count2++)
                {
                if(inpass[count] == specialchars[count2])
                        {
                        specheck = 1;
                        } //endif
                } //endfor
        } //endfor



// these are else ifs so that we don't have multiple output statements
if(lowcheck == 0)
	{
	cout << "\nError: Password does not contain a lowercase character";
    isvalid = 0;
	} //endif there are no lowers
else if(capcheck == 0)
	{
	cout << "\nError: Password does not contain an uppercase character";
    isvalid = 0;
	} //endif there are no caps
else if(digcheck == 0)
	{
	cout << "\nError: Password does not contain a number";
    isvalid = 0;
	} //endif there are no numbers
else if(specheck == 0)
	{
	cout << "\nError: Password does not contain a special character";
    isvalid = 0;
	} //endif there is not a special character

return isvalid;
}

int CalculateNumericalDate(char date[11])
{
int day;
int month;
int year;
int result;

// this works on the assumption that the date has already been validated

// getting the day, month and year as integers from the input date
sscanf(date, "%d/%d/%d", &day, &month, &year);

// output yyyymmdd
result = (1 * day) + (100 * month) + (10000 * year);

return result;
}

int CalculateNumericalDateInt(int day, int month, int year)
{
int result;

// calculate the numerical value
result = (1 * day) + (100 * month) + (10000 * year);

return result;
}

void BubbleSort(int array[], int size)
{
int index;

if(size == 1)
        {
        return;
        } //endif

for(index = 0; index < size-1; index++)
        {
        if(array[index] > array[index + 1])
                {
                swap(array[index], array[index + 1]);
                } //endif
        } //endfor

// recursively calling the sort
BubbleSort(array, size - 1);
}

void BubbleSortDates(char dates[][11], int size)
{
int index;
int numdate1;
int numdate2;

if(size == 1)
        {
        return;
        } //endif

for(index = 0; index < size-1; index++)
        {
        numdate1 = CalculateNumericalDate(dates[index]);
        numdate2 = CalculateNumericalDate(dates[index + 1]);

        if(numdate1 > numdate2)
                {
                swap(dates[index], dates[index + 1]);
                } //endif
        } //endfor

// recursively calling the sort
BubbleSortDates(dates, size - 1);
}

int SortDatesChronologically(char dates[][11], int nodates, int onlyfuture)
{
// today's date
int today;

// temporary date for when iterating though the dates (selected date)
int seldate;

int count;

// the date to start printing from (will be > 0 if starting from current date)
int startfrom = 0;

// sorting the dates
BubbleSortDates(dates, nodates);

if(onlyfuture == 1)
        {
        today = GetSystemsClock();

        // iterate through the sorted array to find the first date greater than the current
        for(count = 0; count < nodates; count++)
                {
                seldate = CalculateNumericalDate(dates[count]);

                if(seldate < today)
                        {
                        // the date after as the if will not run from the first date after today 
                        startfrom = count + 1;
                        } //endif the selected date is before the current date
                } //endfor
        } //endif show only future dates

return startfrom;
}

void BubbleSortMusicPopularity(int array[], int size)
{
int index;

if(size == 1)
        {
        return;
        } //endif

for(index = 0; index < size-1; index++)
        {
        if(array[index] > array[index + 1])
                {
                swap(mucatno[index], mucatno[index + 1]);
                swap(mutitle[index], mutitle[index + 1]);
                swap(muartist[index], muartist[index + 1]);
                swap(mugenre[index], mugenre[index + 1]);
                swap(mupub[index], mupub[index + 1]);
                swap(muplaytime[index], muplaytime[index + 1]);
                swap(mucheck[index], mucheck[index + 1]);
                swap(mufreq[index], mufreq[index + 1]);
                } //endif
        } //endfor

// recursively calling the sort
BubbleSort(array, size - 1);
}

void ExtendedBubbleSort(int array[], int size, void (*swapfunc)(int index))
{
int index;

if(size == 1)
        {
        return;
        } //endif

for(index = 0; index < size-1; index++)
	{
	if(array[index + 1] < array[index])
		{
		swapfunc(index);
		swap(array[index], array[index + 1]);
		} //endif
	} //endfor

// recursively calling the sort
ExtendedBubbleSort(array, size - 1, swapfunc);	
}

int ConvertMonth(char month[32])
{
// comparison variable
int monthcomp = 0;

// the numerical month
int nomonth = 0;

monthcomp = strcmpi(month, "Jan");
if(monthcomp == 0)
        {
        nomonth = 1;
        } //endif

monthcomp = strcmpi(month, "Feb");
if(monthcomp == 0)
        {
        nomonth = 2;
        } //endif

monthcomp = strcmpi(month, "Mar");
if(monthcomp == 0)
        {
        nomonth = 3;
        } //endif

monthcomp = strcmpi(month, "Apr");
if(monthcomp == 0)
        {
        nomonth = 4;
        } //endif

monthcomp = strcmpi(month, "May");
if(monthcomp == 0)
        {
        nomonth = 5;
        } //endif

monthcomp = strcmpi(month, "Jun");
if(monthcomp == 0)
        {
        nomonth = 6;
        } //endif

monthcomp = strcmpi(month, "Jul");
if(monthcomp == 0)
        {
        nomonth = 7;
        } //endif

monthcomp = strcmpi(month, "Aug");
if(monthcomp == 0)
        {
        nomonth = 8;
        } //endif

monthcomp = strcmpi(month, "Sep");
if(monthcomp == 0)
        {
        nomonth = 9;
        } //endif

monthcomp = strcmpi(month, "Oct");
if(monthcomp == 0)
        {
        nomonth = 10;
        } //endif

monthcomp = strcmpi(month, "Nov");
if(monthcomp == 0)
        {
        nomonth = 11;
        } //endif
        
monthcomp = strcmpi(month, "Dec");
if(monthcomp == 0)
        {
        nomonth = 12;
        } //endif

return nomonth;
}

int CalculateDuration(char time1[6], char time2[6])
{
int hour1 = 0, hour2 = 0;
int min1 = 0, min2 = 0;

int itim1 = 0, itim2 = 0;

float diff = 0;

int duration = 0;

// getting the mins and hours from the times
sscanf(time1, "%d:%d", &hour1, &min1);
sscanf(time2, "%d:%d", &hour2, &min2);

// getting both times in minutes
itim1 = (hour1 * 60 + min1);
itim2 = (hour2 * 60 + min2);

// getting the difference between them
diff = abs(itim2 - itim1);

// converting difference into mins rounding up so if 1 min over it counts as an hour
duration = ceil(diff / 60);

return duration;
}

void CalculateEndTime(char time[6], char duration[10], char timeout[6])
{
int duri;
char mins[3];
int hours;

duri = atoi(duration);

// gets the hours and minutes
sscanf(time, "%d:%s", &hours, &mins);

// getting the new hour
hours = hours + duri;

// adds the final result to the output in the form hh:mm
sprintf(timeout, "%d:%s", hours, mins);

if(hours < 10)
	{
	// shuffling the number forward and adding the 0 to make it 5 chars long
	timeout[1] = timeout[0];
	timeout[0] = '0';
	} //endif
}

void GetToday(char output[11])
{
// temporary string to store the time
char temptime[32];

// systems clock time variable
time_t rawtime;

// systems clock date
int sysday;
int sysmonth;
int sysyear;

// the systems clock month as character
char monthchar[4];

// getting the raw time from the sys clock
time(&rawtime);

// copying the rawtime into the temp time variable
strcpy(temptime, ctime(&rawtime));

// gets the details of the sys clock
sscanf(&temptime[20], "%d", &sysyear);
sscanf(&temptime[4], "%3s", &monthchar);
sscanf(&temptime[8], "%d", &sysday);

// gets the month numerically
sysmonth = ConvertMonth(monthchar);

ConvertDateToStr(output, sysday, sysmonth, sysyear);
}

int GetSystemsClock()
{
// temporary string to store the time
char temptime[32];

// systems clock time variable
time_t rawtime;

// systems clock date
int sysday;
int sysmonth;
int sysyear;

// the systems clock month as character
char monthchar[4];

// final return value (as numerical date)
int result;

// getting the raw time from the sys clock
time(&rawtime);

// copying the rawtime into the temp time variable
strcpy(temptime, ctime(&rawtime));

cout << '\n' << temptime;

// gets the details of the sys clock
sscanf(&temptime[20], "%d", &sysyear);
sscanf(&temptime[4], "%3s", &monthchar);
sscanf(&temptime[8], "%d", &sysday);

// gets the month numerically
sysmonth = ConvertMonth(monthchar);

// converts the current date into a numerical value 
result = CalculateNumericalDateInt(sysday, sysmonth, sysyear);

return result;
}

void SubtractDays(char date[11], int days)
{
int day;
int month;
int year;

int curdati;

// days in each month
int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// splits up the date format
sscanf(date, "%d/%d/%d", &day, &month, &year);

// checks if leap year and updates the days in each month
if(year % 4 == 0)
        {
        daysmo[1] = 29;
        } //endif leap year

curdati = day;

// decreasing the month by 1 so that it can be used as an index access
month = month - 1;

while(curdati < days)
	{
	// decrease the month by 2
	month -= 1;

	// add the days in the previous month to make the calculation possible
	curdati += daysmo[month];
	} //endif

// remove the days from the date
curdati -= days;

// converts the date back into the format dd/mm/yyyy
ConvertDateToStr(date, curdati, month + 1, year);
}

void AddDays(char date[11], int days)
{
int day;
int month;
int year;
int count;

int curdati;

// days in each month
int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// splits up the date format
sscanf(date, "%d/%d/%d", &day, &month, &year);

// checks if leap year and updates the days in each month
if(year % 4 == 0)
        {
        daysmo[1] = 29;
        } //endif leap year

// decreasing the month by 1 so that it can be used as an index access
month = month - 1;

curdati = day + days;
while(curdati > daysmo[month])
	{
	curdati -= daysmo[month];
	month += 1;
	} //endwhile

// converts the date back into the format dd/mm/yyyy
ConvertDateToStr(date, curdati, month + 1, year);
}

int AddTimes(char time[6], int hours)
{
int mins;
int hrs;
int nodays = 0;

// gets the hours and mins (mins as str as it won't change)
sscanf(time, "%d:%d", &hrs, &mins);

hrs = hrs + hours;

nodays = floor(hrs/24);

// hours mod 24 to resolve it into a positive number of hours
hrs = hrs % 24;

ConvertTimeToStr(time, hrs, mins);

return nodays;
}

void PrintArray(int array[], int size)
{
int index;

// loops through the array outputting the values
for (index = 0; index < size; index++)
        {
        cout << '\n' << array[index];
        } //endfor
}

void PrintArray(char array[][11], int size)
{
int index;

// loops through the array outputting the values
for (index = 0; index < size; index++)
        {
        cout << '\n' << array[index];
        } //endfor
}

void PrintArray(char array[][48], int size)
{
int index;

// loops through the array outputting the values
for (index = 0; index < size; index++)
        {
        cout << '\n' << array[index];
        } //endfor
}

void PrintArray(char array[][11], int start, int end)
{
int index;

// loops through the array outputting the values
for (index = start; index < end; index++)
        {
        cout << '\n' << array[index];
        } //endfor
}

int DateRangeCk(char date[11], char mindate[11], char maxdate[11])
{
int x;
int min;
int max;

x = CalculateNumericalDate(date);

min = CalculateNumericalDate(mindate);

max = CalculateNumericalDate(maxdate);

if(x < min)
	{
	return -1;
	} //endif the date is less than the minimum
else if(x > max)
	{
	return 1;	
	} //endelseif the date is greater than the maximum
else
	{
	// if it is in the correct range return 0
	return 0;
	} //endelse
}

#pragma endregion
