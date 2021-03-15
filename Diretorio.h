#ifndef DIRETORIO_H
#define DIRETORIO_H
#include "Balde.h"
#include <iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;


class Diretorio
{
    public:
        Diretorio(int B, int M);
        ~Diretorio();
        void Insere(int key,string chave,bool reinsere);
        void Remove(int key,int modo);
        void Atualiza(int key, string chave);
        void Procura(int key);
        void Printa(bool duplicado);

    protected:
        int Hash(int n);
        int PareaIndice(int numBalde, int d);
        void Cresce();
        void Encolhe();
        void Split(int numBalde);
        void Merge(int numBalde);
        string Balde_id(int n);

    private:
         int dGlobal, tamBalde;
         vector<Balde*> dir;
};

#endif // DIRETORIO_H
