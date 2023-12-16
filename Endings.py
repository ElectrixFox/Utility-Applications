fp = ""

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

fp = input("Enter File Path: ")
defa = 1

if defa == 1:
    fp = "cp2.cpp"


codefile = open(fp, 'r')

curfunc = ""
for lnum, line in enumerate(codefile, 1):
    if isFunction(line) == 1:
        curfunc = line.split()[1]
        curfunc = curfunc.split("(")[0]
        print(curfunc)
    if isStartingNewScope(line) == 1:
        print (line)
    
codefile.close()