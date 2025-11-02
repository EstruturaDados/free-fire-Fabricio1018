#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------------
// DEFINIÇÕES GERAIS
//-------------------------------------------------------------------------------------------------------
#define MAX_ITENS 10  // Capacidade máxima da mochila

//-------------------------------------------------------------------------------------------------------
// STRUCT - REPRESENTAÇÃO DO ITEM
//-------------------------------------------------------------------------------------------------------
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (Ex: Arma, Munição, Cura)
    int quantidade;    // Quantidade do item
} Item;

//-------------------------------------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS
//-------------------------------------------------------------------------------------------------------
Item mochila[MAX_ITENS];   // Vetor de itens da mochila
int totalItens = 0;        // Quantidade atual de itens armazenados

//-------------------------------------------------------------------------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
//-------------------------------------------------------------------------------------------------------
void limparBufferEntrada();
void menuPrincipal();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
//-------------------------------------------------------------------------------------------------------
int main() {
    menuPrincipal();
    return 0;
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA LIMPAR BUFFER DE ENTRADA
//-------------------------------------------------------------------------------------------------------
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA EXIBIR O MENU PRINCIPAL
//-------------------------------------------------------------------------------------------------------
void menuPrincipal() {
    int opcao;

    do {
        printf("\n========================================\n");
        printf("          SISTEMA DE MOCHILA\n");
        printf("========================================\n");
        printf("1 - Cadastrar Item (%d/%d)\n", totalItens, MAX_ITENS);
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Item\n");
        printf("5 - Sair\n");
        printf("========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nEncerrando o programa... Até mais!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 5);
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA INSERIR UM NOVO ITEM NA MOCHILA
//-------------------------------------------------------------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nCapacidade máxima atingida! Remova um item antes de cadastrar novos.\n");
        return;
    }

    printf("\n========== CADASTRO DE ITEM ==========\n");
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // remove o \n

    printf("Tipo (Arma, Munição, Cura, etc.): ");
    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBufferEntrada();

    totalItens++;
    printf("\nItem cadastrado com sucesso!\n");
    listarItens();
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA REMOVER UM ITEM PELO NOME
//-------------------------------------------------------------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Desloca os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado!\n");

    listarItens();
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA LISTAR TODOS OS ITENS DA MOCHILA
//-------------------------------------------------------------------------------------------------------
void listarItens() {
    printf("\n========== ITENS NA MOCHILA ==========\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf(" Nome: %s\n", mochila[i].nome);
        printf(" Tipo: %s\n", mochila[i].tipo);
        printf(" Quantidade: %d\n", mochila[i].quantidade);
        printf("----------------------------------------\n");
    }
}

//-------------------------------------------------------------------------------------------------------
// FUNÇÃO PARA BUSCAR UM ITEM PELO NOME (BUSCA SEQUENCIAL)
//-------------------------------------------------------------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf(" Nome: %s\n", mochila[i].nome);
            printf(" Tipo: %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado na mochila.\n");
}