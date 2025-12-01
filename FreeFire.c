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

// Enumeração para critérios de ordenação
typedef enum {
    ORDENAR_NOME =1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE 
} CriterioOrdenacao;

// Estrututura para representar um item
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade;
} Item;

// Variáveis globais
bool ordenadoPorNome = false; // Para controlar se a lista está ordenada por nome
int comparacoes = 0;

// Protótipo das Funções
void limparBuffer();
void adicionarItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void menuOrdenacao(Item mochila[], int totalItens); // Implementada no nível mestre
void ordenarMochila(Item mochila[], int totalItens, CriterioOrdenacao criterio); // Implementada no nível mestre
int buscaBinaria(Item mochila[], int totalItens);
int buscaBinaria_aux(Item mochila[], const char* buscaNome, int inicio, int fim);

// Função Principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    printf("==================================================\n");
    printf("   PLANO DE FUGA - CÓDIGO DA ILHA (NÍVEL MESTRE)\n");
    printf("==================================================\n");
    printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
    
    
    do {
        if (ordenadoPorNome == false) {
            printf("Status da Ordenação por Nome: NÃO ORDENADO\n");
        } else {
            printf("Status da Ordenação por Nome: ORDENADO\n");
        }
        printf("\n-----------------------------------------------\n");
        printf("-----Menu Principal-----\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventário)\n");
        printf("4. Organizar Mochila\n");
        printf("5. Busca Binária por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                ordenadoPorNome = false;
                listarItens(mochila, totalItens);
                printf("Pressione Enter para continuar...");
                limparBuffer();
                getchar();;
                break;
            case 2:
                removerItem(mochila, &totalItens);
                ordenadoPorNome = false; // Apenas uma medida de segurança
                break;
            case 3:
                listarItens(mochila, totalItens);
                printf("\nPressione Enter para continuar...\n");
                limparBuffer();
                getchar();
                break;
            case 4:
                menuOrdenacao(mochila, totalItens);
                break;
            case 5:
                buscaBinaria(mochila, totalItens);
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

    printf("\n--- Coletando Novo Componente ---\n");
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

    // Valida se o valor da propriedade inserido está dentro do permitido
    do {
        printf("Prioridade (1-5, sendo 5 a mais alta): ");
        scanf("%d", &mochila[*totalItens].prioridade);
        if (mochila[*totalItens].prioridade < 1|| mochila[*totalItens].prioridade > 5) {
            printf("Prioridade inválida! Digite um valor entre 1 e 5.\n");
        }
    } while (mochila[*totalItens].prioridade < 1 || mochila[*totalItens].prioridade > 5);

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
    printf("---------------------------------------------------------------------------\n");
    printf("%-25s | %-15s | %-10s | %s\n", "NOME","TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-25s | %-15s | %-10d | %d\n", 
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade,
            mochila[i].prioridade);
    }

    printf("---------------------------------------------------------------------------\n");
    printf("Total de itens: %d/%d\n", totalItens, MAX_ITENS);

}

void menuOrdenacao(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila vazia! Nenhum item para ordenar.\n");
        printf("\nPressione Enter para continuar...\n");
        limparBuffer();
        getchar();
        return;
    }

    int opcao;

    printf("\n--- Estratégia de Organização ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o critério: ");
    scanf("%d", &opcao);

    // Verifica se a opção é válida
    if (opcao >= 1 && opcao <= 3) {
        comparacoes = 0; // Resta o contador
        ordenarMochila(mochila, totalItens, (CriterioOrdenacao)opcao);

        if (opcao == ORDENAR_NOME) {
            ordenadoPorNome = true;
        } else {
            ordenadoPorNome = false;
        }

        printf("\nMochila ordenada com sucesso!\n");
        printf("Comparações realizadas %d\n", comparacoes);
        listarItens(mochila, totalItens);
    } else if (opcao !=0) {
        printf("\nOpção inválida!\n");
    }

    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

// Função de ordenação usando Insertion Sort
void ordenarMochila(Item mochila[],int totalItens, CriterioOrdenacao criterio) {
    int i, j;
    Item chave;

    for (i = 1; i < totalItens; i++) {
        chave = mochila[i];
        j = i - 1;

        while (j >= 0) {
            comparacoes++; // Incrementa o contador

            bool mover = false;

            switch (criterio) {
                case ORDENAR_NOME:
                    mover = strcmp(mochila[j].nome, chave.nome) > 0;
                    break;
                case ORDENAR_TIPO:
                    mover = strcmp(mochila[j].tipo, chave.tipo) > 0;
                    break;
                case ORDENAR_PRIORIDADE:
                // Ordem decrescente para prioridade
                mover = mochila[j].prioridade < chave.prioridade;
                break;
            }

            if (mover) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }

        mochila[j + 1] = chave;
    }
}

// Função para realizr a busca sequencial do item por nome
int buscaBinaria(Item mochila[], int totalItens) {
    // Verifica se há, pelo menos, um item na mochila
    if (totalItens == 0) {
        printf("\nMochila vazia! Nenhum item para buscar.\n");
        printf("\nPressione Enter para continuar...");
        limparBuffer();
        getchar();
        return -1;
    }

    // Verifica se a lista está ordenada pro nome
    if (!ordenadoPorNome) {
        printf("\nAVISO: A busca binária requer que a mochila esteja ordenada por NOME!\n");
        printf("Por favor, ordene a mochila por nome primeiro (opção 4 do menu principal).\n");
        printf("\nPressione Enter para continuar...");
        limparBuffer();
        getchar();
        return -1;
    }

    char buscaNome[TAM_NOME];

    printf("\n--- Busca Binária ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    limparBuffer();
    fgets(buscaNome, sizeof(buscaNome), stdin);

    // Remove o '\n' que o fgets adciona
    buscaNome[strcspn(buscaNome, "\n")] = '\0';
    
    // Chama a função recursiva auxiliar
    int resultado = buscaBinaria_aux(mochila, buscaNome, 0, totalItens - 1);

    if (resultado != -1) {
        printf("\n--- Item Encontrado! ---\n");
        printf("Nome: %s\n", mochila[resultado].nome);
        printf("Tipo: %s\n", mochila[resultado].tipo);
        printf("Quantidade: %d\n", mochila[resultado].quantidade);
        printf("Prioridade: %d\n", mochila[resultado].prioridade);
        printf("-----------------------------------------------\n");
    } else {
        printf("\nItem '%s' não encontrado.\n", buscaNome);
    }

    printf("Pressione Enter para continuar...");
    getchar();;

    return resultado;
}

// Função auxiliar que implementa toda a lógica recursiva da busca sequencial
int buscaBinaria_aux(Item mochila[], const char* buscaNome, int inicio, int fim) {
    // CASO BASE!: FALHA - Elemento não encontrado
    if (inicio > fim) {
        return -1;
    }

    // Calcula o meio
    int meio = inicio + (fim - inicio) / 2;

    // Compara o elemento do meio com o nome buscado
    int comparacao = strcmp(mochila[meio].nome, buscaNome);

    // CASO BASE: Encontrou o item!
    if (comparacao == 0) {
        return meio;
    }

    // CASO RECURSIVO: Busca na metade esquerda
    if (comparacao > 0) {
        return buscaBinaria_aux(mochila, buscaNome, inicio, meio -1);
    }

    // CASO RECURSIVO: Caso não encontre, busca no próximo índice
    return buscaBinaria_aux(mochila, buscaNome, meio + 1, fim);
}