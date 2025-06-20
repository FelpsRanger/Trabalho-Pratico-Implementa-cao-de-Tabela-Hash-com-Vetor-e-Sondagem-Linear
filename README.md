# Trabalho-Pratico-Implementa-cao-de-Tabela-Hash-com-Vetor-e-Sondagem-Linear
Um sistema de cadastro de produtos utilizando uma tabela hash baseada apenas em vetor fixo, com tratamento de colis˜oes por sondagem linear.
# Sistema de Cadastro de Produtos - Tabela Hash

## Descrição
Este projeto implementa um sistema de cadastro de produtos utilizando uma tabela hash com vetor fixo e tratamento de colisões por sondagem linear, conforme especificado no trabalho prático da disciplina AEDI.

## Estrutura do Projeto

### Estrutura do Produto
- **Código do Produto** (int): Chave primária usada na função hash
- **Nome do Produto** (string): Nome do produto (até 100 caracteres)
- **Preço** (float): Preço do produto em reais

### Função Hash Utilizada
```c
int funcao_hash(int codigo) {
    return codigo % TAMANHO_TABELA;
}
```
A função hash utilizada é a **divisão simples**: `código % TAMANHO_TABELA`, onde o tamanho da tabela é definido como 10.

## Tratamento de Colisões

### Sondagem Linear
Quando ocorre uma colisão (duas chaves diferentes resultam no mesmo índice hash), o sistema utiliza **sondagem linear**:
1. Calcula a posição inicial com a função hash
2. Se a posição estiver ocupada, tenta a próxima posição (índice + 1)
3. Continua até encontrar uma posição vazia ou o próprio item
4. Usa aritmética modular para "dar a volta" na tabela quando necessário

### Estados das Posições
Cada posição da tabela pode ter três estados:
- **VAZIO**: Posição nunca foi ocupada
- **OCUPADO**: Posição contém um produto válido
- **REMOVIDO**: Posição tinha um produto que foi removido (importante para não quebrar a sondagem)

## Funcionalidades Implementadas

### Obrigatórias
1. **Inserir produto**: Insere um novo produto na tabela, tratando colisões
2. **Buscar produto**: Localiza um produto pelo código
3. **Remover produto**: Remove um produto, marcando a posição como "removida"
4. **Exibir tabela**: Mostra todo o conteúdo da tabela, incluindo estatísticas

### Extras (Bônus)
1. **Contador de colisões**: Registra o número total de colisões ocorridas
2. **Taxa de ocupação**: Calcula a porcentagem de ocupação da tabela
3. **Exportação CSV**: Exporta o estado atual da tabela para arquivo CSV

## Análise do Tratamento de Colisões

### Vantagens da Sondagem Linear
- **Simplicidade**: Fácil de implementar e entender
- **Localidade de referência**: Elementos próximos tendem a estar em posições adjacentes
- **Eficiência de cache**: Acesso sequencial à memória

### Desvantagens
- **Clustering primário**: Tendência de formar grupos de elementos ocupados
- **Degradação de performance**: Com alta ocupação, o número de tentativas aumenta significativamente

### Estratégias de Otimização Implementadas
1. **Controle de ocupação**: Limita inserções quando a tabela está cheia
2. **Estado REMOVIDO**: Mantém a integridade da sondagem após remoções
3. **Estatísticas**: Monitora colisões e taxa de ocupação para análise de performance

## Como Compilar e Executar

### Compilação
```bash
gcc -o cadastro_produtos tabela_hash.c -Wall -Wextra
```

### Execução
```bash
./cadastro_produtos
```

## Exemplo de Uso

### Inserção com Colisão
- Produto código 15: hash = 15 % 10 = 5 → inserido na posição 5
- Produto código 25: hash = 25 % 10 = 5 → colisão! → inserido na posição 6
- Produto código 35: hash = 35 % 10 = 5 → colisão! → posição 6 ocupada → inserido na posição 7

### Busca com Sondagem
Para buscar o produto código 35:
1. Calcula hash: 35 % 10 = 5
2. Posição 5 tem código 15 (não é o procurado)
3. Tenta posição 6: tem código 25 (não é o procurado)
4. Tenta posição 7: tem código 35 (encontrado!)

### Remoção Segura
Ao remover um produto, a posição é marcada como REMOVIDO, não VAZIO, garantindo que buscas futuras continuem a sondagem corretamente.

## Considerações de Performance

### Taxa de Ocupação Recomendada
- **Ótima**: 50-70% (equilíbrio entre espaço e performance)
- **Aceitável**: até 80%
- **Crítica**: acima de 90% (muitas colisões)

### Análise de Complexidade
- **Melhor caso**: O(1) - sem colisões
- **Case médio**: O(1 + α/2) onde α é a taxa de ocupação
- **Pior caso**: O(n) - todos os elementos em sequência por colisões

## Arquivos Gerados
- `tabela_produtos.csv`: Exportação da tabela em formato CSV
- Contém colunas: Índice, Estado, Código, Nome, Preço

## Observações Técnicas
- Tamanho fixo da tabela: 10 posições
- Buffer de entrada tratado para evitar problemas com scanf/fgets
- Validação de produtos duplicados
- Interface interativa com menu de opções
- Tratamento de erros (tabela cheia, produto não encontrado, etc.)

## Possíveis Melhorias Futuras
1. Implementação de redimensionamento dinâmico
2. Sondagem quadrática ou duplo hash
3. Função hash mais robusta para distribuição uniforme
4. Interface gráfica
5. Persistência de dados em arquivo
# Sistema de Cadastro de Produtos - Tabela Hash

🔗 **[Acesse o sistema online](https://[SEU_USUARIO.github.io/tabela-hash-aedi](https://felpsranger.github.io/Trabalho-Pratico-Implementa-cao-de-Tabela-Hash-com-Vetor-e-Sondagem-Linear/))**

## Sobre o Projeto
Sistema de cadastro de produtos implementado com tabela hash e sondagem linear, desenvolvido para a disciplina de Algoritmos e Estruturas de Dados I (AEDI) da UFAM.

## Funcionalidades
- ✅ Inserir produtos com tratamento de colisões
- ✅ Buscar produtos por código
- ✅ Remover produtos (marcação especial)
- ✅ Visualizar tabela completa
- ✅ Estatísticas em tempo real
- ✅ Exportar dados para CSV

## Tecnologias
- **Versão Web:** HTML5, CSS3, JavaScript
- **Versão Original:** Linguagem C
- **Hospedagem:** GitHub Pages

## Hash Function
```javascript
function funcaoHash(codigo) {
    return codigo % 10;
}
