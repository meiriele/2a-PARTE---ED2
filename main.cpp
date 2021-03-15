#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include <string>
#include"ArvoreQuadTree.h"
#include"NoQuadTree.h"
#include"Diretorio.h"
#include"Balde.h"
#include"ArvoreB.h"
#include"AVL_SEARCH_TREE.h"
#include"ArvoreAVL.h"
#include <chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;


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
    ofstream saida;
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
        Covid19_coord* buffer =  new Covid19_coord[N];
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
        Covid19* buffer = new Covid19[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        Diretorio* dir = new Diretorio(b,m);
        for(int i=0; i<N; i++)
        {
            unsigned long long int key =buffer[i].codigoDaCidade+buffer[i].dataDeConfirmacao.dia+buffer[i].dataDeConfirmacao.mes+buffer[i].dataDeConfirmacao.ano;
            dir->Insere(key,buffer[i],0);
        }
        dir->Printa(0);
    }
    break;

    case 3://INSERCAO DE N CHAVES NA ARVORE AVL
    {
        cout<<"DIGITE O VALOR DE N: "<<endl;
        cin>>N;
        cout<<endl<<endl<<endl;
        Covid19* buffer = new Covid19[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        ArvoreAVL* arv3 = new ArvoreAVL() ;
        for(int i=0; i<N; i++)
        {
            unsigned long long int key =buffer[i].codigoDaCidade+buffer[i].dataDeConfirmacao.dia+buffer[i].dataDeConfirmacao.mes+buffer[i].dataDeConfirmacao.ano;
            arv3->InsertNo(key);
        }
        arv3->ImprimeEmOrdem(arv3->GetRaiz());
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
        Covid19* buffer = new Covid19[N];
        ImportaArquivos(N,buffer,nullptr,1,1);
        ArvoreB* arv4 = new ArvoreB(d);
        for(int i=0; i<N; i++)
        {
            unsigned long long int key =buffer[i].codigoDaCidade+buffer[i].dataDeConfirmacao.dia+buffer[i].dataDeConfirmacao.mes+buffer[i].dataDeConfirmacao.ano;
            arv4->insert(key);
        }
        arv4->percorreArvore();
    }
    break;

    case 5://ANALISE DAS ESTRUTURAS BALANCEADAS
    {
        int nc = 5571;
        Covid19_coord* buffer_c = new Covid19_coord[nc];
        ArvoreQuadTree* arvQT = new ArvoreQuadTree;
        ImportaArquivos(nc,nullptr,buffer_c,0,0);
        for(int i=0; i<nc; i++)
            arvQT->Insere(buffer_c[i]);

        int np =1431490;
        Covid19* buffer_p = new Covid19 [np];
        Diretorio* dir = new Diretorio(6,257);
        ImportaArquivos(np,buffer_p,nullptr,1,0);
        for(int i=0; i<np; i++)
        {
            unsigned long long int key =buffer_p[i].codigoDaCidade+buffer_p[i].dataDeConfirmacao.dia+buffer_p[i].dataDeConfirmacao.mes+buffer_p[i].dataDeConfirmacao.ano;
            dir->Insere(key,buffer_p[i],0);
        }

        int N [5] = {10000,50000,100000,500000,1000000};
        double metrica_busca [3];
        double tempoAVL,tempoB20,tempoB200;
        int n=0; //entrada do vetor N

        //declara saida.txt para N[n]
        saida.open("saida.txt");
        if(saida.is_open())
        {
            saida<< "2o TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS 2 - 2020.3" << endl;
            saida<< "DISCENTE: Maria Meiriele Dias da Silva" << endl;
            saida<< "MATRICULA: 201476009 "<< endl<<endl;
            saida<<"AVALIANDO O TEMPO DE INSERCAO DE "<<N[n]<<" VALORES ALEATORIOS EM ARVORES"<<endl<<endl;

            metrica_busca[0]=0;
            metrica_busca[1]=0;
            metrica_busca[2]=0;

            ArvoreAVL* arvAVL = new ArvoreAVL();
            ArvoreB* arvB20 = new ArvoreB(20);
            ArvoreB* arvB200 = new ArvoreB(200);
            Covid19* bufferALEAT_p = new Covid19[N[n]];

            for(int k=0; k<5; k++) //5 iteracoes para cada valor de N
            {
                ImportaArquivos(N[n],bufferALEAT_p,nullptr,1,1);

                //INSERCAO
                for(int i=0; i<N[n]; i++)
                {
                   unsigned long long int key =bufferALEAT_p[i].codigoDaCidade*100000000+bufferALEAT_p[i].dataDeConfirmacao.dia*1000000+bufferALEAT_p[i].dataDeConfirmacao.mes*10000+bufferALEAT_p[i].dataDeConfirmacao.ano;

                    ti=high_resolution_clock::now();
                    arvAVL->InsertNo(key);
                    tf=high_resolution_clock::now();
                    tempoAVL+=duration_cast<microseconds>(tf-ti).count();

                    ti=high_resolution_clock::now();
                    arvB20->insert(key);
                    tf=high_resolution_clock::now();
                    tempoB20+=duration_cast<microseconds>(tf-ti).count();

                    ti=high_resolution_clock::now();
                    arvB200->insert(key);
                    tf=high_resolution_clock::now();
                    tempoB200+=duration_cast<microseconds>(tf-ti).count();
                }

                metrica_busca[0]+=tempoAVL;
                metrica_busca[1]+=tempoB20;
                metrica_busca[2]+=tempoB200;
                //atualiza saida.txt com iteracao
                saida<< "ITERACAO: "<<k+1<<"  ARVORE AVL: "<<tempoAVL<<"(10^-6 s)"<<"  ARVORE B(d=20): "<<tempoB20<<"(10^-6 s)"<<"  ARVORE B(d=200): "<<tempoB200<<"(10^-6 s)"<<endl;

                tempoAVL=0;
                tempoB20=0;
                tempoB200=0;

            }
            //atualiza saida.txt com media
            saida<< endl<<"MEDIA:"<<endl<<"ARVORE AVL: "<<metrica_busca[0]/5<<"(10^-6 s)"<<"  ARVORE B(d=20): "<<metrica_busca[1]/5<<"(10^-6 s)"<<"  ARVORE B(d=200): "<<metrica_busca[2]/5<<"(10^-6 s)"<<endl;

            delete [] arvAVL;
            delete [] arvB20;
            delete [] arvB200;
            delete [] bufferALEAT_p;

            saida<<endl<<endl<<endl<<endl;
        }
        else
            cerr<<"Erro ao abrir arquivo de saida!"<<endl;
    }
    break;

    default:
        cout<< "OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;

    }


    return 0;
}
