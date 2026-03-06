/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Lembrar de excluir os comentários de visualização utilizados para facilitar fazer código;

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    
    Nodo<T>* deleteEverySingleNode(Nodo<T>* root)
    {
        if(root != NULL)
        {
            root->filhoEsquerda = deleteEverySingleNode(root->filhoEsquerda);
            root->filhoDireita = deleteEverySingleNode(root->filhoDireita);

            delete root;
            root = NULL;
        }
        
        return root;
    }

    ~MinhaArvoreAVL()
    {
        this->raiz = deleteEverySingleNode(this->raiz);
    }
    
   /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if(this->raiz == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     **/

    int quantity(Nodo<T> *root, int cont) const
    {
        if(root == NULL)
        {
            return (cont + 0);
        }
        else
        {
            cont++;
        }
       
        cont = this->quantity(root->filhoEsquerda, cont);
        cont = this->quantity(root->filhoDireita, cont);
       
        return cont;
    }
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const 
    {
        int cont = 0;

        cont = quantity(this->raiz, cont);

        return cont;
    }
    
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool searchKey(Nodo<T> *root, T chave) const
    {
        if(root == NULL)
        {
            return false;
        }

        if(root->chave == chave)
        {
            return true;
        }
        else if(chave < root->chave)
        {
            return this->searchKey(root->filhoEsquerda, chave);
        }
        else
        {
            return this->searchKey(root->filhoDireita, chave);
        }
        
        
    }
    

    virtual bool contem(T chave) const 
    {
        return searchKey(this->raiz, chave);
    }
    
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. 
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> searchKeyRetHeight(Nodo<T> *root, T chave) const
    {
        if(root == NULL)
        {
            return std::nullopt;
        }
        
        if(root->chave == chave)
        {
            return root->altura;
        }
        else if(chave < root->chave)
        {
            return this->searchKeyRetHeight(root->filhoEsquerda, chave);
        }
        else
        {
            return this->searchKeyRetHeight(root->filhoDireita, chave);
        }
    }
    
    
    virtual std::optional<int> altura(T chave) const 
    {
        return searchKeyRetHeight(this->raiz, chave);
    }

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
        
    Nodo<T>* newNode(T chave)
    {
        Nodo<T>* newnode = new Nodo<T>();

        newnode->chave = chave;

        return newnode;
    }
    
    int setNewHeight(Nodo<T> *root)
    {   
        if(root == NULL)
        {
            return -1;
        }

        int hl, hr; //hl = height left, hr= height right

        hl = setNewHeight(root->filhoEsquerda);

        hr = setNewHeight(root->filhoDireita);

        if(hl > hr)
        {
            return hl + 1;
        }
        else
        {
            return hr + 1;
        }
    }

    int getHeight(Nodo<T>* root)
    {
        if(root == NULL)
        {
            return -1;
        }
        else
        {
            return root->altura;
        }
    }

    int bFCalculation(Nodo<T>* root) //calculo do Fator de Balanceamento.
    {
        if(root == NULL)
        {
            return 0;
        }
        else
        {
            int result;

            result = (getHeight(root->filhoEsquerda) - getHeight(root->filhoDireita));
            
            return result;
        }
    }


    Nodo<T>* leftRotation(Nodo<T>* root)
    {
        //Salva o endereço do filho direito.
        Nodo<T>* auxRightSon = root->filhoDireita;

        if(auxRightSon->filhoEsquerda != NULL) //Checa se filho direito possui algum filho esquerdo.
        {
            //Se tiver, salvo o endereço desse filho esquerdo.
            
            Nodo<T>* auxLeftSonOfRightSon = root->filhoDireita->filhoEsquerda;

            root->filhoDireita = auxLeftSonOfRightSon;
            auxRightSon->filhoEsquerda = root; 
           
        }
        else
        {
            //Caso contrário, apenas o antigo filho direito terá como novo filho a esquerda seu antigo pai.

            root->filhoDireita = NULL;
            auxRightSon->filhoEsquerda = root;

        }
        
        auxRightSon->altura = setNewHeight(auxRightSon);
        root->altura = setNewHeight(root);

        return auxRightSon; //Nova raiz da subArvore.
        
    }

    Nodo<T>* rightRotation(Nodo<T>* root)
    {
        //Salva o endereço do filho esquerdo.
        Nodo<T>* auxLeftSon = root->filhoEsquerda;

        if(auxLeftSon->filhoDireita != NULL)//Checa se filho esquerdo possui algum filho direito.
        {
            //Se tiver, salvo o endereço desse filho direito.
            
            Nodo<T>* auxRightSonOfLeftSon = root->filhoEsquerda->filhoDireita;

            root->filhoEsquerda = auxRightSonOfLeftSon;
            auxLeftSon->filhoDireita = root;
        }
        else
        {
            //Caso contrário, apenas o antigo filho esquerdo terá como novo filho a direita seu antigo pai.
            
            root->filhoEsquerda = NULL;
            auxLeftSon->filhoDireita = root;
        }
        
        auxLeftSon->altura = setNewHeight(auxLeftSon);
        root->altura = setNewHeight(root);

        return auxLeftSon; //Nova raiz da subArvore.
    }

    Nodo<T>* leftRightRotation(Nodo<T>* root)
    {
        //Salva o endereço do filho esquerdo.
        Nodo<T>* auxLeftSon = root->filhoEsquerda;
        
        //Salva o endereço do filho direito do filho esquerdo.
        Nodo<T>* auxRightSonOfLeftSon = root->filhoEsquerda->filhoDireita;

        //Primeira Rotação:
        
        if(auxRightSonOfLeftSon->filhoEsquerda != NULL)
        {
            
            auxLeftSon->filhoDireita = auxRightSonOfLeftSon->filhoEsquerda;
            auxRightSonOfLeftSon->filhoEsquerda = auxLeftSon;
            root->filhoEsquerda = auxRightSonOfLeftSon;

        }
        else
        {
            auxLeftSon->filhoDireita = NULL;
            auxRightSonOfLeftSon->filhoEsquerda = auxLeftSon;
            root->filhoEsquerda = auxRightSonOfLeftSon;
        }

        //Segunda Rotação:
        
        if(auxRightSonOfLeftSon->filhoDireita != NULL)
        {
            root->filhoEsquerda = auxRightSonOfLeftSon->filhoDireita;
            auxRightSonOfLeftSon->filhoDireita = root;
        }
        else
        {
            root->filhoEsquerda = NULL;
            auxRightSonOfLeftSon->filhoDireita = root;
        }
        
        auxRightSonOfLeftSon->altura = setNewHeight(auxRightSonOfLeftSon);
        root->altura = setNewHeight(root);
        auxLeftSon->altura = setNewHeight(auxLeftSon);

        return auxRightSonOfLeftSon; //Nova raiz da subArvore.
        
    }

    Nodo<T>* rightLeftRotation(Nodo<T>* root)
    {
        //Salva endereço do filho direito.
        Nodo<T>* auxRightSon = root->filhoDireita;

        //Salva endereço do filho esquerdo do filho direito.
        Nodo<T>* auxLeftSonOfRightSon = root->filhoDireita->filhoEsquerda;

        //Primeira Rotação:
        
        if(auxLeftSonOfRightSon->filhoDireita != NULL)
        {
            auxRightSon->filhoEsquerda = auxLeftSonOfRightSon->filhoDireita;
            auxLeftSonOfRightSon->filhoDireita = auxRightSon;
            root->filhoDireita = auxLeftSonOfRightSon;
        }
        else
        {
            auxRightSon->filhoEsquerda = NULL;
            auxLeftSonOfRightSon->filhoDireita = auxRightSon;
            root->filhoDireita = auxLeftSonOfRightSon;
        }

        //Segunda Rotação:

        if(auxLeftSonOfRightSon->filhoEsquerda != NULL)
        {
            root->filhoDireita = auxLeftSonOfRightSon->filhoEsquerda;
            auxLeftSonOfRightSon->filhoEsquerda = root;
        }
        else
        {
            root->filhoDireita = NULL;
            auxLeftSonOfRightSon->filhoEsquerda = root;
        }

        auxLeftSonOfRightSon->altura = setNewHeight(auxLeftSonOfRightSon);
        root->altura = setNewHeight(root);
        auxRightSon->altura = setNewHeight(auxRightSon);

        return auxLeftSonOfRightSon; //Nova raiz da subArvore.
    }

    /*
        4 tipos de Rotações:
        
            1 - Rotação Simples Esquerda:
                -> Será realizada quando fator de balanceamento do nodo < -1 e filho direito tiver fator de balanceamento <= 0.
            
            2 - Rotação Simples Direita:
                -> Será realizada quando fator de balanceamento do nodo > 1 e filho esquerdo tiver fator de balanceamento => 0.

            3 - Rotação Dupla (Esquerda-Direita): 
                -> Será realizada quando fator de balanceamento do nodo > 1 e filho esquerdo tiver fator de balanceamento < 0.

             4 - Rotação Dupla (Direita-Esquerda): 
                -> Será realizada quando fator de balanceamento do nodo < -1 e filho esquerdo tiver fator de balanceamento > 0.

            obs: Valor Negativo informa que a arvore está desbalanciada pra direita e Valor positivo informa que a arvore está balanceada pra esqueda.
    
    */
    
    Nodo<T>* rotation(Nodo<T>* root)
    {
        int balancefactor = bFCalculation(root);

        if(balancefactor < -1 && bFCalculation(root->filhoDireita) <= 0)
        {
            root = leftRotation(root);
        }
        else if(balancefactor > 1 && bFCalculation(root->filhoEsquerda) >= 0)
        {
            root = rightRotation(root);
        }
        else if(balancefactor > 1 && bFCalculation(root->filhoEsquerda) < 0)
        {
            root = leftRightRotation(root);
        }
        else if(balancefactor < -1 && bFCalculation(root->filhoDireita) > 0)
        {
            root = rightLeftRotation(root);
        }

        return root;
        
    }
    
    Nodo<T>* insert(Nodo<T> *root, T chave)
    {
        if(root == NULL)
        {
            return newNode(chave);
        }
        else
        {
            if(chave < root->chave)
            {
                root->filhoEsquerda = this->insert(root->filhoEsquerda, chave);
            }
            else
            {
                root->filhoDireita = this->insert(root->filhoDireita, chave);
            }
        }

        root->altura = setNewHeight(root);

        root = rotation(root);
        
        return root;

    }
    

    virtual void inserir(T chave) 
    {
        this->raiz = insert(this->raiz, chave);
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * 
     */        

    /*
        4 situações para remoção de um nodo:
        1 - Nodo sem filhos (folha);
        2 - Nodo apenas com filho esquerdo;
        3 - Nodo apenas com filho direto;
        4 - Nodo com ambos os filhos.
        
    */
    Nodo<T>* RecalcHeightAndCheckRotation(Nodo<T>* root)
    {
        root->altura = setNewHeight(root);
        root = rotation (root);

        return root;
    }
    
    
    Nodo<T>* delationOfRoot(Nodo<T>* root, T chave)
    {
        if(root->filhoDireita == NULL && root->filhoEsquerda == NULL)//Caso 1: Raiz sem filhos.
        {
            delete root;
            return NULL;
        }
        else if(root->filhoEsquerda != NULL && root->filhoDireita == NULL)//Caso 2: Raiz sem filho a esquerda.
        {
            Nodo<T>* newRoot = root->filhoEsquerda;
            delete root;
            newRoot = RecalcHeightAndCheckRotation(newRoot);
            return newRoot;
        }
        else if(root->filhoDireita != NULL && root->filhoEsquerda == NULL) //Caso 3: Raiz contem apenas filho direito.
        {
            Nodo<T>* newRoot = root->filhoDireita;
            delete root;
            
            newRoot = RecalcHeightAndCheckRotation(newRoot);
            return newRoot;
        }
        else //Caso 4: Raiz com 2 filhos.
        {
            Nodo<T>* auxLeftSon = root->filhoDireita; //Será nova raiz.
            Nodo<T>* dadaux = root; //Auxiliará na remoção.
               
            while(auxLeftSon->filhoEsquerda != NULL) //Buscar o "menor filho dos maiores" da raiz.
            {
                dadaux = auxLeftSon;
                auxLeftSon = auxLeftSon->filhoEsquerda;
            }
            
            if(dadaux->chave != root->chave) //Se dadaux andou alguma vez, ou seja, auxLeftSon (q começa como raiz da subarvore a direita), tiver algum filho a esquerda:
            {
           
                auxLeftSon->filhoEsquerda = root->filhoEsquerda; //Arvoré a esquerda da raiz, q não se alterará, é apontada pela nova raiz.(sei q auxLeftSon n tem filho a esquerda por condição do while)
            
                if(auxLeftSon->filhoDireita != NULL) //Se auxLeftSon (nova raiz), tiver algum filho a direita:
                {
                    dadaux->filhoEsquerda = auxLeftSon->filhoDireita; //Pai do auxLeftSon aponta pro filho.
                }
                else
                {
                     dadaux->filhoEsquerda = NULL; // Pai do auxLeftSon recebe nulo (n tinha filho algum).
                }
                
                auxLeftSon->filhoDireita = root->filhoDireita; //Nova raiz recebe subarvore a direita
                delete root; //antiga raiz é excluida.

                auxLeftSon = RecalcHeightAndCheckRotation(auxLeftSon); //Recalculo da altura e possivel rotação da nova raiz.

                auxLeftSon->filhoDireita = RecalcHeightAndCheckRotation(auxLeftSon->filhoDireita); //Recalculo da Altura e possivel rotação da subarvore a direita.

                dadaux = auxLeftSon->filhoEsquerda;

                while(dadaux->filhoEsquerda != NULL)//Recalculo da altura e possivel rotação de todas as subarvores q passei em busca da nova raiz da arvore.
                {
                    dadaux = RecalcHeightAndCheckRotation(dadaux);
                    dadaux = dadaux->filhoEsquerda;
                }

                return auxLeftSon; //Retorno nova arvore.
            }
            else //Se dadaux ainda é a raiz.
            {
                auxLeftSon->filhoEsquerda = root->filhoEsquerda; //Arvoré a esquerda da raiz, q não se alterará, é apontada pela nova raiz.(sei q auxLeftSon n tem filho a esquerda por condição do while)

                if(root->filhoDireita->filhoDireita != NULL)//Check se subarvore a direita tem algum filho a direita.
                {
                    auxLeftSon->filhoDireita = root->filhoDireita->filhoDireita;//Se tem, nova raiz aponta pra ela.
                    delete root; //Deleta antiga raiz.
                }
                else
                {
                    auxLeftSon->filhoDireita = NULL; //Se não subarvore a direita é nula, nova raiz recebe null.
                    delete root;//Deleta antiga raiz.
                }

                auxLeftSon = RecalcHeightAndCheckRotation(auxLeftSon); //Recalculo da altura e possivel rotação da arvore.
                
                if(auxLeftSon->filhoDireita != NULL)//Se subarvore a direita existir, recalculo a altura dela e check de rotação.
                {
                    auxLeftSon->filhoDireita = RecalcHeightAndCheckRotation(auxLeftSon->filhoDireita);
                }

                return auxLeftSon; //retorno nova raiz.
            }
        }
        
    }
    
    
    Nodo<T>* delation(Nodo<T>* root, Nodo<T>* fatherOfRoot, T chave)
    {
        if(root == NULL)
        {
            return fatherOfRoot; //Raiz não está contida na arvore.
        }

        if(root->chave == chave)
        {
            if(fatherOfRoot == NULL)
            {
                return delationOfRoot(root, chave); //Deleção de raiz.
            }
            
            
            if(root->filhoDireita == NULL && root->filhoEsquerda == NULL)//Caso 1: Nodo sem filhos, nodo eh folha.
            {
                if(root->chave < fatherOfRoot->chave)
                {
                    delete root;
                    fatherOfRoot->filhoEsquerda = NULL;
                }
                else
                {
                    delete root;
                    fatherOfRoot->filhoDireita = NULL;
                }

                return fatherOfRoot;
            }
            else if(root->filhoEsquerda != NULL && root->filhoDireita == NULL)//Caso 2: Nodo contem apenas filho esquerdo.
            {
                if(root->chave < fatherOfRoot->chave)
                {
                    fatherOfRoot->filhoEsquerda = root->filhoEsquerda;
                    delete root;
                    return fatherOfRoot;
                }
                else
                {
                    fatherOfRoot->filhoDireita = root->filhoEsquerda;
                    delete root;
                    return fatherOfRoot;
                }
            }
            else if(root->filhoDireita != NULL && root->filhoEsquerda == NULL) //Caso 3: Nodo contem apenas filho direito.
            {
                if(root->chave < fatherOfRoot->chave)
                {
                    fatherOfRoot->filhoEsquerda = root->filhoDireita;
                    delete root;
                    return fatherOfRoot;
                }
                else
                {
                    fatherOfRoot->filhoDireita = root->filhoDireita;
                    delete root;
                    return fatherOfRoot;
                }
            }
            else//Caso 4: Nodo com 2 filhos.
            {
                if(root->chave < fatherOfRoot->chave)
                {
                    Nodo<T>* auxLeftSon = root->filhoDireita;
               
                    while(auxLeftSon->filhoEsquerda != NULL) //Buscar o "menor filho dos maiores" de nodo que vou excluir.
                    {
                        auxLeftSon = auxLeftSon->filhoEsquerda;
                    }

                    if(auxLeftSon != root->filhoDireita)
                    {
                        auxLeftSon->filhoEsquerda = root->filhoEsquerda; //'auLeftSon' se torna a nova raiz da subarvore, aponta pra ambos os filho do nó.
                        auxLeftSon->filhoDireita = root->filhoDireita;
                        fatherOfRoot->filhoEsquerda = auxLeftSon; //pai do nó aponta pra nova raiz cm filho esq. já que nova raiz é menor.
                        delete root;
                        return fatherOfRoot;
                    }
                    else
                    {
                        auxLeftSon->filhoEsquerda = root->filhoEsquerda;//'auLeftSon' se torna a nova raiz da subarvore, aponta só para um dos filhos, já que já aponta pro outro.
                        fatherOfRoot->filhoEsquerda = auxLeftSon;//pai do nó aponta pra nova raiz cm filho esq. já que nova raiz é menor.
                        delete root;
                        return fatherOfRoot;
                    }
                    
                }
                else
                {
                    Nodo<T>* auxLeftSon = root->filhoDireita;
               
                    while(auxLeftSon->filhoEsquerda != NULL) //Buscar o "menor filho dos maiores" de nodo que vou excluir.
                    {
                        auxLeftSon = auxLeftSon->filhoEsquerda;
                    }

                    if(auxLeftSon != root->filhoDireita)
                    {
                        auxLeftSon->filhoEsquerda = root->filhoEsquerda;
                        auxLeftSon->filhoDireita = root->filhoDireita;
                        fatherOfRoot->filhoDireita = auxLeftSon;
                        delete root;
                        return fatherOfRoot;
                    }
                    else
                    {
                        auxLeftSon->filhoEsquerda = root->filhoEsquerda;
                        fatherOfRoot->filhoDireita = auxLeftSon;
                        delete root;
                        return fatherOfRoot;
                    }
                }
                    
            }
        }
        else if(chave < root->chave)//Procura chave.
        {
            root = this->delation(root->filhoEsquerda, root, chave);
        }
        else
        {
            root = this->delation(root->filhoDireita, root, chave);
        }

        if(fatherOfRoot != NULL) //Se pai da raiz existir, recalcula sua altura e dos filhos e check de rotação do pai da raiz e dos filhos, se filhos ainda existirem.
        {
            fatherOfRoot = RecalcHeightAndCheckRotation(fatherOfRoot);

            if(fatherOfRoot->filhoDireita != NULL)
            {
                fatherOfRoot->filhoDireita = RecalcHeightAndCheckRotation(fatherOfRoot->filhoDireita);
            }

            if(fatherOfRoot->filhoEsquerda != NULL)
            {
                fatherOfRoot->filhoEsquerda = RecalcHeightAndCheckRotation(fatherOfRoot->filhoEsquerda);
            }
            
            return fatherOfRoot;
        }
        else //Se não recalculo a altura apenas da raiz.
        {
            root = RecalcHeightAndCheckRotation(root);

            return root;
        }

    }
   
    virtual void remover(T chave)
    {
        Nodo<T>* fatherOfRoot = NULL;
        this->raiz = delation(this->raiz, fatherOfRoot, chave);
    }
    
    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    
    std::optional<T> searchKeyLeftSon(Nodo<T> *root, T chave) const
    {
        if(root == NULL)
        {
            return std::nullopt;
        }

        if(root->chave == chave)
        {
            if(root->filhoEsquerda == NULL)
            {
                return std::nullopt;
            }
            else
            {
                return root->filhoEsquerda->chave;
            }
        }
        else if(chave < root->chave)
        {
            return this->searchKeyLeftSon(root->filhoEsquerda, chave);
        }
        else
        {
            return this->searchKeyLeftSon(root->filhoDireita, chave);
        }


    }
    
    virtual std::optional<T> filhoEsquerdaDe(T chave) const 
    {
        return searchKeyLeftSon(this->raiz, chave);
    }

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
     std::optional<T> searchKeyRightSon(Nodo<T> *root, T chave) const
    {
        if(root == NULL)
        {
            return std::nullopt;
        }

        if(root->chave == chave)
        {
            if(root->filhoDireita == NULL)
            {
                return std::nullopt;
            }
            else
            {
                return root->filhoDireita->chave;
            }
        }
        else if(chave < root->chave)
        {
            return this->searchKeyRightSon(root->filhoEsquerda, chave);
        }
        else
        {
            return this->searchKeyRightSon(root->filhoDireita, chave);
        }

    }
    
    virtual std::optional<T> filhoDireitaDe(T chave) const 
    {
        return searchKeyRightSon(this->raiz, chave);
    }
    
    /*  
        Percoreendo uma árvore em ordem, temos:

        1º Na metade a esquerda da raiz:
        
        1.1 Encontrar a subarvore mais a esquerda (extremo esquerdo da AV);
        1.2 Inserir elementos na seguinte ordem: Filho a esquerda, pai, filho a direita;

        2º Na metade a direita da raiz:

        2.1 Encontrar a subarvore mais a esquerda ('praticamente' meio da AV);
        2.2 Inserir elementos na seguinte ordem: Filho a esquerda, pai, filho a direita;

        Se temos a seguinte árvore:

                10
                /\
               7   19  
              /\   /\
             4  8 12 25
             \
              6

        Ao percorrer em ordem, temos: 4-6-7-8-10-12-19-25

        left-center-right;
    */     
    
    ListaEncadeadaAbstrata<T>* inOrderConverter(Nodo<T> *root,ListaEncadeadaAbstrata<T> *inOrderList) const
    {
        if(root != NULL)
        {
            this->inOrderConverter(root->filhoEsquerda, inOrderList);
            inOrderList->inserirNoFim(root->chave);
            this->inOrderConverter(root->filhoDireita, inOrderList);
        }

        return inOrderList;
       
    }
    
    
    virtual ListaEncadeadaAbstrata<T>* emOrdem() const 
    {
        
        ListaEncadeadaAbstrata<T> *inOrderList = new MinhaListaEncadeada<T>();

        if(this->raiz == NULL)
        {
            return inOrderList;
        }

        return inOrderConverter(this->raiz, inOrderList);
    }

    /*
        Percoreendo uma árvore em pré-ordem, temos:

        1º Na metade à esquerda da raiz:
        
        1.1 Vai inserindo todos os nodos q for passando até chegar na subarvore mais a esquerda (Extremo esquerdo da AV);
        1.2 Ao encontrar a subrvore mais a esquerda, insere o filho da esquerda e então o filho da direita;
        1.3 Inserá elementos na seguinte ordem: pai, filho esquerda, filho direita.

        2º Na metade à direita da raiz:

        2.1 Vai inserindo todos os nodos q for passando até chegar na subarvore mais a esquerda('praticamente' meio da AV);
        2.2 Ao encontrar a subrvore mais a esquerda, insere o filho da esquerda e então o filho da direita;
        2.3 Inserá elementos na seguinte ordem: pai, filho esquerda, filho direita.
        
        Se temos a seguinte árvore:

                10
                /\
               7   19  
              /\   /\
             4  8 12 25
             \
              6

        Ao percorrer em pré-ordem, temos: 10-7-4-6-8-19-12-25

        center-left-right
    */     

    ListaEncadeadaAbstrata<T>* preOrderConverter(Nodo<T> *root,ListaEncadeadaAbstrata<T> *preOrderList) const
    {
        if(root != NULL)
        {
            preOrderList->inserirNoFim(root->chave);
            this->preOrderConverter(root->filhoEsquerda, preOrderList);
            this->preOrderConverter(root->filhoDireita, preOrderList);
        }

        return preOrderList;
    }


    virtual ListaEncadeadaAbstrata<T>* preOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *preOrderList = new MinhaListaEncadeada<T>();

        if(this->raiz == NULL)
        {
            return preOrderList;
        }

        return preOrderConverter(this->raiz, preOrderList);
    }

      /*
        Percoreendo uma árvore em pós-ordem, temos:

        1º Na metade à esquerda da raiz:
        
        1.1 Encontrar a subarvore mais a esquerda (extremo esquerdo da AV);
        1.2 Inserir elementos na seguinte ordem: Filho a esquerda, filho a direita e pai;

        2º Na metade à direita da raiz:

        2.1 Encontrar a subarvore mais a esquerda ('praticamente' meio da AV);
        2.2 Inserir elementos na seguinte ordem: Filho a esquerda, filho a direita e pai;
        
        Se temos a seguinte árvore:

                10
                /\
               7   19  
              /\   /\
             4  8 12 25
             \
              6

        Ao percorrer em pré-ordem, temos: 6-4-8-7-12-25-19-10

        left-right-center
    */     
    
    ListaEncadeadaAbstrata<T>* posOrderConverter(Nodo<T> *root,ListaEncadeadaAbstrata<T> *posOrderList) const
    {
        if(root != NULL)
        {
            this->posOrderConverter(root->filhoEsquerda, posOrderList);
            this->posOrderConverter(root->filhoDireita, posOrderList);
            posOrderList->inserirNoFim(root->chave);
        }

        return posOrderList;
    }
    
    
    virtual ListaEncadeadaAbstrata<T>* posOrdem() const
    {
        ListaEncadeadaAbstrata<T> *posOrderList = new MinhaListaEncadeada<T>();

        if(this->raiz == NULL)
        {
            return posOrderList;
        }

        return posOrderConverter(this->raiz, posOrderList);
    }
};

#endif

  