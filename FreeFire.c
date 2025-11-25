#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Estrututura para representar um item
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Protótipo das Funções
void limparBuffer();
void adicionarItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);

// Função Principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    printf("==================================================\n");
    printf("   MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
    printf("==================================================\n");
    printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);

    do {
        printf("\n-----Menu Principal-----\n");
        printf("1. Adicionar Item (loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 0:
                printf("\nSaindo do jogo... Até logo!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para adicionar itens
void adicionarItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    limparBuffer();
    fgets(mochila[*totalItens].nome, TAM_NOME, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo do item (arma, munição, cura, etc.): ");
    //limparBuffer();
    fgets(mochila[*totalItens].tipo, TAM_TIPO, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;
    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover itens
void removerItem( Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nMochila vazia! Não há itens para remoção.\n");
        return;
    }

    char buscaNome[TAM_NOME];
    int encontrado = 0;

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    limparBuffer();
    fgets(buscaNome, TAM_NOME, stdin);
    buscaNome[strcspn(buscaNome, "\n")] = '\0';

    // Buscar e remover o item
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, buscaNome) == 0) {
            encontrado = 1;

            // Desloca os itens para preencher os espaços
            for (int j= i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*totalItens)--;
            printf("\nItem '%s' removido com sucesso!\n", buscaNome);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", buscaNome);
    }
}

// Função para listar todos os itens
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    printf("------------------------------------------------------------\n");
    printf("%-25s %-20s %s\n", "NOME","| TIPO", "| QUANTIDADE");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-25s | %-20s | %d\n", 
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade);
    }

    printf("------------------------------------------------------------\n");
    printf("Total de itens: %d/%d\n", totalItens, MAX_ITENS);

}