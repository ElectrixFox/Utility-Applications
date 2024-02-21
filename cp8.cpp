/******************************************************************************
Program:        SoftwareDevelopment
File:           SoftwareDevelopment.cpp
Functions:      main
Description:    
Author:         Luke Phillips
Environment:    Borland C++ Pro 6.0
Notes:			
Revisions:      18/07/2023
******************************************************************************/

/*
    Indent: CTRL+SHIFT+I
    Dent: CTRL+SHIFT+U
*/

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
#define getch() cin.get()
#define out(x) cout << '\n' << #x << ": " << x << '\n'
#endif

char pound = 156;

char FileName1[80] = "GuestFile";
int ngi;
char ngc[3];

char guestno[128][10];
char gunam[128][48];
char gucontactnam[128][48];
char guconttelenum[128][12];
char guemailaddr[128][48];
char gugenre[128][24];

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
char evcont[128][48];
char evcontemail[128][48];
char evcontnum[128][12];

char FileName3[80] = "MusicFile";
int nmi;
char nmc[3];

char mucatno[500][10];
char mutitle[500][48];
char muartist[500][48];
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
	char djnam[48];
	char djtelenum[12]; 
	char djemailaddr[48];
	char performnam[48];
	char musstyle[24]; 
	char flag[2];
	} DJ_RECORD;
int djno;
DJ_RECORD a_dj;

char FileName7[80] = "ScheduleFile";

// [dj][day][time][slot]
char sch[52][367][24][32];

char FileName8[80] = "UserFile";
int nui;
char nuc[3];
char usrnos[128][10];
char usernames[128][48];
char passwords[128][64];
char loas[128][3];
int curusr;

/* Project Management

 Issues:
 [*] the system cannot add back a recurring event after all DJs have been removed (this can be fixed by adding a warning)
 [*] update system so that it doesn't allow for different types of events to have their details changed such as changing price for a DJ session

 Change Log: 

*/

int MainMenu();

#pragma region DJs

// loads the DJ at the inputted number
void LocateDJ(int idjno);

// sets the flag to the state for the current DJ
void SetDJFlag(int state);

// writes the DJ at idjno to the file
void WriteDJ(int idjno);

// finds first empty slot and returns it as an integer
int GenerateDJNumber();

// checks if the inputted DJ number is ocuppied
int DoesDJExist(int indjno);

// processes the number input and returns -2 if should quit, -1 if not found and location if found
int GetDJNumberInput(char inpdjno[10], int quitoptn = 0);

// outputs the DJ at the inputted number 
void OutputDJ(int idjno);

// views the DJ which is active
int ViewDJAccess();	

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
int ViewGuestByGenre();

int AddGuest();

int ChangeGuest();
int ChangeGuestMenu();
int ChangeGuestName();
int ChangeGuestContactName();
int ChangeGuestContactPhoneNumber();
int ChangeGuestContactEmailAddress();
int ChangeGuestGenre();

int RemoveGuest();

#pragma endregion

#pragma region Music

int ReadBackMusicFile();
int ReWriteMusicFile();

// finds the song with the longest entry and returns that field length, also copies the data for that field into the outvalues
int MusicLongestLength(char title[], int songids[], int size, char outvalues[][256]);

// generates the catalogue number
int GenerateCatalogueNumber(char incatno[10]);

// outputs all of the songs with the song ids (size is the number of ids), heads are the first two letters of the header
// an example would be "TiId" for the title and the ID
void OutputSongs(int songids[], char heads[32], int size);

// outputs the song at the location in a linear layout
void OutputSongLinear(int location);

// converts the playtime into seconds
int ConvertPlaytimeToSecconds(char playtime[6]);

// menu functions

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

int CatalogueChangeMusic();
int CatalogueChangeMusicMenu();
int ChangeMusicTitle();
int ChangeMusicArtist();
int ChangeMusicPlaytime();
int ChangeMusicGenre();
int ChangeMusicCheck();

int CatalogueRemoveMusic();

// playlist functions

int ReadBackPlaylistFile();
int ReWritePlaylistFile();

// returns the duration of the playlist (in seconds) at inevno
int CalculatePlaylistDuration(char inevno[10]);

// creates the output message for the duration calc (diff in mins)
void DurationEnding(char output[64], int durdiff);

// gives an output for if the duration of the playlist is incorrect (returns the duration), allows for playlist duration to be passed in
// returns negative if the duration of the playlist fails the check
int PlaylistDurationCheck(char evno[10], int pldur = 0, int output = 1);

// adds a new song (incatno) to the playlist on inevno 
void AddPlaylistEntry(char inevno[10], char incatno[10]);

// removes all songs according to their event number
void RemovePlaylistEntriesByEvent(char inevno[10]);

// removes an entry from the playlist on inevno with songid incatno
void RemovePlaylistEntry(char inevno[10], char incatno[10]);

// finds the location of the inputted song in the playlist and returns it's location or -1 if it hasn't been found
int FindSongInPlaylist(char inevno[10], char incatno[10]);

// menu functions

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

int ReadBackUserFile();
int ReWriteUserFile();

int GetUserDJ();	// gets DJ associated to the user 
int GetGLOA();	// gets global level of access

int Login();

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

#pragma region Event

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

// checks if the inputted DJ is attending the inputted event returns 0 if not and 1 if so
int IsDJAttending(char inevno[10], int indjno);

// checks if the inputted event is recurring
int IsRecurringEvent(char inevno[10]);

// swaps the event at index and the following event
void SwapEvents(int index);

// removes the event at the location in the events file
void RemoveEvent(int location);

// bubble sorts the dates in the events
void BubbleEventSortDates(int size);

// moves all of the recurrring events to a date close to the given date
void UpdateRecurrringEvents(char date[11]);

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

#pragma region Schedule

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

// sets the schedule slots from the start date and time (for dur number of hours and for djid) as value
void SetScheduleSlots(char value[32], char sdate[11], char stime[6], char dur[10], int djid);

// gets the schedule slot at date and time with djid and copies it into output 
void GetScheduleSlot(char output[32], int date, int time, int djid);

// gets the schedule slot at the date and time by converting them to the required format
void GetScheduleSlot(char output[32], char date[11], char time[6], int djid);

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

// gets the date of the event on the schedule starting from start date and returning schedule index of date
int GetEventDateOnSchedule(char outdate[11], char evnoc[10], int startdt);

// adds the event to the schedule and creates a link for the DJ and event
void AddEventToSchedule(char inevno[10], char type, int indjno, char inguno[10] = "");

// adds a weekly recurring event to the schedule for the rest of the weeks with the same day from the start date
void AddRecurringEventToSchedule(char inevno[10], char type, int indjno);

// adds a guest event to the schedule creating a link between the in DJ and the event
void AddGuestEventToSchedule(char inevno[10], char inguno[10], int indjno);

// adds the event to the DJ's schedule and creates a link for it 
void AddDJToEvent(char inevno[10], int idjno);

// removes the instance of the recurring event on indate or removes all occurrances of the event if a date isn't entered 
void RemoveRecurringEventFromDJ(char evno[10], int indjno);

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

// checks if the slot at the inputted date and time is being used by a DJ
int IsSlotUsed(char date[11], char time[6], int djid);

// outputs all of the data for the row to the screen
void OutputRow(int day, char dayc[4], char content[32], char time[6], int rowlen);

// outputs the events in the left and right stacks to the screen starting at the inputted day with dayit as the day in the week
void OutputEventRow(int day, int dayit, int evnos[], int top, int len);

// outputs the header bar full of '='s for the schedule
void OutputHeaderBar(int len);

// gets all of the events of a type between startdt and enddt (which are schedule coords) for attdj returning the number of events and taking the array to write them to
int FindAllEventsOfTypeBetweenDates(int evnos[], char type, int startdt, int enddt, int attdj);

// gets all of the events of a type between startdt and enddt for attdj returning the number of events and taking the array to write them to
int FindAllEventsOfTypeBetweenDates(int evnos[], char type, char startdt[11], char enddt[11], int attdj);

// adds all of the event numbers of the events found between the inputted start and end date (which are found using CalculateScheduleDateIndex) for the DJ to the evnos array
int FindAllEventsBetweenDates(int evnos[], int startdt, int enddt, int attdj);

// adds all of the event numbers of the events found between the inputted start and end date for the DJ to the evnos array
int FindAllEventsBetweenDates(int evnos[], char startdt[11], char enddt[11], int attdj);

// finds all of the events for a certain DJ between the two inputted times
int FindAllEventsBetweenTimes(int evnos[], char date[11], char stime[6], char etime[6], int attdj);

// finds all of the holiday slots between the start and end date (using the schedule coords) and adds the event numbers for them to an array
int FindAllHolidaySlots(int evnos[], int startdt, int enddt);

// finds all of the holiday slots between the start and end date and adds the event numbers for them to an array
int FindAllHolidaySlots(int evnos[], char startdt[11], char enddt[11]);


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

int EditSchedule();
int EditScheduleMenu();
int ChangeDJAvailability();
int GuestSlots();

// checks if the holiday is approved and returns 1 if it is approved
int IsHolidayApproved(char holref[10]);

// outputs the size number of holidays with holiday references holids and outputs if they are approved if check = 1
void OutputHolidays(int holids[], int size, int check = 0);

// adds an approved holiday to the schedule with the correct modifications made to the schedule
void AddApprovedHolidayToSchedule(char holref[10]);

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

// finds an item in the (integer) array starting with default point of 0 
int FindInArrayInt(int array[], int item, int size, int start = 0);

// finds part of an item in the array 32 bytes with default starting point at 0
int FindPartialInArray32(char array[][32], char item[], int size, int start = 0);

// gets the location of the reference numbers in the array taking in the number of indecies, size of the array and the ids of the elements
void GetRefLocations(char array[][10], int indecies[], int size, int nindecies);

// gets the location of a substring in a string with given size starting at given index
int FindInString(char string[], char substring[], int size, int start = 0);

// gets the location of a character in a string with given size starting at given index
int FindCharInString(char string[], char character, int size, int start = 0);

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

// removes all of the non-unique values from an array (sets them to -1) and returns its new size
int MakeArrayUniqueInt(int array[], int size);

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
int ConvertMonth(char month[4]);

// gets the time difference between two times (returns in hours)
int CalculateDuration(char time1[6], char time2[6]);

// finds the end time of the duration added to the time (outputs to timeout) 
void CalculateEndTime(char time[6], char duration[10], char timeout[6]);

// if date1 = date2 returns 0, if date1 is before date2 then -1, if date1 is after date2 then 1
int DateComp(char date1[11], char date2[11]);

// if time1 = time2 returns 0, if time1 is before time2 then -1, if time1 is after time2 then 1
int TimeComp(char time1[6], char time2[6]);

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

// compares two words to check which one is alphabetically first, returns 0 if they're the same, 1 if wrd1 is before wrd2, -1 for the other way around
int CompareWordsAlphabetically(char word1[], char word2[]);

// binary searches for a date in the dates array starting at start (0) and ending at end (size) returns -(index of closest item) if the item can't be found  
int BinaryDateSearch(char dates[128][11], char date[11], int start, int end);

// gets the choice for the menu by not allowing any invalid values to be entered, returning the correct value of the choice
int GetMenuChoice(int min, int max);

// creates a progress bar of default length 10 characters long for current out of total
void ProgressBar(int current, int total, int len = 10);

#pragma endregion

#pragma region Validation

// checks that the date is in the range of the two dates and returns -1 if before min, 1 if after max, 0 if correct
int DateRangeCk(char date[11], char mindate[11], char maxdate[11]);

// checks if the inputted string is a number, returns 1 if it is, outputs the error message if the output is 1
int IsNumber(char instr[], int output = 0);

// if the value is less than min returns -1, if greater than max 1, if correct 0, output toggles whether output messages should be shown
int RangeCk(int value, int min, int max, int output = 0);

// checks if the inputted string is of sufficient length (0, 1) and doesn't start with an empty character
int PresenceCk(char input[]);

// checks the string is of minimum length and below maximum
int LengthCk(char input[], int min, int max);

// validates the inputted date
int DateValidation(char datevalue[11]);

// validates the inputted email address
int ValidateEmailAddr(char emailaddr[32]);

// validates the inputted phone number
int PhoneNumberFormatCheck(char phonenumber[12]);

// validates the inputted genre
int ValidGenreCk(char inpgenre[24]);

// validates the yes or no input choice
int YesNoValidation(char choice);

// validate the choice is in the options
int MultiOptionValidation(char choice, char optns[]);

// validates the price is within the correct range for each part and that the dot is in the correct place
int ValidatePrice(char price[6]);

// validates that there are no events between the two inputted times on the inputted date for djid
int EventCollisionCheckTime(char date[11], char starttim[6], char endtim[6], int djid);

// validates that there are no events during the current event passed to the routine for djid
int EventCollisionCheckEvent(char evnoc[10], int djid);

// checks if the DJ is available between the given times for the given date and returns 1 if they are
int IsDJAvailable(char date[11], char stime[6], char etime[6], int djid);

// checks if the slots between the given times are available for the guest to be booked on the given date
int IsGuestSlotAvailable(char date[11], char stime[6], char etime[6]);

// validates that a password is secure enough to be used
int PasswordSecurityCheck(char inpass[64]);

// validates the inputted file path is in the correct format
int ValidateFilePath(char filepath[128]);

// copies the validated name into the inpname variable and outputs the message to ask for input
void NameInputPresCk(char inpname[48], char outmsg[], int na = 0);

// copies the validated email address into the inpemailaddr variable and outputs the message to ask for input
void EmailInputCk(char inpemailaddr[48], char outmsg[], int na = 0);

// copies validated phone num into input and gives output message
void PhoneNumInputCk(char intelno[12], char outmsg[], int na = 0);

// copies validated genre into input and gives output message
void GenreInputCk(char inpgenre[24], char outmsg[]);

// copies validated refno into input variable, prompting with output message
void InputRefNoCk(char inprefno[10], char outmsg[], int quitoptn = 0);

// returns validated choice into the variable and prompts input using outmsg
char InputYNChoiceCk(char outmsg[]);

// validates the playtime or the time inputted and promts using outmsg, if valpltim it does the validation for the playtime
void InputTimeCk(char inptime[6], char outmsg[], int valpltim = 0);

// validates that the input time is correct (that it is after or before the comp time depending on the state of after) and prompts using the outmsg, additional correct inputs are given as extra params
void InputTimeCompCk(char inptime[6], char outmsg[], char comptim[6], int after = 1);

// validates that the choice is in the options and then returns the valid choice
char InputMultiOptnChoiceCk(char outmsg[], char options[]);

// validates that the input date is correct and prompts using the outmsg, additional correct inputs are given as extra params (adding a ".(otherparams)" for additionals allows dots to be used in validation of date)
void InputDateCk(char inpdate[11], char outmsg[], char additionals[] = "");

// validates that the input date is correct (that it is after or before the comp date depending on the state of after) and prompts using the outmsg, additional correct inputs are given as extra params
void InputDateCompCk(char inpdate[11], char outmsg[], char compdate[11], int after = 1, char additionals[] = "");

// gets the input reference for the inputted event and copies it into the output variable, prompting with outmsg, using valpl to check if there is a playlist for that event, if valpl is -1 then it validates there isn't already a playlist
void InputEventReferenceCheck(char inref[10], char outmsg[], int valpl = 0);

// gets the input reference for the inputted event with the given type and copies it into the output variable, prompting out msg, use valpl to check if there is a playlist for the event
void InputEventTypeReferenceCheck(char inref[10], char outmsg[], char type, char errmsg[], int valpl = 0);

// gets the input reference for the inputted holiday ref and copies it into the output variable, prompting input with outmsg
void InputHolidayReferenceCheck(char inref[10], char outmsg[]);

// gets the input for the event title, prompting the input using outmsg, if exists is 1 then checks that an event exists with the inputted title if not then only checks something is entered
void InputEventTitleCheck(char intitle[64], char outmsg[], int exists = 1);

// gets the input catalogue number and validates that it is a valid number that exists
void InputCatalogueNumberCheck(char incatno[10], char outmsg[]);

// gets the input catalogue number and checks if it is in the input event if pres is 1 then requires a song that is already present to be entered if 0 then requires a new one, prompts input using outmsg
void InputPlaylistCatnoCheck(char incatno[10], char inevno[10], char outmsg[], int pres, int checked = 1);

// gets the input DJ number and validates it, prompts the input using outmsg
void InputDJNumberCk(char indjnoc[10], char outmsg[], int quitoptn = 0);

// gets the input reference number and validates that it is a valid number that exists, prompting using the outmsg and errmsg if it isn't there, refarr is the array of refs and size is number of refs
void InputReferenceNoCheck(char inrefno[10], char refarr[][10], int size, char outmsg[], char errmsg[], int quitoptn = 0);

// gets the input reference number for the guest and validates that it exists, prompting using outmsg
void InputGuestNumberCheck(char inguno[10], char outmsg[], int quitoptn = 0);

// gets the input price from the user and validates it prompting with outmsg
void InputPriceCk(char inprice[7], char outmsg[]);

// does the one in list validation to check for a valid option for the day in the wek prompting using outmsg
void InputDayOfWeekCk(char inoptn[], char outmsg[]);

// gets the valid input hour from the user and prompts input using outmsg
void InputHourCk(char inhour[3], char outmsg[]);

// gets the validated input for a password against the user number and prompts input using outmsg
// if the user number is -1 then checks if the password is new and if is -2 then the password needs to be present 
void InputPasswordCk(char inpass[64], char outmsg[], int userno = -2);

// gets the validated input for a new or existing username and prompts input using outmsg
void InputUsernameCk(char inusrnam[48], char outmsg[], int newusr = 0);

// gets the validated result for a range check prompting input using output message
void InputRangeCk(char input[10], char outmsg[], int min, int max);

// does the range validation on the level of access and made into its own function for readability
void InputLevelOfAccessCk(char inloa[3], char outmsg[]);

// gets the validated file path input from the user prompting input using outmsg
void InputFilePathCk(char infp[128], char outmsg[]);

#pragma endregion

/* ------------------------------
 *          Main Menu
 * ------------------------------ 
 */

