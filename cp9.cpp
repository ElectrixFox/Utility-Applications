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
