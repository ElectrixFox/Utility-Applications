/******************************************************************************
Program:        3D Array
File:           3Darrays.cpp
Functions:      IsLeapYear, MainMenu, ViewSchedules, AddSchedules, DeleteSchedules, ClearAllSchedules, CoutForSchedule, ViewScheduleMenu, ViewAllSched, ViewPartSched, ReBackScheduleFile, ReWriteScheduleFile, CustomCoutForSched, ConvertDate, ConverTime, ReverseCovertDate
Description:    How to use 2D arrays.
Author:         Thomas Gull
Environments:   Borland C++ Pro 6.0
Notes:
Revisions:      14/08/2023
*******************************************************************************/
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <assert.h>
//#include<vcl.h>

using namespace std;

#define strcmpi(x, y) strcmp(x, y)
#define strncmpi(x, y, z) strncmp(x, y, z)

#ifndef _WIN32
#define itoa(x, y, z) sprintf(y, "%d", x)
#else
#define clrscr() system("CLS")
#endif

// -- Check For Leap Year --
int IsLeapYear(char indate[12]);


//---- Menus ----
int MainMenu();
int ViewSchedules();
int AddSchedules();
int DeleteSchedules();
int ClearAllSchedules();
int CoutForSchedule(int driver);
int ViewScheduleMenu();
int ViewAllSched();
int ViewPartSched();

//---- ReBack & ReWrite for schedule ----
int ReBackScheduleFile();
int ReWriteScheduleFile();

//---- Cout for schedule ----
int CustomCoutForSched();

//---- Converting Date and Time routines
int ConvertDate(char dateconvert[12]);
int ConverTime(char timeconvert[12]);
int ReverseCovertDate(int intdate);

char dateconverting[12];
int startemp = -1;
int day;
int inttime;
int drivernum;
char schedule[367][24][50][3]; // 365 days and 24 hours, 50 possible drivers. If readbcak or rewrite problem then change 2 to 3.
char FileName1[80]="SchedulingFile.txt";
char dateofbooking[11];
char timeofbooking[11];
char drivernum2[3];

//---- Main ----
int main(int argc, char* argv[])
{
int mainstatus=0;

while (mainstatus!=5)
        {
        mainstatus=MainMenu();
        }//endwhile
return 0;
}

int IsLeapYear(char indate[12])
{
int years;
int yeardivision;
int flooryears;
int value;

int isleap = 0;

sscanf(&indate[6], "%d", &years);

yeardivision = years / 4;
flooryears = floor(yeardivision);
if(flooryears == yeardivision)
        {
        isleap = 1;
        }// endif - Setting isleap year 1 if there is a leap year

return isleap;
}

//---- Main Menu ----
int MainMenu()
{
int choice;
cout<<"\n Main Menu";
cout<<"\n =========";
cout<<"\n 1. View Schedules";
cout<<"\n 2. Add Schedules";
cout<<"\n 3. Delete Schedules";
cout<<"\n 4. Clear all Schedules";
cout<<"\n 5. Exit";
cout<<"\n \n Enter choice: ";
cin>>choice;

switch(choice)
        {
        case 1:
                {
                ViewSchedules();
                clrscr();
                break;
                }
        case 2:
                {
                AddSchedules();
                clrscr();
                break;
                }

        case 3:
                {
                DeleteSchedules();
                clrscr();
                break;
                }
        case 4:
                {
                ClearAllSchedules();
                clrscr();
                break;
                }
        case 5:
                {
                break;
                }
        }//endcase
return choice;
}

int ViewSchedules()
{
int viewstatus=0;

while (viewstatus!=3)
        {
        viewstatus=ViewScheduleMenu();
        }//endwhile
return 0;
}

int ViewScheduleMenu()
{
int choice;
clrscr();

cout<<"\n View Schedule Menu";
cout<<"\n ==================";
cout<<"\n 1. View All";
cout<<"\n 2. View by custom date";
cout<<"\n 3. Exit";
cout<<"\n \n Enter choice: ";
cin>>choice;

switch(choice)
        {
        case 1:
                {
                ViewAllSched();
                clrscr();
                break;
                }
        case 2:
                {
                ViewPartSched();
                clrscr();
                break;
                }
        case 3:
                {
                break;
                }
        }//endcase
return choice;
}


