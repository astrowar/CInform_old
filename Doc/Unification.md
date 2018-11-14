## Unificação

Algumas cosntruções de linguagem requerem algo alem da sintaxe comum. precisam ser tratados em termos logicos muito parecidos com o que se tem no prolog
Para isso foi pensado no sistema de unificação de variaveis.

### Sintaxe

A unificação é uma variavel que vai sem valor definido e a medida que seu valor vai sendo inferido, ela vai invocando os termos seguintes.

        if Bob is holding (an hot thing called X) :
           say X is hot
           
Esse é um tipo de phase que passa para o sistema uma variavel indefinida, X, o sistema é que deve completar ela.
Atualmente o sistema de Match é que da conta disso. mas não é suficiente.

