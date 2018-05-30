# Predicades

Predicados .. sao como os asserts do prolog. mas no cinform cada um deles opera como se fosse uma regra independente. ou seja, cada um tem seu proprio conjunto de variaveis locais

um predicado sempre se da inicio no primeiro nivel da linguahe e tem dois pontos seguindo
Por exemplo

    Predicado :
       isto eh um predicado
    
    To decide  X :
       outro predicado

    Grading a number (called N):   #isso inicioa um predicado
       if N > 10 :                 #mas isso nao
          say "manys .."   
       else:    
          say "Just [N]." instead.   
        
    To plainly greet (friend - a person):  #tambem eh um predicado
                say "Hi [friend]."        

Todo predicado possui uma pilha de variaveis locais. elas sao :
   * o outcome de do sistema de regras
   * a lista de variaveis associadas pelo match que invocou essa regra
   
   
um rulebook nao eh um predicado. por isso ele precisa ter um conjunto de variaveis definido na declaracao.
Quando isso ocorre todas as regras daquele rulebook tem acesso a  aquela variavel , eh se torna uma variavel compartilhada entre as regras

    The nearest object rulebook has an thing called item
        (nearest object) rule : now item is anything in pocket.
        (nearest object) rule : 
            if item is nothing :
                now item is (the thing)  produced by (object in the room) rules                
        (nearest object) rule : 
            if item is nothing :
               rule fails.
               
O exemplo acima vai testando cada regra com o mesmo item em sequencia. a  variavel item nao eh resetada entre cada chamada, pois eh global


Tambem sao considerados predicados eventos:

    When dialog scene begins:
         say "dialog begins"
         
    When dialog scene end:
         say "..."         
         
Os event handles das actions tambem sao predicados da linguagem

    Check getting (thing called item):
        if item is not in location;
           say "i cant do it"
           stop the action
    

## Assertions

Basicamente o que nao eh predicado eh assertion. ouseja, uma definicao que eh aplicada ao inicio do codigo, o config se assim podemos dizer . e as declaracoes das coisas


