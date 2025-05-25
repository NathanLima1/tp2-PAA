Para a implementação do problema foi utilizada uma DP de 3 dimensões, sendo elas:

Distância restante para percorrer
Vértices
Capacidade restante para preecher a mochila

3 fors alinhados percorrem a distância, seguido do vértice e por fim a capacidade

A cada vértice seu valor de peso e habilidade é armazenado em duas variáveis para serem utilizados na atualização dos valores

A cada capacidade, previamente os valores são atualizados para si próprio, isso é feito para garantir que toda a matriz será preenchida, não dependendo somente da distância de seus vizinhos

Em seguida para todos os seus vizinhos próximos o suficiente, e caso um estado anterior seja melhor
o valor alcançado com a combinação de l * vertices atuais e o restante com seu vizinho é salvo, além da quantidade l de soldados.

Os seguintes valores do vizinho também é salvo na célula atual: sua distância, seu vértice e sua capacidade

onde são armazenados na matriz em:
data[distancia restante][vértice sendo analisado][capacidade sendo analisada]

onde cada célula representa uma struct do tipo DpItem, formada por value, prev, prev_c, prev_d

Com cada capacidade, distância e vértice anterior salvo, é possível reconstruir a solução apenas percorrendo por eles e considerando algum critério de parada