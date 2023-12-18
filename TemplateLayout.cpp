
// #MENU LOOP FUNCTION
int ID_MenuLoop()
{
int ID_choice;

while (ID_choice != ID_end)
    {
    ID_choice = ID_MenuFunction();
    clrscr();
    }

return 0;
}