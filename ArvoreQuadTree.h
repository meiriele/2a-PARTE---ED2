#ifndef ARVOREQUADTREE_H
#define ARVOREQUADTREE_H
#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include <string>
#include"NoQuadTree.h"


using namespace std;


class ArvoreQuadTree
{
    public:
        ArvoreQuadTree();
        ~ArvoreQuadTree();
        NoQuadTree* Busca (Covid19_coord val);
        void Insere (Covid19_coord val);
        void ImprimeEmOrdem ();

    protected:

    private:
        NoQuadTree* raiz;


        NoQuadTree* AuxBusca(NoQuadTree* p, Covid19_coord val);
        NoQuadTree* Libera (NoQuadTree* p);
        NoQuadTree* AuxInsere (NoQuadTree* p, Covid19_coord val);
        void AuxImprimeEmOrdem(NoQuadTree* p);

};

#endif // ARVOREQUADTREE_H
