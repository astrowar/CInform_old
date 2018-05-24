# Definicao da linguagem

A linguagem ate o momento chamada cinform eh inspirada na inform 7, mas com peculidades proprias

* é dinamicamente tipada
* é interpretada e contem uma runtime ativa
* tem gerenciamento de memoria automatico, via contagem de referencias

## Basico
A linguagem tem dois tipod basicos : Objeto e Tipo 
um objeto eh uma instancia de um tipo. 
Ha entidades que sao tratados como Objetos, mas sao criados pela sintaxe.

um tipo eh criado com a frase:
    K is an kind 

para criar um tipo derivado utiliza:
    Kd is an kind of K
   
para criar um objeto :
    O is an K
    
    
por exemplo:
    thing is an kinf
    fruit is an kind of thing
    apple is an fruit
    
### Propriedades
Objetos possuem propriedades, que podem ser difinidads por entidade ou por tipo:
As propriedades sao divididas em adjetivos e variaveis
Um adjetivo eh uma propriedade que eh um conjunto de adjetivos excludentes entre si
por exemplo, uma coisa pode ser portatil ou não
    thing can be portable

nesse caso , o adetivo portable se torna binario, eh binario ou nao:
    now apple is not portable    
    
o uso do now serve para alterar o estado do interpretador. obeserve que nao eh apenas mudar uma variavel, mas um conjunto de outras coisas podem ser alteradas via now





