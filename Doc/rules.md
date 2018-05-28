# Rule e Rulebooks

## Regras 
 regras sao consideradas analogas ao procedures de outras linguagens
 
 
 blossom shaking rule: 
   say "The summer breeze shakes the apple-blossom."
 
 let the destroyed object be the object produced by the cat behavior rules; 
 
 para invocar uma regra utiliza-se o palavra (follow)
    follow the appraisal rules.
    
 rules tambem possuem argumentos de entrada, as regras de entrada funcionam como match do racket. mas sao verificados em ordem: 
    Grading is a number based rulebook 
    Grading 5: say "It's five. What can I say?" instead. 
    Grading an odd number (called N): say "There's something odd about [N]." instead. 
    Grading a number (called N): say "Just [N]." instead.
    
    a palavra chave (instead) interrompe o fluxo de regras e executa uma saida
    
 
 
 ## rulebook 
 rulebooks possuem um conjunto de regras dentro dele. somente um rulebook possui default outcome e variavel interna
 
 
 The pick a plan rules are a rulebook. 
        The pick a plan rules have default outcome success. [ Or failure, or no outcome ]
        The pick a plan rules have a number called the aptitude mark.
        A pick a plan rule: say "I always fail, regardless the rulebook's default."; rule fails.
        A pick a plan rule: say "I can never make up my mind so one of my peers will now execute."; make no decision.
        A pick a plan rule: say "I exhibit the default behaviour for the rulebook."
        
 cada termo eh executado em ordem de listagem. 
 
 Eh possivel inserir rulebook dentro de rulebook : 
   The key location rule is listed in pick a plan rules.
   
remover de uma listagem especifica   
   The can't act in the dark rule is not listed in the visibility rules. 

listado em lugar nenhum    
   The can't remove from people rule is not listed in any rulebook.

Ou mesmo substiuir toda uma regra:
  the (print fancy final score) rule substitutes for (the print final score) rule.

outra forma de desligar uma regra é  : 
   The (print fancy final score) rule does nothing.
   The (print fancy final score)  rule does nothing unless (the score is 100)
   The (print fancy final score)  rule substitutes for (the print final score) rule when (the score is greater than 100)

  
## termino e results

pose abortar uma regra , basta usar a keyword no final da frase
   continue the action; means "end this rule with no outcome" 
   stop the action; means "end this rule in failure" 
   instead; means "end this rule in failure"

apos invocar a regra pose-se verificar se houve um sucesso ou falha 
   follow search item rule
   if rule succeeded:
      say "found it .. "
      follow used item rule
      if rule failed :
         say "..but i cant use it"
      else
         say "..works fine"
         
alem de deifinir sucesso e fracasso eh possivel retornar um Enum de  valor

Visibility rules have outcomes (there is sufficient light)  and (there is insufficient light)
para verificas a saida da regra use :

    follow Visibility rules 
    if the outcome of the rulebook is (there is insufficient light): 
        say "i cant see anything"

Apenas rulebook producem values e devem ser declarados antes do uso ou insercao.
Observe que apenas rulebook equivalentes podem ser substituidos.

X is (rulebook )
X is (K based rulebook )
X is (rulebook producing L )
X is (K based rulebook producing L)

exemplo :
  The ( nearest item ) rules is a rulebook producing an object
  ( nearest item ) when (thing  called T)  is in pocket: 
    rule succeeds with result T
  ( nearest item ) when (thing  called T)  is in location: 
    rule succeeds with result T    
  ( nearest item ) rule: 
     say "Nothing near to use "
     rule succeeds with result Nothing    

para acessar o item use a sintaxe :
 let (the near item)  be (the object) produced by ( nearest item ) rules
 
 ou seja :
  value = K produced by R rules
  
Para passar os argumentos :
    let (the near item)  be (the object) produced by ( nearest item ) rules for (argument) 
    follow  ( nearest item ) rules for (argument)    -> nao tem valor de retorno
    
Se tentar invocar sem argumento , ha um rumtime erro. invocar com retorno sem usar ele nao resulta em erro.

eh possivel fazer o resultado de uma regra ser o resultado de uma regra interna usando o  abide 

abide R rule by Y :
  follow  R rules for Y
  if rule succeeded :
     rule succeeds 
  if rule failed :     
     rule failed 


anonymously  abide R rule by Y :
  follow  R rules for Y
  if rule succeeded :
     rule succeeds with result ( K produced by R rules)   
  if rule failed :     
     rule failed with result ( K produced by R rules)       
   

         
 
