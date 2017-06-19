#ifndef LISTASIMPLES_H
#define LISTASIMPLES_H
#include <iostream>
#include <stdlib.h>

using namespace std;

// CLASSE BÁSICA DE DADOS

class tdados{
public:
    int dado;
    tdados *prox;
    tdados(int info){dado=info;prox=NULL;}
};

// CLASSE BÁSICA DA LISTA

class tlista{
public:
    tdados *inicio;
    tlista(){inicio=NULL;}
    void inserir(int);
    bool vazia(){return (inicio==NULL);}
    void remover(int);
    void removerPosicao(int);
    int retornarItem(int);                //retorna item da posição x
    int tamanho();                  //tamanho iterativo
    int tamanhorecur(tdados *l);    //tamanho recursivo
    void ntlista();
    void exibir();                  //exibir iterativo
    void exibirrecur(tdados *l);    //exibir recursivo
    void inserirordem (int);
    void addvetor(int vet[],int);   //funçaão para ler um vetor e adicionar os lementos do vetor para lista
};


void tlista::inserir(int info){
    tdados *novo=new tdados(info);
    if(vazia())
        inicio=novo;
    else
    {
    tdados *l=inicio;
    while(l->prox!=NULL)
        l=l->prox;
    l->prox=novo;

  }
}


void tlista::remover(int info){
     if(vazia())
         return;
     if(info==1) {
         tdados *l=inicio;
         inicio=inicio->prox;
         l->prox=l;
         delete(l);
     }
     else
      {
         int cont = 1;
         tdados *la,*ld;
         la=inicio;
         ld=inicio->prox;
         while(ld!=NULL)
         {
             if(cont == info)
                 break;
             la=ld;
             ld=ld->prox;
             cont++;
         }
        if(ld!=NULL)
        {
            la->prox=ld->prox;
            ld->prox=ld;
            delete(ld);
        }
      }
}

void tlista::removerPosicao(int info){
     if(vazia())
         return;
     if(inicio->dado==info) {
         tdados *l=inicio;
         inicio=inicio->prox;
         l->prox=l;
         delete(l);
     }
     else
      {
         tdados *la,*ld;
         la=inicio;
         ld=inicio->prox;
         while(ld!=NULL)
         {
             if(ld->dado==info)
                 break;
             la=ld;
             ld=ld->prox;
         }
        if(ld!=NULL)
        {
            la->prox=ld->prox;
            ld->prox=ld;
            delete(ld);
        }
      }
}

int tlista::retornarItem(int posicao)
{
    tdados *l=inicio;
    for(int i = 1; i < posicao; i++)
        l=l->prox;
    return l->dado;
}

int tlista::tamanho() {
    if(vazia())
       return 0;
    tdados *l=inicio;
    int i=0;
    while (l!=NULL) {
        l=l->prox;
        i=++i;
    }
    return i;
}

int tlista::tamanhorecur(tdados *l){
    if (l==NULL)
        return 0;
    return 1+(tamanhorecur(l->prox));
}


void tlista::ntlista(){
    if(vazia())
        return;
    tdados *l;
    while(!vazia())
        l=inicio;
        inicio=inicio->prox;
        delete(l);
}


void tlista::exibir(){
    if(vazia())
        return;
    tdados *l=inicio;
    while(l!=NULL){
        cout<<l->dado<<" ";
        l=l->prox;
    }
    cout<<endl;
}


void tlista::exibirrecur(tdados *l){
    if(l==NULL)
        return;
    cout<<l->dado<<" ";
    return exibirrecur(l=l->prox);

}


void tlista::inserirordem (int info){
    tdados *novo=new tdados (info);
    if (vazia())
        inicio=novo;
        return;
    if (info<inicio->dado){
       novo->prox=inicio;
       inicio=novo;
       return;
    }
    tdados *l=inicio;
    while(l!=NULL && l->dado<info)
        l=l->prox;
    novo->prox=l->prox;
    l->prox=novo;
}


void tlista::addvetor(int vet[],int n){
for(int i=0;i<n;i++)
    inserir(vet[i]);


}

#endif
