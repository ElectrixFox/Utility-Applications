
// #MENU LOOP FUNCTION
int ID_MenuLoop()
{
int ID_menustatus;

while (ID_menustatus != ID_end)
    {
    ID_menustatus = ID_MenuFunction();
    clrscr();
    }

return 0;
}

// #MENU CASE FUNCTION
int ID_MenuFunction()
{
int ID_choice;

clrscr();

// #OUTPUT MENU NAME
// #OUTPUT CHOICES

cout << "Enter Choice: ";
cin >> ID_choice;

switch (ID_choice)
    {
    case 1:
        {
        ID_MenuOption();
        clrscr();
        break;
        }
    }

return ID_choice;
}