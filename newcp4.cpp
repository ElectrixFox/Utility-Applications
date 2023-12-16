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

using namespace std;
#define getch() cin.get()
#define clrscr() system("cls")

char pound = 156;

char FileName1[80] = "GuestFile";
int ngi;
char ngc[3];

char guestno[128][10]; 
char gunam[128][32]; 
char gucontactnam[128][32]; 
char guconttelenum[128][12]; 
char guemailaddr[128][32]; 


char FileName2[80] = "EventsFile";
int nei;
char nec[3];

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

char FileName3[80] = "MusicFile";
int nmi;
char nmc[3];

char mucatno[500][10]; 
char mutitle[500][48];
char muartist[500][32]; 
char mugenre[500][24]; 
char mupub[500][64]; 
char muplaytime[500][6]; 
char mucheck[500][2]; 
char mufreq[500][10]; 

char FileName4[80] = "EventsLinksFile";
int nli;
char nlc[3];

char evlinkevno[128][10];
char evlinkdjno[128][10];

char FileName5[80] = "PlaylistsLinksFile";
int npi;
char npc[3];

char pllinkcatno[128][10];
char pllinkevno[128][10];

char FileName6[80] = "DJFile";
typedef struct tag_cr
	{
	char djnam[32];
	char djtelenum[12]; 
	char djemailaddr[32]; 
	char performnam[32]; 
	char musstyle[24]; 
	char flag[2];
	} DJ_RECORD;
int djno;
DJ_RECORD a_dj;

char FileName7[80] = "ScheduleFile";

// [dj][day][time]
char sch[52][367][24][32];

int MainMenu();

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
int PlaylistDurationCheck(char evno[10], int pldur = 0, int output = 1);

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

// finds the next available ref number in the number array starting at testnumber
int FindNextReferenceNumber(int testnumber, char numberarr[][10], int size);

// finds the day on the date passed to the function
int FindDayOnDate(char date[11]);

// identifies the headers from their prefixes and outputs them in a list of headers (returns number of headers)
int GetHeaders(char headercombo[32], char output[][32], char prefixindex[][32], char lookupindex[][32], int indexsize);

// formats the alignment of the output and corrects the output format, taking len of longest entry and title
void FormatAlignment(char title[], int longest, char* outformat);

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

// gets the closest Monday to the inputted date, if nothing is inputted then uses today's date
void GetClosestMonday(char indate[11]);

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

/* ------------------------------
 *          Main Menu
 * ------------------------------ 
 */

int main(int argc, char* argv[])
{
int mainstatus = 0;
while (mainstatus != 6)
        {
        mainstatus = MainMenu();
        clrscr();
        } //endwhile

getch();
return 0;
}