int main(int argc, char* argv[])
{
int mainstatus = 0;
ReadBackUserFile();

cin.clear();

//Login();	// goes straight to the login menu
curusr = atoi(usrnos[0]);

while (mainstatus != 7)
	{
	mainstatus = MainMenu();
	clrscr();
	} //endwhile

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

choice = GetMenuChoice(1, 7);

switch(choice)
	{
	case 1:
		{
		DJs();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		Guests();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		Music();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		Admin();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		Events();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		Scheduling();
		clrscr();
		break;
		} //endcase
	case 7:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return choice;
}

#pragma region DJ

void LocateDJ(int idjno)
{
ifstream fin(FileName6, ios::binary);   // opens the file

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
ofstream fout(FileName6, ios::in);  // opens the DJ file to write
fout.seekp(idjno * sizeof(a_dj));   // goes to the DJ's position in the file

// writes the DJ to the file
fout.write((char*)&a_dj, sizeof(a_dj));
fout.close();
}

int GenerateDJNumber()
{
int count;
int exists;
int result = -1;    // starting as -1 so that if the DJ isn't found a null value can be returned

for (count = 1; count < 52; count++)
    {
	exists = DoesDJExist(count);	// checks if the DJ with that number is used
	
	if(exists == 0)
		{
		result = count;
        break;
		} //endif an empty slot is found break and return
    } //endfor loop through all DJs to find empty DJ slot

return result;
}

int DoesDJExist(int indjno)
{
char tflag[2];
int jumpsize = 0;
int exists = 1;

ifstream fin(FileName6, ios::binary);

// getting the size of the jump this is the size of the DJ record - the size of the flag
jumpsize = ((indjno + 1) * sizeof(a_dj)) - sizeof(a_dj.flag);

// getting the flag field in the record
fin.seekg(jumpsize);
fin.get((char*)&tflag, sizeof(tflag));

fin.close();

if(tflag[0] != '1')
	{
	exists = 0;
	} //endif the flag isn't 1

return exists;
}

int GetDJNumberInput(char inpdjno[10], int quitoptn)
{
int state = atoi(inpdjno);
int idjno = atoi(inpdjno);

if ((strcmpi(inpdjno, "q") == 0) && (quitoptn == 1))
	{
    cout << "\nQuitting";
	state = -2;
	} //endif the option is to quit
else if (IsNumber(inpdjno) != 1)
	{
	cout << "\nError: Input Not A Number";
	state = -1;
	} //endif the inputted value isn't a number
else if (RangeCk(idjno, 1, 52, 1) != 0)
	{
	state = -1;
	} //endif the number isn't in the range
else if (DoesDJExist(idjno) != 1)
	{
	cout << "\nError: DJ Doesn't Exist";
	state = -1;
	} //endif the DJ flag isn't 1
else
	{
	LocateDJ(idjno);    // loading the DJ into the DJ struct
	} //endelse all conditions are met for a valid DJ so load it in

return state;
}

void OutputDJ(int idjno)
{
LocateDJ(idjno);
cout << "\nNumber: " << idjno;
cout << "\nName: " << a_dj.djnam;
cout << "\nPerformance Name: " << a_dj.performnam;
cout << "\nMusic Style: " << a_dj.musstyle;
cout << "\nPhone Number: " << a_dj.djtelenum;
cout << "\nEmail Address: " << a_dj.djemailaddr;
}

int ViewDJAccess()
{
clrscr();
cout << "\nView By DJ Number";
cout << "\n=================\n";

OutputDJ(GetUserDJ());

cout << "\nPress any key to return";
getch();
return 0;
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

djchoice = GetMenuChoice(1, 5);

switch(djchoice)
	{
	case 1:
		{
        if(GetGLOA() == 3)
            {
            ViewDJ();
            } //endif the level of access is 3
        else
            {
            ViewDJAccess();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 2:
		{
		if(GetGLOA() == 3)
            {
            AddDJ();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ChangeDJ();
		clrscr();
		break;
		} //endcase
	case 4:
		{
        if(GetGLOA() == 3)
            {
            RemoveDJ();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 5:
		{
		clrscr();
		break;
		} //endcase
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

vidjch = GetMenuChoice(1, 4);

switch(vidjch)
	{
	case 1: 
		{
		ViewDJByName();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ViewByDJNumber();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ViewDJByMusicStyle();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return vidjch;
}

int ViewDJByName()
{
char djname[32];
char tnam[32];
int count = 0;
int compare = 0;
int djnos[10];    // collection of DJs with the same name
int top = 0;

clrscr();
cout << "\nView DJ By Name";
cout << "\n===============\n";

NameInputPresCk(djname, "\nEnter DJ Name: ");   // gets the name input and keeps asking until a valid input is given

ifstream fin(FileName6, ios::binary);

for (count = 1; count < 52; count++)
	{
	// getting the DJ name
	fin.seekg(count * sizeof(a_dj));
	fin.get((char*)&tnam, sizeof(tnam));

	// compares the inputted name to the name in the record
	compare = strcmpi(tnam, djname);

	if(compare == 0) 
		{
        djnos[top++] = count;
		} //endif the DJ has been found then store the number
	} //endfor loop through all DJs in file

fin.close();

if(top == 0)
    {
    cout << "\nError: DJ not found";
    } //endif the final comparison isn't correct

// no else needed here since it won't try and output if it's the same
for(count = 0; count < top; count++)
    {
    if(DoesDJExist(djnos[count]) == 1)
        {
        OutputDJ(djnos[count]);
        } //endif the DJ exists output their details
    } //endfor loop through outputting the DJs

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

InputDJNumberCk(indjno, "\nEnter DJ Number: ");
idjno = atoi(indjno);
OutputDJ(idjno);

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
int top = 0;
int numbers[52];
char key[64];
int ikey;
int j;
int step;
DJ_RECORD key_dj;
DJ_RECORD djdetails[52];

clrscr();
cout << "\nView DJ By Music Style";
cout << "\n======================\n";

GenreInputCk(inpstyle, "\nEnter Music Style: ");
ifstream fin(FileName6, ios::binary);   // opens the file

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

		if(a_dj.flag[0] == '0')
			{
			continue;
			} //endif the DJ doesn't exist continue looping

		// adding the DJ to the stack
		numbers[top] = count;
		strcpy(djdetails[top].djnam, a_dj.djnam);
		strcpy(djdetails[top].performnam, a_dj.performnam);
		strcpy(djdetails[top].musstyle, a_dj.musstyle);
		strcpy(djdetails[top].djtelenum, a_dj.djtelenum);
		strcpy(djdetails[top].djemailaddr, a_dj.djemailaddr);

		top++;
		} //endif
	} //endfor loop through all DJs in file

fin.close();

// insertion sorting the stack
for (step = 1; step < top; step++)
	{
	key_dj = djdetails[step];
	ikey = numbers[step];

	j = step - 1;	// setting first comparison point
	
	// keep shuffling everything to the right until the left is smaller than the right
	while((CompareWordsAlphabetically(key_dj.djnam, djdetails[j].djnam) != -1) && (j >= 0))
		{
		djdetails[j + 1] = djdetails[j];
		numbers[j + 1] = numbers[j];
		--j;
		} //endwhile compare key with each element on left of it until an element smaller than it is found

	// set the found position to the key DJ values
	djdetails[j + 1] = key_dj;
	numbers[j + 1] = ikey;
	} //endfor insertion sort

for (count = 0; count < top; count++)
	{
	cout << "\n\nNumber: " << numbers[count];
	cout << "\nName: " << djdetails[count].djnam;
	cout << "\nPerformance Name: " << djdetails[count].performnam;
	cout << "\nMusic Style: " << djdetails[count].musstyle;
	cout << "\nPhone Number: " << djdetails[count].djtelenum;
	cout << "\nEmail Address: " << djdetails[count].djemailaddr;
	} //endfor loop through and output the stack


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
char tmpnam[48];
char tmpperf[48];
char tmpstyle[32];
char tmptelno[12];
char tmpemail[48];
int idjno;

clrscr();
cout << "\nAdd DJ";
cout << "\n======\n";

idjno = GenerateDJNumber();
LocateDJ(idjno);

NameInputPresCk(tmpnam, "\nEnter DJ Name: ");   // getting input name
EmailInputCk(tmpemail, "\nEnter Email Address: ");  // getting email address input
PhoneNumInputCk(tmptelno, "\nEnter Phone Number: ");  // getting phone number input
NameInputPresCk(tmpperf, "\nEnter DJ Performance Name: ");  // getting input performance name
GenreInputCk(tmpstyle, "\nEnter Music Style: ");  // getting input for music style

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

chandjch = GetMenuChoice(1, 6);

switch(chandjch)
	{
	case 1: 
		{
		ChangeDJName();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ChangeDJPerformanceName();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ChangeDJPhoneNumber();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		ChangeDJEmailAddress();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		ChangeDJMusicStyle();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return chandjch;
}

int ChangeDJName()
{
char tmpdjno[10];
char tmpdjnam[48];
int idjno = -1;

clrscr();
cout << "\nChange DJ Name";
cout << "\n==============\n";

InputDJNumberCk(tmpdjno, "\nEnter DJ Number: ", 1);
if (tmpdjno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(tmpdjno);

cout << "\nDJ Name: " << a_dj.djnam;    // find the old details to display them just to make sure they have the right thing
NameInputPresCk(tmpdjnam, "\nEnter DJ Name: ");   // getting input name

strcpy(a_dj.djnam, tmpdjnam);   // copying the new DJ name into the DJ
WriteDJ(idjno); // updating the DJ record in the file

cout << "\n\nSuccess - Name has been changed\n";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJPerformanceName()
{
char tmpdjno[10];
char tmpdjperfnam[48];
int idjno = -1;

clrscr();
cout << "\nChange DJ Performance Name";
cout << "\n==========================\n";

InputDJNumberCk(tmpdjno, "\nEnter DJ Number: ", 1);
if (tmpdjno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(tmpdjno);

cout << "\nCurrent DJ Performance Name: " << a_dj.performnam;   // find the old details to display them just to make sure they have the right thing
NameInputPresCk(tmpdjperfnam, "\nEnter DJ Performance Name: ");  // getting input performance name
strcpy(a_dj.performnam, tmpdjperfnam);  // copying the new DJ performance name into the DJ
WriteDJ(idjno); // updating the DJ record in the file

cout << "\n\nSuccess - Performance Name has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJPhoneNumber()
{
char tmpdjno[10];
char tmptelno[32];
int idjno = -1;

clrscr();
cout << "\nChange DJ Phone Number";
cout << "\n======================\n";

InputDJNumberCk(tmpdjno, "\nEnter DJ Number: ", 1);
if (tmpdjno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(tmpdjno);

cout << "\nCurrent Phone Number: " << a_dj.djtelenum;   // find the old details to display them just to make sure they have the right thing
PhoneNumInputCk(tmptelno, "\nEnter Phone Number: ");  // getting phone number input

strcpy(a_dj.djtelenum, tmptelno);   // copying the new DJ phone number into the DJ
WriteDJ(idjno); // updating the DJ record in the file

cout << "\n\nSuccess - Phone Number has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJEmailAddress()
{
char tmpdjno[10];
char tmpdjemail[48];
int idjno = -1;

clrscr();
cout << "\nChange DJ Email Address";
cout << "\n=======================\n";

InputDJNumberCk(tmpdjno, "\nEnter DJ Number: ", 1);
if (tmpdjno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(tmpdjno);

cout << "\nDJ Name: " << a_dj.djnam;    // find the old details to display them just to make sure they have the right thing
cout << "\nCurrent Email Address: " << a_dj.djemailaddr;

EmailInputCk(tmpdjemail, "\nEnter Email Address: ");  // getting email address input

strcpy(a_dj.djemailaddr, tmpdjemail);   // copying the new DJ email into the DJ
WriteDJ(idjno); // updating the DJ record in the file

cout << "\n\nSuccess - Email Address has been changed";

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ChangeDJMusicStyle()
{
char tmpdjno[10];
char tmpstyle[24];
int idjno = -1;

clrscr();
cout << "\nChange DJ Music Style";
cout << "\n=====================\n";

InputDJNumberCk(tmpdjno, "\nEnter DJ Number: ", 1);
if (tmpdjno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(tmpdjno);

cout << "\nDJ Name: " << a_dj.djnam;    // find the old details to display them just to make sure they have the right thing
cout << "\nCurrent Music Style: " << a_dj.musstyle;

GenreInputCk(tmpstyle, "\nEnter Music Style: ");  // getting input for music style

strcpy(a_dj.musstyle, tmpstyle);    // copying the new DJ style into the DJ
WriteDJ(idjno); // updating the DJ record in the file

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
int idjno = -1;
char choice;
char tdjnam[48];
int tloc;	// temporary location
char tdate[11];
char outmsg[128] = "\nAre you sure you want to Delete ";

ReadBackEventFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nRemove DJ";
cout << "\n=========\n";

InputDJNumberCk(djnoc, "\nEnter DJ Number: ", 1);
if (djnoc[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit
idjno = atoi(djnoc);

strcpy(tdjnam, a_dj.djnam); // copying in the djname at idjno into the temporary DJ name
cout << "\nDJ to Remove: " << tdjnam;   // find the old details to display them just to make sure they have the right thing

tloc = FindInArray10(evlinkdjno, djnoc, nli);	// finds the DJ in the events links file
GetToday(tdate);	// gets today's date

while(tloc != -1)
	{
	if(DateComp(evdate[tloc], tdate) == 1)
		{
		cout << "\nError: DJ attending events in the future - please remove them from these events before deleting";
		break;
		} //endif there is an event which the DJ is attending in the future

	tloc = FindInArray10(evlinkdjno, djnoc, nli, tloc + 1);	// finds the DJ in the events links file after the current found one
	} //endwhile the DJ is being found in the links file

// creates the output message
strcat(outmsg, tdjnam);
strcat(outmsg, " (y/n): ");
choice = InputYNChoiceCk(outmsg);	 // checking before it get removes the DJ

if(choice == 'y')
	{
	SetDJFlag(0);
	cout << "\n\nSuccess - " << tdjnam << " has been deleted";
	WriteDJ(idjno); // rewrite the DJ so that it has been deleted
	} //endif the choice is yes delete the DJ

cout << "\n\nPress any key to return";
getch();

return 0;
}

#pragma endregion

#pragma region Guest

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
	fin.getline(gugenre[count], sizeof(gugenre[count]));
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
	fout.write((char*)&gugenre[count], strlen(gugenre[count]));
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

guch = GetMenuChoice(1, 5);

switch(guch)
	{
	case 1: 
		{
		ViewGuest();
		clrscr();
		break;
		} //endcase
	case 2:
		{
        if(GetGLOA() == 3)
            {
            AddGuest();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 3:
		{
        if(GetGLOA() == 3)
            {
            ChangeGuest();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 4:
		{
        if(GetGLOA() == 3)
            {
            RemoveGuest();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 5:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return guch;
}

/* ------------------------------
 *          View Guests
 * ------------------------------ 
 */

int ViewGuest()
{
int vistat = 0;
while (vistat != 6)
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
cout << "\n\t5. By Genre";
cout << "\n\t6. Return";

viguch = GetMenuChoice(1, 6);

switch(viguch)
	{
	case 1: 
		{
		ViewGuestByName();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ViewGuestByGuestNumber();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ViewGuestNextAppearance();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		ViewGuestByNextAppearance();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		ViewGuestByGenre();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

NameInputPresCk(ingunam, "\nEnter Guest Name: ");  // getting input guest name
loc = FindInArray48(gunam, ingunam, ngi);   // find the guest name in the guest numbers array

if (loc == -1)
    {
    cout << "\nError: Guest not Found";
    } //endif the guest hasn't been found
else
    {
    OutputGuest(loc);
    } //endelse output the guest

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

InputRefNoCk(inguno, "\nEnter Guest Number: ");	// getting guest number input
loc = FindInArray10(guestno, inguno, ngi);  // find the guest number in the guest numbers array

if (loc == -1)
    {
    cout << "\nError: Guest not Found";
    } //endif the guest hasn't been found
else
    {
    OutputGuest(loc);
    } //endelse output the guest

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

InputRefNoCk(inguno, "\nEnter Guest Number: ");	// getting guest number input
guno = atoi(inguno);

if(nei > 0)
	{
	BubbleEventSortDates(nei);  // sort the events so that it outputs chronologically
	} //endif there are not 0 events

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

if(top > 0)
	{
	OutputGuestEventsTabular(evids, gunos, "GNDaTmCN", top);    // outputs the events in a table
	} //endif there are events for the guest
else
	{
	cout << "\nError: No Events Found";
	} //endelse no events are found
ReadBackEventFile();    // reading the file back again to reverse the sort

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


if(nei > 0)
	{
	BubbleEventSortDates(nei);  // sorting the events chronologically
	} //endif there are not 0 events

for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	if(type == 'G')
		{
		evids[top] = atoi(eventno[count]);
		gunos[top++] = GetScheduleGuestNumber(eventno[count]);
		} //endif found a guest slot
	} //endfor loop through all events anc check if they are a guest slot

if(top > 0)
	{
	OutputGuestEventsTabular(evids, gunos, "GNDaTmCN", top);    // outputs the events in a table
	} //endif there are events for the guests
else
	{
	cout << "\nError: No Events Found";
	} //endelse no events are found
ReadBackEventFile();    // reading the file back again to reverse the sort

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewGuestByGenre()
{
int count;
int loc;
int gulocs[500];
char genre[24];
int top = 0;

ReadBackGuestFile();

clrscr();
cout << "\nView Guest By Genre";
cout << "\n===================\n";

GenreInputCk(genre, "\nEnter Guest Genre: ");

loc = FindInArray24(gugenre, genre, ngi);

if(loc == -1)
	{
	cout << "\nError: No Guests found with that genre";
	} //endif there are no guests with that genre

while(loc != -1)
	{
	gulocs[top++] = loc;
	loc = FindInArray24(gugenre, genre, ngi, loc + 1);	// starting after the previous found record
	} //endwhile loop through all the guests to find those with the correct genre

for(count = 0; count < top; count++)
	{
	OutputGuest(gulocs[top]);
	} //endfor loop through all of the guests outputting them

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
char tmpgunam[48];
char tmpgucontnam[48];
char tmpguconttel[12];
char tmpgucontemail[48];
char tmpguno[10];
char tmpgenre[24];

ReadBackGuestFile();

clrscr();
cout << "\nAdd Guest";
cout << "\n=========\n";

NameInputPresCk(tmpgunam, "\nEnter Guest Name: ");   // getting input guest name

while(FindInArray48(gunam, tmpgunam, ngi) != -1)
    {
    cout << "\nError: There is already a guest with that name";
    NameInputPresCk(tmpgunam, "\nEnter Guest Name: ");   // getting input guest name
    } //endwhile loop though the array to find if there is already a guest with that name

NameInputPresCk(tmpgucontnam, "\nEnter Contact Name: ");   // getting input contact name
PhoneNumInputCk(tmpguconttel, "\nEnter Contact Phone Number: ");  // getting phone number of the contact
EmailInputCk(tmpgucontemail, "\nEnter Contact Email Address: ");  // getting email address of the contact
GenreInputCk(tmpgenre, "\nEnter Guest Genre: ");

GenerateGuestNumber(tmpguno);

cout << "\nGuest Number: " << tmpguno;

// copying the temporary variables into the global file variables
strcpy(guestno[ngi], tmpguno);
strcpy(gunam[ngi], tmpgunam);
strcpy(gucontactnam[ngi], tmpgucontnam);
strcpy(guconttelenum[ngi], tmpguconttel);
strcpy(guemailaddr[ngi], tmpgucontemail);
strcpy(gugenre[ngi], tmpgenre);

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
while (chstat != 6)
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
cout << "\n\t5. Genre";
cout << "\n\t6. Return";

changeguch = GetMenuChoice(1, 6);

switch(changeguch)
	{
	case 1: 
		{
		ChangeGuestName();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ChangeGuestContactName();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ChangeGuestContactPhoneNumber();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		ChangeGuestContactEmailAddress();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		ChangeGuestGenre();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return changeguch;
}

int ChangeGuestName()
{
char inguno[10];
char ingunam[48];
int loc = -1;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Name";
cout << "\n=================\n";

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ", 1);	// gets the inputetd guest number
if(inguno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

loc = FindInArray10(guestno, inguno, ngi);	// finds the guest
cout << "\nCurrent Guest Name: " << gunam[loc]; // showing old name to highlight the changes to be made
NameInputPresCk(ingunam, "\nEnter Guest Name: ");   // getting input guest name

while(FindInArray48(gunam, ingunam, ngi) != -1)
    {
    cout << "\nError: There is already a guest with that name";
    NameInputPresCk(ingunam, "\nEnter Guest Name: ");   // getting input guest name
    } //endwhile loop though the array to find if there is already a guest with that name

strcpy(gunam[loc], ingunam);    // copying inputted name into the correct record
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
int loc = -1;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Contact Name";
cout << "\n=========================\n";

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ", 1);	// gets the inputetd guest number
if(inguno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

loc = FindInArray10(guestno, inguno, ngi);	// finds the guest
cout << "\nCurrent Contact Name: " << gucontactnam[loc];    // showing old name to highlight the changes to be made
NameInputPresCk(ingucontnam, "\nEnter Contact Name: ");   // getting input of the new contact name

strcpy(gucontactnam[loc], ingucontnam); // copying across the new contact name
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
int loc = -1;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Contact Phone Number";
cout << "\n=================================\n";

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ", 1);	// gets the inputetd guest number
if(inguno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

loc = FindInArray10(guestno, inguno, ngi);	// finds the guest
cout << "\nCurrent Phone Number: " << guconttelenum[loc];   // showing the current number to compare with new input
PhoneNumInputCk(inguphonenum, "\nEnter Contact Phone Number: ");  // getting phone number of the contact

strcpy(guconttelenum[loc], inguphonenum);   // copies input into file
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
int loc = -1;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Email Address";
cout << "\n==========================\n";

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ", 1);	// gets the inputetd guest number
if(inguno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

loc = FindInArray10(guestno, inguno, ngi);	// finds the guest
cout << "\nCurrent Email Address: " << guemailaddr[loc];    // outputs the current email address
EmailInputCk(inguemail, "\nEnter Contact Email Address: ");  // getting new email address of the contact

strcpy(guemailaddr[loc], inguemail);    // copies input into file
cout << "\nSuccess - Email Address has been changed\n";

ReWriteGuestFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeGuestGenre()
{
char inguno[10];
char ingenre[24];
int loc = -1;

ReadBackGuestFile();

clrscr();
cout << "\nChange Guest Genre";
cout << "\n==================\n";

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ", 1);	// gets the inputetd guest number
if(inguno[0] == 'q')
	{
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

loc = FindInArray10(guestno, inguno, ngi);	// finds the guest
cout << "\nGuest Name: " << gunam[loc]; // showing old name to highlight the changes to be made
cout << "\nCurrent Genre: " << gugenre[loc];

GenreInputCk(ingenre, "\nEnter Guest Genre: ");

strcpy(gugenre[loc], ingenre);    // copying inputted genre into the correct record
cout << "\nSuccess - Genre has been changed\n";

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
char innam[48];
int find = 0;
int del = 0;
char outmsg[128] = "\nAre you sure you want to Delete ";
char guestname[48];
char choice;
int count;
char tdate[11];
int tguno;
char type;

ReadBackGuestFile();
ReadBackEventFile();

clrscr();
cout << "\nRemove Guest";
cout << "\n============\n";

NameInputPresCk(innam, "\nEnter Guest Name: ");   // gets guest name
find = FindInArray48(gunam, innam, ngi);	// finds the guest name in the guest file

if(find == -1)
    {
    cout << "\nError: Guest Not found\nPress any key to return";
	getch();
    return 0;
    } //endif the guest hasn't been found

strcpy(guestname, gunam[find]);	// copy the name into a temp variable so can be used for outputting later on
GetToday(tdate);	// gets today's date

for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	if(type == 'G')
		{
		tguno = GetScheduleGuestNumber(eventno[count]);

		if((tguno == atoi(guestno[find])) && (DateComp(evdate[count], tdate) == 1))
			{
			cout << "\nError: Guest scheduled for a future appearance - remove the appearance to delete the guest";
			cout << "\nPress any key to return";
			getch();
			return 0;
			} //endif there is a guest event with that guest and it is after the current date
		} //endif found a guest slot
	} //endfor loop through all events anc check if they are a guest slot

strcat(outmsg, guestname);	// completing the prompt message by copying in the needed data
strcat(outmsg, " (y/n): ");
choice = InputYNChoiceCk(outmsg);	// getting the choice

if((choice == 'n') || (choice == 'N'))
	{
	cout << "\nDeletion has been cancelled" << "\nPress any key to return";
	getch();
	return 0;
	} //endif the choice is no return as not needed to keep going

for (del = find; del < ngi; del++)
	{
	strcpy(guestno[del], guestno[del+1]);
	strcpy(gunam[del], gunam[del+1]);
	strcpy(gucontactnam[del], gucontactnam[del+1]);
	strcpy(guconttelenum[del], guconttelenum[del+1]);
	strcpy(guemailaddr[del], guemailaddr[del+1]);
	strcpy(gugenre[del], gugenre[del+1]);
	} //endfor loop to shuffle all the guests back one space

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
		break;
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
	// adds the data (in the found field) for size songs to the outdata
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
int sec = 0;
int min = 0;
int res = 0;

sscanf(playtime, "%d:%d", &min, &sec);  // getting the mins and seconds
res = sec + (60 * min); // converting min to seconds and adding to secs

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

musicchoice = GetMenuChoice(1, 3);

switch(musicchoice)
	{
	case 1: 
		{
		Catalogue();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		Playlists();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

catchoice = GetMenuChoice(1, 5);

switch(catchoice)
	{
	case 1: 
		{
		ViewCatalogue();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		CatalogueAddMusic();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		CatalogueChangeMusic();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		CatalogueRemoveMusic();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

viewcatch = GetMenuChoice(1, 6);

switch(viewcatch)
	{
	case 1: 
		{
		ViewCatalogueByCatalogueNumber();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ViewCatalogueByTitle();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ViewCatalogueByArtist();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		ViewCatalogueByGenre();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		ViewCatalogueByPopularity();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number
loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array

if(loc == -1)
    {
    cout << "\nError: Catalogue Number Not Found";
    } //endif the catalogue number isn't found
else
    {
    OutputSongLinear(loc);
    } //endelse output the song at the location

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

NameInputPresCk(tmptitle, "\nEnter Song Title: ");   // getting song title
loc = FindInArray48(mutitle, tmptitle, nmi);    // finds the title in the array

if(loc == -1)
    {
    cout << "\nError: No Songs with the title " << tmptitle << " found";
    } //endif the song title hasn't been found

while(loc >= 0)
    {
    songs[top++] = atoi(mucatno[loc]);  // adding the last found song to the stack
    loc = FindInArray48(mutitle, tmptitle, nmi, loc + 1);   // finds the title in the array from the starting location of loc + 1
    } //endwhile songs are found add them to the stack and find the next one

if (top != 0)
    {
    OutputSongs(songs, "IdTiPlArGePuCh", top);
    } //endif songs have been found output the contents of the stack, outputting the song details according to the format

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

NameInputPresCk(tmpartist, "\nEnter Song Artist: ");   // getting song artist
loc = FindInArray48(muartist, tmpartist, nmi);  // finds the first song by that artist

if(loc == -1)
    {
    cout << "\nError: No Songs by the artist " << tmpartist << " found";
    } //endif the song artist hasn't been found

while(loc >= 0)
    {
    // adding the song ID to the stack
    songs[top++] = atoi(mucatno[loc]);

    // finds the artist in the array from the starting location of loc + 1
    loc = FindInArray48(muartist, tmpartist, nmi, loc + 1);
    } //endwhile songs have been found output the contents of the stack, outputting the song details according to the format

if(top > 0)
	{
	OutputSongs(songs, "IdTiPlArGePuCh", top);
	} //endif songs are found

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

GenreInputCk(tmpgenre, "\nEnter Song Genre: ");  // getting input for the genre
loc = FindInArray24(mugenre, tmpgenre, nmi);    // finds the first song in the inputted genre

if(loc == -1)
    {
    cout << "\nError: No Songs with the " << tmpgenre << " genre found";
    } //endif the song genre hasn't been found

while(loc >= 0)
    {
    songs[top++] = atoi(mucatno[loc]);  // adding song to the stack
    loc = FindInArray24(mugenre, tmpgenre, nmi, loc + 1);   // finds the genre in the array from the starting location of loc + 1
    } //endwhile songs with the genre have been found in the search

if(top > 0)
	{
	OutputSongs(songs, "TiPlArGePuIdCh", top);  // outputting the title, playtime, artist, genre, publisher, check and ID of songs
	} //endif songs are found

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewCatalogueByPopularity()
{
int count;
int outcatnos[50];
int* ifreqs;    // creating a pointer to the first part of the array

ReadBackMusicFile();

clrscr();
cout << "\nView Catalogue By Popularity";
cout << "\n============================\n";

if(nmi == 0)
	{
	cout << "\n\nPress any key to return";
	getch();
	return 0;
	} //endif the catalogue is empty

ifreqs = new int[nmi];  // creating the new array of size nmi

for(count = 0; count < nmi; count++)
	{
	ifreqs[count] = atoi(mufreq[count]);
	} //endfor loop throught the frequencies and adding them to a list

ExtendedBubbleSort(ifreqs, nmi, SwapSongs); // sorting the music by its frequency

for(count = 0; (count < nmi) && (count < 50); count++)
	{
	outcatnos[nmi - 1 - count] = atoi(mucatno[count]);  // sorts smallest to largest therefore reverse the list
	} //endfor loop adding the top 50 songs (or until end of catalogue) to an array to be outputted

OutputSongs(outcatnos, "RaFrTiPlArGeId", count);    // outputting all of the songs
ReadBackMusicFile();    // reading back again to restore the file back to it's origional state

cout << "\n\nPress any key to return";
getch();

delete ifreqs;  // deleting the array after usage
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
char tmppub[48];
char tmpplaytime[6];
int search;
int cont = 0;

ReadBackMusicFile();

clrscr();
cout << "\nAdd Music";
cout << "\n=========\n";

while(cont == 0)
	{
	NameInputPresCk(tmptitle, "\nEnter Song Title: ");   // getting input title
	NameInputPresCk(tmpartist, "\nEnter Artist: ");   // getting input artist
	InputTimeCk(tmpplaytime, "\nEnter Playtime: ", 1);	// getting the playtime
	NameInputPresCk(tmppub, "\nEnter Publisher: ");   // getting input publisher
	GenreInputCk(tmpgenre, "\nEnter Genre: ");	// getting the input genre
	search = FindInArray48(mutitle, tmptitle, nmi);	// finds the title in the music catalogue

	if((search != -1) && (strcmpi(muartist[search], tmpartist) == 0))
		{
		cout << "\nError: Song already exists";
		continue;	// restarts the loop
		} //endif there is a song with the same title and artist the song already exists

	cont = 1;	// if reaches end then will be correct and unique
	} //endwhile loop until should continue

GenerateCatalogueNumber(tmpcatno);	// generating the catalogue number
cout << "\nCatalgoue Number: " << tmpcatno;

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
int changestat = 0;
while (changestat != 6)
	{
	changestat = CatalogueChangeMusicMenu();
	clrscr();
	} //endwhile

return 0;
}

int CatalogueChangeMusicMenu()
{
int chmuchoice;

clrscr();

cout << "\n\tChange Music Menu";
cout << "\n\t=================\n";
cout << "\n\t1. Title";
cout << "\n\t2. Artist";
cout << "\n\t3. Playtime";
cout << "\n\t4. Genre";
cout << "\n\t5. Check";
cout << "\n\t6. Return";

chmuchoice = GetMenuChoice(1, 6);

switch(chmuchoice)
	{
	case 1: 
		{
		ChangeMusicTitle();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ChangeMusicArtist();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ChangeMusicPlaytime();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		ChangeMusicGenre();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		ChangeMusicCheck();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return chmuchoice;
}

int ChangeMusicTitle()
{
char tmpcatno[10];
int loc = 0;
char ntitle[48];

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Title";
cout << "\n==================\n";

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number

loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array

if(loc == -1)
    {
    cout << "\nError: Catalogue Number Not Found";
    } //endif the catalogue number isn't found
else
	{
	cout << "\nCurrent Title: " << mutitle[loc]; // getting the current title
	NameInputPresCk(ntitle, "\nEnter Song Title: ");   // getting new title
	strcpy(mutitle[loc], ntitle); // copying new title into old title

	ReWriteMusicFile();

	cout << "\nSuccess - Title has been Changed\n";
	} //endelse the number has been found

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicArtist()
{
char nartist[48];
char tmpcatno[10];
int loc = 0;

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Artist";
cout << "\n===================\n";

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number
loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array

if(loc == -1)
    {
    cout << "\nError: Catalogue Number Not Found";
    } //endif the catalogue number isn't found
else
	{
	cout << "\nCurrent Artist: " << muartist[loc];
	NameInputPresCk(nartist, "\nEnter Artist: ");   // getting new title

	strcpy(muartist[loc], nartist); // copying new artist into old artist
	ReWriteMusicFile();

	cout << "\nSuccess - Artist has been Changed\n";
	} //endelse the catalogue number has been found

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

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number
loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array

if(loc == -1)
    {
    cout << "\nError: Catalogue Number Not Found";
    } //endif the catalogue number isn't found
else
	{
	cout << "\nCurrent Playtime: " << muplaytime[loc];
	InputTimeCk(nplaytim, "\nEnter Playtime: ", 1);	// getting the playtime
	strcpy(muplaytime[loc], nplaytim); // copying new playtime into old playtime
	ReWriteMusicFile();

	cout << "\nSuccess - Playtime has been Changed\n";
	} //endelse the catalogue number has been found

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

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number
loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array

if(loc == -1)
    {
    cout << "\nError: Catalogue Number Not Found";
    } //endif the catalogue number isn't found
else
	{
	cout << "\nCurrent Genre: " << mugenre[loc];
	GenreInputCk(ngenre, "\nEnter Genre: "); // getting new genre
	strcpy(mugenre[loc], ngenre); // writing the variable
	ReWriteMusicFile();

	cout << "\nSuccess - Genre has been Changed\n";
	} //endelse the catalogue number has been found

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeMusicCheck()
{
char tmpcatno[10];
int loc = 0;
char choice[2];
int fpos;	// first position of the song in the playlists file

ReadBackMusicFile();

clrscr();
cout << "\nChange Music Check";
cout << "\n==================\n";

InputRefNoCk(tmpcatno, "\nEnter Catalogue Number: ");	// getting catalogue number
loc = FindInArray10(mucatno, tmpcatno, nmi);    // finds the catalogue number in the array
fpos = FindInArray10(pllinkcatno, tmpcatno, nmi);	// finds the song in the playlists

if(fpos != -1)
	{
	cout << "\nError: This song has been used in playlists - it must be removed from all before the check can be changed";
	} //endif the song has been found 
else
	{
	cout << "\nCurrent Check: " << mucheck[loc];
	choice[0] = InputMultiOptnChoiceCk("\nEnter Check: ", "yn");	// gets the choice input for the check
	choice[1] = '\0';
	strcpy(mucheck[loc], choice); // writing the variable

	cout << "\nSuccess - The check has been Changed\n";
	ReWriteMusicFile();
	} //endelse the song hasn't been found

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
char outmsg[128] = "\nAre you sure you want to Delete ";
char choice;

ReadBackPlaylistFile();
ReadBackMusicFile();

clrscr();
cout << "\nRemove Music";
cout << "\n============\n";

InputRefNoCk(innum, "\nEnter Catalogue Number: "); // get song number
find = FindInArray10(mucatno, innum, nmi);	// finds the song in the catalogue

if(FindInArray10(pllinkcatno, innum, npi) != -1)
	{
	cout << "\nError: Song still in playlists - cannot delete song until removed from all playlists\nPress any key to return";
	getch();
	return 0;
	} //endif song is still in playlists

strcpy(songtitle, mutitle[find]);	// copying the title into a temp var for the final output message
strcat(outmsg, songtitle);	// creating the output message
strcat(outmsg, " (y/n): ");
choice = InputYNChoiceCk(outmsg);	// confirmaiton required to reduce mistakes

if(choice != 'y')
	{
	cout << "\nDeletion cancelled\nPress any key to return";
	getch();
	return 0;
	} //endif shouldn't remove

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
	} //endfor loop through all the songs and shuffle them to the right


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
}

void RemovePlaylistEntriesByEvent(char inevno[10])
{
int find = 0;

while(find != -1)
	{
	find = FindInArray10(pllinkevno, inevno, npi);
	
	// removes the link with that event number and catalogue number
	RemovePlaylistEntry(inevno, pllinkcatno[find]);
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

int FindSongInPlaylist(char inevno[10], char incatno[10])
{
int loc;

loc = FindInArray10(pllinkevno, inevno, npi);

while(loc != -1)
	{
	if(strcmpi(pllinkcatno[loc], incatno) == 0)
		{
		break;
		} //endif the song has been found in the playlist break out the loop

	loc = FindInArray10(pllinkevno, inevno, npi, loc + 1);	// finds the location of the next entry in the playlist starting from the next record
	} //endwhile the end of the playlist isn't reached

return loc;
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

playlistschoice = GetMenuChoice(1, 5);

switch(playlistschoice)
	{
	case 1: 
		{
		ViewPlaylist();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		CreatePlaylist();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		EditPlaylist();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		RemovePlaylist();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return playlistschoice;
}

/* ------------------------------
 *         View Playlists
 * ------------------------------ 
 */

int ViewPlaylist()
{
char inpevid[64];
char inevref[10];
int loc = 0;
int top = 0;
int plids[1024];
int pldur;

ReadBackPlaylistFile();
ReadBackMusicFile();
ReadBackEventFile();

clrscr();
cout << "\nView Playlist";
cout << "\n=============\n";

cout << "\nEnter Event Title or Reference: ";
cin.getline(inpevid, 64);

if(IsNumber(inpevid) == 1)
	{
	strncpy(inevref, inpevid, 10);	// copying the input into the reference whilst shrinking it to the correct size
	// BUG: null terminator errors maybe
	loc = FindInArray10(eventno, inevref, nei); // finds the event in the event file
	} //endif the inputted identifier is a reference
else
	{
	loc = FindInArray64(evtitle, inpevid, nei);
	} //endelse find the event title in the events

if(loc == -1)
	{
	cout << "\nError: Event not found\nPress any key to return";
	getch();
	return 0;
	} //endif the event not found exit the program

cout << "\nEvent Title: " << evtitle[loc] << '\n';	// outputting the title for the user
strcpy(inevref, eventno[loc]);	// copying the reference into the input

pldur = CalculatePlaylistDuration(inevref);	// calculating the playlists' duration 
loc = FindInArray10(pllinkevno, inevref, npi); // finding the playlist

if(loc == -1)
	{
	cout << "\nError: Playlist doesn't exist\nPress any key to return";
	getch();
	return 0;
	} //endif the playlist doesn't exist

printf("\nPlaylist Duration: %.2d:%.2d\n\n", pldur/60, pldur % 60);	// giving an output message for the user about the duration of the playlist

while(loc != -1)
	{
	loc = FindInArray10(pllinkevno, inevref, npi, loc + 1); // starts at loc + 1 so it doesn't repeat itself
	plids[top++] = atoi(pllinkcatno[loc]); // adds the catno to the list of catnos and increments the top of the stack
	} //endwhile songs can be found add them to the songidlist

OutputSongs(plids, "TiArPlId", top); // outputs all of the songs tabularly

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

int PlaylistDurationCheck(char evno[10], int pldur, int output)
{
char ending[64];
int evloc;
int evduri;
int durdiff;
int curdur = pldur;
int cdurmin;

evloc = FindInArray10(eventno, evno, nei);	// finds the event in the event file
evduri = atoi(evdur[evloc]) * 60;	// gets the duration of the event in mins

if(pldur == 0)
	{
	curdur = CalculatePlaylistDuration(evno);
	} //endif there is no input duration

// gets the difference in the duration of the playlist and the event
cdurmin = curdur / 60;;
durdiff = evduri - cdurmin;

if(output == 1)
	{
	DurationEnding(ending, durdiff);
	printf("\nPlaylist Duration: %.2d:%.2d\nRequired Duration: %d:00\n%s\n", cdurmin, curdur % 60, evduri, ending);
	} //endif should output

if(durdiff != 0)
	{
	if(curdur == 0)
		{
		curdur = -1;
		} //endif the current duration is 0
	else
		{
		curdur = -abs(curdur);
		} //endelse the playlist isn't empty
	} //endif fails the check

return curdur;
}

int CreatePlaylist()
{
char inevref[10];
char incatno[10];
char ending[64];
char choice = 'y';	// default choice is yes to start the loop
char adch;
int evduri;
int durdiff;
int muloc = -1;
int curdur = 0;
int cdurmin;

ReadBackPlaylistFile();
ReadBackMusicFile();
ReadBackEventFile();

clrscr();
cout << "\nCreate Playlist";
cout << "\n===============\n";

InputEventReferenceCheck(inevref, "\nEnter Event Number: ", -1); // gets the input reference and validates the event exists and that there isn't already a playlist
curdur = abs(PlaylistDurationCheck(inevref));	// getting the duration of the playlist

while(choice == 'y')
	{
	InputPlaylistCatnoCheck(incatno, inevref, "\nEnter Catalogue Number: ", 0);	// gets a valid input 
	muloc = FindInArray10(mucatno, incatno, nmi); // finds the song
	cout << "\nTitle: " << mutitle[muloc];	// outputs title of the song

	adch = InputYNChoiceCk("\nWould you like to add this song (y/n): ");	// gets the choice of what to do

	if (adch == 'y')
		{
		curdur += ConvertPlaytimeToSecconds(muplaytime[muloc]); // adding the new song's duration to the current playlist duration
		AddPlaylistEntry(inevref, incatno); // adds the song to the playlist
		PlaylistDurationCheck(inevref, curdur);	// checking the playlists duration
		} //endif the song should be added
	
	choice = InputYNChoiceCk("\nContinue adding songs (y/n): ");
	} //endwhile should continue adding

ReWritePlaylistFile();
ReWriteMusicFile();

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

editplaylistchoice = GetMenuChoice(1, 3);

switch(editplaylistchoice)
	{
	case 1: 
		{
		AddMusic();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		RemoveMusic();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

InputEventReferenceCheck(inevref, "\nEnter Event Number: ", 1);	// gets the valid input reference for the event
InputPlaylistCatnoCheck(incatno, inevref, "\nEnter Catalogue Number: ", 0);	// gets a valid catalogue number which isn't in the playlist 
AddPlaylistEntry(inevref, incatno);	// adds the song to the playlist
choice = InputYNChoiceCk("\nContinue adding songs (y/n): ");	// asks if should continue adding songs

while(choice == 'y')
	{
	InputPlaylistCatnoCheck(incatno, inevref, "\nEnter Catalogue Number: ", 0);	// gets a valid catalogue number which isn't in the playlist 
	AddPlaylistEntry(inevref, incatno);	// adds the song to the playlist
	choice = InputYNChoiceCk("\nContinue adding songs (y/n): ");	// asking if should continue adding
	} //endwhile should continue adding

ReWritePlaylistFile();
ReWriteMusicFile();

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

InputEventReferenceCheck(inevref, "\nEnter Event Number: ", 1);	// gets the valid input reference for the event
InputPlaylistCatnoCheck(incatno, inevref, "\nEnter Catalogue Number: ", 1);	// gets a valid catalogue number which is in the playlist 
RemovePlaylistEntry(inevref, incatno);	// removing the song from the playlist

ReWritePlaylistFile();
ReWriteMusicFile();

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
char choice;

ReadBackMusicFile();
ReadBackEventFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nRemove Playlist";
cout << "\n===============\n";

InputEventReferenceCheck(evno, "\nEnter Event Number: ", 1);	// gets the valid input reference for the event
choice = InputYNChoiceCk("\nWould you like to remove the playlist from the events it is in (y/n): ");

if(choice == 'y')
	{
	RemovePlaylistEntriesByEvent(evno);	// removing the playlist from all of the events it is on
	cout << "\nSuccess - Playlist removed";

	ReWritePlaylistFile();
	ReWriteMusicFile();
	} //endif confirmed removal

cout << "\nPress any key to return";
getch();

return 0;
}

#pragma endregion

#pragma region Admin

int ReadBackUserFile()
{
int count;
ifstream fin(FileName8, ios::binary);
fin.read((char*)&nuc, sizeof(nuc));
sscanf(&nuc[0], "%d", &nui);

for(count = 0; count < nui; count++)
    {
    fin.getline(usrnos[count], sizeof(usrnos[count]));
    fin.getline(usernames[count], sizeof(usernames[count]));
    fin.getline(passwords[count], sizeof(passwords[count]));
    fin.getline(loas[count], sizeof(loas[count]));
    } //endfor read all the stuff


fin.close();
return 0;
}

int ReWriteUserFile()
{
int count;
ofstream fout(FileName8, ios::binary);
fout.write((char*)&nuc, sizeof nuc);

for(count = 0; count < nui; count++)
    {
	fout.write((char*)&usrnos[count], strlen(usrnos[count]));
    fout.write("\n", 1);
    fout.write((char*)&usernames[count], strlen(usernames[count]));
    fout.write("\n", 1);
    fout.write((char*)&passwords[count], strlen(passwords[count]));
    fout.write("\n", 1);
    fout.write((char*)&loas[count], strlen(loas[count]));
    fout.write("\n", 1);
    } //endfor writing all of the stuff

fout.close();
return 0;
}

int GetUserDJ() 
{
return curusr;
}

int GetGLOA()
{
char gusrno[10];
int loc;

itoa(curusr, gusrno, 10);	// converting current user ID to a string
loc = FindInArray10(usrnos, gusrno, nui);	// finding the current user in the file
return atoi(loas[loc]);	// returning the level of access converted to an integer
}

int Login()
{
char inusrnam[48];
char inpasswrd[64];
int usrloc;

ReadBackUserFile();

InputUsernameCk(inusrnam, "\nEnter username: ");
usrloc = FindInArray48(usernames, inusrnam, nui);	// finds the username
InputPasswordCk(inpasswrd, "\nEnter password: ", atoi(usrnos[usrloc]));	// gets password for the user	

curusr = atoi(usrnos[usrloc]);	// getting the number of the user

return 1;
}

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

adminchoice = GetMenuChoice(1, 6);

switch(adminchoice)
	{
	case 1:
		{
        if(GetGLOA() == 3)
            {
            AddUser();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ChangeUser();
		clrscr();
		break;
		} //endcase
	case 3:
		{
        if(GetGLOA() == 3)
            {
            RemoveUser();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 4:
		{
        if(GetGLOA() == 3)
            {
            Backup();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 5:
		{
        if(GetGLOA() == 3)
            {
            Recovery();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return adminchoice;
}

/* ------------------------------
 *          Add User
 * ------------------------------ 
 */


int AddUser()
{
char username[48];
char password[64];
char inpdjnoc[10];
char loa[3];

clrscr();
cout << "\nAdd User";
cout << "\n========\n";

InputUsernameCk(username, "\nEnter Username: ", 1);
InputPasswordCk(password, "\nEnter Password: ", -1);
InputDJNumberCk(inpdjnoc, "\nEnter Associated DJ: ");
InputLevelOfAccessCk(loa, "\nEnter Access Level: ");

// copying all of the inputs into the main vars
strcpy(usernames[nui], username);
strcpy(passwords[nui], password);
strcpy(usrnos[nui], inpdjnoc);
strcpy(loas[nui], loa);

nui = nui + 1;
itoa(nui, nuc, 10);
ReWriteUserFile();

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
int changstat = 0;
while (changstat != 4)
	{
	changstat = ChangeUserMenu();
	clrscr();
	} //endwhile

return 0;
}

int ChangeUserMenu()
{
int chusrchoice;

clrscr();

cout << "\n\tChange User Menu";
cout << "\n\t================\n";
cout << "\n\t1. Username";
cout << "\n\t2. Password";
cout << "\n\t3. Access Level";
cout << "\n\t4. Return";

chusrchoice = GetMenuChoice(1, 4);

switch(chusrchoice)
	{
	case 1: 
		{
		ChangeUserUsername();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		ChangeUserPassword();
		clrscr();
		break;
		} //endcase
	case 3:
		{
        if(GetGLOA() == 3)
            {
            ChangeUserAccessLevel();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 4:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return chusrchoice;
}

int ChangeUserUsername()
{
char usrnam[48];
char usrno[10];
int loc;

ReadBackUserFile();

clrscr();
cout << "\nChange Username";
cout << "\n===============\n";

if(GetGLOA() == 3)
	{
	InputUsernameCk(usrnam, "\nEnter Username: ");
	loc = FindInArray48(usernames, usrnam, nui);
	} //endif the level of access is admin
else
	{
	itoa(curusr, usrno, 10);	// converting the user number to a string
	loc = FindInArray10(usrnos, usrno, nui);	// finding the user in the array
	strcpy(usrnam, usernames[loc]);
	} //endelse copy the username of current user in

cout << "\nCurrent Username: " << usrnam;
InputUsernameCk(usrnam, "\nEnter New Username: ", 1);	// should get a new unique username

strcpy(usernames[loc], usrnam);	// copying new username into old username

cout << "\n\nSuccess - Username has been changed\n";

ReWriteUserFile();
cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeUserPassword()
{
char usrnam[48];
char passwrd[64];
char passwrd2[64];
char usrno[10];
int cont = 0;
int loc;

ReadBackUserFile();

clrscr();
cout << "\nChange Password";
cout << "\n===============\n";

if(GetGLOA() == 3)
	{
	InputUsernameCk(usrnam, "\nEnter Username: ");
	loc = FindInArray48(usernames, usrnam, nui);
	} //endif the level of access is admin
else
	{
	itoa(curusr, usrno, 10);	// converting the user number to a string
	loc = FindInArray10(usrnos, usrno, nui);	// finding the user in the array
	strcpy(usrnam, usernames[loc]);
	} //endelse copy the username of current user in

InputPasswordCk(passwrd, "\nEnter Password: ", atoi(usrnos[loc]));	// asks for current password

while(cont == 0)
	{
	InputPasswordCk(passwrd, "\nEnter New Password: ", -1);	// asks for new password
	InputPasswordCk(passwrd2, "\nEnter New Password Again: ");	// asks for the 2nd entry of the password
	
	if(strcmpi(passwrd, passwrd2) != 0)
		{
		cout << "\nError: Passwords don't match";
		} //endif the passwords aren't the same
	else
		{
		cont = 1;
		} //endelse the passwords are correct
	} //endwhile loop until double entry is complete

strcpy(passwords[loc], passwrd);	// copying new password into old password
cout << "\n\nSuccess - Password has been changed\n";
ReWriteUserFile();

cout << "\nPress any key to return";
getch();

return 0;
}

int ChangeUserAccessLevel()
{
char usrnam[48];
char passwrd[64];
char nloa[10];
char nloac[3];
int loc;

clrscr();
cout << "\nChange User Access Level";
cout << "\n========================\n";

InputUsernameCk(usrnam, "\nEnter Username: ");
loc = FindInArray48(usernames, usrnam, nui);
cout << "\nAccess Level: " << loas[loc];
InputRangeCk(nloa, "\nEnter New Access Level: ", 1, 3);

strncpy(nloac, nloa, 3);	// copies the first 3 characters of the input into the variable to write to the file
strcpy(loas[loc], nloac);	// copying new level of access into old level of access

cout << "\n\nSuccess - Access Level has been changed\n";
ReWriteUserFile();

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
char usrnam[48];
char outmsg[128];
char inpass[64];
char choice;
int loc;
int count;

clrscr();
cout << "\nRemove User";
cout << "\n===========\n";

InputUsernameCk(usrnam, "\nEnter the username of the user to remove: ");
sprintf(outmsg, "\nAre you sure you want to remove %s (y/n): ", usrnam);	// creating the output message
choice = InputYNChoiceCk(outmsg);

if(choice == 'y')
	{
	InputPasswordCk(inpass, "\nEnter Password: ", -curusr);	// the current user needs to enter their password
	loc = FindInArray48(usernames, usrnam, nui);

	for (count = loc; count < nui; count++)
		{
		strcpy(passwords[count], passwords[count + 1]);        
		strcpy(usernames[count], usernames[count + 1]);        
		strcpy(loas[count], loas[count + 1]);        
		} //endfor loop through all of the users overwriting the user to delete

	nui = nui - 1;
	itoa(nui, nuc, 10);
	ReWriteUserFile();

	cout << "\nSuccess - the user " << usrnam << " has been removed";
	} //endif the choice is to delete


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
char choice;
char command[128];
char inpfp[128];
char outdat[11];
int count;
int nofiles = 8;
char* files[9] = { FileName1, FileName2, FileName3, FileName4, FileName5, FileName6, FileName7, FileName8 };

clrscr();
cout << "\nBackup";
cout << "\n======\n";

choice = InputYNChoiceCk("Would you like to make a new backup (y/n): ");

if(choice == 'y')
	{
	InputFilePathCk(inpfp, "\nEnter Backup File Path: ");
	
	GetToday(outdat);
	// changing the /'s into .'s
	outdat[2] = '.';
	outdat[5] = '.';

	sprintf(inpfp, "%s%s", inpfp, outdat);	// creating the new file path with the directory being the date
	sprintf(command, "mkdir %s > NUL", inpfp);	// copies the command in the given format into the command variable
	system(command);	// creates a directory with the current date as the name
	
	cout << "\nBacking up";
	ProgressBar(0, nofiles, nofiles);
	for(count = 0; count < nofiles; count++)
		{
		sprintf(command, "copy %s %s\\ > NUL", files[count], inpfp);	// copies the command in the given format into the command variable
		system(command);
		ProgressBar(count + 1, nofiles, nofiles);
		} //endfor loop through all of the files and back them up
	
	cout << "\nSuccess - A new backup has been created";
	} //endif should back up the data

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
char choice;
char command[256];
char inpfp[128];
char tmpinpfp[128];
char outmsg[256];
char indat[11];
char indattmp[11];
int count;
int nofiles = 8;
char* files[9] = { FileName1, FileName2, FileName3, FileName4, FileName5, FileName6, FileName7, FileName8 };

clrscr();
cout << "\nRecovery";
cout << "\n========\n";

choice = InputYNChoiceCk("Would you like to recover to a previous version (y/n): ");
InputFilePathCk(inpfp, "\nEnter Backup File Path: ");

sprintf(command, "dir /ad /b %s", inpfp);	// copies the command in the given format into the command variable
system(command);	// outputs the names of all of the directories

InputDateCk(indat, "\nEnter Date to recover to (q to stop): ", ".q");	// getting date
if(indat[0] == 'q')
	{
	cout << "\nQuitting\nPress any key to return";
	getch();
	return 0;
	} //endif should quit

strcpy(indattmp, indat);	// copying the input into a temp var

// changing the slashes to dots
indat[2] = '.';
indat[5] = '.';

sprintf(inpfp, "%s%s\\", inpfp, indat);	// creating the new file path with the directory being the date
sprintf(tmpinpfp, "%s%s", inpfp, FileName1);	// creating the new file path with the directory being the date
ifstream dir(tmpinpfp);
if(dir.good() == 0)
	{
	cout << "\nError: Requested recovery point doesn't exist";
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif the file doesn't exist

sprintf(outmsg, "\nAre you sure you want to recover to %s data after the last backup will be inaccessible (y/n): ", indattmp);
choice = InputYNChoiceCk(outmsg);
if(choice == 'y')
	{
	cout << "\nRecovering";
	ProgressBar(0, nofiles, nofiles);
	for(count = 0; count < nofiles; count++)
		{
		sprintf(command, "copy %s%s > NUL", inpfp, files[count]);	// copies the command in the given format into the command variable
		system(command);
		ProgressBar(count + 1, nofiles, nofiles);
		} //endfor loop through all of the files and back them up
	
	cout << "\n\nSuccess - The system has been recovered to the backup made on " << indattmp;
	} //endif should recover

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

loc = FindInArray10(eventno, evnoc, nei);	// finds location of event in event file

if(strstr(evtitle[loc], "Replay") != NULL)
	{
	type = 'R';
	} //endif replay is in the title
else if(strcmpi(evlocation[loc], "Station") == 0)
	{
	type = 'r';
	} //endelseif checking if it is at the station
else if(strcmpi(evlocation[loc], "Station Repeat"))
	{
	
	} //endelseif the location is station repeating it will be a recurring event
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
}

void RemoveEventLinksEntries(char inevno[10])
{
char tmpdjno[10];
int count = 0;

for(count = 0; count < 52; count++)
	{
	itoa(count, tmpdjno, 10); // converts the count into a string
	RemoveLinksEntry(inevno, tmpdjno); // removes that link
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
}

int GetAttendingDJs(char inevno[10], int outdjids[50], int output)
{
int count;
int compare;
int top = 0;
int tmptop;
int idjno;
char attdjs[50][32];
char slot[32];

for(count = 0; count < nli; count++)
	{
	// checks if there is an event with that event number in the links file
	compare = strcmpi(evlinkevno[count], inevno);

	if(compare == 0)
		{
		idjno = atoi(evlinkdjno[count]);
		LocateDJ(idjno);

		// setting the output array of IDs to have the DJ number in it
		outdjids[top] = idjno;

		// copies the name into the attending DJs
		strcpy(attdjs[top], a_dj.djnam);

		// increments the top of the stack
		top = top + 1;
		} //endif
	} //endfor loop through the array of DJs and finds the event number 

if(top == 0)
	{
	for (count = 1; count < 52; count++)
		{
		GetScheduleSlot(slot, inevno, count);

		if(slot[0] != '*')
			{
			LocateDJ(count);

			// setting the output array of IDs to have the DJ number in it
			outdjids[top] = count;

			// copies the name into the attending DJs
			strcpy(attdjs[top], a_dj.djnam);

			// increments the top of the stack
			top = top + 1;
			} //endif the slot isn't empty add that DJ to the stack
		} //endfor loop through all DJs to find the attending ones on the schedule
	} //endif there are no DJs

if(top == 0)
	{
	top = -1;	
	} //endif the top is still empty set it as -1 as a warning

tmptop = top;

if(output == 1 && tmptop > 0)
	{
	cout << "\nDJs Attending: ";

	while(tmptop > 0)
		{
		// decrement the top pointer
		tmptop = tmptop - 1;

		cout << attdjs[tmptop];

		if(tmptop > 0)
			{
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

int IsDJAttending(char inevno[10], int indjno)
{
int djids[50];
int nodjs;
int isattending = 0;
int loc;

nodjs = GetAttendingDJs(inevno, djids);

if (nodjs != 0)
	{
	loc = FindInArrayInt(djids, indjno, nodjs);

	if(loc != -1)
		{
		isattending = 1;
		} //endif found the DJ in the array
	} //endif there are DJs attending the event

return isattending;
}

int IsRecurringEvent(char inevno[10])
{
int isrecurring = 0;
char output[32];
int itim;
int idat;
int djid;
int loc;

loc = FindInArray10(eventno, inevno, nei);

if (loc == -1)
	{
	isrecurring = -1;	
	} //endif no event was found
else 
	{
	// getting location of event in schedule
	itim = CalculateScheduleTimeIndex(evtime[loc]);
	idat = CalculateScheduleDateIndex(evdate[loc]);
	djid = GetAttendingDJ(inevno);

	GetScheduleSlot(output, idat, itim, djid);

	if(output[1] == 'R')
		{
		isrecurring = 1;
		} //endif the flag is there to say it is a recurring event
	} //endelse if a matching event has been found

if(isrecurring == 0)
	{
	if(GetBaseType(inevno) == 'r')
		{
		isrecurring = 1;
		} //endif the base type is a recurring event
	} //endif the event hasn't been detected as recurring

return isrecurring;
}

void OutputEvent(int date, int time, int djid)
{
int evno;
char evnoc[10];

evno = GetScheduleEventNumber(date, time, djid);

// converts the number to a string
itoa(evno, evnoc, 10);

OutputEvent(evnoc);
}

void OutputEvent(char evno[10])
{
int loc;
int guloc;
int duri;
int durday;
int guno;
int day;
char daysofweek[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
char gunoc[10];
char edate[11];
char etime[6];
int attdjs[50];
char slottype;

loc = FindInArray10(eventno, evno, nei);
slottype = GetBaseType(evno);  // gets the slot type for the switch

// assume the type is external event if it isn't on the schedule
if((slottype == '*') && (strcmpi(evlocation[loc], "") != 0))
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

		CalculateEndTime(evtime[loc], evdur[loc], etime);
		cout << "\nEnd Time: " << etime;
		GetAttendingDJs(eventno[loc], attdjs, 1);   // outputs the attending DJs
		break;
		} //endcase
	case 'r':
		{
		day = FindDayOnDate(evdate[loc]);
		cout << "\nShow Title: " << evtitle[loc];
		cout << "\nDate: " << evdate[loc] << " (Recurring on " << daysofweek[day] << ")";	// output what day it is recurring on
		cout << "\nStart Time: " << evtime[loc];

		CalculateEndTime(evtime[loc], evdur[loc], etime);
		cout << "\nEnd Time: " << etime;
		GetAttendingDJs(eventno[loc], attdjs, 1);   // outputs the attending DJs
		break;
		} //endcase
	case 'G':
		{
		guno = GetScheduleGuestNumber(evno);
		itoa(guno, gunoc, 10);  // convert the guest number to str
		guloc = FindInArray10(guestno, gunoc, ngi);

		cout << "\nGuest Name: " << gunam[guloc];
		cout << "\nDate: " << evdate[loc];
		cout << "\nStart Time: " << evtime[loc];

		CalculateEndTime(evtime[loc], evdur[loc], etime);
		cout << "\nEnd Time: " << etime;
		GetAttendingDJs(eventno[loc], attdjs, 1);   // outputs the attending DJs

		break;
		} //endcase
	case 'E':
		{
		cout << "\nEvent Title: " << evtitle[loc];
		cout << "\nDescription: " << evdescription[loc];
		cout << "\nDate: " << evdate[loc];
		cout << "\nStart Time: " << evtime[loc];

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

		GetAttendingDJs(eventno[loc], attdjs, 1);   // outputs the attending DJs
		break;
		} //endcase
	case 'R':
		{
		// To-Do: Account for this case RIGHT HERE!!!
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
			}//endif
		else
			{
			cout << "N";
			}//endelse

		cout << '\n';
		break;
		} //encase
	case '*':
		{
		cout << "\nUndefined Type";
		break;
		} //endcase
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

void UpdateRecurrringEvents(char date[11])
{
int count;
char type;
int dati;
int evdatloc;	// event date location
int daysaway;	// num of days away from inputted date
char tmpdat[11];

strcpy(tmpdat, date);

GetClosestMonday(tmpdat);	// moves the date to the closest Monday
dati = CalculateScheduleDateIndex(tmpdat);

for(count = 0; count < nei; count++)
	{
	type = GetBaseType(eventno[count]);
	if(type == 'r')
		{
		evdatloc = CalculateScheduleDateIndex(evdate[count]);
		daysaway = evdatloc - dati;

		if(daysaway <= -7)
			{
			AddDays(evdate[count], (floor(abs(daysaway) / 7) * 7));	// getting the absolute amount of weeks away and adding that many days
			} //endif is over a week before
		} //endif is a recurring event
	}
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

BubbleEventSortDates(size - 1); // recursively calling the sort
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

eventschoice = GetMenuChoice(1, 6);

switch(eventschoice)
	{
	case 1: 
		{
		ViewEvents();
		clrscr();
		break;
		} //endcase
	case 2:
		{
        if(GetGLOA() == 3)
            {
            AddEvent();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 3:
		{
        if(GetGLOA() == 3)
            {
            ChangeEvents();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 4:
		{
        if(GetGLOA() == 3)
            {
            RemoveEvents();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 5:
		{
        AllocateDJs();
		clrscr();
		break;
		} //endcase
	case 6:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

vieweventschoice = GetMenuChoice(1, 4);

switch(vieweventschoice)
	{
	case 1: 
		{
		ViewEventsByEventReference();
		clrscr();
		break;
		} //endcase
	case 2: 
		{
		ViewEventsByDate();
		clrscr();
		break;
		} //endcase
	case 3: 
		{
		ViewEventsByTitle();
		clrscr();
		break;
		} //endcase
	case 4: 
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return vieweventschoice;
}

int ViewEventsByEventReference()
{
char inevno[10];
int loc;
char today[11];

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Event Reference";
cout << "\n==============================\n";

InputEventReferenceCheck(inevno, "\nEnter Event Reference: ");	// gets a valid input reference
OutputEvent(inevno);	// outputs the event

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewEventsByDate()
{
int count;
int evid[500];
char inpdat[12];
char choice;
int loc = 0;
int top = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Date";
cout << "\n===================\n";

InputDateCk(inpdat, "\nEnter Date or View From Current Week (C): ", "C");

if (inpdat[0] == 'C')
	{
	choice = 'C';
	inpdat[0] = '\0';

	GetToday(inpdat);
	GetClosestMonday(inpdat);
	} //endif the input date is the current week then it finds the closest Monday to that

UpdateRecurrringEvents(inpdat);
BubbleEventSortDates(nei);	// can still sort as a binary search can then be employed to locate the events easier
loc = BinaryDateSearch(evdate, inpdat, 0, nei);	// gets closest event near the inputted date

// gets the closest events, abs(loc) in case there is not an event on that date
for(count = abs(loc); count < nei; count++)
	{
	if(evtitle[count][0] == '\0')
		{
		continue;
		} //endif there is no title then skip the event
	
	if (choice != 'C' && strcmpi(evdate[count], inpdat) != 0)
		{
		break;
		} //endif view is for a certain date and there is a different date currently

	evid[top++] = atoi(eventno[count]);
	} //endfor loop from the input date to the end of the events file

if(top == 0)
	{
	printf("\nNo Events Found");
	} //endif there are Error: No Events Found
else
	{
	OutputEventsTabular(evid, "TiDaTmLo", top);
	} //endelse

ReadBackEventFile();

cout << "\n\nPress any key to return";
getch();

return 0;
}

int ViewEventsByTitle()
{
char title[64];
int find = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nView Events By Title";
cout << "\n====================\n";

InputEventTitleCheck(title, "\nEnter Event Title: ");
find = FindInArray64(evtitle, title, nei);

while(find != -1)
	{
	OutputEvent(eventno[find]);
	find = FindInArray64(evtitle, title, nei, find + 1);    // going to the location after the found event
	} //endwhile finding events

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

addeventchoice = GetMenuChoice(1, 5);

switch(addeventchoice)
	{
	case 1: 
		{
		DJSession();
		clrscr();
		break;
		} //endcase
	case 2:
		{
		GuestAppearance();
		clrscr();
		break;
		} //endcase
	case 3:
		{
		ExternalEvent();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		Replay();
		clrscr();
		break;
		} //endcase
	case 5:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return addeventchoice;
}

int DJSession()
{
char indjno[10];
char indate[11];
char instime[6];
char inetime[6];
char intitle[64];
int ievno;
char evno[10];
int idjno;
char isrecurring;
int duration; // in hours
char durc[10];
int cont = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nDJ Session";
cout << "\n==========\n";

ievno = GenerateEventNumber(evno);

InputDJNumberCk(indjno, "\nEnter DJ Number: ");	// gets validated inputted DJ number
InputEventTitleCheck(intitle, "\nEnter Title: ", 0);	// gets validated input title
idjno = atoi(indjno); // gets the DJ number as an integer

InputDateCk(indate, "\nEnter Date: ");	// gets validated input date

while(cont == 0)
	{
    InputTimeCk(instime, "\nEnter Start Time: ");	// gets validated input start time
	
    if(IsSlotUsed(indate, instime, idjno) == 1)
        {
	    cout << "\nError: Start time slot already used";
        continue;   // restart the loop
        } //endif the slot is used
    else if(IsDJAvailable(indate, instime, instime, idjno) == 0)
        {
        continue;   // restart the loop
        } //endelseif the DJ isn't available

    cont = 1;   // if the loop reaches the end then it will be fully valid
	} //endif the start time slot is used

cont = 0;   // resetting cont to be used again
while(cont == 0)
	{
    InputTimeCompCk(inetime, "\nEnter End Time: ", instime);	// gets partially validated input end time

    if(EventCollisionCheckTime(indate, instime, inetime, idjno) == 1)
	    {
	    cout << "\nError: The DJ is End time slot already used";
        continue;   // restart the loop
	    } //endif there are any collisions
    else if(IsDJAvailable(indate, instime, inetime, idjno) == 0)
        {
        continue;   // restart the loop
        } //endif the DJ isn't available

    cont = 1;   // if the loop reaches the end then it will be fully valid
	} //endif the start time slot is used

isrecurring = InputYNChoiceCk("\nIs this session a weekly recurring session (y/n): ");	// asks if the event is a recurring event
cout << "\nEvent Number: " << evno;	// outputs event number
duration = CalculateDuration(instime, inetime);	// calculates the duration of the event
itoa(duration, durc, 10);	// converts the duration into a string

// copies locals into their respective globals 
strcpy(eventno[nei], evno);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], instime);
strcpy(evdur[nei], durc);
strcpy(evlocation[nei], "Station");
strcpy(evtitle[nei], intitle);

nei = nei + 1;
itoa(nei, nec, 10);

if(isrecurring == 'y')
	{
	strcpy(evlocation[nei], "Station Repeat");	// marks it as recurring
	AddRecurringEventToSchedule(evno, 'S', idjno);
	} //endif the event should be recurring
else
	{
	AddEventToSchedule(evno, 'S', idjno);
	} //endelse add the event to the schedule

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\n\nSuccess - DJ session has been added to the schedule";

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
int duration; // in hours
char durc[10];
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
int cont = 0;

ReadBackGuestFile();
ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nGuest Appearance";
cout << "\n================\n";

InputDateCk(indate, "\n\nEnter Date to view all slots for or current week, or n to not view (C/N): ", "CN");

if(indate[0] == 'C')
	{
	strcpy(indate, "");	// clearing the input date
	} //endif get current week

if(indate[0] != 'N')
	{
	GetClosestMonday(indate);	// finding the closest Monday to the input date

	cout << "\nClosest Monday: " << dttoday << "\n\n";
	cout << "    ";
	for(time = 0; time < 24; time++)
		{
		if(time < 10)
				{
				cout << "0";
				} //endif the time is less than 10
		
		cout << time << " ";
		} //endfor loop through the hours of the day

	for(day = 0; day < 7; day++)
		{
		cout << '\n' << daysofweek[day];
		for(time = 0; time < 24; time++)
			{
			hasguest = FindScheduleGuestSlot(day, time); // finds if there is a guest at that day and time

			if(hasguest == 0)
				{	
				cout << "  " << sch[0][day][time];
				} //endif
			else
				{
				cout << "  " << "*";
				} //endelse
			}
		} //endfor loop through the hours of the day
	} //endif should show the slots

InputGuestNumberCheck(inguno, "\nEnter Guest Number: ");	// gets the validated guest number
InputDJNumberCk(indjno, "\nEnter Assisting DJ's Number: ");	// gets validated DJ which exists
InputDateCk(indate, "\nEnter Date: ");	// gets validated input date

while(cont == 0)
	{
    InputTimeCk(instime, "\nEnter Start Time: ");	// gets validated input start time
	
    if(IsSlotUsed(indate, instime, idjno) == 1)
        {
	    cout << "\nError: Start time slot already used";
        continue;   // restart the loop
        } //endif the slot is used
    else if(IsDJAvailable(indate, instime, instime, idjno) == 0)
        {
        continue;   // restart the loop
        } //endelseif the DJ isn't available
    else if(IsGuestSlotAvailable(indate, instime, instime) == -1)
        {
        continue;   // restart the loop
        } //endelseif the guest slot isn't available

    cont = 1;   // if the loop reaches the end then it will be fully valid
	} //endif the start time slot is used


cont = 0;   // resetting cont to be used again
while(cont == 0)
	{
    InputTimeCompCk(inetime, "\nEnter End Time: ", instime);	// gets partially validated input start time

    if(EventCollisionCheckTime(indate, instime, inetime, idjno) == 1)
	    {
	    cout << "\nError: The DJ is End time slot already used";
        continue;   // restart the loop
	    } //endif there are any collisions
    else if(IsDJAvailable(indate, instime, inetime, idjno) == 0)
        {
        continue;   // restart the loop
        } //endelseif the DJ isn't available
    else if(IsGuestSlotAvailable(indate, instime, inetime) == -1)
        {
        continue;   // restart the loop
        } //endelseif the guest slot isn't available

    cont = 1;   // if the loop reaches the end then it will be fully valid
	} //endif the start time slot is used

ievno = GenerateEventNumber(evno);	// generates the event number
guloc = FindInArray10(guestno, inguno, ngi);	// finds the guest in the guest file
cout << "\nEvent Number: " << evno;

idjno = atoi(indjno); // gets the DJ number as an integer
duration = CalculateDuration(instime, inetime);	// calculates the duration of the event
itoa(duration, durc, 10); // converts the duration into a string

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

AddEventToSchedule(evno, 'G', idjno, inguno);	// adds the event to the schedule according to its specific details

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
int cont = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nExternal Event";
cout << "\n==============\n";

GenerateEventNumber(evno);  // generates the event number for the event
InputEventTitleCheck(intitle, "\nEnter Event Title: ");	// gets the validated title of the event

cout << "\nEnter Event Description: ";
cin.getline(indesc, 128);
while(PresenceCk(indesc) == 0)
	{
	cout << "\nEnter Event Description: ";
	cin.getline(indesc, 128);
	} //endwhile nothing has been inputted

InputDateCk(indate, "\nEnter Event Date: ");	// gets the validated date of the event
InputTimeCk(instime, "\nEnter Start Time: ");	// gets validated input start time
InputTimeCompCk(inetime, "\nEnter End Time: ", instime, 1);	// gets validated input end time

cout << "\nEnter Event Location: ";
cin.getline(inloc, 32);
while(PresenceCk(inloc) == 0)
	{
	cout << "\nEnter Event Location: ";
	cin.getline(inloc, 32);
	} //endwhile nothing has been inputted

InputPriceCk(inprice, "\nEnter Event Cost (free if free): ");

// acounting for the pound symbol
if(inprice[0] == pound)
	{
	strcpy(inprice, &inprice[1]); // copies the price into the price but ignoring the 1st char which would be the £
	} //endif pound

NameInputPresCk(incontnam, "\nEnter Event Contact name (na if none): ", 1);
EmailInputCk(inemail, "\nEnter Event Contact Email Address (na if none): ", 1);
PhoneNumInputCk(intelno, "\nEnter Event Contact Phone Number (na if none): ", 1);

while(cont == 0)
	{
	InputDJNumberCk(indjno, "\nEnter Attending DJ Number: ");
	idjno = atoi(indjno);	// converts DJ number to integer

    if(EventCollisionCheckTime(indate, instime, inetime, idjno) == 1)
        {
        cout << "\nError: The DJ is end time slot already used";
        continue;
        } //endif there are collisions
    else if(IsDJAvailable(indate, instime, inetime, idjno) == 0)
        {
        continue;
        } //endelseif the DJ isn't available

    cont = 1;   // if reaches the end then will be valid
	} //endif there are any collisions


cout << "\nEvent Number: " << evno;
cout << "\nSuccess - Event has been added to the schedule";

duri = CalculateDuration(instime, inetime);	// calculates the duration of the event in hours
itoa(duri, durc, 10);	// converts the duration to a str

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
char edate[11];
char evnoc[10];
int attdjs[50];
char etitle[128];
char slot[32];
int nodjs;
int idate;
int itime;
int djit;
int loc;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nReplay";
cout << "\n======\n";

InputEventReferenceCheck(inevno, "\nEnter Replay Show Event Number: ", 0);
loc = FindInArray10(eventno, inevno, nei); // finding the event number

InputDateCk(indate, "\nEnter Date: ");	// getting the date for the replay
InputTimeCk(intime, "\nEnter Start Time");	// getting the time for the replay

GenerateEventNumber(evnoc);
GenerateScheduleToken(token, "R", evnoc, ""); // creating the token

// creating the title
strcpy(etitle, "Replay ");
strcat(etitle, evtitle[loc]);

// copying the locals into their respective globals
strcpy(eventno[nei], evnoc);
strcpy(evtitle[nei], etitle);
strcpy(evdate[nei], indate);
strcpy(evtime[nei], intime);
strcpy(evdur[nei], evdur[loc]);
strcpy(evlocation[nei], evlocation[loc]);

// incrementing the global count of how many events there are
nei = nei + 1;
itoa(nei, nec, 10);

idate = CalculateScheduleDateIndex(indate); // finding the date in the schedule
itime = CalculateScheduleTimeIndex(intime); // finding the time in the schedule
nodjs = GetAttendingDJs(inevno, attdjs);	// gets all of the attending DJs

strcpy(edate, evdate[nei]);	// copying the start date into the end date
AddDays(edate, (atoi(evdur[loc]) / 24));	// calculating the end date

for(djit = 0; djit < nodjs; djit++)
	{
	GetScheduleSlot(slot, idate, itime, attdjs[djit]);
	
	// check if the DJ is attending any events at that time
	if(EventCollisionCheckEvent(evnoc, attdjs[djit]) == 0)
		{
		AddEventToSchedule(evnoc, 'R', attdjs[djit]);
		} //endif the slots are empty add the event to the DJs schedule
	} //endfor loop through all DJs and adding this to their schedule

cout << "\nSuccess - Replay has been added to the schedule";

ReadBackEventLinksFile();
ReWriteEventFile();
ReWriteScheduleFile();

cout << "\n\nPress any key to return";
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

changeeventchoice = GetMenuChoice(1, 9);

switch(changeeventchoice)
	{
	case 1: 
		{
		ChangeEventsTitle();
		clrscr();
		break;
		} //endcase
	case 2: 
		{
		ChangeEventsDate();
		clrscr();
		break;
		} //endcase
	case 3: 
		{
		ChangeEventsTime();
		clrscr();
		break;
		} //endcase
	case 4: 
		{
		ChangeEventsLocation();
		clrscr();
		break;
		} //endcase
	case 5: 
		{
		ChangeEventsDescription();
		clrscr();
		break;
		} //endcase
	case 6: 
		{
		ChangeEventsCost();
		clrscr();
		break;
		} //endcase
	case 7: 
		{
		ChangeEventsContact();
		clrscr();
		break;
		} //endcase
	case 8: 
		{
		ChangeEventsPlaylist();
		clrscr();
		break;
		} //endcase
	case 9: 
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

InputEventReferenceCheck(evnoc, "\nEnter Event Number: ");	// gets the number of the event
loc = FindInArray10(eventno, evnoc, nei);
cout << "\nCurrent Title: " << evtitle[loc];

InputEventTitleCheck(ntitle, "\nEnter Title: ", 0);	// gets the title of the event
strcpy(evtitle[loc], ntitle);	// copies the new title into the old title

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
int cevnos[50];
char etime[6];
char today[11];
int cont = 0;
int nevs;	// number of events
int idat;
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

InputEventReferenceCheck(evnoc, "\nEnter Event Number: ");	// gets the event number
loc = FindInArray10(eventno, evnoc, nei);

if(IsRecurringEvent(evnoc) == 1)
	{
	cout << "\nError: To change the date of a recurring event please remove it and recreate it";
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif the event is recurring

cout << "\nTitle: " << evtitle[loc] << "\nDate: " << evdate[loc];

idat = CalculateScheduleDateIndex(evdate[loc]);	// calculating the location of the date in the schedule
nodjs = GetAttendingDJs(evnoc, attdjs);	// getts all of the attending DJs 

strcpy(etime, evtime[loc]);	// copies the time into the end time
AddTimes(etime, atoi(evdur[loc]));	// adds the duration of the event to the time
GetToday(today);	// gets todays date and copies it into the today variable

while(cont == 0)
	{
	InputDateCompCk(ndate, "\nNew Date: ", today);	// asks for the new input

	for(count = 0; count < nodjs; count++)
		{
		if(EventCollisionCheckTime(ndate, evtime[loc], etime, attdjs[count]) != 0)
			{
			cout << "\nError: Another DJ is scheduled at this date and time";
			count = -1;
			break;
			} //endif there is an event at that time then the event can't be moved to that date
        else if(IsDJAvailable(ndate, evtime[loc], etime, attdjs[count]) == 0)
            {
            count = -1;
            break;
            } //endelseif the DJ isn't available
		} //endfor loop through all of the DJs to find the events on that day for them
	if(count == -1)
		{
		continue;
		} //endif count is -1 then there is a conflict

	cont = 1;	// set cont equal to 1 at the end since if the loop reaches the end then it is fully valid
	} //endwhile loop until a valid date that works for all attending DJs is inputted

GetScheduleSlot(slot, evnoc, attdjs[0]); // gets the first slot for each attending DJ
type = slot[0];	// gets the type of slot

if(type == 'G')
	{
	GetScheduleGuestNumber(gunoc);	// gets the guest number of the guest
	} //endif it is a guest event get the guest number

RemoveEventFromSchedule(evnoc);	// removes the event from the schedule
strcpy(evdate[loc], ndate);	// changes the date in the events file
                         
if(type == 'G')
	{
	AddGuestEventToSchedule(evnoc, gunoc, attdjs[0]);	// adds the guest event back to the schedule
	} //endif is a guest event

AddEventToSchedule(evnoc, type, attdjs[0]);	// the event back to the schedule for the first DJ

for(count = 1; count < nodjs; count++)
	{
	AddDJToEvent(evnoc, attdjs[count]);
	} //endfor loop through all the DJs and add them to the events 

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
char slot[32];
int evnos[50];
char type;
char gunoc[10];
int nevs;
int dati;
int timi;
int count;
int nodjs;
int duri;
int loc;
int cont = 0;

ReadBackEventLinksFile();
ReadBackEventFile();
ReadBackScheduleFile();

clrscr();
cout << "\nChange Events Time";
cout << "\n==================\n";

InputEventReferenceCheck(evnoc, "\nEnter Event Number: ");	// gets the event number
loc = FindInArray10(eventno, evnoc, nei);

if(IsRecurringEvent(evnoc) == 1)
	{
	cout << "\nError: To change the time of a recurring event please remove it and recreate it";
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif the event is recurring

nodjs = GetAttendingDJs(evnoc, attdjs);

strcpy(etime, evtime[loc]);	// copy the start time into the end time
AddTimes(etime, atoi(evdur[loc])); // convert the duration to an integer and then add it to the start time to get the end time
dati = CalculateScheduleDateIndex(evdate[loc]);
timi = CalculateScheduleTimeIndex(evtime[loc]);

cout << "\nTitle: " << evtitle[loc] << "\nStart Time: " << evtime[loc] << "\nEnd Time: " << etime;

while(cont == 0)
	{
	InputTimeCk(ntime, "\nNew Start Time: ");	// gets partially validated start time
	timi = CalculateScheduleTimeIndex(ntime);	// gets the location of the new time on the schedule

	for(count = 0; count < nodjs; count++)
		{
		GetScheduleSlot(slot, dati, timi, attdjs[count]);
		
		if(slot[0] != '*')
			{
			cout << "\nError: Another DJ has been scheduled at this date and time";
            count = -1;
			break;
			} //endif the slot isn't free for one DJ
        else if(IsDJAvailable(evdate[loc], ntime, etime, attdjs[count]) == 0)
            {
            count = -1;
            break;
            } //endelseif the DJ isn't available
		} //endfor loop through all of the DJs to find if they are busy at that time
    if(count == -1)
        {
        continue;
        } //endif the count is -1 then there isn't a valid start time

	InputTimeCompCk(netime, "\nNew End Time: ", ntime);	// gets validated end time

	for(count = 0; count < nodjs; count++)
		{
		if(EventCollisionCheckTime(evdate[loc], ntime, netime, attdjs[count]) != 0)
			{
			cout << "\nError: Another DJ is scheduled at this date and time";
			count = -1;
			break;
			} //endif there is an event at that time then the event can't be moved to that date
        else if(IsDJAvailable(evdate[loc], ntime, netime, attdjs[count]) == 0)
            {
            count = -1;
            break;
            } //endelseif the DJ isn't available
		} //endfor loop through all of the DJs to find the events on that day for them
	if(count == -1)
		{
		continue;
		} //endif count is -1 then there is a conflict
	

	cont = 1;	// set cont equal to 1 at the end since if the loop reaches the end then it is fully valid 
	} //endwhile shouldn't continue

duri = CalculateDuration(ntime, netime);
GetScheduleSlot(slot, evnoc, attdjs[0]); // gets the first slot for each attending DJ
type = slot[0];	// gets the type of slot

if(type == 'G')
	{
	GetScheduleGuestNumber(gunoc);	// gets the guest number of the guest
	} //endif it is a guest event get the guest number

RemoveEventFromSchedule(evnoc);	// removes the event from the schedule
itoa(duri, evdur[loc], 10); // write the duration to the duration variable
strcpy(evtime[loc], ntime);	// writing the start time to the time variable

if(type == 'G')
	{
	AddGuestEventToSchedule(evnoc, gunoc, attdjs[0]);	// adds the guest event back to the schedule
	} //endif is a guest event

AddEventToSchedule(evnoc, type, attdjs[0]);	// the event back to the schedule for the first DJ

for(count = 1; count < nodjs; count++)
	{
	AddDJToEvent(evnoc, attdjs[count]);
	} //endfor loop through all the DJs and add them to the events 

cout << "\nSuccess - Time has been Changed";

ReWriteEventFile();
ReWriteScheduleFile();

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

InputEventTypeReferenceCheck(evnoc, "\nEnter Event Number: ", 'E', "\nError: Cannot change location of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc] << "\nLocation: " << evlocation[loc];

cout << "\nEnter Event Location: ";
cin.getline(nlocation, 32);
while(PresenceCk(nlocation) == 0)
	{
	cout << "\nEnter Event Location: ";
	cin.getline(nlocation, 32);
	} //endwhile nothing has been inputted

strcpy(evlocation[loc], nlocation);	// copying new location into file

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

InputEventTypeReferenceCheck(evnoc, "\nEnter Event Number: ", 'E', "\nError: Cannot change description of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc] << "\nDescription: " << evdescription[loc];

cout << "\nEnter Event Description: ";
cin.getline(ndesc, 128);
while(PresenceCk(ndesc) == 0)
	{
	cout << "\nEnter Event Description: ";
	cin.getline(ndesc, 128);
	} //endwhile nothing has been inputted

strcpy(evdescription[loc], ndesc);	// copying description into file variable 

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

InputEventTypeReferenceCheck(evnoc, "\nEnter Event Number: ", 'E', "\nError: Cannot change cost of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, evnoc, nei);

cout << "\nTitle: " << evtitle[loc] << "\nCost: ";

if(isdigit(evcost[loc][0]) != 0)
	{
	cout << pound;
	} //endif there is a digit
cout << evcost[loc];

InputPriceCk(nprice, "\nNew Cost: ");	// gets the validated price input

if(nprice[0] == pound)
	{
	strcpy(evcost[loc], &nprice[1]);
	} //endif there is a pound sign
else
	{
	strcpy(evcost[loc], nprice);
	} //endelse there isn't a pound sign

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

return 0;
}

int ChangeEventsContactMenu()
{
int chevcontch;

clrscr();

cout << "\n\tChange Contact Menu";
cout << "\n\t===================\n";
cout << "\n\t1. Name";
cout << "\n\t2. Email Address";
cout << "\n\t3. Phone Number";
cout << "\n\t4. Return";

chevcontch = GetMenuChoice(1, 4);

switch(chevcontch)
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

return chevcontch;
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

InputEventTypeReferenceCheck(inevno, "\nEnter Event Number: ", 'E', "\nError: Cannot change contact name of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, inevno, nei); // finds the event number in the file

cout << "\nTitle: " << evtitle[loc] << "\nCurrent Contact Name: " << evcont[loc]; // effectively the same thing guest equivalent

NameInputPresCk(inevcontnam, "\nNew Contact Name: ", 1); // inputting the new contact name
strcpy(evcont[loc], inevcontnam); // copying across the new contact name
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

InputEventTypeReferenceCheck(evnoc, "\nEnter Event Number: ", 'E', "\nError: Cannot change contact email address of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, evnoc, nei);	// finds the event in the event file
cout << "\nTitle: " << evtitle[loc] << "\nContact Email Address: " << evcontemail[loc];

EmailInputCk(nemail, "\nNew Email Address: ", 1);

strcpy(evcontemail[loc], nemail); // copying across the new contact name
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

InputEventTypeReferenceCheck(evnoc, "\nEnter Event Number: ", 'E', "\nError: Cannot change contact phone number of a non-external event");	// gets validated event number for an external event
loc = FindInArray10(eventno, evnoc, nei);
cout << "\nTitle: " << evtitle[loc] << "\nContact Phone Number: " << evcontnum[loc];

PhoneNumInputCk(ntelno, "\nNew Phone Number: ", 1);	// getting validated phone number input

strcpy(evcontnum[loc], ntelno); // copying across the new contact name
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
char choice;

ReadBackEventFile();
ReadBackMusicFile();
ReadBackPlaylistFile();

clrscr();
cout << "\nChange Event Playlist";
cout << "\n=====================\n";

InputEventTypeReferenceCheck(evnoc1, "\nEnter Event Number: ", 'S', "\nError: Cannot change the playlist of an event which isn't a show", 1);	// gets validated event number for a show
evloc = FindInArray10(eventno, evnoc1, nei);	// finds the event in the events file
cout << "\nTitle: " << evtitle[evloc];

InputEventTypeReferenceCheck(evnoc2, "\nEnter Event Number of Playlist to Swap to: ", 'S', "\nError: Cannot change the playlist of an event which isn't a show", 1);	// gets the inputted event number and validates that it has a playlist
evloc = FindInArray10(eventno, evnoc2, nei);	// finds the event in the events file
cout << "\nTitle: " << evtitle[evloc];

choice = InputMultiOptnChoiceCk("\nWould you like to swap or copy the entered playilst (S/C): ", "SC");	// choice validation

// getting the first songs for both (allows for future validaion hence why not do while)
lnkloc1 = FindInArray10(pllinkevno, evnoc1, npi);
lnkloc2 = FindInArray10(pllinkevno, evnoc2, npi);

while(lnkloc1 != -1)
	{
	catnos1[back1++] = atoi(pllinkcatno[lnkloc1]);	// writing the catno to the back as int and incrementing back
	lnkloc1 = FindInArray10(pllinkevno, evnoc1, npi);	// finding next entry
	} //endwhile

while(lnkloc2 != -1)
	{
	catnos2[back2++] = atoi(pllinkcatno[lnkloc2]);	// writing the catno to the back as int and incrementing back
	lnkloc2 = FindInArray10(pllinkevno, evnoc2, npi);	// finding next entry
	} //endwhile

if (choice == 'S')
	{
	// clearing the playlists
	RemovePlaylistEntriesByEvent(evnoc1);
	RemovePlaylistEntriesByEvent(evnoc2);

	for (count = 0; count < back2; count++)
		{
		itoa(catnos2[count], tcatno, 10);	// converting the numbers to strings
		AddPlaylistEntry(evnoc1, tcatno);	// adding the entries to the playlist
		} //endfor adding all the songs to the first event's playlist

	for (count = 0; count < back1; count++)
		{
		itoa(catnos1[count], tcatno, 10);	// converting the numbers to strings
		AddPlaylistEntry(evnoc2, tcatno);	// adding the entries to the playlist
		} //endfor loop through all of the songs in the other playlist and add them
	} //endif chosen to swap playlists
else if (choice == 'C')
	{
	RemovePlaylistEntriesByEvent(evnoc1);	// clearing the event to change's playlist

	for(count = 0; count < back2; count++)
		{
		itoa(catnos2[count], tcatno, 10);	// converting the tmpid into a str
		AddPlaylistEntry(evnoc1, tcatno);	// adding the song at the top of the queue from pl2 to pl1
		} //endfor starting from the front of the queue and working to the end
	} //endelse the choice is to copy

cout << "\n\nSuccess - Playlist has been changed";

ReWritePlaylistFile();
ReWriteMusicFile();

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
char etime[6];
int loc;
int evloc;
int idjno;
int nodjs;
char choice;
char contch;

ReadBackEventFile();
ReadBackEventLinksFile();
ReadBackScheduleFile();

clrscr();
cout << "\nAllocate DJs";
cout << "\n============\n";

InputEventReferenceCheck(inevno, "\nEnter Event Number: ");	// gets validated event number input
evloc = FindInArray10(eventno, inevno, nei);	// finds the event in the array of events
strcpy(etime, evtime[evloc]);
AddTimes(etime, atoi(evdur[evloc]));
cout << "\nEvent Title: " << evtitle[evloc];
nodjs = GetAttendingDJs(inevno, djnos, 1);	// outputs the attending DJs

choice = InputMultiOptnChoiceCk("\nWould you like to add or remove a DJ (A/R): ", "AR");

InputDJNumberCk(indjno, "\nEnter DJ Number: ");	// gets the validated DJ number
idjno = atoi(indjno); // converts the DJ number to an integer

LocateDJ(idjno);

if(choice == 'A')
	{
	if((IsDJAttending(inevno, idjno) == 0) && (EventCollisionCheckEvent(inevno, idjno) == 0))
		{
		AddDJToEvent(inevno, idjno);	// allocates the DJ to the event
		cout << "\nSuccess - " << a_dj.djnam << " has been allocated\n";
		} //endif the DJ isn't in the event and there isn't a collision
    else if(IsDJAvailable(evdate[evloc], evtime[evloc], etime, idjno) == 0)
        {
		cout << "\nError: The DJ isn't available";
        } //endelseif the DJ isn't available
	else
		{
		cout << "\nError: DJ is already attending the event";
		} //endelse the DJ is in the event
	} //endif choice is add
else if(choice == 'R')
	{
	if(IsRecurringEvent(inevno) == 1)
		{
		cout << "\nWarning: Removing if no DJs are allocated to a recurring event then it will cease to be a recurring event and will have to be recreated";
		contch = InputYNChoiceCk("Enter to continue with removal of DJ or not (y/n)");

		if(contch == 'y')
			{
			RemoveDJFromEvent(inevno, idjno);	// deallocates the DJ from the event
			cout << "\nSuccess - " << a_dj.djnam << " has been deallocated\n";			
			} //endif the choice is to continue with the deletion
		} //endif is a recurring event
	else if(IsDJAttending(inevno, idjno) == 1)
		{
		RemoveDJFromEvent(inevno, idjno);	// deallocates the DJ from the event
		cout << "\nSuccess - " << a_dj.djnam << " has been deallocated\n";
		} //endelseif the DJ is in the event
	else
		{
		cout << "\nError: DJ isn't attending the event";
		} //endelse the DJ isn't in the event
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
char outmsg[64];
char inpdate[11];
char tmptitle[64];
char evno[10];
int tloc;	// temporary location

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nRemove Events";
cout << "\n=============\n";

InputEventReferenceCheck(evno, "\nEnter Event Reference: ");	// gets the validated event number
find = FindInArray10(eventno, evno, nei);	// gets the event number
strcpy(tmptitle, evtitle[find]);	// copying the found title into the temp variable

if(FindInArray10(evlinkevno, evno, nei) != -1)
	{
	cout << "\nError: There are still DJs attending this event - remove them to remove the event";
	cout << "\nPress any key to return";
	getch();
	return 0;
	} //endif there are links entries between the DJs and the guests

if(IsRecurringEvent(evno) == 1)
	{
	cout << "\nWarning: Recurring Event - Deleting will delete all ocurrances of the event";
	} //endif is a recurring event give a warning

sprintf(outmsg, "\nAre you sure you want to Delete %s (y/n): ", tmptitle);	// creating the confirmation message
choice = InputYNChoiceCk(outmsg);	// confirmaiton required to reduce mistakes

if((choice == 'y') && (IsRecurringEvent(evno) == 1))
	{
	RemoveEventLinksEntries(evno);	// removes the links
	RemovePlaylistEntriesByEvent(evno);	// removes the playlist
	RemoveEvent(find);	// removes the event
	cout << "\nSuccess - " << tmptitle << " has been deleted\n"; // insert check here
	} //endif the event is recurring
else if(choice == 'y')
	{
	RemoveEventFromSchedule(evno);
	RemoveEventLinksEntries(evno);
	RemovePlaylistEntriesByEvent(evno);	// removes the playlist
	RemoveEvent(find);
	cout << "\nSuccess - " << tmptitle << " has been deleted\n"; // insert check here
	} //endif remove only if yes

ReWriteEventFile();
ReWriteScheduleFile();
ReWriteEventLinksFile();

cout << "\nPress any key to return";
getch();

return 0;
}

#pragma endregion

#pragma region Schedule

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

int GetScheduleYear()
{
return 2024;
}

void GetScheduleStartDate(char* outdate)
{
strcpy(outdate, "01/01/2024");
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

void SetScheduleSlots(char value[32], char sdate[11], char stime[6], char dur[10], int djid)
{
int count;
int curhour;
int duri = atoi(dur);
int itim = CalculateScheduleTimeIndex(stime);
int idat = CalculateScheduleDateIndex(sdate);

for(count = 0; count < duri; count++)
	{
	curhour = (itim + count) % 24;

	if((count > 0) && (curhour == 0))
		{
		// increment the date
		idat += 1;
		} //endif curhour is on new day or if the duration is equal to the count

	// sets the schedule slot
	SetScheduleSlot(value, idat, curhour, djid);
	} //endfor loop though duration of event
}

void GetScheduleSlot(char output[32], int date, int time, int djid)
{
if(djid == -1)
	{
	// copy in the default slot plus X to show error
	strcpy(output, "*X");
	} //endif there is no DJ
else
	{
	strcpy(output, sch[djid][date][time]);
	} //endelse copy the slot into the output
}

void GetScheduleSlot(char output[32], char date[11], char time[6], int djid)
{
int idat;
int itim;

idat = CalculateScheduleDateIndex(date);
itim = CalculateScheduleTimeIndex(time);

GetScheduleSlot(output, idat, itim, djid);
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
for(count = 0; count < month - 1; count++)
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

// number of days in each month
int daysinmon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

year = GetScheduleYear();

// +1 to account for the starting at the 0th index
curday = schedindex + 1;

if(year % 4  == 0)
	{
	daysinmon[1] = 29;
	} //endif

for(start = 0; ((curday - daysinmon[start]) > 0) && (start < 12); start++)
	{
	curday -= daysinmon[start];
	} //endwhile the current day is greater than 0

// add one to the day to acount for day 0 and add 2 to the month to acount for it stopping a month early
ConvertDateToStr(outdate, curday, start + 2, year);
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
int holevno;

GetScheduleSlot(val, date, time, djid);

// separating type and event number
if((val[0] == 'H') || (val[1] == 'R'))
	{
	if(strstr(val, "HA") != NULL)
		{
		if(strstr((val), "RR") != NULL)
			{
			sscanf(val, "HA%dRR%d", &holevno, &outevno);
			} //endif a recurring event has been displaced by a holiday
		else if(strstr((val), "AR") != NULL)
			{
			sscanf(val, "HA%dR%d", &holevno, &outevno);
			} //endelse there is a non-recurring show
		else
			{
			sscanf(val, "HA%d", &outevno);
			} //endelse it is just an approved holiday
		} //endif HA is found in the key
	else
		{
		sscanf(&val[2], "%d", &outevno);
		} //endelse the event isn't an approved holiday
	} //endif is a holiday or a recurring event
else
	{
	sscanf(&val[1], "%d", &outevno);
	} //endelse is any other type

return outevno;
}
	
int GetEventDateOnSchedule(char outdate[11], char evnoc[10], int startdt)
{
int djit;
int day;
int time;
int evnoi;
int find = -1;

evnoi = atoi(evnoc);	// getting the event number as an int

for (djit = 1; djit < 52; djit++)
	{
	for (day = startdt; day < (366 - startdt); day++)
		{
		for(time = 0; time < 24; time++)
			{
			if(GetScheduleEventNumber(day, time, djit) == evnoi)
				{
				CalculateDateFromSchedule(outdate, day);
				find = day;
				return find;
				} //endif the event has been found
			} //endfor loop through schedule to get all time slots
		} //endfor loop through whole schedule to find the date of the event
	} //endfor loop through all DJs to find the event

return find;
}

int FindScheduleGuestSlot(int date, int time)
{
int count;
int guslot = -1;
char temptype;

// starting from 1 because DJ 0 is a null DJ for storage purposes
for(count = 1; count < 52; count++)
	{
	// getting the type of the slot at that date and time
	temptype = GetScheduleType(date, time, count);

	if(temptype == 'G')
		{
		guslot = count;
        break;
		} //endif if the type is a guest slot
	} //endfor looping through the DJ schedule's

return guslot;
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
char djnoc[10];
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
	GenerateScheduleToken(schentry, types, inevno);
	} //endif there is not a guest number
else
	{
	GenerateScheduleToken(schentry, types, inevno, inguno);	
	} //endelse generate the schedule token for a guest event

if(type == 'H')
	{
	SetScheduleSlot(schentry, evdate[loc], evtime[loc], indjno);
	} //endif the type is a holiday only add the date and time to the schedule to not overwrite other events
else
	{
	SetScheduleSlots(schentry, evdate[loc], evtime[loc], evdur[loc], indjno);
	} //endelse the type isn't a holiday add all the slots to the schedule

itoa(indjno, djnoc, 10); // converting the DJ number to str
AddLinksEntry(inevno, djnoc);	// adding the DJ link to the links file
}

void AddRecurringEventToSchedule(char inevno[10], char type, int indjno)
{
char schentry[32] = "";
char tmpdat[11];
int loc;
int count;
char djnoc[10];
char types[3] = { type, 'R', '\0' };
int end;

GenerateScheduleToken(schentry, types, inevno);
loc = FindInArray10(eventno, inevno, nei);
strcpy(tmpdat, evdate[loc]);

end = 52 - ceil(CalculateScheduleDateIndex(tmpdat) / 7);    // gets number of remaining weeks in the year

itoa(indjno, djnoc, 10);
AddLinksEntry(inevno, djnoc);

cout << "\nFlag";

for (count = 0; count < end; count++)
	{
	SetScheduleSlots(schentry, tmpdat, evtime[loc], evdur[loc], indjno);
	AddDays(tmpdat, 7);
	} //endfor loop until reaches the end of the schedule
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
	curhour = (itim + count) % 24;

	if((count > 0) && (curhour == 0))
		{
		// increment the date
		idat += 1;
		} //endif curhour is on new day or if the duration is equal to the count
	
	// sets the schedule slot
	SetScheduleSlot(schentry, idat, curhour, indjno);
	} //endfor loop though duration of event

// adds the DJ to the event
AddDJToEvent(inevno, indjno);
}

void AddDJToEvent(char inevno[10], int idjno)
{
int evloc;
char djnoc[10];
char slot[32];
int tdjno;

evloc = FindInArray10(eventno, inevno, nei);
tdjno = GetAttendingDJ(inevno);

GetScheduleSlot(slot, inevno, tdjno);
itoa(idjno, djnoc, 10); // converting the DJ number to str
AddLinksEntry(inevno, djnoc);	// linking the DJ to the event
SetScheduleSlots(slot, evdate[evloc], evtime[evloc], evdur[evloc], idjno);
}

void RemoveRecurringEventFromDJ(char evno[10], int indjno)
{
int loc;
int attdjs[50];
char tmpdat[11];
int count;
int nodjs;
int djit;
int end = 1;

loc = FindInArray10(eventno, evno, nei);
strcpy(tmpdat, evdate[loc]);    // copies the date of the event into a temp variable
end = 52 - ceil(CalculateScheduleDateIndex(tmpdat) / 7);    // gets number of remaining weeks in the year

for (count = 0; count < end; count++)
	{
    SetScheduleSlots("*", tmpdat, evtime[loc], evdur[loc], indjno);
	AddDays(tmpdat, 7);
	}//endfor loop through all of the remaining weeks to remove the event from them
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
int loc;
char djnoc[10];

loc = FindInArray10(eventno, evno, nei);	// getting the location of the event
itoa(indjno, djnoc, 10);	// converts the inputted DJ no into a str

if(IsRecurringEvent(evno) == 1)
    {
    RemoveRecurringEventFromDJ(evno, indjno);
    }//endif the event is recurring
else
    {
    SetScheduleSlots("*", evdate[loc], evtime[loc], evdur[loc], indjno);	// resetting all of the slots for the event for that DJ
    } //endelse isn't a recurring event

RemoveLinksEntry(evno, djnoc);	// removes the DJ link in the links file
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

int IsSlotUsed(char date[11], char time[6], int djid)
{
char slot[32];
int isused = 1;

GetScheduleSlot(slot, date, time, djid);

if(strcmpi(slot, "*") == 0)
	{
	isused = 0;
	} //endif the slot is empty

return isused;
}

void OutputRow(int day, char dayc[4], char content[32], char time[6], int rowlen)
{
int ending = 0;
int contlen = 0;
int minlen = 0;
int maxlen = rowlen;

contlen = strlen(content);

rowlen = rowlen - 13;   // - 13 because that is the total of the necessesary spaces (2 for num day, 3 for day, 5 for time)

maxlen = max(rowlen, contlen);	// getting maximum length of the content
minlen = (rowlen + contlen) - maxlen; // getting minimum length of content

if((rowlen - contlen) > 0)
	{
	ending = rowlen - contlen - 1;
	} //endif the content doesn't fill the whole box

printf("%02d %-3s %-*.*s %-5s%-*.s", day, dayc, minlen, maxlen, content, time, ending, "");
}

void OutputEventRow(int day, int dayit, int evnos[], int top, int len)
{
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
int dayinmo;
int maxevents;
int count;
int index;
char evnoc[10];
char outdate[11];
char output[32];
char etime[6];
char type;
int loc;
int curday;	// the current day being processed

dayinmo = GetDayInMonth(day + dayit);
printf("%02d %s", dayinmo, daysofweek[dayit]);

if((dayit + 1) == 7)
	{
	top = FindAllHolidaySlots(evnos, day, day + 7);
	top = MakeArrayUniqueInt(evnos, top);
	} //endif it is the notifications section to display

for (count = 0; count < top; count++)
	{
	itoa(evnos[count], evnoc, 10);
	loc = FindInArray10(eventno, evnoc, nei);
	type = GetEventType(evnoc);
	CalculateEndTime(evtime[loc], evdur[loc], etime);

	if(type == 'H')
		{
		cout << "\nHoliday";
		} //endif the type is a holiday
	else
		{
		printf("\n%-*s %5s - %5s", len, evtitle[loc], evtime[loc], etime);
		} //endelse the type isn't a holiday
	} //endfor output all of the events for the two days 
}

void OutputHeaderBar(int len)
{
int count;
char spacer[96] = "=";

for(count = 0; count < (len - 1); count++)
    {
    strcat(spacer, "=");
    } //endfor loop until got the spacer of correct length

printf("\n\n%-s\n\n", spacer);
}

int FindAllEventsOfTypeBetweenDates(int evnos[], char type, int startdt, int enddt, int attdj)
{
int day;
int time;
int top = 0;
int tevno;
char slot[32];

for(day = startdt; day < enddt; day++)
	{
	for(time = 0; time < 24; time++)
		{
		GetScheduleSlot(slot, day, time, attdj);
		
		if(slot[0] != type)
			{
			continue;	// skip this iteration in the loop
			} //endif the slot isn't of the correct type

		if(strcmpi(slot, "*") != 0)
			{
			tevno = GetScheduleEventNumber(day, time, attdj); 

			if((evnos[top - 1] != tevno) || (top == 0))
				{
				evnos[top++] = tevno;
				} //endif the event hasn't already been added or if there aren't any events already
			} //endif the slot isn't empty
		} //endfor loop though all times of the day to check for events
	} //endfor loop through all days between and find events

return top;
}

int FindAllEventsOfTypeBetweenDates(int evnos[], char type, char startdt[11], char enddt[11], int attdj)
{
int isdat;
int iedat;

isdat = CalculateScheduleDateIndex(startdt);
iedat = CalculateScheduleDateIndex(enddt);

return FindAllEventsOfTypeBetweenDates(evnos, type, isdat, iedat, attdj);
}

int FindAllEventsBetweenDates(int evnos[], int startdt, int enddt, int attdj)
{
int day;
int time;
int top = 0;
int tevno;
char slot[32];

for(day = startdt; day < enddt; day++)
	{
	for(time = 0; time < 24; time++)
		{
		GetScheduleSlot(slot, day, time, attdj);

		if(strcmpi(slot, "*") != 0)
			{
			tevno = GetScheduleEventNumber(day, time, attdj); 

			if((evnos[top - 1] != tevno) || (top == 0))
				{
				evnos[top++] = tevno;
				} //endif the event hasn't already been added or if there aren't any events already
			} //endif the slot isn't empty
		} //endfor loop though all times of the day to check for events
	} //endfor loop through all days between and find events

return top;
}

int FindAllEventsBetweenDates(int evnos[], char startdt[11], char enddt[11], int attdj)
{
int isdat;
int iedat;

isdat = CalculateScheduleDateIndex(startdt);
iedat = CalculateScheduleDateIndex(enddt);

return FindAllEventsBetweenDates(evnos, isdat, iedat, attdj);
}

int FindAllEventsBetweenTimes(int evnos[], char date[11], char stime[6], char etime[6], int attdj)
{
int timit;
int etimi;
int stimi;
int dati;
char slot[32];
int top = 0;

// gets the start and end times on the schedule
stimi = CalculateScheduleTimeIndex(stime);	
etimi = CalculateScheduleTimeIndex(etime);

dati = CalculateScheduleDateIndex(date);	// gets the date in the schedule

for(timit = stimi; timit < etimi; timit++)
	{
	GetScheduleSlot(slot, dati, timit, attdj);	// gets the schedule slot and loads it into the slot variable

	if(slot[0] != '*')
		{
		evnos[top++] = GetScheduleEventNumber(dati, timit, attdj);		// gets the event number for the event that is found and adds it to an array
		} //endif it isn't an empty slot
	} //endfor loop through all of the events between those times on the inputted date

top = MakeArrayUniqueInt(evnos, top);	// makes the array only have unique event numbers

return top;
}

int FindAllHolidaySlots(int evnos[], int startdt, int enddt)
{
int day;
int time;
int djit;
int tevno;
int top = 0;

for(djit = 1; djit < 52; djit++)
	{
	for(day = startdt; day < enddt; day++)
		{
		for(time = 0; time < 24; time++)
			{
			if(strstr(sch[djit][day][time], "HA") != NULL)
				{
				if(strstr(sch[djit][day][time], "S") != NULL)
					{
					tevno = GetScheduleEventNumber(day, time, djit);

					if((evnos[top] != tevno) || (top == 0))
						{
						evnos[top++] = tevno;
						} //endif the event hasn't already been added or if there aren't any events already
					} //endif there is a show too
				} //endif an approved holiday has been found
			} //endfor loop though all of the times in the day
		} //endfor loop though all the days between the start and end date of the holiday
	} //endfor loop though all of the DJs to find holiday slots

return top;
}

int FindAllHolidaySlots(int evnos[], char startdt[11], char enddt[11])
{
int sdati;
int edati;

sdati = CalculateScheduleDateIndex(startdt);
edati = CalculateScheduleDateIndex(enddt);

return FindAllHolidaySlots(evnos, sdati, edati);
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

schedulingchoice = GetMenuChoice(1, 3);

switch(schedulingchoice)
	{
	case 1: 
		{
		Schedule();
		clrscr();
		break;
		} //endcase
	case 2: 
		{
		Holidays();
		clrscr();
		break;
		} //endcase
	case 3: 
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

return schedulingchoice;
}

/* ------------------------------
 *        Schedule Menu
 * ------------------------------ 
 */

int Schedule()
{
int schedulstatus = 0;
while (schedulstatus != 4)
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
cout << "\n\t3. Edit Schedule";
cout << "\n\t4. Return";

schedulechoice = GetMenuChoice(1, 4);

switch(schedulechoice)
	{
	case 1:
		{
		ViewSchedule();
		clrscr();
		break;
		} //endcase
	case 2:
		{
        if(GetGLOA() == 3)
            {
            CreateSchedule();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
        clrscr();
		break;
		} //endcase
	case 3:
		{
		EditSchedule();
		clrscr();
		break;
		} //endcase
	case 4:
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

viewschedulechoice = GetMenuChoice(1, 4);

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
int day;
char startdt[11];
char enddt[11];
char indjno[10];
char indate[11];
int idjno;
int dtindex;
int len;
int count;
int loc;
char evnoc[10];
int evnos[100];
int dayevnos[8][24];
char output[128];
int tops[10];
int top = 0;
char etime[6];

ReadBackEventLinksFile();
ReadBackScheduleFile();
ReadBackEventFile();

clrscr();
cout << "\nView Schedule By DJ";
cout << "\n===================\n";

InputDJNumberCk(indjno, "\nEnter DJ Number: ");	// gets the valid input DJ number
InputDateCk(indate, "\nEnter week to view or view next or current (N/C): ", "NC");	// gets the input for the week or the additional options

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
	strcpy(startdt, indate);
	} //endelse set the start date to the inputted date

idjno = atoi(indjno);	// gets the DJ number as int
GetClosestMonday(startdt);
UpdateRecurrringEvents(startdt);	// updates all of the starting dates of the events
dtindex = CalculateScheduleDateIndex(startdt);	// getting the starting index for the loop

strcpy(enddt, startdt);	// copying the start date into the end date to then add 7 days to get the ending date
AddDays(enddt, 7);

top = FindAllEventsBetweenDates(evnos, startdt, enddt, idjno);	// finds all of the events between the start and end

for(day = 0; day < 7; day++)
	{
	tops[day] = FindAllEventsBetweenDates(dayevnos[day], dtindex + day, dtindex + day + 1, idjno);
	tops[day] = MakeArrayUniqueInt(dayevnos[day], tops[day]);
	} //endfor loop though all days to find when they swap

cout << "\nStarting Date: " << startdt;

GetRefLocations(eventno, evnos, nei, top);	// gets the locations of the event numbers
len = FindLongestInIndecies(evtitle, evnos, top);

for(day = 0; day < 7; day++)
    {
	OutputHeaderBar(len);
	OutputEventRow(dtindex, day, dayevnos[day], tops[day], len);
    } //endfor loop through all days in the week
OutputHeaderBar(len);

cout << "Notifications: ";

top = FindAllHolidaySlots(evnos, dtindex, dtindex + 28);	// finds all of the holiday slots for the following 4 weeks
GetRefLocations(eventno, evnos, nei, top);	// gets the locations of the event numbers

for(count = 0; count < top; count++)
	{
	CalculateEndTime(evtime[evnos[count]], evdur[evnos[count]], etime);
	printf("\nHoliday Slot on: %10s %5s - %5s", evdate[evnos[count]], evtime[evnos[count]], etime);
	} //endfor loop through all of the holiday slots and output them

top = FindAllEventsOfTypeBetweenDates(evnos, 'E', dtindex, dtindex + 28, idjno);	// finds all of the external events for the following 4 weeks
GetRefLocations(eventno, evnos, nei, top);	// gets the locations of the event numbers
len = FindLongestInIndecies(evtitle, evnos, top);	// finds the longest event title in the located events

for(count = 0; count < top; count++)
	{
	CalculateEndTime(evtime[evnos[count]], evdur[evnos[count]], etime);
	printf("\nUpcomming Event %-*s %10s %5s - %5s", len, evtitle[evnos[count]], evdate[evnos[count]], evtime[evnos[count]], etime);
	} //endfor loop through all of the upcomming external events and output them

top = FindAllEventsOfTypeBetweenDates(evnos, 'S', dtindex, dtindex + 28, idjno);	// finds all of the shows for the following 4 weeks
GetRefLocations(eventno, evnos, nei, top);	// gets the locations of the event numbers

for(count = 0; count < top; count++)
	{
	if(PlaylistDurationCheck(eventno[evnos[count]], 0, 0) != 0)
		{
		printf("\n%-*s (%s) doesn't have a valid playlist", len, evtitle[evnos[count]], eventno[evnos[count]]);
		} //endif the duration of the playlist is less than 
	} //endfor loop through the events and check the playlists are of correct length

ReadBackEventFile();	// refreshing the file so it resets

cout << "\n\nPress any key to return";
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

InputDJNumberCk(indjno, "\nEnter DJ Number");	// gets the validated input number
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
int loc;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
char inpdate[11];
int dtindex;
int dayinmo;

ReadBackScheduleFile();

clrscr();
cout << "\nView Schedule Guest Slots";
cout << "\n=========================\n";

InputDateCk(inpdate, "Enter date to view from, current week or default slots (C/D): ", "CD");	// gets the input for the week or the additional options

if(strcmpi(inpdate, "C") == 0)
	{
	GetToday(inpdate);
	} //endif nothing is entered
else if (strcmpi(inpdate, "D") == 0)
	{
	OutputDJAvailability(0); // technically does the correct thing as the guest slots are just the availability of DJ 0

	cout << "\n\nPress any key to return";
	getch();
	return 0;
	} //endelse if the inputted option is view default slots

cout << "\n          ";

// outputting the times
for(time = 0; time < 24; time++)
	{
	if(time < 10)
			{
			cout << "0";
			} //endif
	cout << time << " ";
	} //endfor

GetClosestMonday(inpdate);
dtindex = CalculateScheduleDateIndex(inpdate);	// getting the starting index for the loop

for(day = 0; day < 7; day++)
	{
	dayinmo = GetDayInMonth(day + dtindex);

	printf("\n%s(%.2d) ", daysofweek[day], dayinmo);
	
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

choice = InputYNChoiceCk("\nShould The Events be added to the Schedule (y/n): ");	// gets the input if the events should be added or not

if(choice == 'n')
	{
	return 0;
	} //endif choice is no

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
	} //endfor loop through the events and check they have been added to the schedule

for(count = 0; count < nei; count++)
	{
	type = GetEventType(eventno[count]);

	// if the type is not a show go to the next event
	if(type != 'S')
		continue;
	
	plcheck = PlaylistDurationCheck(eventno[count], 0, 0);

	if(plcheck != 0)
		{
		cout << "\n\nID: " << eventno[count];
		cout << "\nTitle: " << evtitle[count];
		cout << "\nPlaylist of incorrect length";
		} //endif the duration of the playlist is less than 
	} //endfor loop through the events and check the playlists are of correct length

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

editschedulechoice = GetMenuChoice(1, 3);

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
        if(GetGLOA() == 3)
            {
            GuestSlots();
            } //endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
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
int idjno = 0;

char choice;
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

ReadBackScheduleFile();

do
	{
	clrscr();
	cout << "\nChange DJ Availability";
	cout << "\n======================\n";

	if(idjno == 0)
		{
		InputDJNumberCk(indjno, "\nEnter DJ Number: ");
		idjno = atoi(indjno);
		} //endif there is already a DJ number entered

	OutputDJAvailability(idjno);

	choice = InputMultiOptnChoiceCk("\n\nAdd or Remove Available Slot (A/R): ", "AR");	// gets the slot options

	if(choice == 'A')
		{
		InputDayOfWeekCk(inday, "\nEnter Day: ");	// gets the day of the week
        InputHourCk(intime, "\nEnter Time: ");  // gets the time of day

		day = FindInArray04(daysofweek, inday, 7); // getting the day
		time = atoi(intime); // getting the time

		sch[0][day + 7*idjno][time][0] = 'A';
		} //endif
	else if(choice == 'R')
		{
		InputDayOfWeekCk(inday, "\nEnter Day: ");	// gets the day of the week
		InputHourCk(intime, "\nEnter Time: ");  // gets the time of day

		day = FindInArray04(daysofweek, inday, 7); // getting the day
		time = atoi(intime); // getting the time

		sch[0][day + 7*idjno][time][0] = '*';
		} //endif

	cout << "\nContinue making changes (y/n): ";
	choice = cin.get();
	cin.get();

	} //enddowhile choice is yes 
	while(choice == 'y');

ReWriteScheduleFile();

cout << "\nSuccess - Availability has been changed";

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

OutputDJAvailability(0);    // technically does the correct thing as the guest slots are just the availability of DJ 0
choice = InputMultiOptnChoiceCk("\n\nAdd or Remove a Guest Slot (A/R): ", "AR");

InputDayOfWeekCk(inday, "\nEnter Day: ");	// gets the day of the week
InputHourCk(intime, "\nEnter Time: ");  // gets the time of day

day = FindInArray04(daysofweek, inday, 7);  // getting the day
time = atoi(intime);    // getting the time

if(choice == 'A')
	{
	sch[0][day][time][0] = 'G';
	} //endif add a guest slot set the guest slot
else if(choice == 'R')
	{
	sch[0][day][time][0] = '*';
	} //endif remove a guest slot reset the guest slot


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
int approved = -1; // starting with -1 as it could not be a holiday
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

void OutputHolidays(int holids[], int size, int check)
{
char djnams[500][64];
char approv[500][3];
int tdjid = 0;
char tref[10];
int count;
int maxlen;
int hollen;
char outformat[32] = "%-s\t%-s";
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

	printf(outformat, "ID", "DJ", "Start Date", "End Date", "Approved");
	} //endif should show if checked
else
	{
	printf(outformat, "ID", "DJ", "Start Date", "End Date");
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
		printf(outformat, eventno[holids[count]], djnams[count], sdate, edate, approv[count]);
		} //endif check they output approved or not
	else
		{
		printf(outformat,  eventno[holids[count]], djnams[count], sdate, edate);
		} //endelse
	cout << '\n';
	} //endfor
}

void AddApprovedHolidayToSchedule(char holref[10])
{
int duri;
int count;
int loc;
int attdj;
char slot[32];
char tslot[32];
char nslot[32];
int curhour;
int itim;
int idat;

attdj = GetAttendingDJ(holref);
loc = FindInArray10(eventno, holref, nei);

duri = atoi(evdur[loc]);
itim = CalculateScheduleTimeIndex(evtime[loc]);
idat = CalculateScheduleDateIndex(evdate[loc]);

GetScheduleSlot(slot, holref, attdj);
slot[1] = 'A';

for(count = 0; count < duri; count++)
	{
	curhour = (itim + count) % 24;

	if((count > 0) && (curhour == 0))
		{
		idat += 1;
		} //endif curhour is on new day or if the duration is equal to the count increment the date
	
	GetScheduleSlot(tslot, idat, curhour, attdj);

	if(tslot[0] == 'S')
		{
		tslot[0] = 'R';	// changing the event to a replay
		strcpy(nslot, slot);
		strcat(nslot, tslot);
		SetScheduleSlot(nslot, idat, curhour, attdj);
		} //endif the event is a show copy the ammended slot into the slot
	else
		{
		SetScheduleSlot(slot, idat, curhour, attdj);
		} //endelse set the schedule slot
	} //endfor loop though duration of event
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

holidayschoice = GetMenuChoice(1, 6);

switch(holidayschoice)
	{
	case 1: 
		{
        if(GetGLOA() == 3)
            {
            ViewHolidays();
            }//endif the level of access is 3
        else
            {
            ViewHolidaysByDJ();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 2: 
		{
		BookHolidays();
		clrscr();
		break;
		} //endcase
	case 3: 
		{
		ChangeHolidays();
		clrscr();
		break;
		} //endcase
	case 4: 
		{
		RemoveHolidays();
		clrscr();
		break;
		} //endcase
	case 5: 
		{
        if(GetGLOA() == 3)
            {
            ApproveHolidays();
            }//endif the level of access is 3
        else
            {
            cout << "\nError: Not authorised to access this";
			getch();
            }//endelse the level of access isn't 3
		clrscr();
		break;
		} //endcase
	case 6: 
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

vholch = GetMenuChoice(1, 4);

switch(vholch)
	{
	case 1: 
		{
		ViewHolidaysByDJ();
		clrscr();
		break;
		} //endcase
	case 2: 
		{
		ViewHolidaysByDate();
		clrscr();
		break;
		} //endcase
	case 3: 
		{
		ViewHolidaysByUnapproved();
		clrscr();
		break;
		} //endcase
	case 4: 
		{
		clrscr();
		break;
		} //endcase
	} //endswitch

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

InputDJNumberCk(indjno, "\nEnter DJ Number: ");  // gets the valid DJ number for an existing DJ

idjno = atoi(indjno);

LocateDJ(idjno);
GetToday(today);

dtindex = CalculateScheduleDateIndex(today);

cout << '\n';

// update this bit to use the output with case
for (count = dtindex; count < 367; count++)
	{
	type = GetScheduleType(count, 0, idjno);

	cevno = GetScheduleEventNumber(count, 0, idjno);
	
	if(type == 'H' && (top == 0 || holrefs[top-1] != cevno))
		{
		holrefs[top++] = cevno;
		} //endif the type is a holiday and that it isn't already in the stack (it won't be in the stack if it is empty)
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
int approved;
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
		approved = IsHolidayApproved(eventno[count]);

		if(approved == 0)
			{
			holrefs[top++] = atoi(eventno[count]);
			} //endif not approved
		} //endif
	} //endfor

OutputHolidays(holrefs, top, 1);

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
int count;
int evnos[50];
int nevents;
char type;
char tevnoc[10];
char evno[10];
char durc[10];
char schentry[32] = "";
int cont = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nBook Holidays";
cout << "\n=============\n";

InputDJNumberCk(djnoc, "\nEnter DJ Number: ");  // gets the valid DJ number for an existing DJ
InputDateCk(sdate, "\nEnter Start Date: "); // gets partially validated start date

idjno = atoi(djnoc);    // gets the DJ number as an integer

while(cont == 0)
    {
	InputDateCompCk(edate, "\nEnter End Date: ", sdate, 1);	// gets validated date after the start date
	nevents = FindAllEventsOfTypeBetweenDates(evnos, 'G', sdate, edate, idjno);	// gets all of the guest events between the start and the end date of the event

    if(nevents != 0)
        {
        cout << "\nError: Guest event occurs during that holiday cannot book";
        continue;   // restart the loop
        } //endif there are guest events on that interval for the DJ

    cont = 1;   // continue the adding process since the date must be valid for the loop to reach the end
    } //endwhile loop until a valid date has been entered

sdati = CalculateScheduleDateIndex(sdate);  // gets the start date in the schedule
edati = CalculateScheduleDateIndex(edate);  // gets the end date in the schedule

GenerateEventNumber(evno);  // generates the holiday reference
cout << "\nHoliday Reference: " << evno;

// calculating the diff in days * 24 so it is in hours
dur = 24 * (edati - sdati);
itoa(dur, durc, 10);

// copies locals into their respective globals
strcpy(eventno[nei], evno);
strcpy(evdate[nei], sdate);
strcpy(evtime[nei], "00:00");
strcpy(evlocation[nei], "Holiday");
strcpy(evdur[nei], durc);

cout << "\nSuccess - Holiday has been requested\n";

nei = nei + 1;
itoa(nei, nec, 10);

GenerateScheduleToken(schentry, "HU", evno);
SetScheduleSlot(schentry, sdate, "00:00", idjno);
AddLinksEntry(evno, djnoc);

/* // automatically adds the unapproved bit to the schedule
AddEventToSchedule(evno, 'H', idjno); */

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

changeholidayschoice = GetMenuChoice(1, 3);

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
int cont;
int evnos[500];
int nevents;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nChange Holidays Start Date";
cout << "\n==========================\n";

InputEventReferenceCheck(holref, "\nEnter Holiday Reference: ");	// gets the validated holiday reference
evloc = FindInArray10(eventno, holref, nei);	// finds the holiday in the events file

strcpy(sdate, evdate[evloc]);	// copies the start date into a temp variable
strcpy(edate, sdate);	// copying start date to end date
AddDays(edate, duri / 24);	// getting end date

attdj = GetAttendingDJ(holref);	// gets the DJ who's holiday it is
duri = atoi(evdur[evloc]);	// converts the duration to an integer

cout << "\nCurrent Start Date: " << sdate;

while(cont == 0)
    {
	InputDateCompCk(ndate, "\nNew Start Date: ", edate, 0);	// gets new start date before the end date
	nevents = FindAllEventsOfTypeBetweenDates(evnos, 'G', sdate, edate, attdj);	// gets all of the guest events between the start and the end date of the event

    if(nevents != 0)
        {
        cout << "\nError: Guest event occurs during that holiday cannot have the start date there";
        continue;   // restart the loop
        } //endif there are guest events on that interval for the DJ

    cont = 1;   // continue the adding process since the date must be valid for the loop to reach the end
    } //endwhile loop until a valid date has been entered

RemoveEventFromSchedule(holref);	// removing the event from the schedule to rewrite it
eindx = CalculateScheduleDateIndex(edate);	// gets the location of the end date in the schedule
nduri = (eindx - CalculateScheduleDateIndex(ndate)) * 24; // calculates difference in days then multiplies by 24 to get duration in hours

itoa(nduri, evdur[evloc], 10); // copy new duration into duration field
strcpy(evdate[evloc], ndate); // copy new start date into date

AddEventToSchedule(holref, 'H', attdj);

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
int evnos[500];
int nduri;
int eindx;
int evloc;
int attdj;
int cont;
int nevents;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nChange Holidays End Date";
cout << "\n========================\n";

InputHolidayReferenceCheck(holref, "\nEnter Holiday Reference: ");	// gets the validated holiday reference
evloc = FindInArray10(eventno, holref, nei);	// finds the holiday in the events file

strcpy(edate, evdate[evloc]);	// copying the start date into the end date for the addition to find the end date
AddDays(edate, atoi(evdur[evloc]) / 24);	// calculates the end date
attdj = GetAttendingDJ(holref);	// gets the DJ who's holiday it is

cout << "\nCurrent End Date: " << edate;

while(cont == 0)
    {
	InputDateCompCk(ndate, "\nNew End Date: ", evdate[evloc], 0);	// gets new start date before the end date
	nevents = FindAllEventsOfTypeBetweenDates(evnos, 'G', evdate[evloc], ndate, attdj);	// gets all of the guest events between the start and the end date of the event

    if(nevents != 0)
        {
        cout << "\nError: Guest event occurs during that holiday cannot have the start date there";
        continue;   // restart the loop
        } //endif there are guest events on that interval for the DJ

    cont = 1;   // continue the adding process since the date must be valid for the loop to reach the end
    } //endwhile loop until a valid date has been entered

RemoveEventFromSchedule(holref);	// removing the event from the schedule to rewrite it
eindx = CalculateScheduleDateIndex(edate);	// gets the location of the end date in the schedule
nduri = (eindx - CalculateScheduleDateIndex(ndate)) * 24; // calculates difference in days then multiplies by 24 to get duration in hours

itoa(nduri, evdur[evloc], 10); // copy new duration into duration field
strcpy(evdate[evloc], ndate); // copy new start date into date

AddEventToSchedule(holref, 'H', attdj);

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
int attdj;
char holref[10];
char tdate[11];
char choice;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nRemove Holidays";
cout << "\n===============\n";

InputHolidayReferenceCheck(holref, "\nEnter Holiday Reference: ");	// gets the reference of the holiday
find = FindInArray10(eventno, holref, nei);	// gets the location of the event in the file number
attdj = GetAttendingDJ(holref);	// gets the DJ who's event it is
strcpy(tdate, evdate[find]);	// saving the date for the final output

cout << "\nWarning: Removing the holiday will require you to add the DJ back to all events they were on";
choice = InputYNChoiceCk("\nAre you sure you want to delete the holiday (y/n): ");	// getting confirmation of deletion

if(choice == 'y')
	{
	if(IsHolidayApproved(holref) == 1)
		{
		RemoveEventFromSchedule(holref); // clears the holiday off the schedule
		RemoveEventLinksEntries(holref); // removes all entries with this event
		RemoveEvent(find);
		} //endif the holiday is approved remove it from the events file
	else
		{
		SetScheduleSlot("*", evdate[find], evtime[find], attdj); // clears the holiday off the schedule
		RemoveEventLinksEntries(holref); // removes all entries with this event
		RemoveEvent(find);
		} //endelse the holiday isn't approved remove
	} //endif shouldn't remove the holiday

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
char remch;
int isapp = 0;

ReadBackEventFile();
ReadBackScheduleFile();
ReadBackEventLinksFile();

clrscr();
cout << "\nApprove Holidays";
cout << "\n================\n";

InputHolidayReferenceCheck(holref, "\nEnter Holiday Reference: ");	// gets the reference of the holiday
loc = FindInArray10(eventno, holref, nei);	// finds the holiday in the events file
attdj = GetAttendingDJ(holref);	// gets the DJ who's hoiliday it is
isapp = IsHolidayApproved(holref);	// finds whether the holiday is approved or not
choice = InputMultiOptnChoiceCk("\nEnter to Approve or Unapprove Holiday (A/U): ", "AU");	// gets the choice of what to do to the holiday

if((choice == 'U') && (isapp == 0))
	{
	cout << "\nError: Holiday already unapproved";
	} //endif already unapproved
else if(choice == 'U')
	{
	remch = InputYNChoiceCk("\nWould you like to remove this holiday (y/n): "); // gets yes no choice of whether to remove or not

	if(remch == 'y')
		{
		SetScheduleSlot("*", evdate[loc], evtime[loc], attdj);	// removing the event from the schedule
		RemoveEventLinksEntries(holref);	// removing all links to the event
		RemoveEvent(loc);	// removing the event from the events file
		cout << "\nSuccess - The holiday has been removed\n";
		} //endif the holiday should be removed remove it
	else
		{
		cout << "\nWarning: The holiday will still prevent events being added to the DJ at 00:00";
		} //endelse output warning about assigning events
	} //endelseif the choice is to unapprove the holiday and the holiday is approved

if((choice == 'A') && (isapp == 1))
	{
	cout << "\nError: Holiday already approved";
	} //endif already unapproved
else if(choice == 'A')
	{
	GetScheduleSlot(slot, holref, attdj);
	slot[1] = choice;
	AddApprovedHolidayToSchedule(holref);
	cout << "\nSuccess - The holiday on " << evdate[loc] << " has been approved\n";
	} //endelseif the choice is to approve the DJ then set all the slots correct

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

int FindInArrayInt(int array[], int item, int size, int start)
{
int count = 0;

for (count = start; count < size; count++)
	{
	if(array[count] == item)
		{
		return count;
		} //endif
	} //endfor

return -1;
}

int FindInString(char string[], char substring[], int size, int start)
{
int count;
int find = -1;
int substrlen = strlen(substring);

for (count = start; count < (size - substrlen); count++)	// size - substringlen because access violation will happen if trying to compare after end of string
	{
	if(strnicmp(&string[count], substring, substrlen) == 0)
		{
		find = count;
		break;
		} //endif the substring is found
	} //endfor loop through whole string

return find;
}

int FindCharInString(char string[], char character, int size, int start)
{
int count;
int find = -1;

for (count = start; count < size; count++)
	{
	if(string[count] == character)
		{
		find = count;
		break;
		} //endif the character is found
	} //endfor loop through whole string

return find;
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

int indecies[500];

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
	itoa(indecies[count], refnoc, 10); // converts the song id to a string
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

int MakeArrayUniqueInt(int array[], int size)
{
int nsize;
int sel;
int count;
int loc;

nsize = size;

for (count = 0; count < size; count++)
	{
	sel = array[count];
	loc = FindInArrayInt(array, sel, nsize, count + 1);	// finding each element in the array after its starting pos

	while(loc != -1)
		{
		swap(array[loc], array[nsize - 1]);	// moving the number to the end of the array
		array[nsize - 1] = -1; // setting the duplicate element as -1
		nsize = nsize - 1;	// decreasing the size of the array to cut off the duplicate
		loc = FindInArrayInt(array, sel, nsize, count + 1);	// finding the next occurance
		} //endwhile another of the same number has been found
	} //endfor loop though the array

return nsize;
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
sprintf(time, "%s:%s", hrsc, minc);
}

int FindNextReferenceNumber(int testnumber, char numberarr[][10], int size)
{
int count;
int result = testnumber;
int tmpnum;

for (count = 0; count < size; count++)
    {
    tmpnum = atoi(numberarr[count]); // converts the number to an integer

    if(tmpnum == result)
        {
        result = result + 1;
        return FindNextReferenceNumber(result, numberarr, size); // test it again and return the new found value
        } //endif the number is equal to the result
    } //endfor

return result; // return the value if it hasn't been found
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

// gets the ys in the brackets yy(yy)
endyr = year - 100*(floor(year/100));

if(year % 4 == 0)
        {
        daysmo[1] = 29;
        dooms[0] = 4;
        dooms[1] = 29;
        } //endif leap year

// gets the anchor of the century adds it to the number of leap years + number of years and all of that mod 7
yrcode = (anchor + (int)floor(endyr/4) + endyr) % 7;

day = day - dooms[month - 1];

day = (((day % 7) + yrcode) % 7);

return day;
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

int CompareWordsAlphabetically(char word1[], char word2[])
{
char letter1;
char letter2;
int result = 1;
int minlen;
int index;

letter1 = word1[0];
letter2 = word2[0];

minlen = min(strlen(word1), strlen(word2));

if(strcmpi(word1, word2) == 0)	
	{
	result = 0;
	} //endif
else if((int)letter2 < (int)letter1)
	{
	result = -1;
	} //endif the ASCII value of the first letter is less than the second
else if (letter2 == letter1)
	{
	for (index = 1; index < minlen; index++)
		{
		letter1 = word1[index];
		letter2 = word2[index];

		if((int)letter2 < (int)letter1)
			{
			result = -1;
			break;
			} //endif the ASCII value of the first letter is less than the second
		} //endfor loop through all letters in the words checking until different one is found
	}

return result;
}

int BinaryDateSearch(char dates[128][11], char date[11], int start, int end)
{
int midp;
int dcomp;
int found = -1;

if((end - start) == 1)
	{
	return -start;
	} //endif the size of the remining list is 1

// getting the midpoint of the list
midp = start + floor((end - start) / 2);

dcomp = DateComp(dates[midp], date);

if(dcomp == 0)
	{
	found = midp;
	} //endif they are the same date set found as the midpoint
else if(dcomp == -1)
	{
	found = BinaryDateSearch(dates, date, start, midp);
	} //endelseif the date is before the midpoint
else if(dcomp == 1)
	{
	found = BinaryDateSearch(dates, date, midp, end);
	} //endelseif the date is after the midpoint

return found;
}

int ConvertMonth(char month[4])
{
// the numerical month
int nomonth = 0;
int count;
char lookupindex[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

for(count = 0; count < 12; count++)
	{
	if(strcmpi(month, lookupindex[count]) == 0)
		{
		nomonth = count + 1;
		break;
		} //endif the month has been found break out of the loop
	} //endfor loop through lookup index to find the month

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

diff = abs(itim2 - itim1);	// getting the difference between them

duration = ceil(diff / 60);	// converting difference into mins rounding up so if 1 min over it counts as an hour

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

void GetClosestMonday(char indate[11])
{
char inpdate[11];
int dayofwk;

if(indate[0] == '\0')
	{
	GetToday(inpdate);
	} //endif nothing is entered
else
	{
	strcpy(inpdate, indate);
	} //endelse copy the inputted date into the local date

dayofwk = FindDayOnDate(inpdate);

if(dayofwk == 0)
	{
	dayofwk = 7;
	} //endif the day is a Sunday set the day to 7 so that it goes back 6 days not -1

if(dayofwk != 1)
	{
	SubtractDays(inpdate, dayofwk - 1);
	} //endif the day is not a Monday

// copies the calculated date into the parameter
strcpy(indate, inpdate);
}

int DateComp(char date1[11], char date2[11])
{
int comp = 1;

if(strcmpi(date1, date2) == 0)
	{
	comp = 0;
	} //endif they are the same date
else if((CalculateNumericalDate(date2) - CalculateNumericalDate(date1)) < 0)
	{
	comp = -1;
	} //endelseif convert them to numerical values to compare if the 2nd date is before the 1st


return comp;
}

int TimeComp(char time1[6], char time2[6])
{
int comp = 1;

if(strcmpi(time1, time2) == 0)
	{
	comp = 0;
	} //endif they are the same time
else if((CalculateScheduleTimeIndex(time1) - CalculateScheduleTimeIndex(time2)) < 0)
	{
	comp = -1;
	} //endelseif convert them to numerical values to compare if the 2nd time is before the 1st

return comp;
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

int daysinyr = 365;

// days in each month
int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// splits up the date format
sscanf(date, "%d/%d/%d", &day, &month, &year);

// checks if leap year and updates the days in each month
if(year % 4 == 0)
	{
	daysmo[1] = 29;
	daysinyr += 1;
	} //endif leap year

curdati = day;

// decreasing the month by 1 so that it can be used as an index access
month = month - 1;

while(curdati <= days)
	{
	if (month == 0)
		{
		ConvertDateToStr(date, 31, 12, year-1);
		SubtractDays(date, abs(day - days));
		return;
		}

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
int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	// days in each month

sscanf(date, "%d/%d/%d", &day, &month, &year);	// splits up the date format

// checks if leap year and updates the days in each month
if(year % 4 == 0)
        {
        daysmo[1] = 29;
        } //endif leap year

month = month - 1;	// decreasing the month by 1 so that it can be used as an index access

curdati = day + days;
while(curdati > daysmo[month])
	{
	curdati -= daysmo[month];
	month += 1;
	} //endwhile

ConvertDateToStr(date, curdati, month + 1, year);	// converts the date back into the format dd/mm/yyyy
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

int GetMenuChoice(int min, int max)
{
int stop = 1;
int choice;

while(stop == 1)
    {
    cout << "\n\nEnter Choice: ";
    cin >> choice;

    // adding this to stop input skipping
    cin.ignore(1, '\n');

    stop = abs(RangeCk(choice, min, max, 1));
    } //endwhile the menu shouldn't continue asking

return choice;
}

void ProgressBar(int current, int total, int len)
{
int nchars;
int count;
float percent;

percent = (float)current / total;	// getting (% done)
nchars = percent * len;	// % done * len

printf("\r[");
for (count = 0; count < nchars; count++)
	{
	printf("#");
	} //endfor loop for all of the current done

for (count = 0; count < (len - nchars); count++)
	{
	printf(" ");
	} //endfor loop until the end of the bar

printf("] %d%% Done", (int)(100 * (percent)));
}

#pragma endregion

#pragma region Validation

/* ------------------------------
 *          Validation
 * ------------------------------ 
 */

int DateRangeCk(char date[11], char mindate[11], char maxdate[11])
{
int x;
int min;
int max;
int rtval = 0;

x = CalculateNumericalDate(date);

min = CalculateNumericalDate(mindate);

max = CalculateNumericalDate(maxdate);

if(x < min)
	{
	rtval = -1;
	} //endif the date is less than the minimum
else if(x > max)
	{
	rtval = 1;	
	} //endelseif the date is greater than the maximum

return rtval;
}

int IsNumber(char instr[], int output)
{
int len = strlen(instr);
int count = 0;
int isnum = 1;

for (count = 0; count < len; count++)
	{
	if(isdigit(instr[count]) == 0)
		{
		isnum = 0;
		break;
		} //endif the character isn't a digit break and mark the string as not a number
	} //endfor loop through the string and check each character is a digit

if((isnum == 0) && (output == 1))
    {
    cout << "\nError: Inputted value isn't a number";
    } //endif should output the error message

return isnum;
}

int RangeCk(int value, int min, int max, int output)
{
int isvalid = 0;

if(value < min)
	{
	isvalid = -1;
	} //endif below the minimum
else if(value > max)
	{
	isvalid = 1;
	} //endif above the maximum

if ((output == 1) && (isvalid != 0))
	{
	if(isvalid == -1)
		{
		cout << "\nError: Inputetd Value Below Acceptable Range";
		} //endif isvalid is below the acceptable range
	else
		{
		cout << "\nError: Inputetd Value Above Acceptable Range";
		} //endelse if isvalid isn't -1 it will be 1
	} //endif should output

return isvalid;
}

int PresenceCk(char input[])
{
int isvalid = 1;

if(strlen(input) == 0)
    {
    cout << "\nError: A value needs to be inputted";
    isvalid = 0;
    } //endif the length of the input is 0
else if(isalnum(input[0]) == 0)
    {
    isvalid = 0;
    cout << "\nError: A value needs to be inputted";
    } //endelseif the first character is not alphaneumeric

return isvalid;
}

int LengthCk(char input[], int min, int max)
{
int len;
int isvalid = 1;
int rngck;

len = strlen(input);

rngck = RangeCk(len, min, max);

if(rngck == -1)
    {
    cout << "\nError: The length of the input is below the acceptable length";
    isvalid = 0;
    } //endif the length is below the minimum
else if(rngck == 1)
    {
    cout << "\nError: The length of the input is above the acceptable length";
    isvalid = 0;
    } //endelseif the length is above the maximum

return isvalid;
}

int DateValidation(char datevalue[11])
{
int valid = 1;
int length;
float years;
int months;
int days;

float yearsdivans;
int yearsfloorans;
int daysmo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// getting the length of the date
length = strlen(datevalue);

if(LengthCk(datevalue, 10, 10) == 0)
    {
	cout << " 10";
	valid = 0;
	return valid;
	} //endif the length isn't correct

if((datevalue[2] != '/') || (datevalue[5] != '/'))
	{
	cout << "\nEnter a date with the correct / positions (dd/mm/yyyy)";
	valid = 0;
	return valid;
	} //endif the slashes aren't in the correct places

sscanf(datevalue, "%d/%d/%f", &days, &months, &years);	// get the days as an integer, months as an integer, years as float
yearsdivans = years / 4; // divide the years by 4
yearsfloorans = floor(yearsdivans); // round years down

if((int)yearsdivans == yearsfloorans)
	{
	daysmo[1] = 29;	// setting the number of days in Feb
	} //endif it is a leap year

if(RangeCk(months, 1, 12) != 0)
	{
	cout << "\nError: Month not in the range 1 to 12";
	valid = 0;
	return valid;
	} //endif the month is not in the range 1 to 12

if(RangeCk(days, 1, daysmo[months - 1]) != 0)
	{
	cout << "\nError: Days not in the range 1 to " << daysmo[months - 1];
	valid = 0;
	} //endif the day isn't in the range 1 to num of days in month

return valid;
}

int ValidateEmailAddr(char emailaddr[32])
{
int valid = 1;
int length = strlen(emailaddr);
int atloc = -1;
int dotloc = -1;

if(LengthCk(emailaddr, 5, 32) == 0)
	{
	valid = 0;
	} //endif the length isn't sufficient
	
atloc = FindInString(emailaddr, "@", length-2, 1); // length -2 because you need x@y.z so you need at least 3 characters after the @

if(atloc == -1)
	{
	valid = 0;
	cout << "\nError: Characters needed before @ symbol";
	} //endif @ not found after position 1

dotloc = FindInString(emailaddr, ".", length, atloc + 1); // the . has to be after @ so can start at atloc + 1

if(dotloc == -1)
	{
	valid = 0;
	cout << "\nError: Characters needed before the dot";
	} //endif dot not found

if((dotloc + 1) == length)
	{
	valid = 0;
	cout << "\nError: Characters needed after the dot";
	} //endif check that there are characters after the dot

return valid;
}

int PhoneNumberFormatCheck(char phonenumber[12])
{
int valid = 1;
int length = strlen(phonenumber);

if(LengthCk(phonenumber, 11, 11) != 1)
	{
	valid = 0;
	cout << " of 11 digits";
	} //endif not of correct length

if(phonenumber[0] != '0')
	{
	valid = 0;
	cout << "\nError: Please enter a phone number beginning with a 0";
	} //endif the phone number doesn't start with a 0

if(IsNumber(phonenumber) == 0)
	{
	valid = 0;
	cout << "\nError: Please enter a phone number containing only digits";	
	} //endif the phone number isn't a number

return valid;
}

int ValidGenreCk(char inpgenre[24])
{
int valid = 1;
int loc;
char genres[][24] = { "Rock", "Pop", "Electronic", "Jazz", "Classical", "Heavy rock", "Metal", "Hip Hop", "Rap", "Country", "Electric", "Dance", "Soul", "Folk", "Musical Theatre", "House", "Disco", "Techno" };

loc = FindInArray24(genres, inpgenre, 18);

if(loc == -1)
    {
    valid = 0;
    cout << "\nError: Unknown genre inputted";
    } //endif the genre hasn't been found

return valid;
}

int ValidateTimeFormat(char inptime[6])
{
int valid = 1;
int fpart;
int spart;
int count;

for(count = 0; count < 5; count++)
	{
	if(count == 2)
		{
		count++;
		} //endif count is the colon index

	if (isdigit(inptime[count]) == 0)
		{
		valid = 0;
		cout << "\nError: There should only be digits not other characters";
		break;
		} //endif the position isn't a digit	
	} //endfor loop through the time to find if all the numbers are digits

if(valid == 0)
	{
	return valid;
	} //endif the time is already invalid

if(inptime[2] != ':')
	{
	cout << "\nError: Colon in the incorrect position";
	} //endif the colon isn't in the correct position

sscanf(inptime, "%d:%d", &fpart, &spart);

if(RangeCk(fpart, 0, 59) != 0)
	{
	cout << "\nError: Hours not in the range from 0-59";
	valid = 0;
	} //endif the minutes section is not in the range

if(RangeCk(spart, 0, 59) != 0)
	{
	cout << "\nError: Minutes not in the range from 0-59";
	valid = 0;
	} //endif the seconds section is not in the range

return valid;
}

int ValidatePlaytimeFormat(char inpltime[6])
{
int valid = 1;
int fpart;
int spart;
int count;

for(count = 0; count < 5; count++)
	{
	if(count == 2)
		{
		count++;
		} //endif count is the colon index

	if (isdigit(inpltime[count]) == 0)
		{
		valid = 0;
		cout << "\nError: There should only be digits not other characters";
		} //endif the position isn't a digit	
	} //endfor loop through the time to find if all the numbers are digits

if(inpltime[2] != ':')
	{
	cout << "\nError: Colon in the incorrect position";
	} //endif the colon isn't in the correct position

sscanf(inpltime, "%d:%d", &fpart, &spart);

if(RangeCk(fpart, 0, 59) != 0)
	{
	valid = 0;
	cout << "\nError: Minutes not in the range from 0-59";
	} //endif the minutes section is not in the range

if(RangeCk(spart, 0, 59) != 0)
	{
	valid = 0;
	cout << "\nError: Seconds not in the range from 0-59";
	} //endif the seconds section is not in the range

return valid;
}

int YesNoValidation(char choice)
{
int valid = 0;

if((choice == 'y') || (choice == 'Y') || (choice == 'n') || (choice == 'N'))
    {
    valid = 1;
    } //endif a valid choice is entered
else
    {
    cout << "\nError: Invalid choice entered";
    } //endelse a valid choice isn't entered

return valid;
}

int MultiOptionValidation(char choice, char optns[])
{
int valid = 0;
int count;
int len;

len = strlen(optns);

for (count = 0; count < len; count++)
	{
	if((choice == tolower(optns[count])) || (choice == toupper(optns[count])))
		{
		valid = 1;
		break;
		} //endif the choice has been found
	} //endfor loop through the options and check that they are valid

if(valid == 0)
    {
    cout << "\nError: Invalid choice entered";
    } //endelse a valid choice isn't entered

return valid;
}

int ValidatePrice(char inprice[6])
{
int valid = 1;
int count;

for(count = 0; count < 5; count++)
	{
	if(count == 2)
		{
		if(inprice[2] != '.')
			{
			valid = 0;
			cout << "\nError: Dot not in the correct place";
			break;
			} //endif count is the dot index

		count++;
		} //endif the price doesn't have a dot in the correct place

	if (isdigit(inprice[count]) != 0)
		{
		valid = 0;
		cout << "\nError: There should only be digits not other characters";
		break;
		} //endif the position isn't a digit	
	} //endfor loop until the end of the string and check that each part is a digit

return valid;
}

int EventCollisionCheckTime(char date[11], char starttim[6], char endtim[6], int djid)
{
int collides = 0;
int evnos[500];
int nevs;

nevs = FindAllEventsBetweenTimes(evnos, date, starttim, endtim, djid);	// finds all of the events between the times for a DJ
if(nevs != 0)
	{
	collides = 1;
	} //endif there are events found in the search then there is a collision

return collides;
}

int EventCollisionCheckEvent(char evnoc[10], int djid)
{
int collides = 0;
int evnos[500];
int nevs;
char etime[6];
int loc;
int dati;
int duri;

loc = FindInArray10(eventno, evnoc, nei);	// finds the event in the events file
dati = CalculateScheduleDateIndex(evdate[loc]);	// gets the location of the event in the schedule
duri = atoi(evdur[loc]);	// converts the duration to an integer
strcpy(etime, evtime[loc]);	// copies the start time into the end time for the calc
AddTimes(etime, duri);	// calculates the end date by adding the correct number of days
collides = EventCollisionCheckTime(evdate[loc], evtime[loc], etime, djid);	// checks if there is a collision for the DJ 

return collides;
}

int IsDJAvailable(char date[11], char stime[6], char etime[6], int djid)
{
int available = 1;
int time;
int day;
int stim;
int endtim;

// +6 because the days start from sunday at 0 so if add 6 then mod 7 then it shuffles monday to 0 and sunday to 6
day = (FindDayOnDate(date) + 6) % 7;

stim = CalculateScheduleTimeIndex(stime);
endtim = CalculateScheduleTimeIndex(etime);

for(time = stim; time < (endtim - 1); time++)
    {
    // calculates the starting index by getting the DJ number * 7
    if(sch[0][day + 7 * djid][time][0] != 'A')
        {
        cout << "\nError: DJ isn't available";
        available = 0;
        break;
        } //endif the slot isn't available
	} //endfor loop through the times checking if the DJ is available

return available;
}

int IsGuestSlotAvailable(char date[11], char stime[6], char etime[6])
{
int available = 1;
int time;
int day;
int stim;
int endtim;
int dayit;

// +6 because the days start from sunday at 0 so if add 6 then mod 7 then it shuffles monday to 0 and sunday to 6
day = (FindDayOnDate(date) + 6) % 7;
dayit = CalculateScheduleDateIndex(date);
stim = CalculateScheduleTimeIndex(stime);
endtim = CalculateScheduleTimeIndex(etime);

for(time = stim; time < endtim; time++)
    {
    if(sch[0][day][time][0] != 'G')
        {
        cout << "\nError: No valid guest slot found";
        available = 0;
        break;
        } //endif the slot isn't available
    else if(FindScheduleGuestSlot(dayit, time) == -1)   // finds the first guest event on that date at the time and returns attending DJ 
        {
        cout << "\nError: Guest slot already occupied";
        available = 0;
        break;
        } //endelseif there is a DJ with another guest at the given time
	} //endfor loop through the times checking if the DJ is available

return available;
}

int PasswordSecurityCheck(char inpass[64])
{
// password miniumum length to be valid
int minlen = 10;
int count;
int count2;
int passlen;

int isvalid = 1;

int lencheck = 0;
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
	lencheck = 0;
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

int ValidateFilePath(char filepath[128])
{
int isvalid = 0;

if(isalpha(filepath[0]) == 0)
	{
	cout << "\nError: Path should start with the volume letter";
	} //endif there isn't a letter
else if(filepath[1] != ':')
	{
	cout << "\nError: Path should have a colon after the volume letter";
	} //endelseif there isn't a colon
else if(filepath[2] != '\\')
	{
	cout << "\nError: Path should have a backslash after the colon";
	} //endelseif there isn't a backslash
else
	{
	isvalid = 1;
	} //endelse reached the end so it is valid

return isvalid;
}

void NameInputPresCk(char inpname[48], char outmsg[], int na)
{
char tmpnam[48];

cout << outmsg;
cin.getline(tmpnam, 48);

if((na == 1) && (strcmpi(tmpnam, "na") == 0))
	{
	strcpy(inpname, tmpnam);
	return;
	} //endif the input is na and the na is enabled

while(PresenceCk(tmpnam) != 1)
    {
	if((na == 1) && (strcmpi(tmpnam, "na") == 0))
		{
		strcpy(inpname, tmpnam);
		break;
		} //endif the input is na and the na is enabled
    cout << outmsg;
    cin.getline(tmpnam, 48);
    } //endwhile not allowing user to continue until a name is entered

strcpy(inpname, tmpnam);    // copying the validated input into the parameter
}

void EmailInputCk(char inpemailaddr[48], char outmsg[], int na)
{
char tmpemail[48];

cout << outmsg;
cin.getline(tmpemail, 48);  // inputting the email address

if((na == 1) && (strcmpi(tmpemail, "na") == 0))
	{
	strcpy(inpemailaddr, tmpemail);
	return;
	} //endif the input is na and the na is enabled

while(ValidateEmailAddr(tmpemail) != 1)
    {
	if((na == 1) && (strcmpi(tmpemail, "na") == 0))
		{
		strcpy(inpemailaddr, tmpemail);
		break;
		} //endif the input is na and the na is enabled

    cout << outmsg;
    cin.getline(tmpemail, 48);
    } //endwhile loop until a correct email address has been entered

strcpy(inpemailaddr, tmpemail); // copying the validated input into the parameter
}

void PhoneNumInputCk(char intelno[12], char outmsg[], int na)
{
char tmptelno[12];

cout << outmsg;
cin.getline(tmptelno, 12);  // inputting the phone number

if((na == 1) && (strcmpi(tmptelno, "na") == 0))
	{
	strcpy(intelno, tmptelno);
	return;
	} //endif the input is na and the na is enabled

while(PhoneNumberFormatCheck(tmptelno) != 1)
    {
	if((na == 1) && (strcmpi(tmptelno, "na") == 0))
		{
		strcpy(intelno, tmptelno);
		break;
		} //endif the input is na and the na is enabled

    cout << outmsg;
    cin.getline(tmptelno, 12);
    } //endwhile loop until a correct phone number has been entered

strcpy(intelno, tmptelno); // copying the validated input into the parameter
}

void GenreInputCk(char inpgenre[24], char outmsg[])
{
char tmpstyle[24];

cout << outmsg;
cin.getline(tmpstyle, 24);  // inputting the style

while(ValidGenreCk(tmpstyle) != 1)
    {
    cout << outmsg;
    cin.getline(tmpstyle, 24);
    } //endwhile loop until a valid style has been entered

strcpy(inpgenre, tmpstyle); // copying the validated input into the parameter
}

void InputRefNoCk(char inprefno[10], char outmsg[], int quitoptn)
{
char tmprefno[10];
int cont = 0;

while(cont == 0)
	{
	cout << outmsg;
	cin.getline(tmprefno, 10);  // inputting the refno

	if((quitoptn == 1) && (tmprefno[0] == 'q'))
		{
		cont = 1;
		} //endif the loop should stop
	else if (IsNumber(tmprefno, 1) == 1)
		{
		cont = 1;
		} //endif the entered reference is a number quit
    } //endwhile loop until a valid refno has been entered

strcpy(inprefno, tmprefno); // copying the validated input into the parameter
}

char InputYNChoiceCk(char outmsg[])
{
char choice;

cout << outmsg;
choice = cin.get();  // getting the input choice
cin.get();

while(YesNoValidation(choice) == 0)
    {
    cout << outmsg;
    choice = cin.get();
    cin.get();
    } //endwhile loop until a valid option has been entered

return choice; // copying the choice into the choice parameter
}

void InputTimeCk(char inptime[6], char outmsg[], int valpltim)
{
char tmpinptim[6];

cout << outmsg;
cin.getline(tmpinptim, 6);  // inputting the refno

if(valpltim == 1)
	{
	while(ValidatePlaytimeFormat(tmpinptim) != 1)
		{
		cout << outmsg;
		cin.getline(tmpinptim, 10);
		} //endwhile loop until a valid refno has been entered
	} //endif should validate playtime
else
	{
	while(ValidateTimeFormat(tmpinptim) != 1)
		{
		cout << outmsg;
		cin.getline(tmpinptim, 10);
		} //endwhile loop until a valid refno has been entered
	} //endelse it shouldn't validate the playtime

strcpy(inptime, tmpinptim); // copying the validated input into the parameter
}

void InputTimeCompCk(char inptime[6], char outmsg[], char comptim[6], int after)
{
int valid = 0;
char tmpintim[6];
int comp;

while(valid == 0)
    {
    InputTimeCk(tmpintim, outmsg); // gets partially validated end time
	comp = TimeComp(tmpintim, comptim);	// doing the comparison
	
	if((after == 1) && (comp != 1))
		{
		cout << "\nError: Inputted time is before or the same as " << comptim;
		continue;   // restart the loop
		} //endif the time should be after and is not
	else if((after == 0) && (comp != -1))
		{
		cout << "\nError: Inputted time is after or the same as " << comptim;
		continue;   // restart the loop
		} //endelseif the time should be before and it is after
	
	valid = 1;
	} //endwhile a valid time isn't entered

strcpy(inptime, tmpintim); // copying the validated input into the parameter
}

char InputMultiOptnChoiceCk(char outmsg[], char options[])
{
char choice;

cout << outmsg;
choice = cin.get();  // getting the input choice
cin.get();

while(MultiOptionValidation(choice, options) == 0)
    {
    cout << outmsg;
    choice = cin.get();
    cin.get();
    } //endwhile loop until a valid option has been entered

return choice; // copying the choice into the choice parameter
}

void InputDateCk(char inpdate[11], char outmsg[], char additionals[])
{
char tmpdate[11];
int count = -1;
int dotck = 0;

if(additionals[0] == '.')
	{
	dotck = 1;
	} //endif using dots not /'s

while(count == -1)
	{
	cout << outmsg;
	cin.getline(tmpdate, 11);  // inputting the date

	if(strlen(tmpdate) == 1)
		{
		// starting at dotck as if there is a dot to start the first char isn't wanted
		count = FindCharInString(&additionals[dotck], tmpdate[0], strlen(additionals) - dotck);
		} //endif length is smaller than 2 check if an additional is entered

	if(dotck == 1)
		{
		// setting as slashes
		tmpdate[2] = '/';
		tmpdate[5] = '/';
		} //endif allows dots instead of slashes

	if(count != -1)
		{
		break;
		} //endif the additional option has been found

	count = DateValidation(tmpdate) - 1;	// if the date is invalid then 0 - 1 will be -1 and if it is valid it will be 0
	} //endwhile the count isn't -1

strcpy(inpdate, tmpdate); // copying the validated input into the parameter
}

void InputDateCompCk(char inpdate[11], char outmsg[], char compdate[11], int after, char additionals[])
{
int valid = 0;
char tmpindat[11];
int comp;

while(valid == 0)
    {
    InputDateCk(tmpindat, outmsg); // gets partially validated end date
	comp = DateComp(tmpindat, compdate);	// doing the comparison
	
	if((after == 1) && (comp != 1))
		{
		cout << "\nError: Inputted date is before or the same as " << compdate;
		continue;   // restart the loop
		} //endif the date should be after and is not
	else if((after == 0) && (comp != -1))
		{
		cout << "\nError: Inputted date is after or the same as " << compdate;
		continue;   // restart the loop
		} //endelseif the date should be before and it is after
	
	valid = 1;
	} //endwhile a valid date isn't entered

strcpy(inpdate, tmpindat); // copying the validated input into the parameter
}

void InputEventReferenceCheck(char inref[10], char outmsg[], int valpl)
{
int find = 0;
int cont = 0;
char tmpref[10];

while (cont == 0)
	{
	InputRefNoCk(tmpref, outmsg);	// getting event number input
	find = FindInArray10(eventno, tmpref, nei); // finds the event in the array of events

	if(find == -1)
		{
		cout << "\nError: Event not found";
		continue;	// restarting the loop
		} //endif event not found

	if(GetBaseType(tmpref) == 'H')
		{
		cout << "\nError: Reference inputted is not for an event";
		continue;	// restarting the loop
		} //endif the event type is an event
	
	if(valpl == 1)
		{
		find = FindInArray10(pllinkevno, tmpref, npi);

		if(find == -1)
			{
			cout << "\nError: Playlist doesn't exist";
			continue;	// restarting the loop
			} //endif there isn't a valid playlist for that event
		} //endif should check if there is a playlist
	else if(valpl == -1)
		{
		find = FindInArray10(pllinkevno, tmpref, npi);

		if(find != -1)
			{
			cout << "\nError: Playlist already exists";
			continue;	// restarting the loop
			} //endif there isn't a valid playlist for that event
		} //endelseif the playlist should not already exist 
	
	cont = 1;	// if the loop reaches the end then it is all valid
	} //endwhile loop until a correct event has been inputted

strcpy(inref, tmpref);	// copies input into the parameter
}

void InputEventTypeReferenceCheck(char inref[10], char outmsg[], char type, char errmsg[], int valpl)
{
int cont = 0;

while(cont == 0)
	{	
	InputEventReferenceCheck(inref, outmsg, valpl);

	if(GetBaseType(inref) != type)
		{
		cout << errmsg;
		continue;	// restarts the loop
		} //endif the type of the inputted event isn't the same as the required type
	
	cont = 1;	// if reaches the end then it is valid
	} //endwhile loop until the correct type has been entered
}

void InputHolidayReferenceCheck(char inref[10], char outmsg[])
{
int find = 0;
int cont = 0;
char tmpref[10];

while (cont == 0)
	{
	InputRefNoCk(tmpref, outmsg);	// getting holiday ref input
	find = FindInArray10(eventno, tmpref, nei); // finds the holiday in the array of events

	if(find == -1)
		{
		cout << "\nError: Holiday not found";
		continue;	// restarting the loop
		} //endif holiday not found

	if(GetBaseType(tmpref) != 'H')
		{
		cout << "\nError: Reference inputted is not for a holiday";
		continue;	// restarting the loop
		} //endif the event type is not a holiday
	
	cont = 1;	// if the loop reaches the end then it is all valid
	} //endwhile loop until a correct holiday reference has been inputted

strcpy(inref, tmpref);	// copies input into the parameter
}

void InputEventTitleCheck(char intitle[64], char outmsg[], int exists)
{
char tmptitle[64];
int find = -1;
int valid = 0;

while(valid == 0)
	{
	cout << outmsg;
	cin.getline(tmptitle, 64);

	if(PresenceCk(tmptitle) == 0)
		{
		continue;	// restarting the loop
		} //endif the title isn't valid ask again

	if(exists == 1)
		{
		find = FindInArray64(evtitle, tmptitle, nei);	// finds the event in the events array

		if(find == -1)
			{
			cout << "\nError: No Events With The Title: " << tmptitle << " Found";
			continue;	// restarting the loop
			} //endif no events with inputted title found ask again
		} //endif the event needs to exist

	valid = 1;	// if the loop reaches the end without restarting then it is valid
	} //endwhile a title hasn't been entered

strcpy(intitle, tmptitle);	// copying the input title into the parameter
}

void InputCatalogueNumberCheck(char incatno[10], char outmsg[])
{
int find = -1;
char tmpcatno[10];

while (find == -1)
	{
	InputRefNoCk(tmpcatno, outmsg);	// getting catalogue number input
	find = FindInArray10(mucatno, tmpcatno, nmi); // finds the song in the catalogue

	if(find == -1)
		{
		cout << "\nError: Song not found";
		} //endif song not found
	} //endwhile loop until a correct song has been inputted

strcpy(incatno, tmpcatno);	// copies the input catalogue number into the parameter
}

void InputPlaylistCatnoCheck(char incatno[10], char inevno[10], char outmsg[], int pres, int checked)
{
int find = -1;
int cont = 0;
char tmpcatno[10];

while(cont == 0)
	{
	InputCatalogueNumberCheck(tmpcatno, outmsg);
	find = FindSongInPlaylist(inevno, tmpcatno);

	if((pres == 1) && (find == -1))
		{
		cout << "\nError: Song not found in playlist";	
		continue;	// restarting the loop
		} //endif the song isn't already in the playlist
	else if((pres == 0) && (find != -1))
		{
		cout << "\nError: Song already in playlist";	
		continue;	// restarting the loop
		} //endelseif the song is already in the playlist

	find = FindInArray10(mucatno, tmpcatno, nmi);	// finds the song in the music file
	if((checked == 1) && (mucheck[find][0] != 'Y'))
		{
		cout << "\nError: Song not approved";
		continue;
		} //endif should check if the song is approved and the song isn't checked

	cont = 1;	// if reaches the end of the loop then must be valid	
	} //endwhile there isn't a valid number

strcpy(incatno, tmpcatno);	// copies the inputted catalogue number into the parameter
}

void InputDJNumberCk(char indjnoc[10], char outmsg[], int quitoptn)
{
int find = -1;
char tmpdjnoc[10];

if(GetGLOA() != 3)
	{
	itoa(GetUserDJ(), tmpdjnoc, 10);
	find = 1;
	} //endif the access level is not 3

while(find == -1)
	{
	cout << outmsg;
    cin.getline(tmpdjnoc, 10);
	find = GetDJNumberInput(tmpdjnoc, quitoptn);	// gets the input for the DJ number
	} //endwhile a valid DJ number hasn't been entered

strcpy(indjnoc, tmpdjnoc);	// copies the inputted DJ number into the parameter
}

void InputReferenceNoCheck(char inrefno[10], char refarr[][10], int size, char outmsg[], char errmsg[], int quitoptn)
{
int cont = 0;
char tmprefno[10];

while (cont == 0)
	{
	InputRefNoCk(tmprefno, outmsg, quitoptn);	// getting ref number input

	if(tmprefno[0] == 'q')
		{
		cont = 1;
		} //endif the option is to quit since if the quit option isn't enabled it won't reach this point anyway
	else if(FindInArray10(refarr, tmprefno, size) == -1)
		{
		cout << errmsg;
		} //endif refno not found
	else
		{
		cont = 1;	// if the loop reaches the end then the input is valid
		} //endelse the guest has been found and shouldn't exist
	} //endwhile loop until a correct refno has been inputted

strcpy(inrefno, tmprefno);	// copies the input refno into the parameter
}

void InputGuestNumberCheck(char inguno[10], char outmsg[], int quitoptn)
{
InputReferenceNoCheck(inguno, guestno, ngi, outmsg, "\nError: Guest not found", quitoptn);
}

void InputPriceCk(char inprice[7], char outmsg[])
{
int valid = 0;
char tmprice[7];

while(valid == 0)
	{
	cout << outmsg;
	cin.getline(tmprice, 7);

	if(strcmpi(tmprice, "free") == 0)
		{
		valid = 1;
		break;	// stop looping
		} //endif the price is free stop looping


	if(tmprice[0] == pound)
		{
		valid = ValidatePrice(&tmprice[1]);	// do the validation of the price starting from the irst character
		} //endif the first character is a pound
	else
		{
		valid = ValidatePrice(tmprice);	// do the validation of the price
		} //endelse do the validation starting at the first character
	} //endwhile loop until a valid price has been entered

strcpy(inprice, tmprice);
}

void InputDayOfWeekCk(char inoptn[], char outmsg[])
{
char daysofweek[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
char tmpoptn[64];
int cont = 0;

while(cont == 0)
	{
	cout << outmsg;
	cin.getline(tmpoptn, 64);

	if(FindInArray04(daysofweek, tmpoptn, 7) == -1)
		{
		cout << "\nError: Invalid day entered";
		} //endif the day hasn't been found
	else
		{
		cont = 1;
		} //endelse the input is valid
	} //endwhile an invalid option has been entered

strcpy(inoptn, tmpoptn);	// copies the valid option into the parameter
}

void InputHourCk(char inhour[3], char outmsg[])
{
int valid = 0;
char tmphr[3];
int tmphri;

while(valid == 0)
    {
    cout << outmsg;
    cin.getline(tmphr, 3);

    if(IsNumber(tmphr) == 0)
        {
        cout << "\nError: Number not entered";
        continue;   // restarting the loop
        } //endif the inputted hour is not a number

    tmphri = atoi(tmphr);   // converting the hour to an integer

    if(RangeCk(tmphri, 0, 23) != 0)
        {
        cout << "\nError: Hour not in correct range 0-23";
        continue;   // restarting the loop
        } //endif the hour isn't in the correct range

    valid = 1;  // set valid equal to 1 at the end because if it reaches the end then it is valid
    } //endwhile loop until there is a valid input

strcpy(inhour, tmphr);  // copies the input into the parameter
}

void InputPasswordCk(char inpass[64], char outmsg[], int userno)
{
int find = 0;
int cont = 0;
char tmppass[64];

while (cont == 0)
	{
	cout << outmsg;
	cin.getline(tmppass, 64);
	find = FindInArray64(passwords, tmppass, nui);	// finds the password in the password array

	if((userno == -2) && (find == -1))
		{
		cout << "\nError: Password invalid";
		} //endif the password has to be already there
	else if(userno == -1)
		{
		cont = PasswordSecurityCheck(tmppass);	// validate the password and if it is valid then cont = 1 so looping will end
		} //endelseif the password has to be new
	else if((userno >= 0) && (atoi(usrnos[find]) != userno))
		{
		cout << "\nError: Password incorrect";
		} //endelseif the password should match a given user and the found user isn't the required user 
	else
		{
		cont = 1;
		} //endelse if reaches this point then it is all correct
	} //endwhile loop until a correct input has been entered

strcpy(inpass, tmppass);	// copies the input password into the parameter
}

void InputUsernameCk(char inusrnam[48], char outmsg[], int newusr)
{
char tmpusrnam[48];
int usrloc;
int cont = 0;

while(cont == 0)
	{
	NameInputPresCk(tmpusrnam, outmsg);
	usrloc = FindInArray48(usernames, tmpusrnam, nui);

	if((usrloc != -1) && (newusr == 1))
		{
		cout << "\nError: Username already used";
		} //endif should be a new user and the username is found
	else if((usrloc == -1) && (newusr == 0))
		{
		cout << "\nError: Username not found";
		} //endelseif should be a current user and the username isn't found
	else
		{
		cont = 1;
		} //endelse the username is valid
	} //endwhile loop until a valid username is entered

strcpy(inusrnam, tmpusrnam);	// copying the inputted username into the parameter
}

void InputRangeCk(char input[10], char outmsg[], int min, int max)
{
char tmpin[10];
int stop = 1;

while(stop == 1)
    {
    cout << outmsg;
    cin.getline(tmpin, 10);

	if(IsNumber(tmpin) == 0)
		{
		cout << "\nError: Number not entered";
		} //endif isn't a number
	else
		{
    	stop = abs(RangeCk(atoi(tmpin), min, max, 1));
		} //endelse if the input is a number then do the range check with error messages
    } //endwhile loop until a valid input is given

strcpy(input, tmpin);	// copies the validated input into the output
}

void InputLevelOfAccessCk(char inloa[3], char outmsg[])
{
InputRangeCk(inloa, outmsg, 1, 3);	// does the validation for the level of access
}

void InputFilePathCk(char infp[128], char outmsg[])
{
char tmpfp[128];
int cont = 0;

while(cont == 0)
	{
	cout << outmsg;
	cin.getline(tmpfp, 128);

	cont = ValidateFilePath(tmpfp);
	} //endwhile loop until a valid file path is entered

strcpy(infp, tmpfp);	// copying the inputted file path into the parameter
}

#pragma endregion





