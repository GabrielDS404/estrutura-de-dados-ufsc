#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente
#include "Posicao.h"
#include <cstddef>
#include <cmath>
#include <optional>

using namespace std;

template <typename T, std::size_t capac>
class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, capac> {
public:
    MinhaTabelaEspalhamento() : qtdElementos(0) {}

    ~MinhaTabelaEspalhamento() = default;

    /**
     * @brief Obtém a capacidade da tabela.
     *
     * @return Um inteiro maior do que 0.
     */
    std::size_t capacidade() const {
        return capac;
    }

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     *
     * @param dado O dado a ser inserido.
     */
    void inserir(T dado) {
        size_t indice = funcaoEspalhamento(dado);

        if (!this->tabela[indice].contem(dado)) {
            this->tabela[indice].inserirNoFim(dado);
            ++qtdElementos;
        }
    }

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     *
     * @param dado O dado a ser removido.
     */
    void remover(T dado) {
        size_t indice = funcaoEspalhamento(dado);

        if (!this->tabela[indice].contem(dado)) {
            throw ExcecaoDadoInexistente();
        }

        this->tabela[indice].remover(dado);
        --qtdElementos;
    }

    /**
     * @brief Verifica se \p dado está contido na tabela.
     *
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    bool contem(T dado) const {
        size_t indice = funcaoEspalhamento(dado);
        return this->tabela[indice].contem(dado);
    }

    /**
     * @brief Obtém a posição de um dado na tabela.
     *
     * @param dado O dado sendo buscado.
     * @return Uma instância de Posicao indicando a posição do dado.
     */
    Posicao posicao(T dado) const {
        size_t indice = funcaoEspalhamento(dado);
        size_t tamanhoLista = this->tabela[indice].tamanho();

        if (!this->tabela[indice].contem(dado)) {
            return Posicao(indice, tamanhoLista, nullopt);
        }

        size_t posLista = this->tabela[indice].posicao(dado);
        return Posicao(indice, tamanhoLista, posLista);
    }

    /**
     * @brief Obtém a quantidade de dados contidos na tabela.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t quantidade() const {
        return qtdElementos;
    }

protected:
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     *
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    std::size_t funcaoEspalhamento(T dado) const {
        return codigoEspalhamento(dado) % capacidade();
    }

private:
    size_t qtdElementos; // Contador global de elementos na tabela

    /**
     * @brief Calcula a representação numérica de um tipo integral.
     *
     * @tparam U O tipo integral.
     * @param integral Um valor integral.
     * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
     */
    template <typename U>
    std::size_t codigoEspalhamento(U integral) const {
        static_assert(is_integral_v<U>, "O tipo deve ser integral.");
        return static_cast<size_t>(integral);
    }

    /**
     * @brief Calcula a representação numérica de um string.
     *
     * @param s um string.
     * @return Um inteiro calculado conforme s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1].
     */
    std::size_t codigoEspalhamento(const std::string& string) const {
        size_t hash = 0;
        size_t fator = 1;
        for (auto it = string.rbegin(); it != string.rend(); ++it) {
            hash += (*it) * fator;
            fator *= 31;
        }
        return hash;
    }
};

#endif