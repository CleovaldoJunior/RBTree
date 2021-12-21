#include <stdio.h>
#include <stdlib.h>
#include "rubronegra.h"

void inserir(no** raiz, int key){
    no *temp;
    no *pai;
    no *novo;

    temp = *raiz;
    pai = NULL;

    while(temp != NULL){
        pai = temp;
        if(key > temp->key){
            temp = temp->dir;
        } else{
            temp = temp->esq;
        }
    }
    novo = (no*)malloc(sizeof(struct no));
    novo->key = key;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->c = VERMELHO;
    novo->pai = pai;

    if(*raiz != NULL){
        if(key > pai->key) {
            pai->dir = novo;
        } else{
            pai->esq = novo;
        }
    } else{
        *raiz = novo;
    }

    ajustar_rb(novo, raiz);
}

void ajustar_rb(no *nodo, no **raiz){
    //Raiz é vermelha
    if(eh_raiz(nodo)){
        nodo->c = PRETO;
        return;
    }
    //Pai é vermelho.
    if(nodo->pai->c == VERMELHO){
        //Tio também é vermlho.
        if(cor(tio(nodo)) == VERMELHO){
            tio(nodo)->c = PRETO;
            nodo->pai->c = PRETO;
            nodo->pai->pai->c = VERMELHO;
            ajustar_rb(nodo->pai->pai, raiz);
        }
        // Tio é preto.
        else{
            //Pai e nodo estão na esquerda ROTAÇÃO SIMPLES DIREITA.
            if(filho_esquerdo(nodo->pai) && filho_esquerdo(nodo)){
                no* avo = nodo->pai->pai;
                no* aux = nodo->pai;
                int grandpa_key = avo->key;
                avo->key = avo->esq->key;
                avo->esq = nodo;
                nodo->pai = avo;
                aux->esq = aux->dir;
                aux->dir = avo->dir;
                aux->key = grandpa_key;
                avo->dir = aux;
                aux->pai = avo;
                if(aux->dir != NULL){
                    aux->dir->pai = aux;
                }
                return;
            }
            //Pai e nodo estão na direita ROTAÇÃO SIMPLES ESQUERDA.
            if(filho_esquerdo(nodo->pai) == 0 && filho_esquerdo(nodo) == 0){
                no* avo = nodo->pai->pai;
                no* aux = nodo->pai;
                int grandpa_key = avo->key;
                avo->key = avo->dir->key;
                avo->dir = nodo;
                nodo->pai = avo;
                aux->dir = aux->esq;
                aux->esq = avo->esq;
                aux->key = grandpa_key;
                avo->esq = aux;
                aux->pai = avo;
                if(aux->esq != NULL){
                    aux->esq->pai = aux;
                }
                return;
            }
            //Pai na esquerda e nodo na direita ROTAÇÃO DUPLA DIREITA.
            if(filho_esquerdo(nodo->pai) == 1 && filho_esquerdo(nodo) == 0){
                //PRIMEIRA ROTAÇÃO
                no*aux = nodo->pai;
                int pai_key = aux->key;
                aux->key = nodo->key;
                nodo->key = pai_key;
                aux->dir = nodo->dir;
                nodo->dir = nodo->esq;
                nodo->esq = aux->esq;
                aux->esq = nodo;
                if(nodo->esq != NULL){
                    nodo->esq->pai = nodo;
                }
                if(aux->dir != NULL){
                    aux->dir->pai = aux;
                }
                //SEGUNDA ROTAÇÃO
                no* avo2 = nodo->pai->pai;
                no* aux2 = nodo->pai;
                int grandpa_key2 = avo2->key;
                avo2->key = avo2->esq->key;
                avo2->esq = nodo;
                nodo->pai = avo2;
                aux2->esq = aux2->dir;
                aux2->dir = avo2->dir;
                aux2->key = grandpa_key2;
                avo2->dir = aux2;
                aux2->pai = avo2;
                if(aux2->dir != NULL){
                    aux2->dir->pai = aux2;
                }
             // Pai na direita e nodo na esquerda ROTAÇÃO DUPLA ESQUERDA.
            }else{
                //PRIMEIRA ROTAÇÃO
                no*aux = nodo->pai;
                int pai_key = aux->key;
                aux->key = nodo->key;
                nodo->key = pai_key;
                aux->esq = nodo->esq;
                nodo->esq = nodo->dir;
                nodo->dir = aux->dir;
                aux->dir = nodo;
                if(nodo->dir != NULL){
                    nodo->dir->pai = nodo;
                }
                if(aux->esq != NULL){
                    aux->esq->pai = aux;
                }
                //SEGUNDA ROTAÇÃO.
                no* avo = nodo->pai->pai;
                no* aux2 = nodo->pai;
                int grandpa_key = avo->key;
                avo->key = avo->dir->key;
                avo->dir = nodo;
                nodo->pai = avo;
                aux2->dir = aux2->esq;
                aux2->esq = avo->esq;
                aux2->key = grandpa_key;
                avo->esq = aux2;
                aux2->pai = avo;
                if(aux2->esq != NULL){
                    aux2->esq->pai = aux2;
                }


            }


        }

    }
}


