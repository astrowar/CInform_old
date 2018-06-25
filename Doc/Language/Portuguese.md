# Modulo para lingua Portuguesa

Portugues é um idioma bem complexo e precisa ser tratado com cuidado. uma vez estabelecido as bases, fica mais facil portar os mesmos conceitos para as demais linguas latinas.


## Diferenças do Inform 7 Padrão

No portugues os todos substantivos possuem genero. só isso ja adiciona uma dimensao a mais no tratamento da sintaxe.

    a maçã é um objeto
    o prego é um objeto
    alguns trocados é um objeto
    
Outra diferença está na ordem dos adjetivos. em portugues eles vem depois do substantivo

    a maçã é vermelha
    pegue a maçã vermelha
    the apple is red
    get the red apple
    
O verbo IS do ingues se traduz como o verbo ser, mas tambem pode ser "estar" , mas estar nao é ser ...

IS == SER , IS == ESTAR , BUT SER != ESTAR   


O que leva a uma outra questão ... qual é usado ?

    a maçã pode ser verde ou madura
    a maçã pode estar verde ou madura
    
    if (a maçã esta madura) : ...
    if (a maçã é madura) : ...
    
Embora ambas as formas estejam certas, há implicacoes. 
   é madura implica em um estado fixo, intrinsico ao objeto. 
   esta madura  dá a se estender que o estado é variavel ou indefinido.

O programa pode aceitar as duas formas. mas as duas formas não são a mesma coisa para quem lê.
   
Ao gerar os modulos de suporte para multiplas linguas fica mais evidente que Verb pode ser composto. nesse caso o verbo é indireto e requer uma preposicao

PP = prepositional phrase 

VP -> Verb NP      
   coma a pizza

VP -> Verb NP PP   
   coma a pizza com o garfo

VP -> Verb PP  
   coma com o garfo

NP -> det Nominal
NP -> ProperNoum

Nominal -> Noum+  

 PP -> Preposition NP 

 Basicamente Para definir um verbo ou acao, precisa deficnir se o verbo é :
VP -> Verb (noum1)
VP -> Verb Preposition (noum1) 
VP -> Verb (noum1) Preposition (noum2)


	The verb to suspect implies the suspecting relation. 
	The verb to be suspicious of implies the suspecting relation.
	The verb to be able to approach implies the approachability relation.
	The verb to be embedded in implies the reverse incorporation relation.

    O verbo suspeitar implica na relação suspeitando.
    O verbo embutir implica na relação incorporação.
    O verbo (poder se aproximar) implica a relação de acessibilidade.

    The verb to notice means the noticing relation
    O verbo notar significa a relação percebedora 

Nota-se que neste ultimo termo falta o "de" .. "of"  em ingles

O registro de verbos é feito pelo bloco Verb que deriva para VerbPP e VerbNoumPP
VerbPP requer a preposicao e VerbNoumPP requer um noum entre o verbo e a preposicao.





se o player pode se aproximar do alvo então : ....

    Understand "draw the attention of [someone] to [someone]" as drawing the attention of it to. Drawing the attention of it to is an action applying to two visible things.

A traducao fica:
    Entenda "chame a atenção de [alguem] para [algo]" como (charmar a atenção dele)
    (charmar a atenção dele) é uma ação aplicada a duas coisas visiveis.


o Entenda nesse caso gera um patten para ser usado a posteriori
Entenda "XXX [Noum1] XX X [Noum2] X"  como ...  O entenda serve apenas o Try e Replace de noums

    Understand ("your local" , "your" , "local" or "my local") as the vicar.
    Entenda ("caneca" , "calice" ou "taça") como copo.
    Entranda "tropa" como plural de soldado

    Entenda o comando "agarrar" como  "pegar"


    Understand "box of [something related by containment]" as a box.
	Understand "box in [something related by reversed containment]" as a box.

    Entenda "caixa do [algo relacionado por conteção]" como caixa

    Understand "paint [something] [a color]" as painting it the color. 
    Entenda "pintar [algo] [cor]" como pintando ele cor 




## Modulo de geração Gramatical

Este é com certeza a parte mais complexa do sistema de gramatica. pois deve juntar as informcoes e sintetizar uma frase com concordancia.
  Essas informações de concordancia devem ser Genero, numero e grau. isso para portugues.  As informacoes do substantivo vem de sua declaracao primaria na sua criacao.
   A porta é ...
   Alguns fiapos estão na sala.

   NoumSuplPt ->  word + (article , gender, number)

    alguns fiapos são... ->       fiapos (alguns, male, plural  ) 
    Bob é ..  Bob (nothing , nothing , singular )

    "[The noun] [carry] too much static charge."
    "[O sustantivo] [carrega] muita carga estatica."

se aplica na caneca :

    "a caneca carrega muita carga estatica."    

Se o tempo for passado:

    "a caneca carregou muita carga estatica."    

Aplicando o sou/estou
    "[O sustantivo] [esta] [carregando] muita carga estatica." 
    "a caneca estava carregando muita carga estatica."    




# Runtime Parser

Isso nos leva ao runtime parser. a peça que falta no interpreter. ler os comandos do user, entender e chamar os comandos em si.
No caso do parser padrão, cada entrada do usuario. chama um action no parser.
