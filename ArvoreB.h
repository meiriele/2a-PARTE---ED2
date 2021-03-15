#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include <iostream>

class NoB
{
    int *chave; // ponteiro que aponta pra um vetor com as chaves
    int d;          // grau minimo
    NoB **C;       // ponteiro que aponta pra um vetor de ponteiros com os filhos
    int n;          // Numero de nos atuais
    bool folha;        // booleano verificar se é folha

public:
    NoB(int di, bool folha1)    // construtor do Nó que recebe a ordem e se é uma folha
    {   d = di;
        folha = folha1;
        chave = new int [2 * d - 1];       //aloca memoria para o num max de chaves
        C = new NoB *[2 * d];                   //aloca memoria para o num max de filhos
        n = 0;
    };

    // Função que procura um  chave, ela é um ponteiro e percorre a arvore usando a estrategia binaria
    NoB *procuraAux(int k, long int *numCopias, long int *numComparacoes)
    {   int i = 0;
    //encontra a primeira chave maior e
        while (i < n && k > chave[i])
            i++;

        (*numComparacoes)+=i;
        //se a chave encontrada eh igual a k, retorna esse nó
        (*numComparacoes)++;
        if (chave[i] == k)
            return this;

        if (folha == true)          //se a chave nao eh encontrada e o no atual eh folha, retorna NULL
            return NULL;
        //vai para o filho aprorpiado
        return C[i]->procuraAux(k, numCopias, numComparacoes);
    };

    // Insere num vetor que tem espaço sobrando, onde ele simplismente precisa achar a
    // posição necessaria e inserir. Funcao chamada quando o nno nao esta cheio
    void insereNaoCheio(int k, long int *numCopias, long int *numComparacoes)
    {
        int i = n - 1;      //inicializa com o elemento mais a direita
        if (folha == true)  //se for uma folha
        {   //loop para encontrar a localizacao da nova chave a ser inserida e mover todas as chaves maiores
            //que k uma posicao a frente.
            while (i >= 0 && chave[i] > k)
            {
                chave[i + 1] = chave[i];
                (*numCopias)++;
                (*numComparacoes)++;

                i--;
            }
            //insere a nova chave na posicao encontra
            chave[i + 1] = k;
            (*numCopias)++;
            n = n + 1;
        }
        else        //se o no nao eh folha
        {           //encontra o filho que vai receber a nova chave
            while (i >= 0 && chave[i] > k)
            {
                i--;
                (*numComparacoes)++;
            }
            //confere se o filho encontrado esta cheio
            if (C[i + 1]->n == 2 * d - 1)
            {
                divideFilho(i + 1, C[i + 1], numCopias, numComparacoes);       //caso o filho esteja cheio

            // Depois de  dividir,  a chave do meio de C[i] sobe e
            // C[i] eh partido em 2. Conferir qual dos dois irá receber a nova chave
                (*numComparacoes)++;
                if (chave[i + 1] < k)
                    i++;
            }
            C[i + 1]->insereNaoCheio(k, numCopias, numComparacoes);
        }
    };
    // Dá o split do filho pra inserção de um novo valor, a função dá um split classico onde ele
    //divide o filho em dois, encaixa o valor requerido e depois retorna os dois vetores e qual numero irá "subir"
    void divideFilho(int i, NoB *y, long int *numCopias, long int *numComparacoes)
    {   //cria um novo no para guardar d-1 chaves de y
        NoB *z = new NoB (y->d, y->folha);
        z->n = d - 1;

        for (int j = 0; j < d - 1; j++)     //copias as ultimas d-1 chaves de y para z
        {
            z->chave[j] = y->chave[j + d];
            (*numCopias)++;
        }

        if (y->folha == false)      //copia o ultimo d filho de y para z
        {
            for (int j = 0; j < d; j++){
                z->C[j] = y->C[j + d];
                (*numCopias)++;
            }

        }

        y->n = d - 1;       //diminui o numero de chaves em y

        for (int j = n; j >= i + 1; j--)        //como o no recebera um novo filho, cria um espaco para o nvo filho
        {
            C[j + 1] = C[j];
            (*numCopias)++;
        }

        C[i + 1] = z;       //inclui o novo filho ao no
        (*numCopias)++;

        //agora uma chave de y se movera para o no
        //encontra a posicao da nova chave e move todas as chaves maiores pra frente
        for (int j = n - 1; j >= i; j--)
        {
            chave[j + 1] = chave[j];
            (*numCopias)++;
        }
        //copia  a chave do meio de y para o no
        chave[i] = y->chave[d - 1];
        (*numCopias)++;

        n = n + 1;      //incrementa o contador de chave no no
    };

