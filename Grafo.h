#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "No.h"
#include "Arco.h"
#include <iostream>
#include <map>
#include <algorithm>

#define tam_populacao 100 ///tamanho

#define fracAleatorios 0.1 ///fracao de individuos aleatorios que seguem para proxima geracao

#define fracMelhores 0.1 ///fracao de melhores individuos que seguem para proxima geracao

#define erro_fObjetivo 1e-8 ///erro de convergencia para o calculo de perdas

using namespace std;
typedef u_int u_int;
struct Dijkstra;
void calculaPerda(Arco *a);
bool menorPerda(Arco *a1, Arco *a2);
bool compareReverse(u_int a, u_int b);
bool menorfluxo(Arco *a1, Arco *a2);
void movimentoSolucao(vector<Arco*> solucao);

struct Solucao{
    bool **vetChaves;
    double valorObjetivo;
};
bool melhorObjetivo(Solucao solucao1, Solucao solucao2);

class Grafo
{
public:
    double perdaTotal;
    No *listaNos;
    u_int grau;///maior grau de v�rtice do grafo
    u_int numeroNos;///n
    u_int numeroArcos;///m
    u_int contAux;/// contador auxiliar

    ///agora vai, tem que ir

    vector<No*> nosEntrada; /// nos do grafo que tem grau de entrada maior que 1


    double pb, vb, zb, fator;
    ///agora vai, tem que ir

    bool flagDir;///flag indicando se o grafo � direcionado ou n�o
    int auxEhNoArticulacao(No* no);
    void auxBuscaProfundidade(No *no, No* noArv, Grafo* Arv);
//    void incrementaContador(No* n);
    void atualizaDist(No* u, map<u_int, No*> Q, map<u_int, double> distancias);
    Grafo();
    No *getListaNos(){return this->listaNos;};
    u_int getGrau(){     return grau;    };
    u_int getNumeroNos(){    return numeroNos;   };
    u_int getNumeroArcos(){    return numeroArcos;   };
    bool getFlagDir(){  return flagDir; };
    void setFlagDir(bool flag){ flagDir=flag;   };
    u_int getContAux(){  return contAux; };
    void setContAux(u_int i){ contAux=i;   };

    void leDataArquivo(char nome[]);

    No* buscaNo(u_int id);
    No* insereNo(u_int id);
    void removeNo(u_int id);

    void imprime();

    void atualizaGrau();
    void atualizaGrausEntradaSaidaDosNos();
    void desmarcaNos();
    void leArquivo(char nome[]);

    void insereArco(No* noOrigem, No* noDestino, u_int id, bool atualizarGrau = true);
    void insereArcoID(u_int idOrigem, u_int idDestino, u_int id);

    void removeArco(u_int idOrigem, u_int idDestino);
    void removeArco(No* noOrigem, No* noDestino, bool atualizarGrau = true);
    void removeArcos(No *no, bool atualizarGrau);
    void removeArcosLigadasAoNo(No *no, bool atualizarGrau);

    bool ehGrafoCompleto();
    bool ehGrafoKRegular(u_int k);
    bool mesmaComponenteFortementeConexa(u_int id1, u_int id2);
    bool mesmaComponenteFortementeConexa(No *i1, No *i2);

    Grafo *subGrafoInduzido(u_int E[], u_int tam);

    u_int* sequenciaGrau();

    bool saoAdjacentes(u_int id1, u_int id2);
    bool saoAdjacentes(No *no1, No *no2);

    u_int numeroNosComponenteFortementeConexa(No *no);
    bool ehNoArticulacao(u_int id);
    bool ehNoArticulacao(No* no);

    bool ehArcoPonte(u_int id);
    bool ehArcoPonte(Arco* arco);

    bool ehFortementeConexo();
    u_int rubustezVertice(u_int *ids);
    u_int rubustezAresta();

    void percursoProfundidade(No *inicio);
    Grafo* buscaProfundidade(No *no);
    Grafo* BuscaEmLargura(No *no);

    vector<No*> vizinhancaAberta(u_int id, bool fechada = false);
    vector<No*> vizinhancaFechada(u_int id, bool fechada = true);
    bool ehGrafoKRegular();

    Grafo* clone();

    vector<No*> ordenacaoTopologicaDAG();

    int numeroComponentesConexas();

    Arco* buscaArco(u_int id1, u_int id2);
    Arco* buscaArco(No* no1, No* no2);
    Arco* buscaArcoID(u_int id);

    double** algoritmoFloyd();
    double consultaMenorCaminhoEntreDoisNos(u_int i, u_int j);

    vector<Arco*> algorimoPrim();

    /**
    Retorna o subgrafo (ou floresta de subgrafos se o grafo nao e n�o-conexo)
    contendo as arestas de fluxo minimo que ligam todos os nos do grafo
    que formam a arvore/floresta
    */
    vector<Arco*> Kruskal();




    ///funcoes trabalho IC:
    u_int n_marcados;/// contagem percurso em profundidade
    No *insereNoCargaVoltagem(u_int id, double carga, double potencia_reativa, double voltagem);
    void insereArcoDados(u_int idOrig, u_int idDest, u_int ID, double resistencia, double reatancia, double fluxoP_ativ, double fluxoP_reativ, bool chave);
    void leEntrada(char nome[]);

    void AtualizaFLuxos();
    void AuxAtualizaFLuxos(No *no);
    void construtivo();
    void AuxConstrutivo(No *no);
    vector<Arco*> geraVetorArcos();
    bool validaSolucao();
    double calculaPerdaTotal();

    void foward(u_int it);
    void Auxfoward(No *no, Arco *ak, u_int it);
    void backward();
    void Auxbackward(No *no);
    void calcula_fluxos_e_perdas(double tol);

    double *soma_perdas();

    double p_ativ_total, p_reat_total;



    bool verificaSolucaoValida(Solucao solucao);
    void auxVerificaSolucaoValida(No *no, u_int &marcados, bool &ciclo);
    ///agora vai!--------------tem que ir


    double cargasPerdasRamoAtiv(No *no);
    void auxcargasPerdasRamoAtiv(No *no, double &soma);

    double cargasPerdasRamoReAtiv(No *no);
    void auxcargasPerdasRamoReAtiv(No *no, double &soma);

    void abreFechaChavesGrafo(Solucao solucao);
    double funcaoObjetivo(Solucao solucao, double tol);

    void imprimeChaves(Solucao solucao);

    double tensaoMinima();

    ///CONSTRUTIVOS:
    Solucao construtivoAleatorio();



    ///FUNCOES DE ALGORITMO GENETICO-----------------------------------------

    void mutacao(Solucao &solucao);
    Solucao cruzamento_metade(Solucao pai1, Solucao pai2);
    Solucao cruzamentoAleatorio(Solucao pai1, Solucao pai2);

    ///retorna o melhor individuo
    Solucao algoritmoGenetico(u_int itSemMelhora);

    vector<Solucao> populacaoInicial(u_int num_individuos);///gera uma populacao inicial
    void proximaGeracao(vector<Solucao>&populacao);///faz cruzamentos e mutacoes
    void sobrevivencia(vector<Solucao>& populacao);///seleciona melhores individuos
    Solucao melhorIndividuoPopulacao(vector<Solucao> populacao);///retorna o melhor individuo da populacao

    ///FUNCOES DE ALGORITMO GENETICO-----------------------------------------




    ///agora vai!--------------tem que ir

    ~Grafo();
};

#endif // DIGRAFO_H_INCLUDED
