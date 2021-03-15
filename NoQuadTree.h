#ifndef NOQUADTREE_H
#define NOQUADTREE_H
#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include <string>


using namespace std;

typedef struct
{
    int codigoDoEstado;
    int codigoDaCidade;
    string cidade;
    float lat;
    float lon;
    string capital;
} Covid19_coord;

class NoQuadTree
{
    public:
        NoQuadTree();
        ~NoQuadTree();
        Covid19_coord GetCampo();
        float GetCoordX();
        float GetCoordY();
        NoQuadTree* GetFilhoNW();
        NoQuadTree* GetFilhoNE();
        NoQuadTree* GetFilhoSW();
        NoQuadTree* GetFilhoSE();
        void SetCampo(Covid19_coord p);
        void SetCoordX(float p);
        void SetCoordY(float p);
        void SetFilhoNW(NoQuadTree*p);
        void SetFilhoNE(NoQuadTree*p);
        void SetFilhoSW(NoQuadTree*p);
        void SetFilhoSE(NoQuadTree*p);

    protected:

    private:
        Covid19_coord campo;
        float x;
        float y;
        NoQuadTree* nw;
        NoQuadTree* ne;
        NoQuadTree* sw;
        NoQuadTree* se;
};

#endif // NOQUADTREE_H