    // função que percorre a arvore e imprime os Ids de cada dado armazenado nela
    void percorreSubArvore()
    {   int i;
        for (i = 0; i < n; i++)
        {
            //se o no nao eh folha, antes de imprimir a chave[i], percorre a subarvore enraizada com o filho[i]
            if (folha == false)
                C[i]->percorreSubArvore();
            cout <<" "<<chave[i];
        }
        //imprime a subarvore enraizada com o ulimo filho
        if (folha == false)
            C[i]->percorreSubArvore();
        cout<<endl;
    };

    friend class ArvoreB; //Marcando a arvore que usa esses nós como "amiga" para permiti-la usar os seus privados
};


class ArvoreB
{
    private:
        NoB *raiz; //ponteiro pra raiz
        int t;           // grau minimo
        long int numComparacoes;
        long int numCopias;

  public:
      ArvoreB(int _t) //construtor arvore
      {
          raiz = NULL;          //raiz recebe NULL
          t = _t;               //grau minimo da arvore(d)
      }
      // função que percorre a arvore chamando a função equivalente no Nó, começando pela raiz
      void percorreArvore()
      {
          if (raiz != NULL)
              raiz->percorreSubArvore();
      }
      // função que procura um Nó arvore chamando a função equivalente no Nó
      NoB *procura(int k){
          return (raiz == NULL) ? NULL : raiz->procuraAux(k, &numCopias, &numComparacoes);
    }

    //Função que insere na arvore usando os metodos "inserenaocheio" e "dividefilho", implementadas no Nó
    void insert(int k)
    {
      if (raiz == NULL)
      { //aloca memoria para a raiz
          raiz = new NoB(t, true);
          raiz->chave[0] = k;       //insere a chave
          registraCopia();
          raiz->n = 1;          //atualiza o numero de chavesna raiz
      }
      else      //se arvore nao estiver vazia
      {
          if (raiz->n == 2 * t - 1)         //se a raiz está cheia, entao a arvore ira crescer em altura
          {
              NoB *s = new NoB(t, false);       //aloca memoria para nova raiz

              s->C[0] = raiz;                 //antiga raiz vira filha da nova raiz
              registraCopia();

              s->divideFilho(0, raiz,&numCopias, &numComparacoes);         //divide a antiga raiz e sobe uma chave para a nova raiz

              int i = 0;                    //agora a nova raiz tem 2 filhos, e precisa escolher qual deles ficara nova chave

              registraComparacao();
              if (s->chave[0] < k)
                  i++;

              s->C[i]->insereNaoCheio(k, &numCopias, &numComparacoes);

              raiz = s;     //muda a raiz
          }
          else  //se a raiz nao  estiver cheia. chama a funcao inserirNaoCheio pra ela
              raiz->insereNaoCheio(k, &numCopias, &numComparacoes);
      }
  }


    // obetem o  numero de comparacoes
    // retorna int

    long int getNumComparacoes(){
        return numComparacoes;
    }


    // Obtem o numero de copias
    // retorna int
    long int getNumCopias(){
        return numCopias;
    }

    // Reseta os contadores de estatisticas
    void resetContadores(){
        numComparacoes = 0;
        numCopias = 0;
    }


    // Registra a comparacao, esse metodo deve ser chamado no codigo onde
    // tiver uma comparação entre elementos da arvore
    void registraComparacao(){
        numComparacoes++;
    }


    // Registra a copia, esse metodo deve ser chamado no codigo onde
    // tiver uma copia entre elementos da arvore
    void registraCopia(){
        numCopias++;
    }
};



#endif // ARVOREB_H_INCLUDED

