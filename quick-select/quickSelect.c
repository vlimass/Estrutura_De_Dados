#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_INPUT 20 // Tamanho máximo do input de um número da lista

// Erro para caso em que o K escolhido é inválido
int error_k = 0;

// Estrutura para a lista de números que será fornecida
typedef struct Lista {
  int valor;
  struct Lista* next;
} Lista;


void acrescentaNaLista(Lista** lista, int valor) {
  Lista* new_List = (Lista*)malloc(sizeof(Lista));
  new_List->valor = valor;
  new_List->next = NULL;

  if (*lista == NULL) {
      *lista = new_List;
  } else {
    Lista* current = *lista;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_List;
  }
}

int* listaParaVetor(Lista* vetor, int tamanho) {
  int* novoVetor = (int*)malloc(tamanho * sizeof(int));
  Lista* current = vetor;
  int i = 0;
  while (current != NULL) {
      novoVetor[i] = current->valor;
      current = current->next;
      i++;
  }
  return novoVetor;
}

void troca(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int particiona(int vet[], int inicio, int fim) {
  // Pivot é o último elemento
  int pivot = vet[fim];
  int i = inicio, j = inicio;

  while (j <= fim - 1) {
    if (vet[j] <= pivot) {
      troca(&vet[i], &vet[j]);
      i++;
    }
    
    j++;
  }

  troca(&vet[i], &vet[fim]);
  return i; 
}

int quickSelect(int vet[], int inicio, int fim, int k) {
  if (k > 0 && k <= fim - inicio + 1) {
    int pos = particiona(vet, inicio, fim);

    if (pos - inicio == k - 1) {
      return vet[pos];

    }
    if (pos - inicio > k - 1) {
      return quickSelect(vet, inicio, pos - 1, k);

    } 
    
    return quickSelect(vet, pos + 1, fim, k - pos + inicio - 1);
       
  } else {
    // Caso de erro: valor de K é inválido
    error_k++;
    printf("ERRO! O k-ésimo inserido é inválido para este vetor. Por favor, insira outro valor para K!\n");

    return -1;
  }

}

int main(int argc, char *argv[]){
  Lista* lista = NULL;
  char input[MAX_TAM_INPUT];
  long int valor;
  char * fimptr;
  int * vetor;
  int tam = 0;
  int k;
  int flag = 0; // Aviso para casos de input não aceitos pelo programa
  int resultado;

  if(argc <= 1) {
    printf("É necessário inserir como parâmetro -k VALOR para buscar o k-ésimo menor elemento do vetor.\n");
    return 1;
  }
  
  for(int i = 0; i < argc; i++){
    if(!strcmp(argv[i], "-k")){
      // Recebe o index do k-ésimo menor elemento do vetor
      k = atoi(argv[i + 1]);

      // Valida a flag
      flag++;
    } 
  }

  if(!flag){
    printf("Não foi informado o k-ésimo menor elemento desejado. Insira -k VALOR\n");
    return 1;
  }

  printf("Insira os números do vetor (a cada número digite ENTER e, para parar, digite ENTER sem nenhum número na linha):\n");

  while (fgets(input, MAX_TAM_INPUT, stdin) != NULL) {
    valor = strtol(input, &fimptr, 10);
    if (fimptr == input || *fimptr != '\n') {
        break;
    }
    acrescentaNaLista(&lista, (int)valor);
    tam++;
  }

  vetor = listaParaVetor(lista, tam);

  resultado = quickSelect(vetor, 0, tam - 1, k);
  if(!error_k) printf("O elemento que está na %da posição desse vetor é: %d\n", k, resultado);

  return 0;
}
