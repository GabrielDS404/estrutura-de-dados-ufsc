# Estrutura de Dados: Árvore AVL em C++ (Self-Balancing BST)

Implementação avançada de uma Árvore Binária de Busca Auto-balanceada (Árvore AVL), desenvolvida para a disciplina de Estrutura de Dados da Engenharia de Computação (UFSC).

## 📌 Sobre o Projeto
Este projeto vai além das árvores binárias convencionais ao implementar o algoritmo AVL, que garante o balanceamento automático da estrutura após cada inserção ou remoção. O sistema previne a degradação da árvore em uma lista, mantendo a complexidade de tempo de busca, inserção e deleção sempre otimizada em `O(log n)`. 

## ⚙️ Arquitetura e Funcionalidades
* **Auto-Balanceamento (Fator de Balanceamento):** Implementação nativa de cálculos de altura e verificação de balanceamento.
* **Algoritmos de Rotação:** Lógica completa de rotações de nós para manter a simetria da árvore:
  * Rotação Simples à Esquerda (RR) e à Direita (LL).
  * Rotação Dupla Esquerda-Direita (LR) e Direita-Esquerda (RL).
* **Deleção Complexa:** Tratamento dos 4 casos clássicos de remoção em Árvores Binárias (Nó folha, nó com um filho, nó com dois filhos buscando o sucessor in-order).
* **Travessias (Integração de Estruturas):** Implementação de métodos de travessia `em-ordem`, `pré-ordem` e `pós-ordem`. Os resultados são retornados instanciando e preenchendo uma estrutura de **Lista Encadeada** customizada (`MinhaListaEncadeada`), provando a interoperabilidade entre as estruturas criadas do zero.

## 🛠️ Tecnologias e Boas Práticas
* **C++ Genérico (Templates):** Uso de `template <typename T>` permitindo o armazenamento de qualquer tipo de dado na Árvore.
* **Testes Automatizados (Google Test):** Cobertura rigorosa de testes unitários validando cenários críticos de rotação encadeada e esvaziamento da árvore.
* **Gerenciamento de Memória:** Destruição recursiva segura de todos os nós (`deleteEverySingleNode`) para evitar *memory leaks*.
* **Build System:** CMake.