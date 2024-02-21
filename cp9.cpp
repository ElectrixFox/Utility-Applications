//- VAT Validation -
int VATvalidation(char vat[25])
{
//-- int variables --
int count;
int valid = 0;
int position;
int nonapplic = 0;

nonapplic = strlen(vat);

if(nonapplic == 0)
	{
	valid = 1;
	}//endif - If customer doesn't have a VAT number, then validation is ignored for it.

if(nonapplic != 0 && valid == 0)
	{
	if(strlen(vat) == 11)
		{
		if(vat[0] == 'G')
			{
			if(vat[1] == 'B')
				{
				for(count = 2; count < 11; count++)
					{
					if(isdigit(vat[count]))
						{
						valid = 1;
						}//endif - VAT is valid.
					else
						{
						clrscr();
						position = count;
						cout << "\n Position " << position + 1 << ", '" << vat[count] << "' needs to be a number.";
						getch();
						valid = 0;
						}//endelse - Ouput error message if a character is found in positions [2] to [10].
					}//endfor - Loop to make sure positions [2] to [10] are numbers.
				}//endif - Makes sure position [2] is a 'B'.
			else
				{
				clrscr();
				cout << "\n Position 2 needs to be a 'B'.";
				valid = 0;
				}//endelse - Ouput error message if position [2] isn't a 'B'. 
			}//endif - Makes sure position [1] is a 'G'.
		else
			{
			clrscr();
			cout << "\n Position 1 needs to be a 'G'.";
			valid = 0;
			}//endelse - Ouput error message if position [1] isn't a 'G'. 
		}//endif - Sees if VAT number length is equal to 11.
	else
		{
		clrscr();
		cout << "\n VAT Number, " << vat << " needs to be a length of 11";
		valid = 0;
		}//endelse - Ouput error message if VAT number isn't equal to 11.
	}//endif - User has entered a VAT number.
    
return valid;
}

