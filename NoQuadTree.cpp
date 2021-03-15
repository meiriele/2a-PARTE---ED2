#include "NoQuadTree.h"

NoQuadTree::NoQuadTree() { }

NoQuadTree::~NoQuadTree() { }

Covid19_coord NoQuadTree::GetCampo()
{
    return campo;
}

float NoQuadTree::GetCoordX()
{
    return x;
}

float NoQuadTree::GetCoordY()
{
    return y;
}

NoQuadTree* NoQuadTree::GetFilhoNW()
{
    return nw;
}

NoQuadTree* NoQuadTree::GetFilhoNE()
{
    return ne;
}

NoQuadTree* NoQuadTree::GetFilhoSW()
{
    return sw;
}

NoQuadTree* NoQuadTree::GetFilhoSE()
{
    return se;
}

void NoQuadTree::SetCampo(Covid19_coord p)
{
    campo = p;
}

void NoQuadTree::SetCoordX(float p)
{
    x = p;
}

void NoQuadTree::SetCoordY(float p)
{
    y = p;
}

void NoQuadTree::SetFilhoNW(NoQuadTree*p)
{
    nw = p;
}

void NoQuadTree::SetFilhoNE(NoQuadTree*p)
{
    ne = p;
}

void NoQuadTree::SetFilhoSW(NoQuadTree*p)
{
    sw = p;
}

void NoQuadTree::SetFilhoSE(NoQuadTree*p)
{
    se = p;
}
