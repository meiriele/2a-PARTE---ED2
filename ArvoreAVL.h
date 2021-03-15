#ifndef ARVOREAVL_H
#define ARVOREAVL_H
#include<NoAVL.h>


class ArvoreAVL
{
    public:
        ArvoreAVL();
        ~ArvoreAVL();
        bool Busca (int val);
        bool vazia ();
        void Insere (int val);
        int GetAltura();
        void ImprimeEmOrdem();

    protected:

    private:
        NoAVL* raiz;

        NoAVL* libera (NoAVL*p);
        bool AuxBusca (NoAVL* p, int val);
        NoAVL* AuxInsere (NoAVL* p, int val, NoAVL* father);
        int AuxGetAltura(NoAVL* p);
        void AuxImprimeEmOrdem(NoAVL* p);
        void AtualizaBalanceamento(NoAVL* no);
        void RotacaoSimplesAEsquerda (NoAVL* p);
        void RotacaoSimplesADireita (NoAVL* p);
        void RotacaoDuplaAEsquerda (NoAVL* p);
        void RotacaoDuplaADireita (NoAVL* p);
        NoAVL* AuxRetornaPonteiro (NoAVL* p, int val);
};

#endif // ARVOREAVL_H
