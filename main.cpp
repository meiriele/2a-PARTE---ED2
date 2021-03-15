#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include <string>
#include"ArvoreQuadTree.h"
#include"NoQuadTree.h"
#include"Diretorio.h"
#include"Balde.h"
#include"ArvoreAVL.h"
#include"NoAVL.h"
#include"ArvoreB.h"
#include <chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;


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

/*typedef struct
{
    int codigoDoEstado;
    int codigoDaCidade;
    string cidade;
    float lat;
    float lon;
    string capital;
} Covid19_coord;
*/

void ImportaArquivos (int n,Covid19* buffer_proc, Covid19_coord* buffer_c, bool arq_P,bool aleatorio)
{
    if(arq_P == 1)
    {
        fstream arquivo;
        arquivo.open ("brazil_covid_cities_processado.csv");

        if(aleatorio == 1)
        {
            if(arquivo.is_open())
            {
                string sout;
                arquivo.seekg(0,ios::end); //leva o ponteiro para o fim do arquivo
                int tamanho = arquivo.tellg(); //mostra a qtdade de bytes de onde esta o ponteiro no arquivo

                for(int i=0; i<n; i++)
                {
                    int blind = rand() %tamanho;
                    arquivo.seekg(blind,ios::beg);
                    arquivo.ignore(1000,'\n'); //leva o ponteiro ate o final da linha
                    getline(arquivo,sout);// getline(arquivo,sout);
                    stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                    getline(s, sout,',');
                    buffer_proc[i].estado = sout;
                    getline(s, sout,',');
                    buffer_proc[i].cidade = sout;
                    getline(s, sout,',');
                    buffer_proc[i].codigoDaCidade = atoi (sout.c_str());
                    getline(s, sout,'-');
                    buffer_proc[i].dataDeConfirmacao.dia = atoi (sout.c_str());
                    getline(s, sout,'-');
                    buffer_proc[i].dataDeConfirmacao.mes = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].dataDeConfirmacao.ano = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].numDeCasos = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].numDeObitos = atoi (sout.c_str());
                }
                arquivo.close();
            }

            else
                cerr<<"Erro ao abrir arquivo de dados!"<<endl<<endl;
        }
        else
        {
            if(arquivo.is_open())
            {
                string sout;
                getline(arquivo,sout);//o primeiro a gente ignora pq eh o cabecario
                for(int i=0; i<n; i++)
                {
                    getline(arquivo,sout);// getline(arquivo,sout);
                    stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                    getline(s, sout,',');
                    buffer_proc[i].estado = sout;
                    getline(s, sout,',');
                    buffer_proc[i].cidade = sout;
                    getline(s, sout,',');
                    buffer_proc[i].codigoDaCidade = atoi (sout.c_str());
                    getline(s, sout,'-');
                    buffer_proc[i].dataDeConfirmacao.dia = atoi (sout.c_str());
                    getline(s, sout,'-');
                    buffer_proc[i].dataDeConfirmacao.mes = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].dataDeConfirmacao.ano = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].numDeCasos = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_proc[i].numDeObitos = atoi (sout.c_str());
                }
                arquivo.close();
            }

            else
                cerr<<"Erro ao abrir arquivo de dados!"<<endl;
        }
    }

    else

    {
        fstream arquivo;
        arquivo.open ("brazil_cities_coordinates.csv");

        if(aleatorio == 1)
        {
            if(arquivo.is_open())
            {
                string sout;
                arquivo.seekg(0,ios::end); //leva o ponteiro para o fim do arquivo
                int tamanho = arquivo.tellg(); //mostra a qtdade de bytes de onde esta o ponteiro no arquivo

                for(int i=0; i<n; i++)
                {
                    int blind = rand() %tamanho;
                    arquivo.seekg(blind,ios::beg);
                    arquivo.ignore(1000,'\n'); //leva o ponteiro ate o final da linha
                    getline(arquivo,sout);// getline(arquivo,sout);
                    stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                    getline(s, sout,',');
                    buffer_c[i].codigoDoEstado = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].codigoDaCidade = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].cidade = sout;
                    getline(s, sout,',');
                    buffer_c[i].lat = atof (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].lon = atof (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].capital = sout;
                }
                arquivo.close();
            }
            else
                cerr<<"Erro ao abrir arquivo de dados!"<<endl<<endl;
        }
        else
        {
            if(arquivo.is_open())
            {
                string sout;
                getline(arquivo,sout);//o primeiro a gente ignora pq eh o cabecario
                for(int i=0; i<n; i++)
                {
                    getline(arquivo,sout);// getline(arquivo,sout);
                    stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                    getline(s, sout,',');
                    buffer_c[i].codigoDoEstado = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].codigoDaCidade = atoi (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].cidade = sout;
                    getline(s, sout,',');
                    buffer_c[i].lat = atof (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].lon = atof (sout.c_str());
                    getline(s, sout,',');
                    buffer_c[i].capital = sout;

                }
                arquivo.close();
            }
            else
                cerr<<"Erro ao abrir arquivo de dados!"<<endl;
        }
    }
}


