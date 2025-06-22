#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 13  // Número primo para melhor distribuição
#define MAX_NOME 100
#define FATOR_CARGA_MAX 0.7  // 70% de ocupação máxima
#define MAX_TENTATIVAS 20    // Segurança contra loops infinitos

/*
 * ===============================================================================
 *                    PARTE 1 - ESTRUTURAS E FUNÇÕES BÁSICAS
 *                           Desenvolvida por: FELIPE RANGEL
 * ===============================================================================
 */

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

/**
 * Função hash melhorada usando multiplicação por número primo
 * Reduz clustering e melhora distribuição
 * FELIPE RANGEL - Implementação da função hash principal
 */
int funcao_hash(int codigo) {
    if (codigo < 0) codigo = -codigo;  // Garante valor positivo
    return (codigo * 31) % TAMANHO_TABELA;
}

/**
 * Função hash secundária para double hashing (futura implementação)
 * FELIPE RANGEL - Função auxiliar para possível expansão
 */
int funcao_hash_secundaria(int codigo) {
    if (codigo < 0) codigo = -codigo;
    return 7 - (codigo % 7);  // 7 é primo menor que TAMANHO_TABELA
}

/**
 * Verifica se a tabela precisa ser redimensionada
 * FELIPE RANGEL - Controle do fator de carga
 */
int precisa_redimensionar(TabelaHash *th) {
    float fator_carga = (float)th->total_produtos / TAMANHO_TABELA;
    return fator_carga > FATOR_CARGA_MAX;
}

/**
 * Inicializar a tabela hash
 * FELIPE RANGEL - Configuração inicial da estrutura
 */
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

/*
 * ===============================================================================
 *                    PARTE 2 - VALIDAÇÕES E OPERAÇÕES CRUD
 *                           Desenvolvida por: KAIO SOBRAL
 * ===============================================================================
 */

/**
 * Valida entrada do código do produto
 * KAIO SOBRAL - Sistema de validação de código
 */
int validar_codigo(int codigo) {
    if (codigo <= 0) {
        printf("Erro: Código deve ser um número positivo!\n");
        return 0;
    }
    if (codigo > 999999) {
        printf("Erro: Código muito grande (máximo 999999)!\n");
        return 0;
    }
    return 1;
}

/**
 * Valida entrada do preço do produto
 * KAIO SOBRAL - Sistema de validação de preço
 */
int validar_preco(float preco) {
    if (preco < 0) {
        printf("Erro: Preço não pode ser negativo!\n");
        return 0;
    }
    if (preco > 999999.99) {
        printf("Erro: Preço muito alto (máximo R$ 999999.99)!\n");
        return 0;
    }
    return 1;
}

/**
 * Valida entrada do nome do produto
 * KAIO SOBRAL - Sistema de validação de nome
 */
int validar_nome(char *nome) {
    if (strlen(nome) == 0) {
        printf("Erro: Nome não pode estar vazio!\n");
        return 0;
    }
    if (strlen(nome) >= MAX_NOME) {
        printf("Erro: Nome muito longo (máximo %d caracteres)!\n", MAX_NOME - 1);
        return 0;
    }
    return 1;
}

/**
 * Inserir produto na tabela hash (melhorado)
 * KAIO SOBRAL - Operação de inserção com sondagem linear
 */
int inserir_produto(TabelaHash *th, int codigo, char *nome, float preco) {
    // Validações de entrada
    if (!validar_codigo(codigo) || !validar_nome(nome) || !validar_preco(preco)) {
        return 0;
    }
    
    // Verificar fator de carga
    if (precisa_redimensionar(th)) {
        printf("Aviso: Tabela com alta ocupação (%.1f%%). Considere aumentar tamanho.\n", 
               (float)th->total_produtos / TAMANHO_TABELA * 100);
    }
    
    // Verificar se a tabela está cheia
    if (th->total_produtos >= TAMANHO_TABELA) {
        printf("Erro: Tabela cheia!\n");
        return 0;
    }
    
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int colisoes = 0;
    int tentativas = 0;
    
    // Sondagem linear com limite de tentativas
    do {
        tentativas++;
        
        // Segurança contra loop infinito
        if (tentativas > MAX_TENTATIVAS) {
            printf("Erro: Muitas tentativas de inserção. Tabela pode estar corrompida.\n");
            return 0;
        }
        
        // Verificar se produto já existe
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            printf("Erro: Produto com código %d já existe na posição %d!\n", codigo, pos);
            return 0;
        }
        
        // Posição disponível encontrada
        if (th->tabela[pos].estado == VAZIO || th->tabela[pos].estado == REMOVIDO) {
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
            
            // Mostrar estatísticas após inserção
            printf("Taxa de ocupação: %.1f%%\n", 
                   (float)th->total_produtos / TAMANHO_TABELA * 100);
            return 1;
        }
        
        // Próxima posição (sondagem linear)
        colisoes++;
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Erro: Não foi possível inserir o produto!\n");
    return 0;
}

