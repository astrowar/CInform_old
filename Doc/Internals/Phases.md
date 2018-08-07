### Phrases

Phrases são como certas constrtucoes semanticas sao itendificadas. as phases sao aquilo que sao transformados em codigo.

ha dois tipos de frases. as internas e as externas.

## Phrases internas
Frases internas sao ideintificadas pelo sistema. A frase mais comum é o DirectAssign.
sua construcao se da na forma :

    X is Y

E outras construcoes tais como: 

    if X :
    let X be Y
    now X
    try X
    
    
Essas frases evocan diretamente o bytecode associado. Sendo os termos X , Y os argumentos

## Phrases externas

Estas são definidas pelo inicio TO e seguido de alguma denominacao sobre o que ela faz

    To replace (X) by (Y) in ( list - Z ) : ....

Isso cria um tipo de procedure, sem valor de retorno. cada item dentro do parenteses é um argumento
  Quando a variavel vem sozinha é um Any, se tiver tipo associado , é um match daquele tipo
  
    To open (locked door - L ) : ....

Nessa composicao o interpreter vai verificar se o argumento eh um "locked door" seja la o que isso quer dizer.
so entao libera o corpo da funcao
