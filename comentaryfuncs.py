import re

fn = input("Enter File Name: ")
gap = int(input("Enter num functions before new line: "))

if ".cpp" not in fn:
    fn += ".cpp"

print(fn)
f = open(fn, "r")

def fnd(x):
    pattern = r'\b\w+\b\s+(\w+)\s*\('
    match = re.search(pattern, ln)

    if match:
        return match.group(1)

# regex pattern
pattern = r'\b\w+\b\s+(\w+)\s*\('

lns = []

ln = f.readline()

while "int main" not in ln:

    if "#define" not in ln:
        match = fnd(ln)

        if match:
            lns.append(match)

    ln = f.readline()

for i in range(0, len(lns)):
    print(lns[i])

f.close()

f = open("funcs.txt", "w")

final = ""

if(gap == 0):
    gap = len(lns)

for i in range (0, len(lns)):

    if i % gap == 0:
        final += "\n" + lns[i]
    else:
        final += " " + lns[i]

f.writelines(final)

f.close()