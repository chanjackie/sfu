
import random

chars = "0123456789"

for i in range(26):
    chars += chr(65+i)

for i in range(26):
    chars += chr(97+i)

for i in range(20):
    n = random.randint(250, 500)
    x = ""
    for j in range(n):
        x += chars[random.randint(0, len(chars)-1)]
    print x
        