/**
 * Buscar produto na tabela hash (melhorado)
 * KAIO SOBRAL - Operação de busca com sondagem linear
 */
int buscar_produto(TabelaHash *th, int codigo) {
    if (!validar_codigo(codigo)) {
        return -1;
    }
    
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int tentativas = 0;
    
    do {
        tentativas++;
        
        // Segurança contra loop infinito
        if (tentativas > MAX_TENTATIVAS) {
            printf("Erro: Muitas tentativas de busca. Tabela pode estar corrompida.\n");
            return -1;
        }
        
        // Posição vazia = produto não existe
        if (th->tabela[pos].estado == VAZIO) {
            printf("Produto com código %d não encontrado (posição %d vazia após %d tentativa(s)).\n", 
                   codigo, pos, tentativas);
            return -1;
        }
        
        // Produto encontrado
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            printf("Produto encontrado na posição %d após %d tentativa(s):\n", pos, tentativas);
            printf("┌─────────────────────────────────────┐\n");
            printf("│ Código: %-27d │\n", th->tabela[pos].codigo);
            printf("│ Nome: %-29s │\n", th->tabela[pos].nome);
            printf("│ Preço: R$ %-24.2f │\n", th->tabela[pos].preco);
            printf("└─────────────────────────────────────┘\n");
            return pos;
        }
        
        // Próxima posição
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Produto com código %d não encontrado após verificar toda a tabela.\n", codigo);
    return -1;
}

/**
 * Remover produto da tabela hash (melhorado)
 * KAIO SOBRAL - Operação de remoção com marcação especial
 */
int remover_produto(TabelaHash *th, int codigo) {
    if (!validar_codigo(codigo)) {
        return 0;
    }
    
    int pos = funcao_hash(codigo);
    int pos_original = pos;
    int tentativas = 0;
    
    do {
        tentativas++;
        
        // Segurança contra loop infinito
        if (tentativas > MAX_TENTATIVAS) {
            printf("Erro: Muitas tentativas de remoção. Tabela pode estar corrompida.\n");
            return 0;
        }
        
        // Posição vazia = produto não existe
        if (th->tabela[pos].estado == VAZIO) {
            printf("Produto com código %d não encontrado para remoção.\n", codigo);
            return 0;
        }
        
        // Produto encontrado - marcar como removido
        if (th->tabela[pos].estado == OCUPADO && th->tabela[pos].codigo == codigo) {
            char nome_removido[MAX_NOME];
            strcpy(nome_removido, th->tabela[pos].nome);
            
            th->tabela[pos].estado = REMOVIDO;
            th->total_produtos--;
            
            printf("Produto '%s' removido da posição %d após %d tentativa(s)!\n", 
                   nome_removido, pos, tentativas);
            printf("Taxa de ocupação: %.1f%%\n", 
                   (float)th->total_produtos / TAMANHO_TABELA * 100);
            return 1;
        }
        
        // Próxima posição
        pos = (pos + 1) % TAMANHO_TABELA;
        
    } while (pos != pos_original);
    
    printf("Produto com código %d não encontrado para remoção.\n", codigo);
    return 0;
}

/*
 * ===============================================================================
 *                    PARTE 3 - INTERFACE E FUNCIONALIDADES EXTRAS
 *                           Desenvolvida por: GUSTAVO SOUZA
 * ===============================================================================
 */

