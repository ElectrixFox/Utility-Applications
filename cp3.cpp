using namespace std;
#define getch() cin.get()
#define clrscr() system("cls")

int main()
{
if(2 == 4)
	{
	if("hoolsi" == "h")
        {

        } //endif
	} //endif

while(2 == 4)
	{
	for (;;)
		{

		} //endfor

	if ("2" == "h")
		{

		} //endif
	} //endwhile

if("day" == "time")
	{

	}
else if ("hellow" == "he")
	{

	} //endelseif
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