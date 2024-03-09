import pandas as pd

codefile = open("cp10.cpp", 'r')
types = [ "int", "char", "float", "void" ]

prams_bottom = -1

var_names = []
var_types = []
var_scope = []
var_funcs = []

def ContainsType(line):
    types = [ "int", "char", "float", "void" ]
    line = str(line)
    
    lnsplit = line.split()

    for type in types:
        if type in lnsplit:
            return type
    
    return 0

def isStartingNewScope(line):
    line = str(line)

    if ContainsType(line) != 0:
        return 0

    if "{" in line:
        return 1
    elif "}" in line:
        return -1
    
    return 0

# currently doesn't account for: (Type) (Name) = (Function)(Params) 
def isFunction(line):
    line = str(line)

    # splits the line down
    parts = line.split()
    
    # checks if the line is empty
    if len(parts) == 0:
        return 0

    # if the line doesn't contain a type then return
    if ContainsType(parts[0]) == 0:
        return 0
    
    if "=" in line:
        return 0
    
    # if the line doesn't contain an open bracket for starting the function
    if "(" not in line or ")" not in line:
        return 0
    
    # checks if there is a ; and a ) then the ; must be after the )
    if (")" in line) and (";" in line):
        if (line.find(";") < line.find(")")):
            return 0

    return 1

def SeparateSizes(typ, vardec):
    final = []

    if "[" not in vardec:
        if typ == "int":
            final = "short"
        
        return final

    splited = vardec.split("[")[1:]

    for item in splited:
        if ";" in item:
            item = item[:-1]
        if "]" in item:
            item = item[:-1]
        
        final.append(item)
    
    return final

def GetFunction(line):
    parts = line.split()

    for item in parts:
        if "(" in item:
            index = item.find("(")
            item = item[:index]
            return item
        
    return ""

def GetParams(line):
    # array of parameters
    params = []

    # finds the first open bracket
    index = line.find("(")

    if((prams_bottom == 1) and (";" in line)):
        return []
    elif((prams_bottom == 0) and (";" not in line)):
        return []

    # stop if there are no params
    if "()" in line[index:]:
        return []

    # split the line to only being after the ( in the function declaration
    line = line[(index + 1):]    
    
    # split at every comma
    parts = line.split(",")

    # loop through each param and get it's type and name
    for item in parts:
        # separating the variable
        sepvar = item.split()

        # removing ; first as it removes the last char not the exact char
        if ";" in sepvar[1]:
            sepvar[1] = sepvar[1][:-1]

        if ")" in sepvar[1]:
            sepvar[1] = sepvar[1][:-1]

        # if there is a size in the separated variable
        if "[" in sepvar[1]:
            index = sepvar[1].find("[")
            sepvar[1] = sepvar[1][:index]
        
        # setting up the variable
        var = [sepvar[0], sepvar[1]]

        # adding the variable to the parameters
        params.append(var)


    return params

def GetVariable(line):
    parts = line.split()

    ftype = ""
    varnam = ""
    size = ""

    if parts[1][0].isupper() == True:
        return []
    elif "main" in parts[1]:
        return []

    if "[" in line:
        size = SeparateSizes(parts[1], parts[0])

        index = parts[1].find("[")
        parts[1] = parts[1][:index]
        
    if ";" in parts[1]:
        parts[1] = parts[1][:-1]

    return parts[:2]

def GetReferences(varnam):
    actfunc = ""
    funcs = []

    # opening the file again
    nfile = open("cp10.cpp", 'r')

    for line in nfile:
        # finds the next function
        if(isFunction(line) == 1):
            # sets the new active function
            actfunc = GetFunction(line)

        # if there are already functions
        if(len(funcs) > 0):
            # check if the last added function is equal to the active function
            if(funcs[-1:][0] == actfunc):
                # skip onto the next line if there isn't a new function
                continue
        
        # if there isn't an active function
        if(actfunc == ""):
            continue
        
        # if the variable is in the line
        if (varnam in line):
            # finds where the variable starts
            index = line.find(varnam)

            # checks if there is a letter after the end of variable, if there is then it isn't a variable on its own
            if(line[index + len(varnam)].isalpha() == True):
                continue
        
            # if it finds a comment
            if("\\" in line):
                # if the variable is found before the comments start
                if (line.find(varnam) < line.find("\\")):
                    # append the current function to the list of functions
                    funcs.append(actfunc)
            else:
                # append the current function to the list of functions
                funcs.append(actfunc)
                
    return funcs
                
def GetVariables():
    # the active function
    actfunc = ""
    scope = "Global"
    for line in codefile:
        if(actfunc != ""):
            scope = "Local"
        
        # finds the next function
        if(isFunction(line) == 1):
            # sets the new active function
            actfunc = GetFunction(line)

            print("Line: ", line)
            print("Line: ", line[:-1])

            print(line)

            # gets params
            params = GetParams(line[:-1])

            print("Split: ", line[:-1])
            print("Params: ", params)

            scope = "Parameter"

            # prints params
            for param in params:
                var_names.append(param[1])
                var_types.append(param[0])
                var_scope.append(scope)
                var_funcs.append(actfunc)
                print(f"{param[1]} {param[0]} {scope} {actfunc}")
        else:
            var = []
            for type in types:
                if line.startswith(type):
                    var = GetVariable(line) 

            if(len(var) == 2):
                var_names.append(var[1])
                var_types.append(var[0])
                var_scope.append(scope)
                var_funcs.append(actfunc)
                print(f"{var[1]} {var[0]} {scope} {actfunc}")


    data = {
        'Variable Name': var_names,
        'Type': var_types,
        'Scope': var_scope,
        'Functions': var_funcs
    }


    df = pd.DataFrame(data)

    df.to_excel("Variables.xlsx", index=False)

globs = [
    "ngi", "ngc", "guestno", "gunam", "gucontactnam", "guconttelenum", "guemailaddr",
    "gugenre", "nei", "nec", "eventno", "evdate", "evtime", "evdur", "evlocation",
    "evdescription", "evtitle", "evcost", "evcont", "evcontemail", "evcontnum",
    "nmi", "nmc", "mucatno", "mutitle", "muartist", "mugenre", "mupub", "muplaytime",
    "mucheck", "mufreq", "nli", "nlc", "evlinkevno", "evlinkdjno", "npi", "npc", "pllinkcatno",
    "pllinkevno", "djno", "sch", "nui", "nuc", "usrnos", "usernames", "passwords", "loas", "curusr"
]


for glob in globs:
    fs = GetReferences(glob)
    outy = ', '.join(fs)
    print("\n" + glob + ":", outy)