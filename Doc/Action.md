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
 
 
 
