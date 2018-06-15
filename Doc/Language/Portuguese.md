# Modulo para lingua Portuguesa

Portugues é um idioma bem complexo e precisa ser tratado com cuidado. uma vez estabelecido as bases, fica mais facil portar os mesmos conceitos para as demais linguas latinas.


## Diferebcas entre o inform 7 Padrão

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
   
