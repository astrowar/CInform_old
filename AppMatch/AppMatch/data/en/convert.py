 import os
def loadverbs_old():
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

def fix_punct(x):
    return x.replace('-',"_")

def write_tenses(f, prexix,  tense_list):
    f.write("constexpr static const VERBTENSE "+fix_punct(prexix)+"_tenses[] = {")
    first =True
    for t in tense_list :
        if first == False: f.write(",")
        f.write('{"' + t[0]+ '","'+ t[1] +'"}')
        first = False
    f.write("};\n")

def write_verb(f, prexix,  tense_list):
    n= len(tense_list)
    f.write('{ "'+prexix+'",'+str(n)+','+ fix_punct(prexix)+"_tenses }" )


def loadverbs():
    vb = open("verbs.txt","r")
    f = open("verb_n.ixx","w")    
    #f.write("static const verbalConj verbs[] = {\n")
    first = True
    verbs_conj = {}
    for l in  vb.readlines():
        #if   first == False  :
        #    f.write(",\n")                            
        w,verbo,tempo = l.split()
        if (verbo in verbs_conj) == False:
            verbs_conj[verbo] = []
        verbs_conj[verbo].append( [tempo,w])

        #lastEntry = '{"'+w+'","' + verbo + '",'+ tempo + '}'
        #f.write(lastEntry)
        first= False
 
    #f.write("};\n")                
    #f.close()
    #print(verbs_conj) 

    vlist = verbs_conj.keys() 
    vlist=  list(vlist)
    vlist.sort()
    vlist = vlist[0:20]
    for v  in vlist :
        write_tenses(f,v,verbs_conj[v] )

    
    first = True
    nv = len(vlist)
    f.write("\n\n")
    f.write("constexpr static const VERBDEF verb_eng["+str(nv)+"] = {")
    for v  in vlist :
        if(first == False ): f.write(',\n                                       ')
        write_verb(f,v,verbs_conj[v] )        
        first = False
    f.write("\n};\n")        
    print("done")
    f.close()


def loadnoums():
    nn = open("noms.txt","r")
    f = open("noums.ixx","w")
    f.write("constexpr static const noumConj noms[] = {\n")
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