void pre_order(no *raiz){
    if(raiz == NULL){
        ;
    } else{
        if(raiz->c == PRETO){
            printf("\x1b[30m[%d]\x1b[0m", raiz->key);

        }else{
            printf("\x1b[31m[%d]\x1b[0m", raiz->key);
        }
        pre_order(raiz->esq);
        pre_order(raiz->dir);

    }
}

void in_order(no *raiz){
    ;
}

void pos_order(no *raiz){
    ;
}

int eh_raiz(no* nodo){
    if(nodo->pai == NULL){
        return 1;
    } else{
        return 0;
    }

}

int filho_esquerdo(no* nodo){
    if(nodo->pai->esq == nodo){
        return 1;
    } else{
        return 0;
    }
}

int cor(no* nodo){
   if(nodo == NULL || nodo->c == PRETO){
       return PRETO;
   }
   if(nodo->c == VERMELHO){
       return VERMELHO;
   }
   if(nodo->c == DUPLO_PRETO){
       return DUPLO_PRETO;
   }
}

no* tio(no* nodo){
    if(filho_esquerdo(nodo->pai)){
        return nodo->pai->pai->dir;
    } else{
        return nodo->pai->pai->esq;
    }
}

int Maior(no *raiz){
    no *aux = raiz;
    if(aux == NULL){
        return 0;
    } else{
        while(aux->dir != NULL){
            aux = aux->dir;
        }
        return aux->key;

    }

}

int tem_filho(no* nodo){
    if(nodo->dir != NULL || nodo->esq != NULL){
        return 1;
    } else{
        return 0;
    }
}





// Remoção
void remover(no **raiz, int key){
    no* temp;
    no* pai;
    temp = *raiz;
    pai = NULL;

    // PERCORRE A ARVORE
    while(temp != NULL && temp->key != key){
        pai = temp;
        if(key > temp->key){
            temp = temp->dir;
        } else{
            temp = temp->esq;
        }
    }

    //Elemento não existe.
    if(temp == NULL){
        return;
    }

    //Elemento a ser removido tem dois filhos.
    if(temp->esq != NULL && temp->dir != NULL){
        temp->key = Maior(temp->esq);
        remover(&temp->esq, temp->key);
        return ;
    }

     // Apenas filho esquerdo
    if(temp-> esq != NULL && temp->dir == NULL){
        if(filho_esquerdo(temp)){
            pai->esq = temp->esq;
            pai->esq->c = PRETO;
            pai->esq->pai = pai;
        }else{
            pai->dir = temp-> esq;
            pai->dir->c = PRETO;
            pai->dir->pai = pai;
        }
        return ;
    }
    // Apenas filho direito
    if(temp -> esq == NULL && temp->dir != NULL){
        if(filho_esquerdo(temp) == 0){
            pai->dir = temp->dir;
            pai->dir->c = PRETO;
            pai->dir->pai = pai;
        }else{
            pai->esq = temp->dir;
            pai->esq->c = PRETO;
            pai->esq->pai = pai;
        }
        return ;
    }
    //Não tem filho e é vermelho
    if(temp->esq == NULL && temp->dir == NULL && temp->c == VERMELHO){
        if(filho_esquerdo(temp)){
            pai->esq = NULL;
        }else{
            pai->dir = NULL;
        }
        return ;
    }

    //Não tem filho e é preto
    if(temp->esq == NULL && temp->dir == NULL && temp->c == PRETO){
        no* duplo_preto = (no*) malloc(sizeof(no));
        duplo_preto->esq = NULL;
        duplo_preto->dir = NULL;
        duplo_preto->c = DUPLO_PRETO;
        duplo_preto->pai = temp->pai;

        if(filho_esquerdo(temp)){
            pai->esq = duplo_preto;
        }else{
            pai->dir = duplo_preto;
        }
        reajustar(raiz, duplo_preto);
    }
}

