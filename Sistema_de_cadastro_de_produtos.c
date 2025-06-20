#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10
#define MAX_NOME 100

// Estados possíveis de cada posição da tabela
typedef enum {
    VAZIO,
    OCUPADO,
    REMOVIDO
} Estado;

// Estrutura do produto
typedef struct {
    int codigo;
    char nome[MAX_NOME];
    float preco;
    Estado estado;
} Produto;

// Estrutura da tabela hash
typedef struct {
    Produto tabela[TAMANHO_TABELA];
    int total_colisoes;
    int total_produtos;
} TabelaHash;

// Função hash: código % TAMANHO_TABELA
int funcao_hash(int codigo) {
    return codigo % TAMANHO_TABELA;
}

// Inicializar a tabela hash
void inicializar_tabela(TabelaHash *th) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        th->tabela[i].estado = VAZIO;
        th->tabela[i].codigo = 0;
        strcpy(th->tabela[i].nome, "");
        th->tabela[i].preco = 0.0;
    }
    th->total_colisoes = 0;
    th->total_produtos = 0;
}

// Inserir produto na tabela hash
int inserir_produto(TabelaHash *th, int codigo, char *nome, float preco) {
    // Verificar se a tabela está cheia
    if (th->total_produtos >= TAMANHO_TABELA) {
        printf("Erro: Tabela cheia!\n");
        return 0;
    }
    
    // Verificar se o produto já existe
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int colisoes = 0;
    
    do {
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            printf("Erro: Produto com código %d já existe!\n", codigo);
            return 0;
        }
        
        if (th->tabela[pos].estado == VAZIO || th->tabela[pos].estado == REMOVIDO) {
            // Posição encontrada para inserção
            th->tabela[pos].codigo = codigo;
            strcpy(th->tabela[pos].nome, nome);
            th->tabela[pos].preco = preco;
            th->tabela[pos].estado = OCUPADO;
            th->total_produtos++;
            th->total_colisoes += colisoes;
            
            printf("Produto inserido com sucesso na posição %d", pos);
            if (colisoes > 0) {
                printf(" (após %d colisão(ões))", colisoes);
            }
            printf("!\n");
            return 1;
        }
        
        // Sondagem linear
        colisoes++;
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Erro: Não foi possível inserir o produto!\n");
    return 0;
}

// Buscar produto na tabela hash
int buscar_produto(TabelaHash *th, int codigo) {
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int tentativas = 0;
    
    do {
        tentativas++;
        
        if (th->tabela[pos].estado == VAZIO) {
            printf("Produto com código %d não encontrado (posição %d vazia após %d tentativa(s)).\n", 
                   codigo, pos, tentativas);
            return -1;
        }
        
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            printf("Produto encontrado na posição %d após %d tentativa(s):\n", pos, tentativas);
            printf("Código: %d\n", th->tabela[pos].codigo);
            printf("Nome: %s\n", th->tabela[pos].nome);
            printf("Preço: R$ %.2f\n", th->tabela[pos].preco);
            return pos;
        }
        
        // Sondagem linear
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Produto com código %d não encontrado após verificar toda a tabela.\n", codigo);
    return -1;
}

// Remover produto da tabela hash
int remover_produto(TabelaHash *th, int codigo) {
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int tentativas = 0;
    
    do {
        tentativas++;
        
        if (th->tabela[pos].estado == VAZIO) {
            printf("Produto com código %d não encontrado para remoção.\n", codigo);
            return 0;
        }
        
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            th->tabela[pos].estado = REMOVIDO;
            th->total_produtos--;
            printf("Produto removido da posição %d após %d tentativa(s)!\n", pos, tentativas);
            return 1;
        }
        
        // Sondagem linear
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Produto com código %d não encontrado para remoção.\n", codigo);
    return 0;
}

