import os
import random
import math

cwd = os.getcwd()
print(cwd)

groupTitle = input("Group title: ")
dir = cwd + '\\' + groupTitle + "_instances"
print(dir)
if not os.path.exists(dir):
	os.mkdir(dir)
os.chdir(dir)

n1,n2 = input("Value for n1, n2: ").split()
n1 = int(n1)
n2 = int(n2)
print("n1, n2:", n1, n2)

p1,p2 = input("Value for p1, p2: ").split()
p1 = int(p1)
p2 = int(p2)
print("p1, p2:", p1, p2)

m1, m2 = input("Value for m1, m2: ").split()
m1 = int(m1)
m2 = int(m2)
print("m1, m2:", m1, m2)

c11, c12 = input("Values for c1: ").split()
c11 = int(c11)
c12 = int(c12)
print("c11, c12:", c11, c12)

c21, c22 = input("Values for c2: ").split()
c21 = int(c21)
c22 = int(c22)
print("c21, c22:", c21, c22)

for i in range(5):
	f = open(groupTitle + "_instance" + str(i+1) + ".dzn", "w+")
	n = random.randint(n1, n2)
	f.write("n = " + str(n) + ";\n")
	k = int(p2 * n2)
	f.write("k = " + str(k) + ";\n")
	price = []
	for j in range(n):
		p = random.randint(p1, p2)
		price.append(p)
	f.write("price = " + str(price) + ";\n")
	m = random.randint(m1, m2)
	f.write("m = " + str(m) + ";\n")
	buy = []
	free = []
	z = 0
	while (len(buy) < m):
		z += 1
		b = random.randint(1, n)
		c1 = random.uniform(c11, c21)
		c2 = random.uniform(c12, c22)
		fr = round(b*c1/c2)
		# print(b, fr)
		if fr != 0 and ((fr+b) <= n) and ((c11/c12) <= (fr/b)) and ((fr/b) <= (c21/c22)):
			buy.append(b)
			free.append(fr)
		if (z > 10000):
			break
	f.write("buy = " + str(buy) + ";\n")
	f.write("free = " + str(free) + ";\n")

wait = input("DONE. PRESS ANY KEY TO EXIT.")