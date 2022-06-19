# projeto-final-c
Projeto final da disciplina de Fundamentos de Programação do curso de Sistemas de Informação - UTFPR

Jogo da Vida

Em 1970, o matemático britânico John Conway propôs um jogo baseado em autômatos celulares que simula os
processos de nascimento, sobrevivência e morte. As regras do jogo são baseadas no fato que um ser vivo necessita de
outros seres vivos para sobreviver e procriar. Contudo, o excesso de indivíduos provoca a morte devido à escassez de
comida. Leia o artigo “Jogo da Vida” (PDF) disponibilizado no site da disciplina para saber mais informações. O estado
de cada geração é determinado a partir da geração anterior de acordo com as seguintes regras:

- Uma célula viva morre de solidão se tiver menos de duas vizinhas vivas.
- Uma célula viva morre por superpopulação se tiver mais que três vizinhas vivas.
- Uma célula viva sobrevive se tiver duas ou três vizinhas vivas.
- Uma célula morta ganha vida se tiver exatamente três vizinhas vivas.

Observe que estas regras são aplicadas simultaneamente, ou seja, os nascimentos, mortes e sobrevivências num dado
passo do jogo dentro da geração corrente são função da configuração atual (então é preciso salvar as mudanças numa
outra matriz para não modificar a atual e só ao final da geração atual esta deve ser atualizada). Considere como vizinhas
as células localizadas na horizontal, vertical e diagonal.


Autômatos Celulares

Os Autômatos Celulares são sistemas evolutivos baseado em regras simples. Os Autômatos Celulares são formados
por uma rede de células, um gride. Cada célula ocupa uma posição na rede e possui um determinado estado inicial que
é alterado de acordo com as regras e com o estado das células vizinhas. Cada célula evolui em função do seu estado
anterior e do estado anterior das células vizinhas. A partir de um ponto inicial e, baseado em uma regra que determina as
condições para mudança de estado, a célula com estado inicial, ao ser alterado, interfere na célula vizinha, desencadeando
um efeito evolutivo. Sendo que a mudança dos estados ocorre simultaneamente a cada instante de tempo e sem qualquer
tipo de entrada. Iniciando um comportamento autônomo e evolutivo os Autômatos Celulares possuem três características
importantes:

- Paralelismo: As células evoluem simultaneamente e independentes. A atualização do estado da célula é autônoma e
independente.

- Localidade: A atualização do estado da célula depende somente do seu estado atual e do estado atual das
células vizinhas. Homogeneidade: As regras valem para todas as células.
Existe uma série de diferentes imagens que podem ocorrer no Jogo da Vida, incluindo, vida eterna, osciladores e
naves espaciais.

Para mais detalhes sobre o jogo da vida, veja o artigo ao final deste documento e acesse os links:

http://dan-scientia.blogspot.com/2011/12/o-jogo-da-vida-de-john-conway.html
https://pt.wikipedia.org/wiki/Jogo_da_vida
