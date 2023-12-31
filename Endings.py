import os

fp = ""
os.system("cls")

def ContainsType(line):
    types = [ "int", "char", "float", "void" ]
    line = str(line)
    
    lnsplit = line.split()

    for type in types:
        if type in lnsplit:
            return type
    
    return 0

# function definition = <Name><Open Bracket><Params><Close Bracket>

# currently doesn't account for: (Type) (Name) = (Function)(Params) 
def isFunction(line):
    line = str(line)
    
    # if the line doesn't contain a type then return
    if ContainsType(line) == 0:
        return 0
    
    # if the line doesn't contain an open bracket for starting the function
    if "(" not in line or ")" not in line:
        return 0

    return 1

def isStartingNewScope(line):
    line = str(line)

    if ContainsType(line) != 0:
        return 0

    if "{" in line:
        return 1
    elif "}" in line:
        return -1
    
    return 0

def isSelection(line):
    line = str(line)
    statements = [ "else if", "if", "for", "while", "do", "switch", "case", "else" ]

    target = ""

    # finding if there is one in there
    for selcstat in statements:
        if selcstat in line:
            target = selcstat

    if target == "":
        return 0     

    pos = 0
    fpos = 0
    lsplit = line.split()

    # finding the target in the split up line
    for test in lsplit:
        if target in test:
            fpos = pos
        pos +=1

    if not (fpos < len(lsplit) - 1):
        return 0

    if target == "case":
        if (':' not in lsplit[fpos + 1]) and (':' not in lsplit[fpos]):
            return 0
    else:
        if ('(' not in lsplit[fpos + 1]) and ('(' not in lsplit[fpos]):
            return 0
        elif '(' in lsplit[fpos + 1]:
            if lsplit[fpos + 1][0] != '(':
                return 0
        elif lsplit[fpos].find(target) > 0:
            if lsplit[fpos][lsplit[fpos].find(target) - 1].isalpha():
                return 0
            
    #print(line, end = '\0')

    return target

def hasEnding(selc, line):
    statements = {  
        "else": "endelse",
        "if": "endif", 
        "for": "endfor", 
        "while": "endwhile", 
        "do": "enddo", 
        "switch": "endswitch", 
        "case": "endcase", 
        "else if": "endelseif"
        }

    if statements[selc] not in line:
        return statements[selc]
    else:
        return 1

fp = input("Enter File Path: ")

codefile = open(fp, 'r')

flecont = codefile.readlines()

codefile.close()

print("1. Display Error Locations")
print("2. Write new changes to new file")
print("3. Write new changes to file")

choice = input("Enter choice: ")

codefile = open(fp, 'r')

curfunc = ""
curselc = ""
selcstack = []
inscope = 0
olddepth = 0

for lnum, line in enumerate(codefile, 1):
    if isFunction(line) == 1:
        # getting the function name in the string
        curfunc = line.split()[1]
        # getting rid of the start of the function to get the function name
        curfunc = curfunc.split("(")[0]
        continue

    stnscpe = isStartingNewScope(line)
    iselec = isSelection(line)

    if stnscpe == 1:
        inscope += 1

    # if the scope is ending then do the addition of the tags
    if (stnscpe == -1) and (inscope == olddepth):
        print(f"curdepth {inscope} and old depth {olddepth}")
        inscope -= 1

        # if the stack is empty then continue
        if len(selcstack) == 0:
            curselc = ""
            continue

        topsel = selcstack.pop()
        ending = hasEnding(topsel, line)
        if ending != 1:
            if choice == "1":
                print(f"Missing {ending} on line {lnum}")
                continue
            
            # lnum - 1 as starts at 0
            # removes all of the new lines
            # adds the ending comment
            # adds the new line
            end = (flecont[lnum-1].replace("\n", "") + " //" + ending) + '\n'

            # sets the file content
            flecont[lnum-1] = end
    
    # else if the scope is not ending then check if there is a selection statement there
    elif iselec != 0:
        olddepth = inscope
        curselc = iselec
        selcstack.append(curselc)

codefile.close()

if choice != "1":
    ncodefile = open("new" + fp, 'w')

    ncodefile.writelines(flecont)

    ncodefile.close()