int ViewAllSched()
{
int daytem = 1;
int drivernumber; 
ReBackScheduleFile();

cout<<"\n View Schedules: ";

cout << "\n Enter the driver you wish to view the schedule for: ";
cin >> drivernumber;
drivernum = drivernum - 1;

cout<<"\n\t\t00:00\t01:00\t02:00\t03:00\t04:00\t05:00\t06:00\t07:00\t08:00\t09:00\t10:00\t11:00\t12:00\t13:00\t14:00\t15:00\t16:00\t17:00\t18:00\t19:00\t20:00\t21:00\t22:00\t23:00";
for(day = 0; day < 366; day++)
        {
        ReverseCovertDate(daytem);
        cout << "\n\n " << dateconverting;
        daytem = daytem + 1;
        CoutForSchedule(drivernumber);
        schedule[day + 1];
        
        }//endfor day

cout << "\n\n Please press a key to go to back to main menu.";
cin.get();
getch();
return 0;
}

int ViewPartSched()
{
char viewstart[12];
char viewend[12];
int end;
int start;

ReBackScheduleFile();

cin.get();
cout << "\n Please enter the start date you would like to view from: ";
cin.getline(viewstart, 12);
start = ConvertDate(viewstart);

startemp = startemp + start;

cout << "\n Please enter the start date you would like to view from: ";
cin.getline(viewend, 11);
end = ConvertDate(viewend);

end = end + 1;

cout<<"\n View Schedules: ";
cout<<"\n\t\t9AM\t10AM\t11AM\t12PM\t13PM\t15PM\t16PM";
for(start = start; start < end; start++)
        {
        ReverseCovertDate(start);
        cout << "\n\n " << dateconverting;
        CustomCoutForSched();
        schedule[startemp + 1];
        startemp = startemp + 1;
        }//endfor day

cout << "\n\n Please press a key to go to back to main menu.";

getch();
return 0;
}

//---- Add to Schedule ----
int AddSchedules()
{
ReBackScheduleFile();

cout<<"\n Add Schedules";
cin.get();

cout<<"\n Enter date: ";
cin.getline(dateofbooking, 11);
day = ConvertDate(dateofbooking);

cout<<"\n Enter time: ";
cin.getline(timeofbooking, 6);
inttime = ConverTime(timeofbooking);

cout<<"\n Enter driver: ";
cin.getline(drivernum2, 3);
sscanf(&drivernum2[0], "%d", &drivernum);

strcpy(schedule[day-1][inttime - 1][drivernum],"B");

ReWriteScheduleFile();
getch();
return 0;
}

//---- Delete Schedule ----
int DeleteSchedules()
{
ReBackScheduleFile();

cout<<"\n Delete Schedules";
cout<<"\n Enter date and time you want to delete below.";

cin.get();
cout << "\n Please enter the date: ";
cin.getline(dateofbooking, 11);
day = ConvertDate(dateofbooking);

cout<<"\n Please enter the time: ";
cin.getline(timeofbooking, 6);
inttime = ConverTime(timeofbooking);

strcpy(schedule[day - 1][inttime - 1][drivernum - 1],"O");

ReWriteScheduleFile();
getch();
return 0;
}

//---- Clear Schedule ----
int ClearAllSchedules()
{
cout<<"\n Clear All Schedules";
for(day = 0; day < 366; day++)
        {
        for(inttime = 0; inttime < 24; inttime++)
                {
                for (drivernum = 0; drivernum < 50; drivernum++)
                        {
                        strcpy(schedule[day][inttime][drivernum],"O");
                        }
                
                }//endfor
        }//endfor
ReWriteScheduleFile();
getch();
return 0;
}

int ReBackScheduleFile()
{
ifstream fin(FileName1, ios::in);
for(day = 0; day < 366; day++)
        {
        for(inttime = 0; inttime < 24; inttime++)
                {               
                for (drivernum = 0; drivernum < 50; drivernum++)
                        {
                        fin.getline((char*)&schedule[day][inttime][drivernum], 4);
                        }
                
                }//endfor inttime
        }//endfor day

fin.close();
return 0;
}

int ReWriteScheduleFile()
{
ofstream fout(FileName1, ios::binary);
for(day = 0; day < 366; day++)
        {
        for(inttime = 0; inttime < 24; inttime++)
                {
                for (drivernum = 0; drivernum < 50; drivernum++)
                        {
                        fout.write((char*)&schedule[day][inttime][drivernum], sizeof(schedule[day][inttime][drivernum]));
                        fout.write("\n ", 1);
                        }
                }//endfor inttime
        }//endfor day
fout.close();
return 0;
}

int CoutForSchedule(int driver)
{
for(inttime = 0; inttime < 24; inttime++)
                {
                cout<<"\t";
                cout<<schedule[day][inttime][driver];
                }//endfor inttime
return 0;
}

