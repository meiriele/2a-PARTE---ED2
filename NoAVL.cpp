#include "NoAVL.h"

NoAVL::NoAVL() { }

NoAVL::~NoAVL() { }

int NoAVL::getID()
{
    return id;
}

int NoAVL::getFatbalance()
{
    return fatbalance;
}

NoAVL* NoAVL::getDir()
{
    return dir;
}

NoAVL* NoAVL::getEsq()
{
    return esq;
}

NoAVL* NoAVL::getPai()
{
    return pai;
}

void NoAVL::setID(int val)
{
    id = val;
}
void NoAVL::setFatbalance(int val)
{
    fatbalance = val;
}

void NoAVL::setDir(NoAVL* p)
{
    dir = p;
}

void NoAVL::setEsq(NoAVL* p)
{
    esq = p;
}

void NoAVL::setPai(NoAVL* p)
{
    pai = p;
}
