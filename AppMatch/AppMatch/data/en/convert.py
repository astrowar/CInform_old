import os
def loadverbs():
    vb = open("verbs.txt","r")
    f = open("verb.ixx","w")
    
    f.write("static const verbalConj verbs[] = {\n")
    first = True
    for l in  vb.readlines():
        if   first == False  :
            f.write(",\n")            
                
        w,verbo,tempo = l.split()
        lastEntry = '{"'+w+'","' + verbo + '",'+ tempo + '}'
        f.write(lastEntry)
        first= False

    
    f.write("};\n")                
    f.close()
    
    print("done")


def loadnoums():
    nn = open("noms.txt","r")
    f = open("noums.ixx","w")
    f.write("static const noumConj noms[] = {\n")
    first = True
    for l in  nn.readlines():
        if   first == False  :
            f.write(",\n")
            
        w,base,tempo = l.split()        
        rr =  '{"'+w+'","' + base + '",'+ tempo + '}'
        f.write(rr)
        first= False

    f.write("};\n")
    f.close()
    print("done")



loadverbs()
loadnoums()
