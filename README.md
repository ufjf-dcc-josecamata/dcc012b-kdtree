# DCC012b - KDTree 

## Definição

Uma árvore k-d é uma árvore binária em que cada nó é um ponto k-dimensional. 
Cada nó não-folha pode ser considerado implicitamente como um gerador de um hiperplano que divide 
o espaço em duas partes, conhecido como semiespaço. Os pontos à esquerda do hiperplano são representados 
pela subárvore esquerda desse nó e pontos à direita do hiperplano são representados pela subárvore direita. 
A direção do hiperplano é escolhida da seguinte maneira: cada nó na árvore é associado a uma das k-dimensões, 
com o hiperplano perpendicular a esse eixo dimensional. Assim, por exemplo, se para uma determinada operação de 
split o eixo "x" é escolhido, todos os pontos da subárvore com um valor "x" menor que o nó irão aparecer na subárvore 
esquerda e todos os pontos com um valor "x" maior vão estar na subárvore direita. 

## Operações em árvores k-d
### Construção 
Dada um lista de poonts k-dimensional, a arvore é construida da seguinte forma: 
 - À medida que se desce pela árvore, ciclos através dos eixos são usados para selecionar os planos de divisão. (Por exemplo, em uma árvore 3-dimensional, a raiz deveria ter um plano alinhado em x, os filhos da raiz teriam ambos os planos alinhados em y, os netos da raiz teriam todos planos alinhados em z, os bisnetos da raiz teriam planos alinhados em x, os trinetos da raiz teriam planos alinhados em y, e assim por diante).
- Em cada etapa, o ponto selecionado para criar o plano de corte será a mediana dos pontos colocados na árvore k-d, o que respeita suas coordenadas no eixo que está sendo usado.

```

function arvoreKD (lista pointList, int profundidade)
{
    // Selecione o eixo com base na profundidade para que o eixo percorra todos os valores válidos
    var int eixo := profundidade mod k;
    
    // Ordena a lista de pontos e escolhe a mediana como elemento de pivô
    // Seleciona a mediana usando eixo
    mediana := selectMediana(eixo, pointList);
    
    // Cria o nó e constrói a subárvore
    node.location := mediana;
    node.filhoEsquerda := arvoreKD(pontos em pointList antes de mediana, profundidade+1);
    node.filhoDireita  := arvoreKD(pontos em pointList depois de mediana, profundidade+1);
    return node;
}

```


### Inserção

A adição em uma árvore k-d se é feita da mesma forma que qualquer outra árvore de busca. Primeiro, atravessa-se a árvore a partir da raiz move-se para a o filho à esquerda ou para a direita, dependendo se o ponto a ser inserido deve estar na "esquerda" ou "direita" do plano divisor. Uma vez que você chegar ao nó em que o filho deve estar localizado, adicione o novo ponto como filho à esquerda ou à direita do nó folha, de novo, dependendo de que lado do plano divisor contém o novo nó.

### Vizinho mais proximo (nearest)

O algoritimo de busca do ponto mais próximo visa encontrar o ponto na árvore que está mais próximo de um determinado ponto de entrada. 
Essa pesquisa pode ser feita de forma eficiente, utilizando as propriedades da árvore para eliminar rapidamente grandes porções do espaço de busca.

## Implementação

Na pasta [kdtree](kdtree) encontra a implementação das classes [ponto](kdtree/ponto.h) que representa um ponto k-dimensional e 
a classe [kdtree](kdtree.h) com a implementação da KDTreeNode e KDTree. As principais operações foram implementadas, dentre elas:
- *contains* que verifica se um ponto esta na kdtree.
- *nearest* que retorna o ponto mais próximo de um determinado ponto. 

### O que deve ser feito nesta atividade?

Vocês devem implementar o algoritmo de inserção de um ponto na arvore. Veja os comentários no código-fonte.

## Compilação, execução e testes.

Para compilar deve-se seguir os passos:

```shell
cmake -B build 
cd build
make
```

Para executar:
```shell
./tests/test1
./tests/test2
```

Para Ctest:
```shell
ctest 
```



