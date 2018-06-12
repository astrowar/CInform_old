# Unicode 

Documento que descreve como lidar com o unicode no CInform

## Internal Implementation

Não existe nada ainda que lida com isso. ou seja. nao tem suporte. o suporte ao unicode precisa ser amplo e universal. 
Pois não se sabe em quais plataformas ira rodsar. web, terminal, app ...

As soluções nativas em c++ do unicode são pobres. funcionam bem se considerar wstring. mas isso nao basta para dar suporte a liguagem como o arabe e o chines
E uma das liguagems alvo na terceira fase é o arabe.

## External implementation

é precisa normalizar como os inputs e outputs são tratados. neste caso se deve normalizar com o Node.JS e a engine V8. pois estes são os que melhor lidam com essa questão e são em c++


