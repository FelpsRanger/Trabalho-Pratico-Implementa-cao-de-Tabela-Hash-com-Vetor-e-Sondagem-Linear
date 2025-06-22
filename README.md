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

## 🛠️ Tecnologias Utilizadas

### Versão C
- **Linguagem:** C (padrão C99)
- **Compilador:** GCC
- **Bibliotecas:** stdio.h, stdlib.h, string.h

### Versão Web
- **Frontend:** HTML5, CSS3, JavaScript (ES6+)
- **Estilo:** CSS Grid, Flexbox, Gradientes
- **Responsividade:** Design adaptativo
- **Compatibilidade:** Navegadores modernos

## 👥 Divisão de Responsabilidades

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

## 📁 Estrutura do Projeto

```
📂 Sistema-Cadastro-Produtos/
├── 📄 main.c                 # Versão em C
├── 📄 index.html            # Versão Web
├── 📄 README.md             # Este arquivo
├── 📄 tabela_produtos.csv   # Arquivo de exportação (gerado)
└── 📂 docs/                 # Documentação adicional
    ├── 📄 manual_usuario.md
    └── 📄 documentacao_tecnica.md
```

## 🚀 Como Executar

### Versão C

#### Compilação
```bash
gcc -o sistema_produtos main.c -std=c99 -Wall
```

#### Execução
```bash
./sistema_produtos
```

#### Requisitos
- GCC 4.8 ou superior
- Sistema operacional: Linux, macOS, Windows (com MinGW)

### Versão Web

#### Execução Local
1. Baixe o arquivo `index.html`
2. Abra em qualquer navegador moderno
3. Não requer servidor web

#### Execução com Servidor
```bash
# Python 3
python -m http.server 8000

# Node.js (com http-server)
npx http-server

# Acesse: http://localhost:8000
```

#### Requisitos
- Navegador moderno (Chrome 60+, Firefox 55+, Safari 12+)
- JavaScript habilitado
- Não requer conexão com internet

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

## 🧪 Testes e Validações

### Cenários de Teste
- ✅ Inserção de produtos válidos
- ✅ Inserção de produtos duplicados
- ✅ Busca de produtos existentes
- ✅ Busca de produtos inexistentes
- ✅ Remoção de produtos existentes
- ✅ Remoção de produtos inexistentes
- ✅ Tabela cheia
- ✅ Colisões múltiplas
- ✅ Validação de entrada inválida

### Validações Implementadas
- **Código:** Números positivos de 1 a 999999
- **Nome:** Não vazio, máximo 99 caracteres
- **Preço:** Valores não negativos, máximo R$ 999999.99

## 📈 Estatísticas Monitoradas

- **Total de produtos** na tabela
- **Total de colisões** ocorridas
- **Taxa de ocupação** da tabela
- **Posições vazias** disponíveis
- **Colisões por produto** (média)
- **Distribuição** dos produtos na tabela

## 🔮 Melhorias Futuras

### Funcionalidades Planejadas
- [ ] Redimensionamento dinâmico da tabela
- [ ] Implementação de Double Hashing
- [ ] Sistema de persistência em arquivo
- [ ] Interface web mais avançada
- [ ] Relatórios em PDF
- [ ] Sistema de backup automático

### Otimizações Técnicas
- [ ] Função hash mais robusta
- [ ] Compressão de dados
- [ ] Cache de consultas frequentes
- [ ] Índices secundários
- [ ] Balanceamento de carga

## 🤝 Contribuição

### Como Contribuir
1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-funcionalidade`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um Pull Request

### Padrões de Código
- **C:** Siga o padrão K&R com comentários em português
- **Web:** Use ES6+, CSS modular e HTML semântico
- **Documentação:** Mantenha README e comentários atualizados

## 📞 Contato

### Desenvolvedores
- **Felipe Rangel** - Estruturas e Algoritmos
- **Kaio Sobral** - Lógica de Negócio e Validações  
- **Gustavo Souza** - Interface e Experiência do Usuário

### Instituição
**Universidade Federal do Amazonas - UFAM**  
Curso: Ciência da Computação  
Disciplina: Estruturas de Dados  

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

## 🏆 Agradecimentos

Agradecemos à **UFAM** pela oportunidade de desenvolver este projeto e aos professores que nos orientaram durante o desenvolvimento. Este trabalho representa nossa compreensão prática dos conceitos de estruturas de dados e sua aplicação em sistemas reais.

---

<div align="center">

**⭐ Se este projeto foi útil para você, considere dar uma estrela!**

**🔧 Desenvolvido com dedicação pela equipe UFAM**

</div>
