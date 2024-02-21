import pandas as pd

codefile = open("cp9.cpp", 'r')
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

        # gets params
        params = GetParams(line[:-1])

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
