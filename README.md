# CInform - Community Inform
uma Engine de ficcao iterativa para portugues, ingles e outras linguas. Com foco em flexibilidade e portabilidade, fortemente baseada no inform7

## Uso
 a engine ainda nao possui um input definido, sendo ainda um biblioteca de suporte para um futuro compilador e interpreter
  
 
## Compatibilidade
A engine nao possui nenhum foco em compatibilidade com sistemas de IF ja existentes. O proposito eh ser ilimitado no sistema. por ser escrita em c++ puro, sem uso de bibliotecas externas, permite o port para qualquer plataforma , incluindo o porte para javascript atraves do emscriptem.

### Language diferences

A linguagem em si é algum semelhante ao inform 7. porem com mudancas. uma delas é o uso extensivo de parenteses para um melhor entendimento da sintaxe de cada frase. 

A linguagem nao é tipada como o inform. Embora existam tipos internos, as variaveis nao sao estritas. permitindo um tipo de programacao de tipos  genericos em si mesmo.  
Recursos de metaprogramacao será implemetado no futuro, quando a liguagem estive mais madura.

### Virtual Machine

A maquina virtual que roda essa implementacao é propria. nao depende de outras tais como o glux ou z-machine. O codigo gerado é um bytecode em forma de arvore. que é uma conversao direta do codigo fonte. isso trasnfere o trabalho do compilador para o interpreter.
Remover essa dependencia permite a iteracao direta do codigo com o ambiente de execucao. tal como inserir HTML , incorporar imagens, extrapolar os limites de memoria e ate mesmo a inclusao de multitarefa nativa.

### Focus

OOriginalmente, o inform 7 é focado totalmente no desenvolvimento de ficção iterativa. sendo presso ao subgenero de sala, objetos, ações. reimplementar a linguagem em sua propria maquina virtual pe

## Supported Languages

Ate o momento o parser esta pronto para reconhecer apenas o ingles. e de uma forma simples.
Recursos de suporte para outras linguas, entre elas o portugues, serão implementados a medida que os modulos de linguagem forem esritos.
A ideia é que o parser e o interpreter sejam codificados na mesma lingua. Assim, um byecode codificado em alemão so rodaria na VM para alemão. Porem todas compartilham a estrutura basica e a logica. 
Essa separacao abrupta permite que linguagens muito diferentes entre si possam existir. ja que fazer um sistema com linuagem universao ja foi demostrado pelo google so ser possivel se o contexto d frase for incluido.

## Contrib
  Qualquer contribuição é bem vinda. principalmente na escrita de teste para a linguagem. Ver Doc/ unit Tests
  sugestões de linguagem e aprimoramentos tambem são aceitos, mas neste primeiro estagio o objetivo e tornar o sistema usavel
  Exemplos de codigos completos e como eles devem se comportar são bem vindos para complementar os testes
  sugestões para o sistema de linguagem para gerar frases em cada linguagem são bem vindas , ja que essa parte esta quase vazia.
  um Modelo de mundo ( define o que é uma sala , porta, pessoa , adjetivos , ações basicas )  tambem pode ser elaborado antes da conclusão dos codigos.
  
  ### how Contrib
   Até o momento a melhor forma de contribuir é fazendo o fork , implementar as mudancas e submeter o pull request.  
   Outra forma é escrever a sugestão como um issue usando a devida Flag. 
   No momento o codigo estão tão complexo e pouco documentado que contribuições no source code estão congeladas até uma documentação mais profunda seja elaborada.
   
   
