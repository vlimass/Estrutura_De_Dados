#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Erro para caso em que o K escolhido é inválido
int error_k = 0;

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
    printf("ERRO! O k-ésimo inserido é inválido. Por favor, insira outro valor para K!\n");

    return -1;
  }

}

int main(int argc, char *argv[]){
  int arr[] = { 10, 4, 5, 8, 6, 11, 26, 192, 45, 123, -12, 32, 2, 6};
  int tam = sizeof(arr) / sizeof(arr[0]);
  int k;
  int flag = 0; // Aviso para casos de input não aceitos pelo programa
  int result;

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
      printf("\tNão foi informado o k-ésimo menor elemento desejado. Insira -k VALOR\n");
      return 1;
  }


  result = quickSelect(arr, 0, tam - 1, k);
  if(!error_k) printf("%d\n", result);

  return 0;
}
