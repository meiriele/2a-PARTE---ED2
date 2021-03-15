#include "Balde.h"
#include <iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

Balde::Balde(int B, int M)
{
    dlocal = B;
    tam = M;
}

Balde::~Balde() { }

int Balde::Insere(int key,string chave)
{
    map<int,string>::iterator inc;
    inc = pseudochaves.find(key);
    if(inc!=pseudochaves.end())
        return -1;
    if(EstaCheio())
        return 0;
    pseudochaves[key] = chave;
    return 1;
}

int Balde::Remove(int key)
{
    map<int,string>::iterator inc;
    inc = pseudochaves.find(key);
    if(inc!=pseudochaves.end())
    {
        pseudochaves.erase(inc);
        return 1;
    }
    else
    {
        cout<<"Esta chave nao existe!"<<endl;
        return 0;
    }
}


int Balde::Atualiza(int key, string chave)
{
    map<int,string>::iterator inc;
    inc = pseudochaves.find(key);
    if(inc!=pseudochaves.end())
    {
        pseudochaves[key] = chave;
        cout<<"Valor atualizado!"<<endl;
        return 1;
    }
    else
    {
        cout<<"Chave nao existe! Atualizacao nao realizada."<<endl;
        return 0;
    }
}


void Balde::Procura(int key)
{
    map<int,string>::iterator inc;
    inc = pseudochaves.find(key);
    if(inc!=pseudochaves.end())
    {
        cout<<"Elemento encontrado = "<<inc->second<<endl;
    }
    else
    {
        cout<<"Chave nao existe!"<<endl;
    }

}

int Balde::EstaCheio()
{
    if(pseudochaves.size()==tam)
        return 1;
    else
        return 0;
}

int Balde::EstaVazio()
{
    if(pseudochaves.size()==0)
        return 1;
    else
        return 0;
}

int Balde::GetdLocal()
{
    return dlocal;
}

int Balde::AumentadLocal()
{
    dlocal++;
    return dlocal;
}

int Balde::DiminuidLocal()
{
    dlocal--;
    return dlocal;
}

map<int, string> Balde::Copia()
{
    map<int, string> temp(pseudochaves.begin(),pseudochaves.end());
    return temp;
}

void Balde::Limpa()
{
    pseudochaves.clear();
}

void Balde::Printa()
{
    map<int,string>::iterator inc;
    for(inc=pseudochaves.begin(); inc!=pseudochaves.end(); inc++)
        cout<<inc->first<<endl;
    cout<<endl;
}
