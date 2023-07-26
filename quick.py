fin = []
out = []
funcdefs = []
inp = input("Option: ")

choice = ""

if(inp == "FILE"):
    fp = input("Enter FilePath: ")
    f = open(fp, "r")

    ln = f.readline()
    print(ln)
    while(ln != ''):
        out.append(ln.strip())
        ln = f.readline()
        
    f.close()
else:
        out.append(inp)

while inp != "q" and inp != "FILE":
    inp = input()
    
    if(inp != "q"):
        out.append(inp)

equ = ""

for i in range(0, len(out[0]) + 5):
    equ += "="


fin.append("cout << \"\\n\\t" + out[0] + " Menu" + "\";")
fin.append("cout << \"\\n\\t" + equ + "\\n\";")


p = len(out)

for i in range(1, len(out)):
    fin.append("cout << \"\\n\\t" + str(i) +". " + str(out[i]) + "\";")

fin.append("cout << \"\\n\\t" + str(p) + ". Return\";")

if(inp != "FILE"):
    choice = input("Enter choice variable name: ")

if(inp == "FILE"):
    choice =  (str(out[0]).replace(" ", "")).lower() + "choice"

funcdefs.append(out[0].replace(" ", ""))
funcdefs.append(out[0].replace(" ", "") + "Menu")

fin.insert(0, "int " + str(choice) + ";")
fin.insert(1, "")
fin.insert(0, "int " + funcdefs[1] + "()\n{")

fin.insert(2, "\nclrscr();")

fin.append("\ncout << \"\\nEnter Choice: \";")
fin.append("cin >> " + str(choice) + ";")

fin.append("\nswitch(" + str(choice) + ")\n\t{")

for i in range(1, len(out)):
    fin.append("\tcase " + str(i) + ": ")
    fin.append("\t\t{")
    
    
    funcdefs.append(str(out[i]).replace(" ", ""))
    
    if(out[0].find("View") != -1):
        funcdefs[len(funcdefs)-1] = (str(out[0]).replace(" ", "")) + funcdefs[len(funcdefs)-1]
    if(out[0].find("Change") != -1):
        funcdefs[len(funcdefs)-1] = (str(out[0]).replace(" ", "")) + funcdefs[len(funcdefs)-1]
    
    fin.append("\t\t" + funcdefs[len(funcdefs)-1] + "();")
    fin.append("\t\tclrscr();")
    fin.append("\t\tbreak;")
    fin.append("\t\t} // endcase")

fin.append("\tcase " + str(p) + ": ")
fin.append("\t\t{")
fin.append("\t\tclrscr();")
fin.append("\t\tbreak;")
fin.append("\t\t} // endcase")
fin.append("\t}")

fin.append("\nreturn " + str(choice) + ";\n}")

fin2 = []
motherfunc = input("Generate Mother Function (y/n): ")

fst = out[0][0:out[0].find(" ")]

stat = fst.lower() + "status"
if motherfunc == "y" or motherfunc == "Y":
    fin2.append("int " + funcdefs[0] + "()\n{")
    fin2.append("int " + stat + " = 0;")
    fin2.append("while (" + stat + " != " + str(len(out)) + ")\n\t{")
    fin2.append("\t" + stat + " = " + funcdefs[1] + "();")
    fin2.append("\tclrscr();\n\t} //endwhile")
    fin2.append("\ngetch();")
    fin2.append("return 0;")
    fin2.append("}")

decs = ""

if motherfunc != "Y":
    decs = input("Generate Function Declarations (y/n): ")

fin3 = []
if decs == "y" or motherfunc == "Y":
     for i in range(0, len(funcdefs)):  
        fin3.append("int " + funcdefs[i] + "();")
    

defs = ""

if motherfunc != "Y":
    defs = input("Generate Function Definitions (y/n): ")

fin4 = []
if defs == "y" or motherfunc == "Y":
    for i in range(1, len(out)):
        fin4.append("\nint " + funcdefs[i+1] + "()\n{")
        
        outs = str(out[i])
        
        if(out[0].find("View") != -1):
            outs = out[0] + " " + outs
        if(out[0].find("Change") != -1):
            outs = out[0] + " " + outs
        
        equ2 = ""
        for j in range(0, len(outs)):
            equ2 += "="

        fin4.append("clrscr();\ncout << \"\\n" + outs + "\";")
        fin4.append("cout << \"\\n" + equ2 + "\\n\";\n")
        fin4.append("cout << \"\\nPress any key to return\";\ngetch();")
        fin4.append("\nreturn 0;\n}")

fout = open("out.txt", "w")

for i in range(0, len(fin3)):
    fout.writelines("\n" + fin3[i])

fout.writelines("\n\n")

for i in range(0, len(fin2)):
    fout.writelines("\n" + fin2[i])

fout.writelines("\n\n")

for i in range(0, len(fin)):
    fout.writelines("\n" + fin[i])

for i in range(0, len(fin4)):
    fout.writelines("\n" + fin4[i])

fout.close()
