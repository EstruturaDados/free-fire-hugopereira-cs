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
int buscarItemPorNome(Item mochila[], int totalItens, const char* item); // Implementada no nível Aventureiro
int buscarItemPorNome_aux(Item mochila[], const char* buscaNome, int inicio, int fim);

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
        printf("-----------------------------------------------\n");
        printf("-----Menu Principal-----\n");
        printf("1. Adicionar Item (loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item Por Nome\n");
        printf("0. Sair\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                printf("Pressione Enter para continuar...");
                limparBuffer();
                getchar();;
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItemPorNome(mochila, totalItens, NULL);
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

    printf("Tipo do item (arma, municao, cura, etc.): ");
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
    printf("%-25s | %-20s | %s\n", "NOME","TIPO", "QUANTIDADE");
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

// Função para realizr a busca sequencial do item por nome
int buscarItemPorNome(Item mochila[], int totalItens, const char* item) {
    char buscaNome[TAM_NOME];

    printf("Digite o nome do item que deseja buscar: ");
    limparBuffer();
    fgets(buscaNome, sizeof(buscaNome), stdin);

    // Remove o '\n' que o fgets adciona
    buscaNome[strcspn(buscaNome, "\n")] = '\0';
    
    // Chama a função recursiva auxiliar
    int resultado = buscarItemPorNome_aux(mochila, buscaNome, 0, totalItens);

    if (resultado != -1) {
        printf("\n--- Item Encontrado! ---\n");
        printf("Nome: %s\n", mochila[resultado].nome);
        printf("Tipo: %s\n", mochila[resultado].tipo);
        printf("Quantidade: %d\n", mochila[resultado].quantidade);
        printf("-----------------------------------------------\n");
    } else {
        printf("\nItem '%s' não encontrado.\n", buscaNome);
    }

    printf("Pressione Enter para continuar...");
    getchar();;

    return resultado;
}

// Função auxiliar que implementa toda a lógica recursiva da busca sequencial
int buscarItemPorNome_aux(Item mochila[], const char* buscaNome, int inicio, int fim) {
    // CASO BASE!: FALHA - Nome não encontrado
    if (inicio >= fim) {
        return -1;
    }

    // CASO BASE 2: ENCONTROU O ITEM
    // Compara o item na posição 'indice' atual com o item procurado.
    if (strcmp(mochila[inicio].nome, buscaNome) == 0) {
        return inicio;
    }

    // CASO RECURSIVO: Caso não encontre, busca no próximo índice
    return buscarItemPorNome_aux(mochila, buscaNome, inicio + 1, fim);
}