int CustomCoutForSched()
{
for(inttime = 0; inttime < 24; inttime++)
                {
                cout<<"\t";
                cout<<schedule[startemp][inttime];
                }//endfor inttime
return 0;
}

int ConvertDate(char dateconvert[12])
{
int days;
int months;
int years;
int yeardivision;
int flooryears;
int value;

sscanf(&dateconvert[0], "%d", &days); // Converting day

sscanf(&dateconvert[3], "%d", &months);

sscanf(&dateconvert[6], "%d", &years);

yeardivision = years / 4;
flooryears = floor(yeardivision);
if(flooryears == yeardivision)
        {
        if(months >= 2)
                {
                value = days + 1;
                }// endif - If leap year, any month on or after feburary needs an extra day.
        }// endif - Calcualtion to determine leap year or not.

if(months == 1)
        {
        value = days;
        }
if(months == 2)
        {
        value = days + 28;
        }
if(months == 3)
        {
        value = days + 28 + 31;
        }
if(months == 4)
        {
        value = days + 28 + 31 + 30;
        }
if(months == 5)
        {
        value = days + 28 + 31 + 30 + 31;
        }
if(months == 6)
        {
        value = days + 28 + 31 + 30 + 31 + 30;
        }
if(months == 7)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31;
        }
if(months == 8)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31 + 31;
        }
if(months == 9)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        }
if(months == 10)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
        }
if(months == 11)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
        }
if(months == 12)
        {
        value = days + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31;
        }
getch();
return value;
}

int ConverTime(char timeconvert[12])
{
int hours;

sscanf(&timeconvert[0], "%d", &hours); // Converting hours entered into a integer.

if(hours < 0 || hours > 23) // Validating the hours converted is between the bounds of 0 and 23.
                {
                cout << " \n Error "; // Outputs error if 
                getch();
                }//endelse
getch();
return hours;
}

int ReverseCovertDate(int intdate)
{
int years;
int flooryears;
int yeardivision;
int day = 0;

char dayconvert[4];
char monthconvert[3];
char yearconvert[5];

strcpy(yearconvert, "2024");
sscanf(&yearconvert[0], "%d", &years);

yeardivision = years / 4;
flooryears = floor(yeardivision);
if(flooryears == yeardivision)
        {
        day = 1;
        }// endif - If leap year, any month on or after feburary needs an extra day.

if(intdate >= 1 && intdate <= 31)
        {
        strcpy(monthconvert, "01");
        }
if(intdate >= 32 && intdate <= 59 + day)
        {
        strcpy(monthconvert, "02");
        intdate = intdate - 31 - day;
        }
if(intdate >= 60 + day && intdate <= 90 + day)
        {
        strcpy(monthconvert, "03");
        intdate = intdate - 31 - 28;
        }
if(intdate >= 91 + day && intdate <= 120 + day)
        {
        strcpy(monthconvert, "04");
        intdate = intdate - 31 - 28 - 31;
        }
if(intdate >= 121 + day && intdate <= 151 + day)
        {
        strcpy(monthconvert, "05");
        intdate = intdate - 31 - 28 - 31 - 30;
        }
if(intdate >= 152 + day && intdate <= 181 + day)
        {
        strcpy(monthconvert, "06");
        intdate = intdate - 31 - 28 - 31 - 30 - 31;
        }
if(intdate >= 182 + day && intdate <= 212 + day)
        {
        strcpy(monthconvert, "07" + day);
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30;
        }
if(intdate >= 213 + day && intdate <= 243 + day)
        {
        strcpy(monthconvert, "08");
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30 - 31;
        }
if(intdate >= 244 + day && intdate <= 273 + day)
        {
        strcpy(monthconvert, "09");
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31;
        }
if(intdate >= 274 + day && intdate <= 304 + day)
        {
        strcpy(monthconvert, "10");
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30;
        }
if(intdate >=305 + day && intdate <= 334 + day)
        {
        strcpy(monthconvert, "11");
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30 - 31;
        }
if(intdate >= 335 + day && intdate <= 365 + day)
        {
        strcpy(monthconvert, "12");
        intdate = intdate - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30 - 31 - 30;
        }
itoa(intdate, dayconvert, 10);

if(intdate < 10)
        {
        dateconverting[0] = '0';
        strcpy(&dateconverting[1], dayconvert);
        }
else
        {
        strcpy(&dateconverting[0], dayconvert);
        }

dateconverting[2] = '/';
strcpy(&dateconverting[3], monthconvert);

dateconverting[5] = '/';
strcpy(&dateconverting[6], yearconvert);

return 0;
}