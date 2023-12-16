codefile = open("cp.cpp", 'r')

types = [ "int", "char", "float", "void" ]

def SeparateSizes(typ, vardec):
    if "[" not in vardec:
        if typ == "int":
            final = "short"
        
        return final

    splited = vardec.split("[")[1:]
    final = []

    for item in splited:
        if ";" in item:
            item = item[:-1]
        if "]" in item:
            item = item[:-1]
        
        final.append(item)
    
    return final

def GetVarName(line):
    parts = line.split()

    ftype = ""
    varnam = ""
    size = ""

    ftype = parts[0]


    if parts[1][0].isupper() == True:
        return
    elif "main" in parts[1]:
        return
    
    varnam = parts[1]
    if "[" in line:
        size = SeparateSizes(parts[1])
        print(size)
        
    print(f"{ftype} {varnam}")
        

for line in codefile:
    for type in types:
        if line.startswith(type):
            GetVarName(line)