void PrintArquivo(int n,Covid19* buffer_proc,Covid19_coord* buffer_c,bool arq_P)
{
    if(arq_P == 1)
    {
        cout<<"PADRAO: sigla_do_estado,nome_da_cidade,codigo_da_cidade,data_de_confirmacao,numero_de_casos,numero_de_obitos"<<endl<<endl;
        for(int i=0; i<n; i++)
        {
            cout<<buffer_proc[i].estado<<","<<buffer_proc[i].cidade<<","<<buffer_proc[i].codigoDaCidade<<",";
            cout<<buffer_proc[i].dataDeConfirmacao.dia<<"-"<<buffer_proc[i].dataDeConfirmacao.mes<<"-"<<buffer_proc[i].dataDeConfirmacao.ano<<",";
            cout<<buffer_proc[i].numDeCasos<<","<<buffer_proc[i].numDeObitos<<endl;
        }
        cout<<endl<<endl;
    }
    else
    {
        cout<<"PADRAO: codigo_do_estado,codigo_da_cidade,nome_da_cidade,latitude,longitude,capital"<<endl<<endl;
        for(int i=0; i<n; i++)
        {
            cout<<buffer_c[i].codigoDoEstado<<","<<buffer_c[i].codigoDaCidade<<","<<buffer_c[i].cidade<<",";
            cout<<buffer_c[i].lat<<","<<buffer_c[i].lon<<","<<buffer_c[i].capital<<endl;
        }
        cout<<endl<<endl;
    }
}


int main (int argc, char* argv[])
{
    time_point<high_resolution_clock>ti,tf;
    srand (time(NULL));
    int menu,N;
    cout<< "2o TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS 2 - 2020.3" << endl;
    cout<< "DISCENTE: Maria Meiriele Dias da Silva" << endl;
    cout<< "MATRICULA: 201476009 "<< endl;
    cout<< endl << endl << "MENU"<< endl;
    cout<< "1 - MODULO DE TESTES: INSERCAO DE N CIDADES NA QUAD-TREE"<<endl;
    cout<< "2 - MODULO DE TESTES: INSERCAO DE N REGISTROS NA TABELA-HASH"<<endl;
    cout<< "3 - MODULO DE TESTES: INSERCAO DE N CHAVES NA ARVORE AVL"<<endl;
    cout<< "4 - MODULO DE TESTES: INSERCAO DE N CHAVES NA ARVORE B"<<endl;
    cout<< "5 - ANALISE DAS ESTRUTURAS BALANCEADAS"<<endl;
    cout<< "SUA ESCOLHA: ";
    cin>>menu;
    cout<<endl;

    switch (menu)
    {

    case 1://INSERCAO DE N CIDADES NA QUAD-TREE
    {
        cout<<"DIGITE O VALOR DE N: "<<endl;
        cin>>N;
        cout<<endl<<endl<<endl;
        ArvoreQuadTree* arv1 = new ArvoreQuadTree();
        Covid19_coord buffer[N];
        ImportaArquivos(N,nullptr,buffer,0,1);
        for(int i=0; i<N; i++)
            arv1->Insere(buffer[i]);
        arv1->ImprimeEmOrdem();
    }
    break;

    case 2://INSERCAO DE N REGISTROS NA TABELA-HASH
    {
        cout<<"DIGITE O VALOR DE N: "<<endl;
        cin>>N;
        cout<<endl<<endl<<endl;
        int b,m;
        cout<<"DIGITE O TAMANHO DO BALDE: "<<endl;
        cin>>m;
        cout<<"DIGITE O d GLOBAL INICIAL: "<<endl;
        cin>>b;
        Covid19 buffer[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        Diretorio* dir = new Diretorio(b,m);
        for(int i=0; i<N; i++)
        {
            string aux = to_string(buffer[i].dataDeConfirmacao.dia) + to_string(buffer[i].dataDeConfirmacao.mes) + to_string(buffer[i].dataDeConfirmacao.ano);
            dir->Insere(buffer[i].codigoDaCidade,aux,0);
        }
        dir->Printa(0);
    }
    break;

    case 3://INSERCAO DE N CHAVES NA ARVORE AVL
    {
        cout<<"DIGITE O VALOR DE N: "<<endl;
        cin>>N;
        cout<<endl<<endl<<endl;
        Covid19 buffer[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        ArvoreAVL* arv3 = new ArvoreAVL() ;
        for(int i=0; i<N; i++)
            arv3->Insere(buffer[i].codigoDaCidade);
        arv3->ImprimeEmOrdem();
    }
    break;

    case 4://INSERCAO DE N CHAVES NA ARVORE B
    {
        cout<<"DIGITE O VALOR DE N: "<<endl;
        cin>>N;
        cout<<endl<<endl<<endl;
        int d;
        cout<<"DIGITE O VALOR DE d: ";
        cin>>d;
        cout<<endl;
        Covid19 buffer[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        ArvoreB* arv4 = new ArvoreB(d);
        for(int i=0; i<N; i++)
            arv4->insert(buffer[i].codigoDaCidade);
        arv4->percorreArvore();
    }
    break;

    case 5://ANALISE DAS ESTRUTURAS BALANCEADAS
    {
        cout<<"ESTE MODULO NAO ESTA IMPLEMENTADO"<<endl;
    }
    break;

    default:
        cout<< "OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;

    }


    return 0;
}
