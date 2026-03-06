# Estrutura de Dados: Lista Encadeada em C++

Implementação robusta de uma Lista Encadeada (Linked List) desenvolvida para a disciplina de Estrutura de Dados do curso de Engenharia de Computação (UFSC).

## 📌 Sobre o Projeto
Este repositório contém a construção do zero de uma das estruturas de dados mais fundamentais da computação, aplicando conceitos avançados de C++ moderno. O foco do projeto não é apenas a manipulação de ponteiros, mas a criação de uma arquitetura segura, genérica e totalmente validada por testes automatizados.

## ⚙️ Arquitetura e Funcionalidades
* **Tipagem Genérica (Templates):** A estrutura foi projetada usando `template<typename T>`, permitindo que a lista armazene dinamicamente qualquer tipo de dado.
* **Orientação a Objetos e Interfaces:** O código utiliza herança através da interface abstrata `ListaEncadeadaAbstrata`, definindo um contrato rigoroso de métodos para a classe concreta `MinhaListaEncadeada`.
* **Tratamento de Exceções Customizadas:** Implementação de classes de erro específicas (ex: `ExcecaoListaEncadeadaVazia`, `ExcecaoPosicaoInvalida`) para evitar falhas de memória e garantir a previsibilidade do sistema.
* **Testes Unitários:** Cobertura de testes automatizados validando todos os cenários de inserção, remoção, busca e lançamento de exceções.

## 🛠️ Tecnologias Utilizadas
* **Linguagem:** C++ (Padrão C++17)
* **Build System:** CMake
* **Framework de Testes:** Google Test (GTest)
* **Gerenciamento de Memória:** Uso intensivo de alocação/desalocação dinâmica (`new` e `delete`).