//- National Insurance Number Validation - 
int ValidatingNI(char nationinsur[14])
{
//-- int variables --
int lenghthnationinsur = 0; // Length of national insurance number.
int valid = 1; // All positions are always valid unless it is found in the one of the array's.
int find; // Variable for FOR loop.      
int tempvalid = 0; // Temp valid for checking end of NI num againt the end array.     
int foundpos2array; // Found character that is character array.
int foundpos1array; // Found character that is character array.
int foundprefix; // Variable used to validate that the prefix has been founded.
int foundendarray; // Variable used to validate that the endcharacter has been founded in the array.
int numpostion[20] = {3, 4, 6, 7, 9 ,10};
int spacepostion[20] = {2, 5, 8, 11};
int count;

//-- char variables --
char characterarray[40][3] = {"D", "F", "I", "Q", "U", "V", "O", "BG", "GB", "KN", "NK", "NT", "TN", "ZZ", "A", "B", "C", "D"}; // Position 2 character array.
char temppos2array[2]; // Temp variable so that a single character (nationinsur[1]) can be searched in the array.
char temppos1array[2]; // Temp variable so that a single character can be searched in the array.
char tempprefix[3]; // Temp variable so that a two characters (nationinsur[0] and [1]) can be searched in the array.
char tempendarray[2]; // Temp variable so that a single character (nationinsur[12]) can be searched in the array.


for(find = 0; find < 14;find++)
	{
	nationinsur[find] = toupper(nationinsur[find]); //Changes lower case characters into uppercase.
	}//endfor - Looping through all character in nationinsur.

strncpy (temppos1array, nationinsur, 1); // Copys the first 1 positions in the string so it can be used in the position one character array loop.
strncpy (&temppos2array[0], &nationinsur[1], 1); // Copys the first position in the string so it can be used in the position two character array loop.
strncpy (tempprefix, nationinsur, 2); // Copys the first 2 positions in the string so it can be used in the prefix array loop.
strcpy (tempendarray, &nationinsur[12]); // Copys the first 14 position in the string so it can be used in the position 14 character array loop.


lenghthnationinsur = strlen(nationinsur); // Getting Length of nationalinsur.

//---- Checking if postition 1 has a letter in the 1st array that isn't allowed ----
if(lenghthnationinsur == 13)
	{
	if(isalpha(nationinsur[0])) // Checking if posistion is 0 is a character.
		{
		for(find = 0; find < 6; find++) //For loop to find if any letters match the Array.
			{
			foundpos1array = strcmpi(temppos1array, characterarray[find]);
			if(foundpos1array == 0)
				{
				clrscr();
				cout <<"\n The characters D, F, I, Q, U, and V cannot be used in position 1.\n";
				valid = 0;
				}//endif - One of the character from the characterarray has been found in the NI number at position [0].
			}//endfor - End of for loop searching for character 1 in character 1 array.
		}//endif - End of checking if position 0 is a character.
	else
		{
		clrscr();
		cout << "\n Position 1 needs to be a letter. \n";
		valid = 0;
		}//endelse - End of else outputting the error message and making valid 0.
	}//endif - End of checking if lenghthnationinsur 15
else
	{
	clrscr();
	cout<<"\n Length of national insurance number is not 13 character long! It should look be in this format --> QQ 12 34 56 A. \n";
	valid = 0;
	}//endelse - Ouputting error message if ni number isn't the right length.

//---- Checking if postition 2 has a letter in the 2nd array that isn't allowed ----
if(valid == 1)
	{
	if(isalpha(nationinsur[1]) != 0) // Checking if posistion 0 in the temp 2 array.
		{
		for(find = 0; find < 7; find++) // For loop to find if any letters match the Array
			{
			foundpos2array = strcmpi(temppos2array, characterarray[find]);
			if(foundpos2array == 0)
				{
				clrscr();
				cout <<"\n The characters D, F, I, Q, U, V, and O cannot be used in position 2. \n";
				valid = 0;
				}//endif - One of the character from the characterarray has been found in the NI number at position [1].
			}//endif - End of for loop searching for character 1 in character 1 array
		}//endif - End of checking if position 1 is a character
	else
		{
		clrscr();
		cout << "\n Position 2 needs to be a letter. \n";
		valid = 0;
		}//endelse - End of else outputting the error message and making valid 0.
	}//endif - Validating position [1] with the characters in the character array.

//---- Checking if postition 1 and 2 has a prefix in the prefix array that isn't allowed ----
if(valid == 1)
	{
	for(find = 7; find < 14; find++) // For loop to find if any letters match the Array
		{
		foundprefix = strncmpi(tempprefix, characterarray[find], 2);
		if(foundprefix == 0)
			{
			clrscr();
			cout << "\n National insurance numbers cannot start with the following: BG, GB, KN, NK, NI, TN, ZZ. \n";
			valid = 0;
			}//endif - Ouput error message if prefix's are found in tempprefix.
		}//endfor - Looping throught the array to see if any prefix's match in tempprefix.
	}//endif - Validating position [0] and [1] with the prrefix's in the character array.



// ---- Checking for number and spaces in correct posistion. ----

if(valid == 1)
	{
	for(count = 0; count < 6; count++)
		{
		if(isdigit(nationinsur[numpostion[count]]))
			{
			valid = 1;
			}//endif - Position of where a number should be is in numpostion[count] = (e.g. 4) with nationinsur[numpostion(e.g. 4) [count]] being the position in the nationinsur where a number should be.
		else
			{
			clrscr();
			cout << "\n Position " << numpostion[count] + 1 << " needs to be a number. \n";
			valid = 0;
			break;
			}//endelse - Outputs error message for where a number is needed in numposition[count]. Would show the place before without + 1.
		}//endfor - Looping through numposition array in increments of 1.
	}//endif - Continues if unallowed prefix's haven't been found.

if(valid == 1)
	{
	for(count = 0; count < 4; count++)
		{
		if(nationinsur[spacepostion[count]] == ' ')
			{
			valid = 1;
			}//endif - Position of where space should be is in spacepostion[count] = (e.g. 2) with nationinsur[spacepostion(e.g. 2) [count]] being the position in the nationinsur where a space should be.
		else
			{
			clrscr();
			cout << "\n Position " << spacepostion[count] + 1 << " needs to be a space. \n"; // Plus 1 because pointer starts at zero in array. 
			valid = 0;
			break;
			}//endelse - Outputs error message for where a space is needed in spacepostion[count]. Would show the place before without + 1.
		}//endfor - Looping through spacepostion array in increments of 1.
	}//endif - Continues if numbers are present in the correct positions.


/*---- Checking against the last character array at postion 12 to see if 
       national insuranace number ends in the following in the array.     ---- */
if(valid == 1)
	{
	for(find = 14; find < 18; find++) // For loop to find if any letters match the Array
		{
		foundendarray = strcmpi(tempendarray, characterarray[find]);
		if(foundendarray == 0)
			{
			tempvalid = 1;
			}//endif - If tempendarray matches with a character in the array it is valid.
		}//endfor - End of for loop searching for character 1 in character 1 array.
	}//endif - End of checking if position 1 is a character.

if(valid == 1)
	{
	if(tempvalid != 1)
			{
			clrscr();
			cout << " National insurance number must end in A, B, C, or D. \n";
			}//endif - Error message if tempvalid is still 0.
	}//endif - Is valid == 1.

valid = tempvalid;

return valid ;
}

