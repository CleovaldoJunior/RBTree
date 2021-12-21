#ifndef RUBRONEGRA_RUBRONEGRA_H
#define RUBRONEGRA_RUBRONEGRA_H

enum cor {VERMELHO , PRETO, DUPLO_PRETO};

typedef struct no{
    int key;
    enum cor c;
    struct no *esq, *dir, *pai;
} no;

void inserir(no**raiz, int key);

void ajustar_rb(no *nodo, no **raiz);

void pre_order(no *raiz);

void in_order(no *raiz);

void pos_order(no *raiz);

int Maior(no *raiz);

int eh_raiz(no* nodo);

int filho_esquerdo(no* nodo);

int cor(no* nodo);

no* tio(no* nodo);

void remover(no **raiz, int key);

void reajustar(no **raiz, no* duplo_preto);

int tem_filho(no* nodo);


#endif //RUBRONEGRA_RUBRONEGRA_H
