#ifndef BALDE_H
#define BALDE_H
#include <iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

typedef struct
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
} Covid19;

class Balde
{


public:
    Balde(int B, int M);
    ~Balde();
    int Insere(unsigned long long int key,Covid19 chave);
    int Remove(unsigned long long int key);
    int Atualiza(unsigned long long int key, Covid19 chave);
    void Procura(unsigned long long int key);
    int EstaCheio();
    int EstaVazio();
    int GetdLocal();
    int AumentadLocal();
    int DiminuidLocal();
    map<unsigned long long int, Covid19> Copia();
    void Limpa();
    void Printa();

private:
    int dlocal,tam;
    map<unsigned long long int, Covid19> pseudochaves;
};

#endif // BALDE_H
