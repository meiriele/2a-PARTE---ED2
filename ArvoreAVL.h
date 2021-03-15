#include <bits/stdc++.h>
using namespace std;

struct NoAVL
{
    int data{};
    NoAVL* esq = nullptr;
    NoAVL* dir = nullptr;
    NoAVL* pai = nullptr;
    int altura;
};

class ArvoreAVL
{

    NoAVL* raiz;

public:
    ArvoreAVL() : raiz(nullptr) {}

    NoAVL* GetRaiz()
    {
        return raiz;
    }

    int max(int a, int b)
    {
        return (a > b ? a : b);
    }

    void InsertNo(int stuff)
    {
        if(raiz == nullptr)
        {
            raiz = new NoAVL();
            raiz->data = stuff;
            raiz->altura = 0;
            raiz->pai = nullptr;
        }
        else
        {
            auto linker = GetRaiz();
            NoAVL* newno = new NoAVL();
            newno->data = stuff;

            while(linker != nullptr)
            {
                if(linker->data > stuff)
                {
                    if(linker->esq == nullptr)
                    {
                        linker->esq = newno;
                        newno->altura = 0;
                        newno->pai = linker;
                        break;
                    }
                    else
                    {
                        linker = linker->esq;
                    }
                }
                else
                {
                    if(linker->dir == nullptr)
                    {
                        linker->dir = newno;
                        newno->altura = 0;
                        newno->pai = linker;
                        break;
                    }
                    else
                    {
                        linker = linker->dir;
                    }
                }
            }
            Rebalancer(newno);
        }
    }

    int GetAltura(NoAVL* temp)
    {
        return ((temp == nullptr) ? -1 : temp->altura);
    }

    int FatorDeBalanceamento(NoAVL* temp)
    {
        return (GetAltura(temp->dir) - GetAltura(temp->esq));
    }

    void AlturaBalance(NoAVL* temp)
    {
        int l = -1, r = -1;
        if(temp->esq)
        {
            l = temp->esq->altura;
        }
        if(temp->dir)
        {
            r = temp->dir->altura;
        }
        temp->altura = max(l, r) + 1;
    }

    void ArvoreFix(NoAVL* temp)
    {
        if(FatorDeBalanceamento(temp) == 2)
        {
            if(FatorDeBalanceamento(temp->dir) < 0)
            {
                RotacaoDireita(temp->dir);
            }
            RotacaoEsquerda(temp);
            AlturaBalance(temp);
        }
        else if(FatorDeBalanceamento(temp) == -2)
        {
            if(FatorDeBalanceamento(temp->esq) > 0)
            {
                RotacaoEsquerda(temp->esq);
            }
            RotacaoDireita(temp);
            AlturaBalance(temp);
        }
    }

    void Rebalancer(NoAVL* temp)
    {
        if(temp == raiz)
        {
            ArvoreFix(raiz);
        }
        else
        {
            while(temp != nullptr)
            {
                AlturaBalance(temp);
                temp = temp->pai;
                if(temp)
                {
                    ArvoreFix(temp);
                }
            }
        }
    }

    void RotacaoEsquerda(NoAVL* x)
    {
        NoAVL* nw_no = new NoAVL();
        if(x->dir->esq)
        {
            nw_no->dir = x->dir->esq;
        }
        nw_no->esq = x->esq;
        nw_no->data = x->data;
        x->data = x->dir->data;

        x->esq = nw_no;
        if(nw_no->esq)
        {
            nw_no->esq->pai = nw_no;
        }
        if(nw_no->dir)
        {
            nw_no->dir->pai = nw_no;
        }
        nw_no->pai = x;

        if(x->dir->dir)
        {
            x->dir = x->dir->dir;
        }
        else
        {
            x->dir = nullptr;
        }

        if(x->dir)
        {
            x->dir->pai = x;
        }

        AlturaBalance(x->esq);
        if(x->dir)
        {
            AlturaBalance(x->dir);
        }
        AlturaBalance(x);
    }

    void RotacaoDireita(NoAVL* x)
    {
        NoAVL* nw_no = new NoAVL();
        if(x->esq->dir)
        {
            nw_no->esq = x->esq->dir;
        }
        nw_no->dir = x->dir;
        nw_no->data = x->data;
        x->data = x->esq->data;

        x->dir = nw_no;
        if(nw_no->esq)
        {
            nw_no->esq->pai = nw_no;
        }
        if(nw_no->dir)
        {
            nw_no->dir->pai = nw_no;
        }
        nw_no->pai = x;

        if(x->esq->esq)
        {
            x->esq = x->esq->esq;
        }
        else
        {
            x->esq = nullptr;
        }

        if(x->esq)
        {
            x->esq->pai = x;
        }

        AlturaBalance(x->dir);
        if(x->esq)
        {
            AlturaBalance(x->esq);
        }
        AlturaBalance(x);
    }

    NoAVL* Busca(int stuff)
    {
        auto temp = GetRaiz();
        if(temp == nullptr)
        {
            return nullptr;
        }

        while(temp)
        {
            if(stuff == temp->data)
            {
                return temp;
            }
            else if(stuff < temp->data)
            {
                temp = temp->esq;
            }
            else
            {
                temp = temp->dir;
            }
        }
        return nullptr;
    }

    void PreOrdemTraversal(NoAVL* temp)
    {
        if(temp == nullptr)
        {
            return;
        }
        cout << "->" << temp->data;
        PreOrdemTraversal(temp->esq);
        PreOrdemTraversal(temp->dir);
    }

    void PosOrdemTraversal(NoAVL *temp)
    {
        if(temp == nullptr)
        {
            return;
        }
        PosOrdemTraversal(temp->esq);
        PosOrdemTraversal(temp->dir);
        cout << "->" << temp->data;
    }


void ImprimeEmOrdem(NoAVL* p)
{
    if (p!= nullptr)
    {
        cout<<p->data<<" esq ->";
        ImprimeEmOrdem(p->esq);
        cout<<" dir->";
        ImprimeEmOrdem(p->dir);
    }
    else
        cout<<"NULL"<<endl;
}

};

