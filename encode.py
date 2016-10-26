import os
import re

lns = open("CMakeLists.txt","r").readlines()

obj = ""
for l in lns:
  m = re.search(  "AppMatch/AppMatch/(.+)cpp" , l )
  if m!= None :
     fullp = m.group(0)
     fp = m.group(1)+"bc"

     cmd = "emcc -s ELIMINATE_DUPLICATE_FUNCTIONS=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_FILESYSTEM=1 -std=c++14 -fno-exceptions -fno-rtti  -stdlib=libc++  -Oz "+ fullp + " -o obj/"+ fp
     #print cmd
     #print cmd
     #os.system(cmd)
     obj  = obj +" obj/"+ fp

cmdLink = "emcc -s EXPORTED_FUNCTIONS='[\"_sayHi\"]' -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='[\"sayHi\"]'  -s DISABLE_EXCEPTION_CATCHING=1 -s NO_FILESYSTEM=1   -Oz -o a.out.js " + obj
print(cmdLink)
os.system( cmdLink  )