/**
 * Exibir toda a tabela hash (melhorado)
 * GUSTAVO SOUZA - Interface visual da tabela com estatísticas
 */
void exibir_tabela(TabelaHash *th) {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              TABELA HASH                                 ║\n");
    printf("╠═══════╦═══════════╦════════╦═══════════════════════╦═══════════════════╣\n");
    printf("║ Índice║ Estado    ║ Código ║ Nome                  ║ Preço             ║\n");
    printf("╠═══════╬═══════════╬════════╬═══════════════════════╬═══════════════════╣\n");
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("║   %2d  ║ ", i);
        
        switch (th->tabela[i].estado) {
            case VAZIO:
                printf("%-9s ║ %-6s ║ %-21s ║ %-17s ║\n", 
                       "VAZIO", "-", "-", "-");
                break;
            case REMOVIDO:
                printf("%-9s ║ %-6s ║ %-21s ║ %-17s ║\n", 
                       "REMOVIDO", "-", "-", "-");
                break;
            case OCUPADO:
                char preco_str[20];
                snprintf(preco_str, sizeof(preco_str), "R$ %.2f", th->tabela[i].preco);
                printf("%-9s ║ %6d ║ %-21s ║ %-17s ║\n",
                       "OCUPADO",
                       th->tabela[i].codigo,
                       th->tabela[i].nome,
                       preco_str);
                break;
        }
    }
    
    printf("╚═══════╩═══════════╩════════╩═══════════════════════╩═══════════════════╝\n");
    
    // Estatísticas melhoradas
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ESTATÍSTICAS                                ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Total de produtos: %-51d ║\n", th->total_produtos);
    printf("║ Total de colisões: %-51d ║\n", th->total_colisoes);
    printf("║ Taxa de ocupação: %.1f%%%-50s ║\n", 
           (float)th->total_produtos / TAMANHO_TABELA * 100, "");
    printf("║ Posições vazias: %-53d ║\n", 
           TAMANHO_TABELA - th->total_produtos);
    
    float colisoes_por_produto = th->total_produtos > 0 ? 
                                (float)th->total_colisoes / th->total_produtos : 0;
    printf("║ Colisões por produto: %.2f%-46s ║\n", colisoes_por_produto, "");
    
    // Aviso sobre fator de carga
    if (precisa_redimensionar(th)) {
        printf("║ AVISO: Alta ocupacao - considere aumentar tamanho da tabela       ║\n");
    }
    
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n\n");
}

/**
 * Exportar tabela para CSV (melhorado)
 * GUSTAVO SOUZA - Funcionalidade de exportação dos dados
 */
void exportar_csv(TabelaHash *th) {
    FILE *arquivo = fopen("tabela_produtos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }
    
    // Cabeçalho com encoding UTF-8
    fprintf(arquivo, "Indice,Estado,Codigo,Nome,Preco,Hash_Original\n");
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        fprintf(arquivo, "%d,", i);
        
        switch (th->tabela[i].estado) {
            case VAZIO:
                fprintf(arquivo, "VAZIO,,,,-\n");
                break;
            case REMOVIDO:
                fprintf(arquivo, "REMOVIDO,,,,-\n");
                break;
            case OCUPADO:
                fprintf(arquivo, "OCUPADO,%d,\"%s\",%.2f,%d\n",
                        th->tabela[i].codigo,
                        th->tabela[i].nome,
                        th->tabela[i].preco,
                        funcao_hash(th->tabela[i].codigo));
                break;
        }
    }
    
    // Adicionar estatísticas no final
    fprintf(arquivo, "\n# ESTATISTICAS\n");
    fprintf(arquivo, "# Total de produtos,%d\n", th->total_produtos);
    fprintf(arquivo, "# Total de colisoes,%d\n", th->total_colisoes);
    fprintf(arquivo, "# Taxa de ocupacao,%.1f%%\n", 
            (float)th->total_produtos / TAMANHO_TABELA * 100);
    
    fclose(arquivo);
    printf("Tabela exportada para 'tabela_produtos.csv' com sucesso!\n");
    printf("   Arquivo inclui dados e estatisticas da tabela.\n");
}

