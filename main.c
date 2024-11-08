#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;      // Ponteiro genérico para os elementos da pilha
    int inicio;        // Índice do primeiro elemento
    int fim;           // Índice do último elemento
    int tamanho;       // Quantidade atual de elementos na pilha
    int capacidade;    // Capacidade total da pilha
} Pilha;

Pilha* criarPilha(int capacidadeInicial) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) return NULL;

    pilha->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    pilha->inicio = 0;
    pilha->fim = -1;
    pilha->tamanho = 0;
    pilha->capacidade = capacidadeInicial;

    return pilha;
}

void dobrarCapacidade(Pilha *pilha) {
    int novaCapacidade = pilha->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);

    for (int i = 0; i < pilha->tamanho; i++) {
        int indice = (pilha->inicio + i) % pilha->capacidade;
        novosDados[i] = pilha->dados[indice];
    }

    free(pilha->dados);
    pilha->dados = novosDados;
    pilha->inicio = 0;
    pilha->fim = pilha->tamanho - 1;
    pilha->capacidade = novaCapacidade;
}

int inserirNaPilha(Pilha *pilha, void *item) {
    if (pilha->tamanho == pilha->capacidade) {
        dobrarCapacidade(pilha);
    }

    pilha->fim = (pilha->fim + 1) % pilha->capacidade;
    pilha->dados[pilha->fim] = item;
    pilha->tamanho++;
    return 1;
}

void* removerDaPilha(Pilha *pilha) {
    if (pilha->tamanho == 0) {
        return NULL;
    }

    void *item = pilha->dados[pilha->fim];
    pilha->fim = (pilha->fim - 1) % pilha->capacidade;
    pilha->tamanho--;
    return item;
}

void limparPilha(Pilha *pilha) {
    if (pilha != NULL) {
        free(pilha->dados);
        free(pilha);
    }
}

int main() {
    int capacidadeInicial;
    printf("Digite a capacidade inicial da pilha: ");
    scanf("%d", &capacidadeInicial);

    Pilha *pilha = criarPilha(capacidadeInicial);

    int quantidade;
    printf("Quantos números você quer adicionar à pilha? ");
    scanf("%d", &quantidade);

    for (int i = 0; i < quantidade; i++) {
        int *valor = (int *) malloc(sizeof(int));
        printf("Digite o valor %d: ", i + 1);
        scanf("%d", valor);
        inserirNaPilha(pilha, valor);
        printf("Inserido: %d\n", *valor);
    }

    printf("\nRemovendo valores da pilha:\n");
    for (int i = 0; i < quantidade; i++) {
        int *valor = (int *) removerDaPilha(pilha);
        if (valor != NULL) {
            printf("Removido: %d\n", *valor);
            free(valor);
        }
    }

    limparPilha(pilha);
    return 0;
}
