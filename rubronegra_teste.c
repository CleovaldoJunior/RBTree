#include <stdio.h>
#include <stdlib.h>
#include "rubronegra.h"
#include "rubronegra.c"

int main() {
    int n;
    int opcao;
    no *arvore = NULL;
    while(1==1) {
        printf("1 -> inserir\n2 -> print ordenado\n3 -> remover\n999 -> sair\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                printf("Numero para inserir:");
                scanf("%d", &n);
                inserir(&arvore, n);
                break;
            case 2:
                pre_order(arvore);
                printf("\n");
                break;
            case 3:
                printf("Numero para remover:");
                scanf("%d", &n);
                remover(&arvore, n);
                break;
            case 999:
                exit(0);
        }

    }
}

