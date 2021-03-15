#include "ArvoreQuadTree.h"

ArvoreQuadTree::ArvoreQuadTree()
{
    raiz = nullptr;
}

ArvoreQuadTree::~ArvoreQuadTree()
{
    raiz = Libera (raiz);
}

NoQuadTree* ArvoreQuadTree:: Libera (NoQuadTree* p)
{
    if (p != nullptr)
    {
        p->SetFilhoNE(Libera(p->GetFilhoNE()));
        p->SetFilhoNW(Libera(p->GetFilhoNW()));
        p->SetFilhoSE(Libera(p->GetFilhoSE()));
        p->SetFilhoSW(Libera(p->GetFilhoSW()));
        delete p;
        p = nullptr;
    }
    return nullptr;
}

NoQuadTree* ArvoreQuadTree::Busca (Covid19_coord val)
{
    return AuxBusca(raiz,val);
}

NoQuadTree* ArvoreQuadTree::AuxBusca(NoQuadTree* p, Covid19_coord val)
{
    if (p == nullptr)
    {
        cout<<"CIDADE NAO ESTA NA ARVORE!"<<endl;
        return nullptr;
    }
    else if( p->GetCampo().codigoDaCidade == val.codigoDaCidade)
    {
        cout<<"CIDADE ENCONTRADA!"<<endl;
        return p;
    }
    else if(val.lat > p->GetCoordX() && val.lon <= p->GetCoordY())
        return AuxBusca(p->GetFilhoNW(),val);
    else if(val.lat > p->GetCoordX() && val.lon > p->GetCoordY())
        return AuxBusca(p->GetFilhoNE(),val);
    else if(val.lat <= p->GetCoordX() && val.lon <= p->GetCoordY())
        return AuxBusca(p->GetFilhoSW(),val);
    else if(val.lat <= p->GetCoordX() && val.lon > p->GetCoordY())
        return AuxBusca(p->GetFilhoSE(),val);
    else
        cout<<"Confere que deu alguma zebra nessa busca!"<<endl;
    return nullptr;
}

void ArvoreQuadTree::Insere (Covid19_coord val)
{
    raiz = AuxInsere(raiz,val);
}

NoQuadTree* ArvoreQuadTree::AuxInsere (NoQuadTree* p, Covid19_coord val)
{
    if (p == nullptr)
    {
        p = new NoQuadTree();
        p->SetCampo(val);
        p->SetCoordX(val.lat);
        p->SetCoordY(val.lon);
        p->SetFilhoNE(nullptr);
        p->SetFilhoNW(nullptr);
        p->SetFilhoSE(nullptr);
        p->SetFilhoSW(nullptr);
    }
    else if(val.lat <  p->GetCoordX())
    {
        if(val.lon < p->GetCoordY())
            p->SetFilhoSW(AuxInsere(p->GetFilhoSW(),val));
        else
            p->SetFilhoSE(AuxInsere(p->GetFilhoSE(),val));
    }
    else
    {
        if(val.lon< p->GetCoordY())
            p->SetFilhoNW(AuxInsere(p->GetFilhoNW(),val));
        else
            p->SetFilhoNE(AuxInsere(p->GetFilhoNE(),val));
    }
    return p;
}

void ArvoreQuadTree::AuxImprimeEmOrdem(NoQuadTree* p)
{
    if (p!= nullptr)
    {
        cout<<p->GetCampo().cidade<<" NE ->";
        AuxImprimeEmOrdem(p->GetFilhoNE());
        cout<<" SE->";
        AuxImprimeEmOrdem(p->GetFilhoSE());
        cout<<" SW->";
        AuxImprimeEmOrdem(p->GetFilhoSW());
        cout<<" NW->";
        AuxImprimeEmOrdem(p->GetFilhoNW());
    }
    else
        cout<<"NULL"<<endl;
}

void ArvoreQuadTree::ImprimeEmOrdem ()
{
        AuxImprimeEmOrdem(raiz);
}
