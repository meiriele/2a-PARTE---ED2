#ifndef BALDE_H
#define BALDE_H
#include <iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

class Balde
{


public:
    Balde(int B, int M);
    ~Balde();
    int Insere(int key,string chave);
    int Remove(int key);
    int Atualiza(int key, string chave);
    void Procura(int key);
    int EstaCheio();
    int EstaVazio();
    int GetdLocal();
    int AumentadLocal();
    int DiminuidLocal();
    map<int, string> Copia();
    void Limpa();
    void Printa();

private:
    int dlocal,tam;
    map<int, string> pseudochaves;
};

#endif // BALDE_H
