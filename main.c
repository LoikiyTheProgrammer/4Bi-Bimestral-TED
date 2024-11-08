#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;     // Ponteiro genérico para os elementos da pilha
    int topo;         // Índice do topo da pilha
    int capacidade;   // Capacidade total da pilha
} Pilha;

Pilha* criarPilha(int capacidadeInicial) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) return NULL;

    pilha->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    pilha->topo = -1;
    pilha->capacidade = capacidadeInicial;

    return pilha;
}

void dobrarCapacidade(Pilha *pilha) {
    int novaCapacidade = pilha->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);

    for (int i = 0; i <= pilha->topo; i++) {
        novosDados[i] = pilha->dados[i];
    }

    free(pilha->dados);
    pilha->dados = novosDados;
    pilha->capacidade = novaCapacidade;
}

int inserirNaPilha(Pilha *pilha, void *item) {
    if (pilha->topo == pilha->capacidade - 1) {
        dobrarCapacidade(pilha);
    }

    pilha->dados[++(pilha->topo)] = item;
    return 1;
}

void* removerDaPilha(Pilha *pilha) {
    if (pilha->topo == -1) {
        return NULL;
    }

    return pilha->dados[(pilha->topo)--];
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
        printf("Inserido na pilha: %d\n", *valor);
    }

    printf("\nRemovendo valores da pilha:\n");
    for (int i = 0; i < quantidade; i++) {
        int *valor = (int *) removerDaPilha(pilha);
        if (valor != NULL) {
            printf("Removido da pilha: %d\n", *valor);
            free(valor);
        }
    }

    limparPilha(pilha);
    return 0;
}
