#include <stdio.h> 
#include <stdlib.h>

typedef struct Aresta {
  int a, b, peso;
} Aresta;

int acha(int *conj, int x) {
  if(x != conj[x]){
    conj[x] = acha(conj, conj[x]);
  }
  
  return conj[x];
}

void une(int *conj, int *rank, int a, int b) {
  a = acha(conj, a);
  b = acha(conj, b);

  if(a != b) {
    if (rank[a] < rank[b]) {
      conj[a] = b;
    } else {
      conj[b] = a;
      if (rank[a] == rank[b]) {
        rank[a]++;
      }
    }
  }
}

int main() {
  int n, m, a, b, peso, teste1, teste2;
  scanf("%d %d", &n, &m);
  setbuf(stdin, NULL);

  int *conj = malloc(m * sizeof(int));
  int *rank = malloc(m * sizeof(int));

  Aresta *arestas = malloc(m * sizeof(Aresta));
  Aresta *resultado = malloc(m * sizeof(Aresta));

  int tam_resultado = 0;
  int soma = 0;
  
  for(int i = 0; i < m; i++) {
    conj[i] = i;
    rank[i] = 0;
  }

  for(int i = 0; i < m; i++) {
    scanf("%d %d %d", &a, &b, &peso);
    setbuf(stdin, NULL);

    arestas[i].a = a;
    arestas[i].b = b;
    arestas[i].peso = peso;
  }

  for(int i = 0; i < m; i++){
    for(int j = 0; j < m; j++) {
      if(arestas[i].peso < arestas[j].peso) {
        Aresta aux = arestas[i];
        arestas[i] = arestas[j];
        arestas[j] = aux;
      }
    }
  }

  for(int i = 0; i < m; i++){
    teste1 = acha(conj, arestas[i].a);
    teste2 = acha(conj, arestas[i].b);

    if(teste1 != teste2) {
      resultado[tam_resultado] = arestas[i];
      tam_resultado++;
      une(conj, rank, arestas[i].a, arestas[i].b);
      soma += arestas[i].peso;
    }
  }

  // Imprime o resultado 
  printf("\n%d\n", soma);
  return 0;
}