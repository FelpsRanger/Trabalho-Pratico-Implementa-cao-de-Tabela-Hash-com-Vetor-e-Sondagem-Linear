# 📦 Sistema de Cadastro de Produtos - Tabela Hash

> **Estrutura de Dados - Tabela Hash com Sondagem Linear**  
> Universidade Federal do Amazonas - UFAM  
> Desenvolvido por: **Felipe Rangel**, **Kaio Sobral** e **Gustavo Souza**

## Versão C e web para teste
- [Codigo em C](https://www.onlinegdb.com)
- [Site](https://felpsranger.github.io/Trabalho-Pratico-Implementacao-de-Tabela-Hash-com-Vetor-e-Sondagem-Linear/)

## 📋 Sobre o Projeto

Este projeto implementa um sistema completo de cadastro de produtos utilizando **Tabela Hash** como estrutura de dados principal. O sistema foi desenvolvido em duas versões: uma implementação em **C** (console) e uma versão **Web** (HTML/CSS/JavaScript) com interface gráfica moderna.

### 🎯 Objetivos

- Demonstrar o funcionamento prático de uma Tabela Hash
- Implementar tratamento de colisões por sondagem linear
- Criar um sistema CRUD completo para produtos
- Desenvolver uma interface amigável para interação do usuário
- Aplicar conceitos de validação e segurança de dados

## 🚀 Funcionalidades

### ✨ Operações Principais
- **Inserir** produtos com validação de dados
- **Buscar** produtos por código
- **Remover** produtos (marcação como removido)
- **Exibir** tabela completa com estatísticas
- **Exportar** dados para CSV
- **Informações técnicas** do sistema

### 📊 Características Técnicas
- **Tamanho da tabela:** 13 posições (número primo)
- **Função hash:** `(codigo × 31) % 13`
- **Tratamento de colisões:** Sondagem Linear
- **Estados das posições:** VAZIO, OCUPADO, REMOVIDO
- **Fator de carga máximo:** 70%
- **Limite de tentativas:** 20 (segurança)

## 👥 Divisão da construção do código
### 🔧 Felipe Rangel - Estruturas e Funções Básicas
**Responsável pela base da implementação:**
- Definição das estruturas de dados (`Produto`, `TabelaHash`, `Estado`)
- Implementação da função hash principal
- Função hash secundária (para expansões futuras)
- Sistema de controle do fator de carga
- Inicialização da tabela hash
- Documentação técnica das funções base

### 📝 Kaio Sobral - Validações e Operações CRUD
**Responsável pela lógica de negócio:**
- Sistema completo de validações (código, nome, preço)
- Implementação da operação **Inserir** com sondagem linear
- Implementação da operação **Buscar** com contagem de tentativas
- Implementação da operação **Remover** com marcação especial
- Tratamento de colisões e estatísticas
- Controle de segurança contra loops infinitos

### 🎨 Gustavo Souza - Interface e Funcionalidades Extras
**Responsável pela experiência do usuário:**
- Interface visual da tabela com formatação
- Sistema de menu interativo
- Funcionalidade de exportação para CSV
- Exibição de estatísticas detalhadas
- Informações técnicas do sistema
- Controle principal e loop de execução
- Utilitários de interface (limpeza de buffer, etc.)

## 📖 Manual de Uso

### Versão C

#### Menu Principal
```
╔═══════════════════════════════════════════════════════════╗
║              SISTEMA DE CADASTRO DE PRODUTOS             ║
╠═══════════════════════════════════════════════════════════╣
║ 1. Inserir produto                                       ║
║ 2. Buscar produto                                        ║
║ 3. Remover produto                                       ║
║ 4. Exibir tabela completa                                ║
║ 5. Exportar para CSV                                     ║
║ 6. Informações técnicas                                  ║
║ 0. Sair                                                  ║
╚═══════════════════════════════════════════════════════════╝
```

#### Exemplo de Uso
```bash
# Inserir produto
Escolha uma opção: 1
Código do produto (1-999999): 12345
Nome do produto: Notebook Dell
Preço do produto (R$): 2500.00

# Buscar produto
Escolha uma opção: 2
Código do produto: 12345
```

### Versão Web

#### Interface Gráfica
- **Menu interativo** com botões coloridos
- **Formulários** com validação em tempo real
- **Tabela visual** com formatação profissional
- **Estatísticas** em cards informativos
- **Mensagens** de feedback para todas as operações

## 🔍 Algoritmos Implementados

### Função Hash
```c
int funcao_hash(int codigo) {
    if (codigo < 0) codigo = -codigo;
    return (codigo * 31) % TAMANHO_TABELA;
}
```

### Sondagem Linear
```c
do {
    if (tabela[pos].estado == VAZIO || tabela[pos].estado == REMOVIDO) {
        // Inserir aqui
        break;
    }
    pos = (pos + 1) % TAMANHO_TABELA;
} while (pos != pos_original);
```

### Tratamento de Colisões
- **Método:** Sondagem Linear (Linear Probing)
- **Vantagem:** Simples implementação, boa performance
- **Controle:** Limite de tentativas para evitar loops infinitos

## 📊 Análise de Complexidade

| Operação | Melhor Caso | Caso Médio | Pior Caso |
|----------|-------------|------------|-----------|
| Inserir  | O(1)        | O(1)       | O(n)      |
| Buscar   | O(1)        | O(1)       | O(n)      |
| Remover  | O(1)        | O(1)       | O(n)      |

**Nota:** O pior caso ocorre quando há muitas colisões consecutivas.



