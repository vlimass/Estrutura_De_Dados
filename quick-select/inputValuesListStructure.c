#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM_INPUT 20 // Tamanho máximo de um número

typedef struct Arr {
    int valor;
    struct Arr* next;
} Arr;

void acrescentaAoVetor(Arr** vetor, int valor) {
    Arr* new_Arr = (Arr*)malloc(sizeof(Arr));
    new_Arr->valor = valor;
    new_Arr->next = NULL;

    if (*vetor == NULL) {
        *vetor = new_Arr;
    } else {
        Arr* current = *vetor;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_Arr;
    }
}

void print_list(Arr* vetor) {
    Arr* current = vetor;
    while (current != NULL) {
        printf("%d ", current->valor);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Arr* vetor = NULL;
    char input[MAX_TAM_INPUT];
    long int valor;
    char *fimptr;
    int tam = 0;

    printf("Insira os números do vetor (a cada número digite ENTER e, para parar, digite ENTER sem nenhum número na linha):\n");

    while (fgets(input, MAX_TAM_INPUT, stdin) != NULL) {
        valor = strtol(input, &fimptr, 10);
        if (fimptr == input || *fimptr != '\n') {
            break;
        }
        acrescentaAoVetor(&vetor, (int)valor);
        tam++;
    }

    printf("Os números digitados foram: ");
    print_list(vetor);
    printf("Tamanho da lista: %d\n", tam);

    return 0;
}
