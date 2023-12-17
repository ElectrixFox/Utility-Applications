import os

prefstyle = " //"

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
    statements = [ "else if", "if", "for", "while", "do", "switch", "case", "else", "default" ]

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

    if not (fpos < len(lsplit) - 1) and target != "default":
        return 0

    if target == "case":
        if (':' not in lsplit[fpos + 1]) and (':' not in lsplit[fpos]):
            return 0
    elif target == "default":
        if (':' not in lsplit[fpos]):
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
            
    # print(line, end = '\0')

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
        "default": "enddefaultcase",
        "else if": "endelseif"
        }

    if statements[selc] not in line:
        return statements[selc]
    else:
        return 1

def LoopUntilEnding(lines, st, en, out):
    target = isSelection(lines[st-1])
    
    i = st

    while (i < en):
        issel = isSelection(lines[i])

        if issel != 0:
            i = LoopUntilEnding(lines, i+1, en, out)

            # continuing so that the loop can restart without incrementing to check the next line doesn't contain
            continue

        isnscope = isStartingNewScope(lines[i])

        if isnscope == -1:
            if(i == en):
                return
            
            if(target == 0):
                i += 1
                continue

            hasend = hasEnding(target, lines[i])

            if hasend != 1:
                if out == 1:
                    print(f"Missing {hasend} on line {i + 1}")

                # removes the new line from the end of the line, adds the comment style to the ending and then adds the new line at the end
                lines[i] = lines[i].replace("\n", "") + prefstyle + hasend + '\n'
            else:
                print(f"Found ending on line {i+1}")

            return (i + 1)
        i += 1

    return i 

def CommentMenu():
    fp = ""
    os.system("CLS")

    fp = input("Enter File Path: ")
    output = 0

    codefile = open(fp, 'r')
    flecont = codefile.readlines()
    codefile.close()

    print("1. Display Error Locations")
    print("2. Write new changes to new file")
    print("3. Write new changes to file")

    choice = input("Enter choice: ")

    if choice == "1":
        output = 1

    # loops through finding and checking for selection statments with no ending comments
    LoopUntilEnding(flecont, 0, len(flecont)-1, output)

    if choice == "2":
        ncodefile = open("new" + fp, 'w')
        ncodefile.writelines(flecont)
        ncodefile.close()
    elif choice == "3":
        ncode = open(fp, 'w')
        ncode.writelines(flecont)
        ncode.close()
