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

# parse for the first layer
# then treat layer 2 as layer 1 and repeat until max layers
def ParseMenuStructure(fp, nlayer):
    menfle = open(fp, 'r')
    lines = menfle.readlines()
    menfle.close()

    mennams = []

    for line in lines:
        print(line, end = '\0')

    for line in lines:
        if line.count("#") == nlayer:
            name = line.replace("\n", "")
            name = name.replace("#", "")
            mennams.append(name)
    mendict = dict()

    for nme in mennams:
        mendict[nme] = []

    curmen = ""
    for line in lines:
        if line.count("#") == nlayer:
            curmen = line.replace("\n", "")
            curmen = curmen.replace("#", "")
        elif line.count("#") == (nlayer + 1):
            mendict[curmen].append(line)

    return mendict

def GetMenuName(mendict, mennum):
    mendict = dict(mendict)
    keys = list(mendict.keys())

    return keys[mennum]

def GetOptionCount(mendict, mennum):
    mendict = dict(mendict)
    keys = list(mendict.keys())

    return len(mendict[keys[mennum]])

def ProcessTemplateMenuLoop(lines, mendict):
    nlines = 0
    scpestart = 0
    scpeend = 0
    menfunclnes = []
    menstatlines = []
    menfunccallslines = []

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

    menfunclnes = lines[scpestart:scpeend + 1]

    menname = GetMenuName(mendict, 0)
    endnum = GetOptionCount(mendict, 0)

    # To-Do: change this so that it does the replacement as it finds them
    for i in range(scpestart, scpeend):
        line = lines[i]
        if "ID_menustatus" in line:
            menstatlines.append(i)
            if "ID_end" in line:
                menfunclnes[i - scpestart] = menfunclnes[i - scpestart].replace("ID_end", str(endnum))
        if "ID_MenuFunction();" in line:
            menfunccallslines.append(i)

    for line in menfunclnes:
        print(line)


    statusvar = menname.lower() + "status"
    
    # changing the name of the function
    menfunclnes[0] = menfunclnes[0].replace("ID_MenuLoop()", menname + "()")

    # replacing all of the status variables
    for ln in menstatlines:
        menfunclnes[ln - scpestart] = menfunclnes[ln - scpestart].replace("ID_menustatus", statusvar)

    # replacing the function calls
    for ln in menfunccallslines:
        menfunclnes[ln - scpestart] = menfunclnes[ln - scpestart].replace("ID_MenuFunction();", menname + "Menu();")
    
    for line in menfunclnes:
        print(line, end = '\0')

# ideally this will require a template cpp to get format from
def MenuBuilderMenu():
    choice = ""
    fp = "TemplateLayout.cpp"

    clrscr()

    cfile = open(fp, 'r')
    lines = cfile.readlines()
    cfile.close()

    mendict = ParseMenuStructure("MenuContent.txt")

    ProcessTemplateMenuLoop(lines, mendict)
    return "3"

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
