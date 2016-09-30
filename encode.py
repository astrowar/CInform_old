import os 
lns = open("files4.bat","r")
for l in lns:
  print l
  os.system(l)