/**
 * Função para limpar o buffer de entrada
 * GUSTAVO SOUZA - Utilitário para limpeza de buffer
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Função para mostrar informações técnicas
 * GUSTAVO SOUZA - Exibição de informações do sistema
 */
void mostrar_info_tecnica() {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          INFORMAÇÕES TÉCNICAS                            ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Tamanho da tabela: %-54d ║\n", TAMANHO_TABELA);
    printf("║ Funcao hash: (codigo x 31) %% %d%-36s ║\n", TAMANHO_TABELA, "");
    printf("║ Tratamento de colisões: Sondagem Linear%-34s ║\n", "");
    printf("║ Fator de carga máximo: %.0f%%%-47s ║\n", FATOR_CARGA_MAX * 100, "");
    printf("║ Limite de tentativas: %-50d ║\n", MAX_TENTATIVAS);
    printf("║ Validacoes: Codigo, nome e preco%-40s ║\n", "");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
}

/**
 * Menu principal (melhorado)
 * GUSTAVO SOUZA - Interface do usuário e navegação
 */
void menu() {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    SISTEMA DE CADASTRO DE PRODUTOS                       ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ 1. Inserir produto                                                    ║\n");
    printf("║ 2. Buscar produto                                                     ║\n");
    printf("║ 3. Remover produto                                                    ║\n");
    printf("║ 4. Exibir tabela completa                                             ║\n");
    printf("║ 5. Exportar para CSV                                                  ║\n");
    printf("║ 6. Informacoes tecnicas                                               ║\n");
    printf("║ 0. Sair                                                               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

/**
 * Função principal do programa
 * GUSTAVO SOUZA - Controle principal e loop de execução
 */
int main() {
    TabelaHash tabela_hash;
    inicializar_tabela(&tabela_hash);
    
    int opcao;
    int codigo;
    char nome[MAX_NOME];
    float preco;
    
    printf("╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    TABELA HASH - CADASTRO DE PRODUTOS                    ║\n");
    printf("║                              Versão 2.0                                  ║\n");
    printf("║                                                                           ║\n");
    printf("║    Desenvolvido por: Felipe Rangel, Kaio Sobral e Gustavo Souza         ║\n");
    printf("║                     Universidade Federal do Amazonas                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    
    mostrar_info_tecnica();
    
    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Entrada inválida! Digite um número.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("\n╔═══════════════════ INSERIR PRODUTO ═══════════════════╗\n");
                printf("Código do produto (1-999999): ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Erro: Código inválido!\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();
                
                printf("Nome do produto: ");
                if (fgets(nome, MAX_NOME, stdin) == NULL) {
                    printf("Erro ao ler nome!\n");
                    break;
                }
                nome[strcspn(nome, "\n")] = 0; // Remove quebra de linha
                
                printf("Preço do produto (R$): ");
                if (scanf("%f", &preco) != 1) {
                    printf("Erro: Preço inválido!\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();
                
                inserir_produto(&tabela_hash, codigo, nome, preco);
                break;
                
            case 2:
                printf("\n╔═══════════════════ BUSCAR PRODUTO ════════════════════╗\n");
                printf("Código do produto: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Erro: Código inválido!\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();
                
                buscar_produto(&tabela_hash, codigo);
                break;
                
            case 3:
                printf("\n╔═══════════════════ REMOVER PRODUTO ═══════════════════╗\n");
                printf("Código do produto: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Erro: Código inválido!\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();
                
                remover_produto(&tabela_hash, codigo);
                break;
                
            case 4:
                exibir_tabela(&tabela_hash);
                break;
                
            case 5:
                printf("\n╔═══════════════════ EXPORTAR CSV ══════════════════════╗\n");
                exportar_csv(&tabela_hash);
                break;
                
            case 6:
                mostrar_info_tecnica();
                break;
                
            case 0:
                printf("\nObrigado por usar o sistema! Saindo...\n");
                printf("Desenvolvido por: Felipe Rangel, Kaio Sobral e Gustavo Souza\n");
                break;
                
            default:
                printf("Opcao invalida! Escolha entre 0-6.\n");
                break;
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while (opcao != 0);
    
    return 0;
}