void reajustar(no** raiz, no* duplo_preto){
    if(eh_raiz(duplo_preto)){
        if(duplo_preto->c == DUPLO_PRETO){

            *raiz = NULL;
        }else{
            duplo_preto->c = PRETO;
        }
        return ;
    }
    //CASO 2 : DUPLO PRETO ESQ, PAI PRETO, IRMÃO VERMELHO
    if(filho_esquerdo(duplo_preto) && cor(duplo_preto->pai) == PRETO && cor(duplo_preto->pai->dir) == VERMELHO && cor(duplo_preto->pai->dir->esq) == PRETO && cor(duplo_preto->pai->dir->dir) == PRETO){
        no* p = duplo_preto->pai;
        no* s = p->dir;
        //ROTAÇÃO.
        int P_ESQUERDO = filho_esquerdo(p);
        p->dir = s->esq;
        s->esq = p;
        s->pai = p->pai;
        if(P_ESQUERDO){
            s->pai->esq = s;
        } else{
            s->pai->dir = s;
        }
        s->c = PRETO;
        p->c = VERMELHO;
        if(p->dir != NULL){
            p->dir->pai = p;
        }
        if(p->esq != NULL){
            p->esq->pai = p;
        }
        if(s->dir != NULL){
            s->dir->pai = s;
        }
        if(s->esq != NULL){
            s->esq->pai = s;
        }
    }
    // CASO 2 : SIMETRICO.
    if(filho_esquerdo(duplo_preto) == 0 && cor(duplo_preto->pai) == PRETO && cor(duplo_preto->pai->esq) == VERMELHO && cor(duplo_preto->pai->esq->dir) == PRETO && cor(duplo_preto->pai->esq->esq) == PRETO){
        no* p = duplo_preto->pai;
        no* s = p->esq;

        int P_ESQUERDA = filho_esquerdo(p);
        p->esq = s->dir;
        s->dir = p;
        s->pai = p->pai;
        if(P_ESQUERDA){
            s->pai->esq = s;
        } else{
            s->pai->dir = s;
        }
        s->c = PRETO;
        p->c = VERMELHO;
        if(p->dir != NULL){
            p->dir->pai = p;
        }
        if(p->esq != NULL){
            p->esq->pai = p;
        }
        if(s->dir != NULL){
            s->dir->pai = s;
        }
        if(s->esq != NULL){
            s->esq->pai = s;
        }
    }
    //CASO 3: DUPLO PRETO ESQ, PAI PRETO, IRMÃO PRETO.
    if(filho_esquerdo(duplo_preto) && cor(duplo_preto->pai) == PRETO && cor(duplo_preto->pai->dir) == PRETO && cor(duplo_preto->pai->dir->esq) == PRETO && cor(duplo_preto->pai->dir->dir) == PRETO){
        no* p = duplo_preto->pai;
        p->dir->c = VERMELHO;
        p->c = DUPLO_PRETO;
        if(cor(duplo_preto) == DUPLO_PRETO && duplo_preto != NULL){
            duplo_preto = NULL;
        } else{
            duplo_preto->c = PRETO;
        }
        duplo_preto = p;
    }
    //CASO 3: SIMETRICO.
    if(filho_esquerdo(duplo_preto) == 0 && cor(duplo_preto->pai) == PRETO && cor(duplo_preto->pai->esq) == PRETO && cor(duplo_preto->pai->esq->dir) == PRETO && cor(duplo_preto->pai->esq->esq) == PRETO){
        no* p = duplo_preto->pai;
        p->esq->c = VERMELHO;
        p->c = DUPLO_PRETO;
        if(cor(duplo_preto) == DUPLO_PRETO && duplo_preto != NULL){
            duplo_preto = NULL;
        } else{
            duplo_preto->c = PRETO;
        }
        duplo_preto = p;
    }
    //CASO 4: DUPLO PRETO ESQUERDA, PAI VERMELHO, IRMÃO PRETO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) && cor(duplo_preto->pai) == VERMELHO && cor(duplo_preto->pai->dir) == PRETO && cor(duplo_preto->pai->dir->esq)== PRETO && cor(duplo_preto->pai->dir->dir) == PRETO){
        duplo_preto->pai->c = PRETO;
        duplo_preto->pai->dir->c = VERMELHO;
        if(tem_filho(duplo_preto)){
            duplo_preto->c = PRETO;
            if(cor(duplo_preto->dir) == DUPLO_PRETO){
                duplo_preto->dir = NULL;
            } else{
                duplo_preto->esq = NULL;
            }

        } else{
            duplo_preto->pai->esq = NULL;
        }
        return;
    }
    //CASO 4: SIMETRICO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) == 0 && cor(duplo_preto->pai) == VERMELHO && cor(duplo_preto->pai->esq) == PRETO && cor(duplo_preto->pai->esq->dir)== PRETO && cor(duplo_preto->pai->esq->esq) == PRETO){
        duplo_preto->pai->c = PRETO;
        duplo_preto->pai->esq->c = VERMELHO;
        if(tem_filho(duplo_preto)){
            duplo_preto->c = PRETO;
            if(cor(duplo_preto->dir) == DUPLO_PRETO){
                duplo_preto->dir = NULL;
            } else{
                duplo_preto->esq = NULL;
            }

        } else{
            duplo_preto->pai->dir = NULL;
        }
        return;
    }
    //CASO 5: DUPLO PRETO ESQUERDA, PAI COR ARBITRARIA, IRMÃO PRETO, SOBRINHO INTERO VERMELHO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) && cor(duplo_preto->pai->dir) == PRETO && cor(duplo_preto->pai->dir->esq) == VERMELHO && cor(duplo_preto->pai->dir->dir) == PRETO ){
        no* p = duplo_preto->pai;
        no* s = p->dir;
        no* x = s->esq;

        s->esq = x->dir;
        x->dir = s;
        p->dir = x;

        x->c = PRETO;
        s->c = VERMELHO;

        p->dir->pai = p;
        x->dir->pai = x;

    }

    //CASO 5 SIMETRICO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) == 0 && cor(duplo_preto->pai->esq) == PRETO && cor(duplo_preto->pai->esq->dir) == VERMELHO && cor(duplo_preto->pai->esq->esq) == PRETO){
        no* p = duplo_preto->pai;
        no* s = p->esq;
        no* x = s->dir;

        s->dir = x->esq;
        p->esq = x;
        x->esq = s;

        x->c = PRETO;
        s->c = VERMELHO;

        p->esq->pai = p;
        x->esq->pai = x;
    }

    //CASO 6 : DUPLO PRETO ESQ, S PRETO E Y VERMELHO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) && cor(duplo_preto->pai->dir) == PRETO && cor(duplo_preto->pai->dir->dir) == VERMELHO){
        no* p = duplo_preto->pai;
        no* s = p->dir;
        no* x = s->esq;

        int P_ESQUERDO = filho_esquerdo(p);

        s->esq = p;
        p->dir = x;
        s->pai = p->pai;
        p->c = PRETO;
        p->pai = s;
        if(x != NULL){
            x->pai = p;
        }
        s->dir->c = PRETO;
        if(cor(s->pai) == VERMELHO){
            s->c = PRETO;
        } else{
            s->c = VERMELHO;
        }
        if(P_ESQUERDO){
            s->pai->esq = s;
        } else {
            s->pai->dir = s;
        }
        if(cor(p->esq) == DUPLO_PRETO && (cor(p->esq->dir) == DUPLO_PRETO || cor(p->esq->esq)== DUPLO_PRETO)){
            if(cor(p->esq->esq) == DUPLO_PRETO){
                p->esq->esq = NULL;
            } else{
                p->esq->dir = NULL;
            }
            p->esq->c = PRETO;
        } else{
            p->esq = NULL;
        }
        return;
    }

    // CASO 6 SIMETRICO
    if(duplo_preto != NULL && filho_esquerdo(duplo_preto) == 0 && cor(duplo_preto->pai->esq) == PRETO && cor(duplo_preto->pai->esq->esq) == VERMELHO){
        no* p = duplo_preto->pai;
        no* s = p->esq;
        no* x = s->dir;

        int P_ESQUERDO = filho_esquerdo(p);

        s->dir = p;
        p->esq = x;
        s->pai = p->pai;
        p->c = PRETO;
        p->pai = s;
        if(x != NULL){
            x->pai = p;
        }

        s->esq->c = PRETO;

        if(cor(s->pai) == VERMELHO){
            s->c = PRETO;
        } else{
            s->c = VERMELHO;
        }


        if(P_ESQUERDO){
            s->pai->esq = s;
        } else {
            s->pai->dir = s;
        }

        if(cor(p->dir) == DUPLO_PRETO && (cor(p->dir->esq) == DUPLO_PRETO) || cor(p->dir->dir)== DUPLO_PRETO){
            if(cor(p->dir->dir) == DUPLO_PRETO){
                p->dir->dir = NULL;
            } else{
                p->dir->esq = NULL;
            }
            p->dir->c = PRETO;
        } else{
            p->dir = NULL;
        }
        return;



    }
    reajustar(raiz, duplo_preto);
}
