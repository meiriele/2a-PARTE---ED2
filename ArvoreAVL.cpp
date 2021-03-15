#include "ArvoreAVL.h"
#include<iostream>

using namespace std;

ArvoreAVL::ArvoreAVL()
{
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL()
{
    raiz = libera (raiz);
}

NoAVL* ArvoreAVL::libera (NoAVL*p)
{
    if(p!=nullptr)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p=nullptr;
    }
    return nullptr;
}

bool ArvoreAVL::vazia ()
{
    return raiz == nullptr;
}

bool ArvoreAVL::Busca (int val)
{
    return AuxBusca(raiz, val);
}

bool ArvoreAVL::AuxBusca (NoAVL* p, int val)
{
    if(p == nullptr)
        return false;
    else if(p->getID() == val)
        return p;
    else if(p->getID()<val)
        return AuxBusca(p->getEsq(),val);
    else
        return AuxBusca(p->getDir(),val);
}

NoAVL* ArvoreAVL:: AuxRetornaPonteiro (NoAVL* p, int val)
{
    if(p == nullptr)
    {
        return nullptr;
    }
    else if(p->getID() == val)
    {
        return p;
    }
    else if(p->getID()<val)
        return AuxRetornaPonteiro(p->getDir(),val);
    else
        return AuxRetornaPonteiro(p->getEsq(),val);
}

void ArvoreAVL::Insere (int val)
{
    raiz = AuxInsere(raiz,val, nullptr);
    AtualizaBalanceamento(AuxRetornaPonteiro(raiz,val));


}

NoAVL* ArvoreAVL::AuxInsere (NoAVL* p, int val, NoAVL* father)
{
    if(p == nullptr)
    {
        p = new NoAVL();
        p->setID(val);
        p->setFatbalance(0);
        p->setDir(nullptr);
        p->setEsq(nullptr);
        p->setPai(father);
    }
    else if (p->getID()<val)
        p->setDir(AuxInsere(p->getDir(),val,p));
    else
        p->setEsq(AuxInsere(p->getEsq(),val,p));
    return p;
}


void ArvoreAVL::AtualizaBalanceamento(NoAVL* no)
{
    if(no!= nullptr)
    {
        no->setFatbalance(AuxGetAltura(no->getDir()) - AuxGetAltura(no->getEsq()));
        //cout<<"ID: "<<no->getID()<<"  FATBALANCE: "<<no->getFatbalance()<<endl;
        if(no->getFatbalance() == -2)
        {
            no->getEsq()->setFatbalance(AuxGetAltura(no->getEsq()->getDir()) - AuxGetAltura(no->getEsq()->getEsq()));
            if(no->getEsq()->getFatbalance() == -1 || no->getEsq()->getFatbalance() == 0)
                RotacaoSimplesADireita(no);
            else if (no->getEsq()->getFatbalance() == 1)
                RotacaoDuplaADireita(no);
        }
        else if (no->getFatbalance() == 2)
        {
            no->getDir()->setFatbalance(AuxGetAltura(no->getDir()->getDir()) - AuxGetAltura(no->getDir()->getEsq()));
            if(no->getDir()->getFatbalance() == 1 || no->getDir()->getFatbalance() == 0 )
                RotacaoSimplesAEsquerda(no);
            else if (no->getDir()->getFatbalance() == -1)
                RotacaoDuplaAEsquerda(no);
        }
        else
            AtualizaBalanceamento(no->getPai());
    }
}

void ArvoreAVL:: RotacaoSimplesAEsquerda (NoAVL* p)
{
    NoAVL* q = p->getDir();
    p->setDir(q->getEsq());
    q->setEsq(p);
    NoAVL* aux = p->getPai();
    p->setPai(q);
    q->setPai(aux);
    if (aux != nullptr)
        aux->setDir(q);
    if(raiz == p)
        raiz =q;
    //cout<<"Rotacao Simples para a Esquerda!"<<endl;
}

void ArvoreAVL:: RotacaoSimplesADireita (NoAVL* p)
{
    NoAVL* q = p->getEsq();
    p->setEsq(q->getDir());
    q->setDir(p);
    NoAVL* aux = p->getPai();
    p->setPai(q);
    q->setPai(aux);
    if (aux != nullptr)
        aux->setEsq(q);
    if(raiz == p)
        raiz =q;
    //cout<<"Rotacao Simples para a Direita!"<<endl;
}

void ArvoreAVL:: RotacaoDuplaAEsquerda (NoAVL* p)
{
    NoAVL* q = p->getDir();
    NoAVL* r = q->getEsq();
    p->setDir(r->getEsq());
    q->setEsq(r->getDir());
    r->setEsq(p);
    r->setDir(q);
    NoAVL* aux = p->getPai();
    p->setPai(r);
    q->setPai(r);
    r->setPai(aux);
    if(raiz == p)
        raiz =r;
    else
    {
        r->getPai()->setEsq(r);
        r->getPai()->setFatbalance(r->getPai()->getDir()-r->getPai()->getEsq());
    }
    //cout<<"Rotacao Dupla para a Esquerda!"<<endl;
}

void ArvoreAVL:: RotacaoDuplaADireita (NoAVL* p)
{
    NoAVL* q = p->getEsq();
    NoAVL* r = q->getDir();
    p->setEsq(r->getDir());
    q->setDir(r->getEsq());
    r->setDir(p);
    r->setEsq(q);
    NoAVL* aux = p->getPai();
    p->setPai(r);
    q->setPai(r);
    r->setPai(aux);
    if(raiz == p)
        raiz =r;
    else
    {
        r->getPai()->setDir(r);
        r->getPai()->setFatbalance(r->getPai()->getDir()-r->getPai()->getEsq());
    }
    //cout<<"Rotacao Dupla para a Direita!"<<endl;
}

int ArvoreAVL::GetAltura()
{
    return AuxGetAltura(raiz);
}

int ArvoreAVL::AuxGetAltura(NoAVL* p)
{
    int he, hd;
    if (p == nullptr)
        return -1;
    else
    {
        he = AuxGetAltura(p->getEsq());
        hd = AuxGetAltura(p->getDir());
        return 1+(he>hd ? he: hd);
    }
}

void ArvoreAVL::ImprimeEmOrdem()
{
    AuxImprimeEmOrdem(raiz);
}

void ArvoreAVL::AuxImprimeEmOrdem(NoAVL* p)
{
    if (p!= nullptr)
    {
        cout<<p->getID()<<" esq ->";
        AuxImprimeEmOrdem(p->getEsq());
        cout<<" dir->";
        AuxImprimeEmOrdem(p->getDir());
    }
    else
        cout<<"NULL"<<endl;
}