// Exibir toda a tabela hash
void exibir_tabela(TabelaHash *th) {
    printf("\n=== TABELA HASH ===\n");
    printf("Índice | Estado    | Código | Nome                | Preço\n");
    printf("-------|-----------|--------|---------------------|----------\n");
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("   %d   | ", i);
        
        switch (th->tabela[i].estado) {
            case VAZIO:
                printf("VAZIO     | -      | -                   | -\n");
                break;
            case REMOVIDO:
                printf("REMOVIDO  | -      | -                   | -\n");
                break;
            case OCUPADO:
                printf("OCUPADO   | %6d | %-19s | R$ %.2f\n",
                       th->tabela[i].codigo,
                       th->tabela[i].nome,
                       th->tabela[i].preco);
                break;
        }
    }
    
    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Total de produtos: %d\n", th->total_produtos);
    printf("Total de colisões: %d\n", th->total_colisoes);
    printf("Taxa de ocupação: %.1f%%\n", (float)th->total_produtos / TAMANHO_TABELA * 100);
    printf("====================\n\n");
}

// Exportar tabela para CSV (funcionalidade extra)
void exportar_csv(TabelaHash *th) {
    FILE *arquivo = fopen("tabela_produtos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }
    
    fprintf(arquivo, "Indice,Estado,Codigo,Nome,Preco\n");
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        fprintf(arquivo, "%d,", i);
        
        switch (th->tabela[i].estado) {
            case VAZIO:
                fprintf(arquivo, "VAZIO,,,\n");
                break;
            case REMOVIDO:
                fprintf(arquivo, "REMOVIDO,,,\n");
                break;
            case OCUPADO:
                fprintf(arquivo, "OCUPADO,%d,%s,%.2f\n",
                        th->tabela[i].codigo,
                        th->tabela[i].nome,
                        th->tabela[i].preco);
                break;
        }
    }
    
    fclose(arquivo);
    printf("Tabela exportada para 'tabela_produtos.csv' com sucesso!\n");
}

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu principal
void menu() {
    printf("\n=== SISTEMA DE CADASTRO DE PRODUTOS ===\n");
    printf("1. Inserir produto\n");
    printf("2. Buscar produto\n");
    printf("3. Remover produto\n");
    printf("4. Exibir tabela\n");
    printf("5. Exportar para CSV\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    TabelaHash tabela_hash;
    inicializar_tabela(&tabela_hash);
    
    int opcao;
    int codigo;
    char nome[MAX_NOME];
    float preco;
    
    printf("=== TABELA HASH - CADASTRO DE PRODUTOS ===\n");
    printf("Tamanho da tabela: %d\n", TAMANHO_TABELA);
    printf("Função hash: código %% %d\n", TAMANHO_TABELA);
    printf("Tratamento de colisões: Sondagem Linear\n");
    
    do {
        menu();
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("\n=== INSERIR PRODUTO ===\n");
                printf("Código do produto: ");
                scanf("%d", &codigo);
                limpar_buffer();
                
                printf("Nome do produto: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove quebra de linha
                
                printf("Preço do produto: R$ ");
                scanf("%f", &preco);
                limpar_buffer();
                
                inserir_produto(&tabela_hash, codigo, nome, preco);
                break;
                
            case 2:
                printf("\n=== BUSCAR PRODUTO ===\n");
                printf("Código do produto: ");
                scanf("%d", &codigo);
                limpar_buffer();
                
                buscar_produto(&tabela_hash, codigo);
                break;
                
            case 3:
                printf("\n=== REMOVER PRODUTO ===\n");
                printf("Código do produto: ");
                scanf("%d", &codigo);
                limpar_buffer();
                
                remover_produto(&tabela_hash, codigo);
                break;
                
            case 4:
                exibir_tabela(&tabela_hash);
                break;
                
            case 5:
                printf("\n=== EXPORTAR PARA CSV ===\n");
                exportar_csv(&tabela_hash);
                break;
                
            case 0:
                printf("Saindo do programa...\n");
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}