//- Date Validation -
int ValidatingDate(char valdate[11])
{
//-- int variables --
int valid = 0;
int length;
int months;
int days;

//-- float variables --
float years;
float yeardivision;
float flooryears;

length = strlen(valdate);

if(length == 10)
    {
     if(valdate[2]== '/' && valdate[5]== '/')
		{
		sscanf(&valdate[3], "%d", &months);
		if(months >= 1 && months <= 12)
			{
			sscanf(&valdate[0], "%d", &days);
			if(months == 4 || months == 6 || months == 9 || months == 11)
				{
				if(days >=1 && days <=30)
					{
					valid = 1;
					}//endif - User enters day between 1 and 30 for the month they have entered.
				else
					{
					cout<<" ERROR: April, June, September and November have 30 days. Please enter a value between 1 and 30.\n";
					}//endelse - Outputting error message
				}//endif - The months are equal too 4, 6, 9 or 11.

			if(months == 1 || months == 3 || months == 7 || months == 8 || months == 10 || months == 12)
				{
				if(days >= 1 && days <= 31)
					{
					valid = 1;
					}//endif - User enters day between 1 and 31 for the month they have entered.
				else
					{
					cout<<" ERROR: January, March, May, July, August, October and December have 31 days. Please enter a value between 1 and 31.\n";
					}//endelse - Outputting error message
				}//endif - The months are equal too 1, 3, 7, 8, 10 or 12.

			if(months == 2)
				{
				sscanf(&valdate[6], "%f", &years);
				yeardivision = years / 4;
				flooryears = floor(yeardivision);
				if(flooryears == yeardivision)
					{
					if(days >=1 && days <= 29)
						{
						valid = 1;
						}//endif - User enters day between 1 and 29 for the month they have entered.
					else
						{
						cout<<" ERROR: The year "<<years<<" is a leap year. February will have 29 days. Please enter a value between 1 and 29 for Febuary.\n";
						}//endelse - Output error message if user enters a day outside 1 and 29 for febuary.
					}//endif - The current year is divisible by 4 without any remainders. 

				if(flooryears != yeardivision)
					{
					if(days >= 1 && days <= 28)
						{
						valid = 1;
						}//endif - User enters a valid day for febuary.
					else
						{
						clrscr();
						cout<<" ERROR: The year "<<years<<" is not a leap year. February will have 28 days. Please enter a value between 1 and 28 for Febuary.\n";
						}//endelse - Ouput error message if user enters 29 days for febuary if its not a leap year.
					}//endif - If this year does have remainders when divided by 4.
				}//endif - The month the user entered is 2.
			}//endif - User enters months between 1 and 12.
		else
			{
			clrscr();
			cout<<" ERROR: Months cannot be less than and equal to 0 and more than 12. Please enter a month between 0 and 12.\n";
			}//endelse - Output error message if user entered a month that is not valid.
		}//endif - User has placed '/' in the correct positions.
    else
        {
        clrscr();
        cout<<" ERROR: / is in the wrong place. It must be in this format dd/mm/yyyy.\n";
        }//endelse - Output error message if '/' is missing or not in the correct positions. 
    }//endif - User has entered a which has a length of 10 characters.
else
    {
	clrscr();
    cout<<" ERROR: Date entered must be 10 character in length. It must be in this format dd/mm/yyyy.\n";
    }//endelse - Output error message if user enters a date this is not in the format dd/mm/yyyy.
        
return valid;
}
