#ifndef DIRETORIO_H
#define DIRETORIO_H
#include "Balde.h"
#include <iostream>
#include<string>
#include <bits/stdc++.h>

/*typedef struct
{
    int dia;
    int mes;
    int ano;
} Date;

typedef struct
{
    Date dataDeConfirmacao;
    string estado;
    string cidade;
    int codigoDaCidade;
    int numDeCasos;
    int numDeObitos;
} Covid19;*/

using namespace std;


class Diretorio
{
    public:
        Diretorio(int B, int M);
        ~Diretorio();
        void Insere(unsigned long long int key,Covid19 chave,bool reinsere);
        void Remove(unsigned long long int key,int modo);
        void Atualiza(unsigned long long int key, Covid19 chave);
        void Procura(unsigned long long int key);
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
