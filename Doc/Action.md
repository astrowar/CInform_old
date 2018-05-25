# Action
os action por si nao sao nada alem de uma forma de disparar um conjunto de eventos
cada action vai disparar na ordem os eventos
Before, Instead , Check, Carry out , After e Report


"Before" rules genuinely precede checking of any kind. 
They also differ from instead rules in that they do not automatically stop the action in its tracks. 
Rather, they are provided as an opportunity to ensure that something else is done first. For example:
    Before taking the napkin :
       say "(first unfolding its delicate origami swan)"
       
O default de Before é (continue the action)
O default de Instead é (stop the action)

Extes comandos (continue e stop)  deteminam se a acao continua no proximo passo.
Observe que cada etapa pode ter mais de uma regra.
Por exemplo 

Before taking the napkin : ...
Before taking anything : ...
Before taking anything in darkness : ...

são executado se a acao take napkin for ativada no escuro.  Em qual ordem ? nao sei , espero que seja do mais generico para o especifico
por que ?

supnha que hava uma regra:

    Instead taking an carring thing :
      say "i already have" 
    Instead taking heavy thing :
      say "Ohh .. is heavy!" 
 
 o primeiro esta no sistema basico , o segundo foi adicionado ... se tentar pegar algo pessado que esta em posse de si, o que sera dito ? 
 
 
## Fail Reasons 
As acoes sao considerada como eventos , estes eventos podem ser finalizados com falhas especificas

Para tal basta informar o comando fail seguido do texto que identifica o motivo da falha
Essa informacao seguira no fluxo de comando ate encontrar o comando catch ou sair do nivel de identacao .. ou seja no mesmo nivel do try

exemplo:
    Check diagnosing: 
    if noun is not a person:
       say "Only people can have diagnoses." 
       fail "not person"
       stop action   //nao eh invocado
       
Faz a acao falhar automaticamente e da um stop na acao .. observe que o stop por si so nao eh uma falha, mas um descarte do que vem depois.
Quando um try é invocado, eh armazenado um novo valor na pilha de fail . quando sai daquele nivel, a pilha eh descartada. (estou falando da CommandList )
o catch nao precisa ser chamado na sequencia do try, mas seria bom para evitar confusao

    try examine computer
    catch "require item" :
        say "you need something to examine the computer"

o catch funciona como um comparador de strings normais, incluindo regex. Talvex fique meio reduntande certas coisas. mas quem decide eh o autor

o catch nao elimina o fail reason da pilha.. assim eh possivel chamar em sequencia

    try examine computer
     catch "require item" :
        say "you need something to examine the computer"
     catch "require light" :
        say "is too dark to see anything"   



Agora a coisa pega ...

    Check login computer : 
         if password is not know:
            say "the login screen is protect by an password ..."
            fail "require password"
            stop action 
         
    Check examine computer : 
         try login on computer      
         catch "require password" :
            try hacking computer                  
            catch "not a hacker":
                say "you is not a hacker"
                

Dada a sequencia acima, qual erro vai ser visivel a quem tenta try examine computer e nao tiver a senha ?
deveria ser algo como "the login screen is protect by an password ..."   e so .
mas vai imprimir isso sequido de "you is not a hacker"
e se for um hacker vai parecer que nao ocorreu nada .. mas foi liberado ?

pode-se resolver usando :

    Instead examine broken computer : 
         say "is not working..."
         fail "computer broken"
         
    Check examine computer : 
         try login on computer      
         catch "require password" :
            say "maybe i can hack the password ..."
            try silently hacking computer                                             
            catch any
                say ".. but i can not"
                stop the action            
            say ".. sucess"                   
         catch any :            
                say "I am unable to examine"
                stop the action            
          
          
    Report examine computer :                 
         say "the contents of computer:"
         say (contents of computer)
         
            

Instead so eh falha se tiver um fail , se tiver um continue action ou nenhum fail .. eh um sucesso.
