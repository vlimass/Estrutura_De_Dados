#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_INPUT 100

typedef struct Lista {
  int numVert;
  struct Lista * prox;
} Lista;

void insere(Lista **ptlista, int x){ 
  Lista *novo = malloc(sizeof(Lista));

  if (novo == NULL){
    printf("Erro de alocacao de memória\n");
    exit(1);
  }

  novo->numVert = x;
  novo->prox = *ptlista;
  *ptlista = novo;
}

int main(int argc, char **argv){
  char temp;
  int vertices, arestas;
  char *entrada = malloc(sizeof(char)*MAX_TAM_INPUT);

  if (entrada == NULL){
    printf("Erro de alocacao de memória\n");
    return 1;
  }
    
  // Input do número de vértices e arestas
  printf("Insira o número de vértices e arestas ({VÉRTICES} + space + {ARESTAS}) e, depois, coloque o valor dos vértices conectados a cada vértice por linha em ordem crescente (a cada entrada, digite ENTER para computar os valores):\n");

  scanf("%[^\n]", entrada);
  sscanf(entrada, "%d %d", &vertices, &arestas);
  scanf("%c", &temp);

  Lista **adjacencias = malloc(sizeof(Lista*) * (vertices + 1));
  if (adjacencias == NULL){
    printf("Erro de alocacao de memória\n");
    return 1;
  }

  for (int i = 0; i <= vertices; i++){
    adjacencias[i] = NULL;
  }
    
  //Input da lista de adjacências 
  char *linha = NULL;
  size_t tamLinha = 0;

  for(int i = 1; i <= vertices; i++){
    getline(&linha, &tamLinha, stdin);
    int pos = 0;
    int numLido = 0;
    int numChars;

    while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
      pos += numChars;
      if(strlen(linha) != 0){
        insere(&adjacencias[i], numLido);
      }
    }
  }

  //Inicializando os vetores de grau e ordem
  Lista *pt;
  int *grausEntrada = malloc(sizeof(int) * (vertices + 1));
  int *ordem = malloc(sizeof(int) * (vertices));

  if (grausEntrada == NULL){
    printf("Erro de alocacao de memória\n");
    return 1;
  }

  if (ordem == NULL){
    printf("Erro de alocacao de memória\n");
    return 1;
  }
  
  // Algoritmo de Ordenação topológica
  for (int i = 1; i <= vertices; i++){
    grausEntrada[i] = 0;
  }

  int fim = 0, inicio = 0;

  for(int i = 1; i <= vertices; i++){
    pt = adjacencias[i];
    while(pt != NULL){
      grausEntrada[pt->numVert]++;
      pt = pt->prox;
    }
  }

  for (int i = 1; i <= vertices; i++){
    if (grausEntrada[i]==0){
      ordem[fim] = i;
      fim++;
    }
  }

  while(inicio != fim){
    int v = ordem[inicio];
    int w;
    inicio++;
    pt = adjacencias[v];

    while(pt != NULL){
      w = pt->numVert;
      grausEntrada[w]--;

      if (grausEntrada[w] == 0){
        ordem[fim] = w;
        fim++;
      }

      pt = pt->prox;
    }
  } 

  // Impressão dos resultados
  printf("-> Ordenação topológica: ");
  for(int i = 0; i < vertices; i++){
    printf("%d ", ordem[i]);
  }
  printf("\n");

  free(entrada);
  free(linha);
  free(adjacencias);
  free(pt);
  free(grausEntrada);
  free(ordem);

  return 0;
}