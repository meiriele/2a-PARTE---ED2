#include "Diretorio.h"
#include <iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

Diretorio::Diretorio(int B, int M)
{
    dGlobal = B;
    tamBalde = M;
    for(int i = 0 ; i < 1 << B; i++ )
    {
        dir.push_back(new Balde(B,M));
    }
}

Diretorio::~Diretorio(){}

int Diretorio::Hash(int n)
{
    return n&((1<<dGlobal)-1);
}

int Diretorio::PareaIndice(int numBalde, int d)
{
    return numBalde^(1<<(d-1));
}

void Diretorio::Cresce()
{
    for(int i = 0 ; i < 1<<dGlobal ; i++ )
        dir.push_back(dir[i]);
    dGlobal++;
}

void Diretorio::Encolhe()
{
    int i,flag=1;
    for( i=0 ; i<dir.size() ; i++ )
    {
        if(dir[i]->GetdLocal()==dGlobal)
        {
            flag=0;
            return;
        }
    }
    dGlobal--;
    for(i = 0 ; i < 1<<dGlobal ; i++ )
        dir.pop_back();

}

void Diretorio::Split(int numBalde)
{
    int dlocal,indicePareamento,indiceDiferenciacao,sizeDir,i;
    map<int, string> temp;
    map<int, string>::iterator inc;

    dlocal = dir[numBalde]->AumentadLocal();
    if(dlocal>dGlobal)
        Cresce();
    indicePareamento = PareaIndice(numBalde,dlocal);
    dir[indicePareamento] = new Balde(dlocal,tamBalde);
    temp = dir[numBalde]->Copia();
    dir[numBalde]->Limpa();
    indiceDiferenciacao = 1<<dlocal;
    sizeDir= 1<<dGlobal;
    for( i=indicePareamento-indiceDiferenciacao ; i>=0 ; i-=indiceDiferenciacao )
        dir[i] = dir[indicePareamento];
    for( i=indicePareamento+indiceDiferenciacao ; i<sizeDir ; i+=indiceDiferenciacao)
        dir[i] = dir[indicePareamento];
    for(inc=temp.begin();inc!=temp.end();inc++)
        Insere((*inc).first,(*inc).second,1);
}

void Diretorio::Merge(int numBalde)
{
    int dlocal,indicePareamento,indiceDiferenciacao,sizeDir,i;

    dlocal = dir[numBalde]->GetdLocal();
    indicePareamento = PareaIndice(numBalde,dlocal);
    indiceDiferenciacao = 1<<dlocal;
    sizeDir = 1<<dGlobal;

    if( dir[indicePareamento]->GetdLocal()== dlocal )
    {
        dir[indicePareamento]->DiminuidLocal();
        delete(dir[numBalde]);
        dir[numBalde] = dir[indicePareamento];
        for( i=numBalde-indiceDiferenciacao ; i>=0 ; i-=indiceDiferenciacao )
            dir[i] = dir[indicePareamento];
        for( i=numBalde+indiceDiferenciacao ; i<sizeDir ; i+=indiceDiferenciacao )
            dir[i] = dir[indicePareamento];
    }
}

string Diretorio::Balde_id(int n)
{
   int d;
    string s;
    d = dir[n]->GetdLocal();
    s = "";
    while(n>0 && d>0)
    {
        s = (n%2==0?"0":"1")+s;
        n/=2;
        d--;
    }
    while(d>0)
    {
        s = "0"+s;
        d--;
    }
    return s;
}

void Diretorio::Insere(int key,string chave,bool reinsere)
{
   int numBalde = Hash(key);
    int estado = dir[numBalde]->Insere(key,chave);
    if(estado==1)
    {
        if(!reinsere)
            cout<<"Reinsercao da chave "<<key<<" no balde "<<Balde_id(numBalde)<<endl;
        else
            cout<<"Movimentacao da chave "<<key<<" para o balde "<<Balde_id(numBalde)<<endl;
    }
    else if(estado==0)
    {
        Split(numBalde);
        Insere(key,chave,reinsere);
    }
    else
    {
        cout<<"Chave "<<key<<" ja se encontra no balde "<<Balde_id(numBalde)<<endl;
    }
}

void Diretorio::Remove(int key,int modo)
{
    int numBalde = Hash(key);
    if(dir[numBalde]->Remove(key))
        cout<<"Chave "<<key<<" deletada do balde "<<Balde_id(numBalde)<<endl;
    if(modo>0)
    {
        if(dir[numBalde]->EstaVazio() && dir[numBalde]->GetdLocal()>1)
            Merge(numBalde);
    }
    if(modo>1)
    {
        Encolhe();
    }
}

void Diretorio::Atualiza(int key, string chave)
{
   int numBalde = Hash(key);
    dir[numBalde]->Atualiza(key,chave);
}

void Diretorio::Procura(int key)
{
    int numBalde = Hash(key);
    cout<<"Procurando pela chave "<<key<<" no balde "<<Balde_id(numBalde)<<endl;
    dir[numBalde]->Procura(key);
}

void Diretorio::Printa(bool duplicado)
{
    int i,j,d;
    string s;
    set<string> amostragem;
    cout<<"d Global : "<<dGlobal<<endl;
    for(i=0;i<dir.size();i++)
    {
        d = dir[i]->GetdLocal();
        s = Balde_id(i);
        if(duplicado || amostragem.find(s)==amostragem.end())
        {
            amostragem.insert(s);
            for(j=d;j<=dGlobal;j++)
                cout<<" ";
            cout<<s<<" => ";
            dir[i]->Printa();
        }
    }
}
