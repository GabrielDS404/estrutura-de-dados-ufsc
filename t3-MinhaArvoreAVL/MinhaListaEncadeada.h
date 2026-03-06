#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"

template <typename T>
class MinhaListaEncadeada :  public ListaEncadeadaAbstrata<T>
{
    ~MinhaListaEncadeada<T>() 
    {
        while(this->_primeiro != NULL)
        {
            removerDoInicio();
        }

    };

    //Retorna nº de itens na lista. Número que o registro de controle marca.
    
    virtual size_t tamanho() const  
    {
        return this->_tamanho;
    }
    
    
    /*Função checa se a lista está vazia. Se o registrador de controle apontar pra nulo, significa q
    não tem nenhum elemento, retorna true. Caso contrário, falso*/
    
    virtual bool vazia() const
    {
        if(this->_primeiro != NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    /*Função que retorna a posição de um determinado item. Primeiro checará se a lista eh vazia e jogará
    exceção caso estiver vazia. Depois procura o determinado item. Se ele existir, retorna sua poição,
    se não jogará exceção item inexistente*/
    
    virtual std::size_t posicao(T dado) const
    {
        bool check = vazia(); 

        if(check != false) 
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        int pos = 0; 
        
        Elemento<T> *findposition = this->_primeiro; 
        
        while(findposition != NULL)
        {
            if(findposition->dado == dado)
            {
                return pos;
            }
            
            pos++;
            findposition = findposition->proximo;
        }
            
        delete findposition;
        throw ExcecaoDadoInexistente();
        
    }
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        Elemento<T> *checkposition = this->_primeiro;
        
        while(checkposition != NULL)
        {
            if(checkposition->dado == dado)
            {
                return true;
            }

            checkposition = checkposition->proximo;
        }

        return false;
    }

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        Elemento<T> *newfirst = new Elemento(dado);

        if(this->_primeiro == NULL)
        {
            this->_primeiro = newfirst;
            newfirst->proximo = NULL;
        }
        else
        {
            newfirst->proximo = this->_primeiro;
            this->_primeiro = newfirst;
        }

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
    virtual void inserir(std::size_t posicao, T dado)
    {
        
        if(posicao < 0 || posicao > this->_tamanho)
        {
            throw ExcecaoPosicaoInvalida();         
        }

        int position =0;
        
    
        Elemento<T> *findprevpos = this->_primeiro;
        Elemento<T> *newKitem = new Elemento(dado);
        
        
        if(findprevpos != NULL && posicao != 0)
        {
            
            while (findprevpos->proximo != NULL)
            {
                if(posicao - 1 == position)
                {
                    break;
                }

                findprevpos = findprevpos->proximo;
                position++;
            }
            
            if(findprevpos->proximo == NULL)
            {
                inserirNoFim(dado);
                delete newKitem;  
            }
            else
            {
                newKitem->proximo = findprevpos->proximo;
                findprevpos->proximo = newKitem;
                this->_tamanho++;
            }
        }
        else
        {
            inserirNoInicio(dado);
            delete newKitem; 
        }

    }  

    
    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado) 
    {
        Elemento<T> *findprevlast = this->_primeiro;
        Elemento<T> *newlast = new Elemento(dado);
        newlast->proximo = NULL;
        
        if(findprevlast == NULL)
        {
            inserirNoInicio(dado);
            delete newlast;
        }
        else
        {
            
            while(findprevlast->proximo != NULL)
            {
                findprevlast = findprevlast->proximo;
            }

            findprevlast->proximo = newlast;
            
            this->_tamanho++;
        }

    }

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio() 
    {
        bool check = vazia(); 

        if(check != false)
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        T getData =0;
        Elemento<T> *remover = this->_primeiro;
        
        getData = remover->dado;

        if(remover->proximo != NULL)
        {
            this->_primeiro = remover->proximo;
        }
        else
        {
            this->_primeiro = NULL;
        }

        delete remover;
        this->_tamanho--;

        return getData;
        
    }
    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao) 
    {
        
        if(posicao < 0 || posicao >= this->_tamanho)
        {
            throw ExcecaoPosicaoInvalida();         
        }

        int position =0;
        T getData =0;

        Elemento<T> *findprevpos = this->_primeiro; // findprevpos == FIND PREVIOUS POSITION;
        
        if(findprevpos->proximo == NULL || posicao == 0)
        {
            getData = removerDoInicio();
        }
        else
        {
            while (findprevpos->proximo != NULL)
            {
                if(posicao - 1 == position)
                {
                    break;
                }

                findprevpos = findprevpos->proximo;
                position++;
            }

            if(findprevpos->proximo == NULL)
            {
                getData = removerDoFim();
            }
            else
            {
                Elemento<T> *saveKposplus01 = findprevpos->proximo->proximo; //SAVE K POSITION PLUS 1;
                getData = findprevpos->proximo->dado;
                delete findprevpos->proximo;
                findprevpos->proximo = saveKposplus01;
                
                this->_tamanho--;
            }
        }

        return getData;
    }
    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim() 
    {
        bool check = vazia(); 

        if(check != false)
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        int pos = 1; //position
        T getData =0;
        Elemento<T> *findprevlast = this->_primeiro; //find previous to last
        
        if(findprevlast->proximo == NULL)
        {
            getData = removerDoInicio();            
        }
        else
        {
            while(this->_tamanho - 1 != pos)
            {
                findprevlast = findprevlast->proximo;
                pos++;
            }

            getData = findprevlast->proximo->dado;
            delete findprevlast->proximo;
            findprevlast->proximo = NULL; 
            this->_tamanho--;

        }

        return getData;
    }
    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) 
    {
        bool check = vazia(); 

        if(check != false)
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        int getPosition = posicao(dado);

        T getData = removerDe(getPosition);
        
    }
};

#endif