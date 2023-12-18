import os

def clrscr():
    os.system("cls")

# gets the end of the scope from the first found {, starting at linenum (currently linenum needs to be the start of the scope to end)
def FindEndOfScope(lines, linenum):
    nlines = 0
    depth = 0
    nlines = len(lines)

    for i in range(linenum + 1, nlines):
        line = lines[i]

        if "{" in line:
            depth += 1
        if "}" in line:
            depth -= 1

        # if returned to origional depth then return the line on which this happened
        if depth == 0:
            return i
        

def ProcessTemplateMenuLoop(lines):
    nlines = 0
    scpestart = 0
    scpeend = 0

    nlines = len(lines)

    for i in range(0, nlines):
        line = lines[i]

        # marks the start of the loop function
        if "// #MENU LOOP FUNCTION" in line:
            # starting 1 after to acount for the actual function name (int MainMenu())
            scpestart = i + 1
            break

    print(lines[scpestart])
    
    scpeend = FindEndOfScope(lines, scpestart)

    print(lines[scpeend])

    print(f"Scope starts at line {scpestart + 1} and ends at line {scpeend + 1}")
    


# ideally this will require a template cpp to get format from
def MenuBuilderMenu():
    choice = ""
    fp = ""

    clrscr()

    print("\tMenu Builder Menu")
    print("\t=================")
    print("\t1. Output Results")
    print("\t2. Write Results to Output File")
    print("\t3. Return")

    choice = input("\nEnter Choice: ")

    if choice == "3":
        return choice
    
    clrscr()

    fp = input("Enter Template File Path: ")

    cfile = open(fp, 'r')
    lines = cfile.readlines()
    cfile.close()
    
    if choice == "1":
        ProcessTemplateMenuLoop(lines)

    input("Press any key to return")
    

ch = ""
while ch != "3":
    ch = MenuBuilderMenu()
