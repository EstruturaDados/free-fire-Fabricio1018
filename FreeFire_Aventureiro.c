#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================================================================
// CONSTANTES E ESTRUTURAS
// =====================================================================

#define TAM 10  // Tamanho máximo do vetor

// Estrutura base para armazenar um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =====================================================================
// VARIÁVEIS GLOBAIS
// =====================================================================

Item mochilaVetor[TAM];   // Mochila implementada como vetor
int qtdItensVetor = 0;    // Contador de itens no vetor

No* inicioLista = NULL;   // Início da lista encadeada

// Contadores globais de comparações (para estatísticas)
int totalCompSeqVetor = 0;
int totalCompBinVetor = 0;
int totalCompLista = 0;

// =====================================================================
// PROTÓTIPOS DAS FUNÇÕES
// =====================================================================

// Vetor
void inserirItemVetor(Item novo);
void removerItemVetor(char nome[]);
void listarItensVetor();
void ordenarVetor();
int buscarSequencialVetor(char nome[], int* comparacoes);
int buscarBinariaVetor(char nome[], int* comparacoes);

// Lista encadeada
void inserirItemLista(Item novo);
void removerItemLista(char nome[]);
void listarItensLista();
No* buscarItemLista(char nome[], int* comparacoes);
void liberarLista();

// Utilitários
void limparBufferEntrada();
void exibirComparativo();

// =====================================================================
// FUNÇÃO PRINCIPAL
// =====================================================================

int main() {
    int opcao;
    char nomeBusca[30];
    int comparacoes;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Inserir novo item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Ordenar vetor\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        if (opcao == 1) {
            Item novo;
            printf("Nome: ");
            fgets(novo.nome, 30, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = 0;
            printf("Tipo: ");
            fgets(novo.tipo, 20, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = 0;
            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);
            limparBufferEntrada();

            // Inserção paralela nas duas estruturas
            inserirItemVetor(novo);
            inserirItemLista(novo);
        }

        else if (opcao == 2) {
            printf("Nome do item a remover: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            removerItemVetor(nomeBusca);
            removerItemLista(nomeBusca);
        }

        else if (opcao == 3) {
            listarItensVetor();
            listarItensLista();
        }

        else if (opcao == 4) {
            printf("Nome do item a buscar: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            int compSeqVetor = 0, compBinVetor = 0, compLista = 0;

            int posSeq = buscarSequencialVetor(nomeBusca, &compSeqVetor);
            ordenarVetor(); // garantir ordenação antes da busca binária
            int posBin = buscarBinariaVetor(nomeBusca, &compBinVetor);
            No* resultadoLista = buscarItemLista(nomeBusca, &compLista);

            totalCompSeqVetor += compSeqVetor;
            totalCompBinVetor += compBinVetor;
            totalCompLista += compLista;

            printf("\n--- RESULTADOS DA BUSCA ---\n");
            printf("[VETOR - SEQUENCIAL] %s (%d comparações)\n",
                   posSeq != -1 ? "Encontrado" : "Não encontrado", compSeqVetor);
            printf("[VETOR - BINÁRIA]   %s (%d comparações)\n",
                   posBin != -1 ? "Encontrado" : "Não encontrado", compBinVetor);
            printf("[LISTA - SEQUENCIAL] %s (%d comparações)\n",
                   resultadoLista ? "Encontrado" : "Não encontrado", compLista);
        }

        else if (opcao == 5) {
            ordenarVetor();
        }

    } while (opcao != 0);

    // Exibir estatísticas finais
    exibirComparativo();

    // Liberar memória da lista
    liberarLista();

    printf("\nEncerrando o programa e liberando memória...\n");
    return 0;
}

// =====================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// =====================================================================

// ------------------------------
// UTILITÁRIOS
// ------------------------------
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirComparativo() {
    printf("\n========================================\n");
    printf("  COMPARATIVO DE DESEMPENHO FINAL\n");
    printf("========================================\n");
    printf("Vetor (Busca Sequencial): %d comparações totais\n", totalCompSeqVetor);
    printf("Vetor (Busca Binária):    %d comparações totais\n", totalCompBinVetor);
    printf("Lista Encadeada:          %d comparações totais\n", totalCompLista);

    printf("\n--- Conclusão ---\n");
    printf("• A busca binária no vetor é mais eficiente (menos comparações).\n");
    printf("• A lista encadeada tem inserção mais simples, mas busca mais lenta.\n");
    printf("• O vetor precisa ser reordenado, mas permite busca mais rápida.\n");
    printf("========================================\n");
}

// ------------------------------
// FUNÇÕES DO VETOR
// ------------------------------

void inserirItemVetor(Item novo) {
    if (qtdItensVetor >= TAM) {
        printf("[VETOR] Mochila cheia!\n");
        return;
    }
    mochilaVetor[qtdItensVetor++] = novo;
    printf("[VETOR] Item '%s' inserido com sucesso.\n", novo.nome);
}

void removerItemVetor(char nome[]) {
    for (int i = 0; i < qtdItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < qtdItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            qtdItensVetor--;
            printf("[VETOR] Item '%s' removido.\n", nome);
            return;
        }
    }
    printf("[VETOR] Item '%s' não encontrado.\n", nome);
}

void listarItensVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < qtdItensVetor; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    for (int i = 0; i < qtdItensVetor - 1; i++) {
        for (int j = 0; j < qtdItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("[VETOR] Itens ordenados por nome.\n");
}

int buscarSequencialVetor(char nome[], int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < qtdItensVetor; i++) {
        (*comparacoes)++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(char nome[], int* comparacoes) {
    int inicio = 0, fim = qtdItensVetor - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// ------------------------------
// FUNÇÕES DA LISTA ENCADEADA
// ------------------------------

void inserirItemLista(Item novo) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("[LISTA] Falha ao alocar memória.\n");
        return;
    }
    novoNo->dados = novo;
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    printf("[LISTA] Item '%s' inserido com sucesso.\n", novo.nome);
}

void removerItemLista(char nome[]) {
    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicioLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            printf("[LISTA] Item '%s' removido.\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("[LISTA] Item '%s' não encontrado.\n", nome);
}

void listarItensLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = inicioLista;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarItemLista(char nome[], int* comparacoes) {
    *comparacoes = 0;
    No* atual = inicioLista;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void liberarLista() {
    No* atual = inicioLista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}
