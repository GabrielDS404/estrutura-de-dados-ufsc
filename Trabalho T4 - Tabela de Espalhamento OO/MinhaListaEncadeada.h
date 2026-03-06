#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T> {
public:
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada() {
        while (!vazia()) {
            removerDoInicio();
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const {
        return this->_tamanho;
    }

    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const {
        return this->_tamanho == 0;
    }

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const {
        if (vazia()) throw ExcecaoListaEncadeadaVazia();

        Elemento<T>* atual = this->_primeiro;
        std::size_t indice = 0;

        while (atual != nullptr) {
            if (atual->dado == dado) {
                return indice;
            }
            atual = atual->proximo;
            indice++;
        }

        throw ExcecaoDadoInexistente();
    }

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const {
        Elemento<T>* temp = this->_primeiro;

        while (temp != nullptr) {
            if (temp->dado == dado) {
                return true;
            }
            temp = temp->proximo;
        }
        return false;
    }

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) {
        Elemento<T>* novoElemento = new Elemento<T>(dado, this->_primeiro);
        this->_primeiro = novoElemento;
        this->_tamanho++;
    }

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado) {
        if (posicao > this->_tamanho) throw ExcecaoPosicaoInvalida();

        if (posicao == 0) {
            inserirNoInicio(dado);
            return;
        }

        Elemento<T>* atual = this->_primeiro;
        for (std::size_t i = 0; i < posicao - 1; ++i) {
            atual = atual->proximo;
        }

        Elemento<T>* novoElemento = new Elemento<T>(dado, atual->proximo);
        atual->proximo = novoElemento;
        this->_tamanho++;
    }

    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado) {
        if (vazia()) {
            inserirNoInicio(dado);
            return;
        }

        Elemento<T>* atual = this->_primeiro;
        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }

        atual->proximo = new Elemento<T>(dado);
        this->_tamanho++;
    }

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio() {
        if (vazia()) throw ExcecaoListaEncadeadaVazia();

        Elemento<T>* temp = this->_primeiro;
        T valorRemovido = temp->dado;

        this->_primeiro = temp->proximo;
        delete temp;
        this->_tamanho--;

        return valorRemovido;
    }

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao) {
        if (posicao >= this->_tamanho) throw ExcecaoPosicaoInvalida();

        if (posicao == 0) return removerDoInicio();

        Elemento<T>* anterior = this->_primeiro;
        for (std::size_t i = 0; i < posicao - 1; ++i) {
            anterior = anterior->proximo;
        }

        Elemento<T>* temp = anterior->proximo;
        T valorRemovido = temp->dado;

        anterior->proximo = temp->proximo;
        delete temp;
        this->_tamanho--;

        return valorRemovido;
    }

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim() {
        if (vazia()) throw ExcecaoListaEncadeadaVazia();

        if (this->_tamanho == 1) return removerDoInicio();

        Elemento<T>* atual = this->_primeiro;
        while (atual->proximo->proximo != nullptr) {
            atual = atual->proximo;
        }

        T valorRemovido = atual->proximo->dado;
        delete atual->proximo;
        atual->proximo = nullptr;
        this->_tamanho--;

        return valorRemovido;
    }

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) {
        if (vazia()) throw ExcecaoListaEncadeadaVazia();

        if (!contem(dado)) throw ExcecaoDadoInexistente();

        removerDe(posicao(dado));
    }
};

#endif