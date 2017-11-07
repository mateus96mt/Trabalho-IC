#include "No.h"
#include "Arco.h"
#include <stdio.h>
#include <iostream>

using namespace std;

No::No(u_int id){
    this->id = id;
    this->proxNo = NULL;
    this->listaArcos = NULL;
    this->grau = 0;
    this->grauSaida = 0;
    this->grauEntrada = 0;
    this->carga = 0.0;
    this->marcado = false;
    this->nivel = 0;
}

void No::removeArcos(){
    Arco *aux1, *aux2=this->getListaArcos();
    while(aux2!=NULL){
        aux1 = aux2;
        aux2 = aux2->getProxArco();
        delete aux1;
    }
    this->grau = 0;
    this->setListaArcos(NULL);
}

double No::hashing(u_int id){
    u_int valor = 0;
    int primos[7] = {251,337,157,193,229,263,127};
    for(double i = 0; i < id; i+=0.01)
        valor = valor*primos[valor%7] + id;
    return valor%101;
}

void No::insereArco(No* noDestino, u_int id){
    Arco *novaArco = new Arco(id);
    novaArco->setNoDestino(noDestino);
    novaArco->setNoOrigem(this);
    novaArco->setProxArco(this->listaArcos);
    novaArco->setfluxoP_ativ(hashing(id));
    this->setListaArcos(novaArco);
    this->grau++;
}

void No::imprime(){
//    cout<<"( "<<"id:"<<this->getID()<<"\tgrau:"<<this->grau<<"\tfluxo:"<<this->fluxo<<"\tnivel:"<<this->nivel<<" )";
    printf("( id:%2d grauE:%2d  grauS:%2d  c: %2.1f : p_re :%2.1f : v:%2.5f :)", id, grauEntrada, grauSaida, carga, potencia_reativa, voltagem);
    Arco *arc = this->getListaArcos();

    while(arc!=NULL){
//        cout<< " --|A" << arc->getID() << "|--> " << arc->getNoDestino()->getID() << " " << "fluxo: " << arc->getfluxo() << " ";
        printf("\n");
        arc->imprime();
        arc = arc->getProxArco();
    }
    cout<<endl;
}

bool No::ehAdjacente(No *no){
    ///pesquisa na lista de adjacencia do n�
    Arco *aux=this->listaArcos;
    while(aux!=NULL){
        if(no==aux->getNoDestino())
            return true;
        aux=aux->getProxArco();
    }
    return false;
}
