import os
import EndingComments as ec

separator = ", "

# checks if the it is a function (if declaration 1 then checks if it is a function declaration)
def isFunction(line, declaration):
    if '(' not in line or ')' not in line:
        return 0
    
    # more validation will be needed here as it only checks there are brackets
    if(declaration != 1): 
        return 1

    hastpe = getFunctionType(line)

    if hastpe == 0:
        return 0
    
    if ';' not in line:
        return 0
    
    return 1

def getFunctionName(line):
    line = str(line)
    lsplit = line.split()

    for i in range(0, len(lsplit)):
        if getFunctionType(lsplit[i]) != 0:
            # return everything to the left of the open bracket
            return lsplit[i+1][:lsplit[i+1].find('(')]

    return 0

def getFunctionType(line):
    return ec.ContainsType(line)


def FindAllFunctions(lines):
    functions = []
    for line in lines:
        isfunc = isFunction(line, 1)
        if isfunc == 1:
            functions.append(getFunctionName(line))
    
    return functions

def FunctionsMenu():
    fp = ""

    os.system("cls")  
    
    print("\tFunctions Menu")
    print("\t==============")
    print("\t1. Output Functions")
    print("\t2. Write Functions To File")
    print("\t3. Return")

    choice = input("\nEnter choice: ")

    if choice == "3":
        return choice
    
    os.system("cls")
    fp = input("Enter File Path: ")

    numperline = input("Enter the number of functions per line: ")

    cfile = open(fp, 'r')
    lines = cfile.readlines()
    cfile.close()

    funcs = FindAllFunctions(lines)
    nlines = len(lines)

    if choice == "1":
        for i in range(0, len(funcs)): 
            print(funcs[i], end=' \0')

            # adding the new line
            if i % int(numperline) == 0:
                print()
    elif choice == "2":
        i = 0
        while "Function" not in lines[i]:
            i += 1

            if i == nlines:
                break
        if i < nlines:
            lines[i] = lines[i].replace("\n", "")
            ntabs = 4

            final = ""
            for j in range(0, len(funcs)): 
                final += funcs[j] + separator

                if j == 0:
                    continue

                # adding the new line
                if j % int(numperline) == 0:
                    final += '\n'
                    lines.insert(i + 1, final)
                    final = ""
                    final = ntabs * '\t'
                    print(final + '1')

            print(lines)

            cfile = open(fp, 'w')
            cfile.writelines(lines)
            cfile.close()
        else:
            print("Error: Commentary box not found")
    input("\nPress any key to return")
    return choice

ch = ""

while ch != "3":
    ch = FunctionsMenu()