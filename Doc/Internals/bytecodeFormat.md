#ByteCode Format

The bytecode is an portable way to move the source file from compiler to interpreter.
The compiler is jut an parser, thats convert  natural language to bytecode format.

The bytecode format by numered lines descripting the Block struct of sourcefile.

the line is composte by :

    ID TYPE Member1 Member2 ....
    
the id is the identification obj object in the bytecode, justa an reference 
Type is the enumerate value from  BlockTypeEnum.hpp    for the object. 
Note if the  BlockType enum changes, all bytecodes files become invalid.

example:

    1 17 'best' 
    2 17 'money' 
    3 17 'from' 
    4 122  (  1 2 3  )  
    5 121 'the' 4 
    
this lines store 5 objects.
 the first object is type 17 , from BlockType, will see , is an **BlockNoumStr**
 BlockNoumStr has only one argument : string
 
 ```c++
 obj[1] = BlockNoumStr("best")
 obj[2] = BlockNoumStr("money")
 obj[3] = BlockNoumStr("from")
```

the object 4 is type 122 : **BlockNoumCompose**  , the arguments is std::vector\<HBlockNoum>
 , the list (1 2 3) is that list, from objects obj[1],obj[2],obj[3]
 
  ```c++
  obj[4] = BlockNoumCompose({obj[1],obj[2],obj[3]})  
 ```
 
 And the object id 5 is an **BlockNoumDet**, the arguments are string and BlockNoum
 
  ```c++
   obj[5] = BlockNoumDet( "the" ,obj[4])  
  ```
  
Follow this logic, is possible understand all bytecode file.  Note that bytecode is very dependent of the project version, small changs will invalidade all bytecodes.

The object order of the declaration is very restricted. all objects need to be created before they are referenced. Circular dependencies ** will never ** be allowed for memory sanity.
  