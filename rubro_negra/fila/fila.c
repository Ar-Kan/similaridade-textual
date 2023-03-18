#include <stdio.h>
#include <stdlib.h>

#include "fila.h"


Fila *inicializar_fila() {
    Fila *fila = (Fila *) malloc(sizeof(Fila)); // aloca descritor de fila

    if (fila) { // testa se conseguiu alocar o descritor
        fila->primeiro = NULL; // inicializa ponteiros
        fila->ultimo = NULL;
    }
    return fila;
}

int fila_esta_vazia(Fila *fila) {
    if (!fila) {
        printf("descritor nao alocado");
        return -1;
    } else if (!(fila->primeiro))
        return 1;
    else
        return 0;

}

Nodo *consultar_fila(Fila *fila) {
    if (!fila) {
        printf("descritor nao alocado");
        return 0;
    }
    if (!(fila->primeiro))
        return 0;
    else
        return fila->primeiro->nodo;

}


int inserir_na_fila(Fila **fila, Nodo *nodo) {
    if (!nodo) return 0;

    TipoFila *novo;
    if (*fila) { // testa se o descritor foi alocado
        novo = (TipoFila *) malloc(sizeof(TipoFila));
        novo->nodo = nodo;
        novo->elo = NULL;
        if (!((*fila)->primeiro)) // vai ser o primeiro da fila
            (*fila)->primeiro = novo;
        else
            (*fila)->ultimo->elo = novo; // insere no final
        (*fila)->ultimo = novo;
        return 1;
    } else {
        printf("descritor nao alocado");
        return 0;
    }
}


int remover_da_fila(Fila **fila, Nodo **nodo) {
    TipoFila *ptaux;
    if (*fila) { //testa se o descritor foi alocado
        if ((*fila)->primeiro) { // testa se tem algum elemento na fila
            ptaux = (*fila)->primeiro;
            *nodo = (*fila)->primeiro->nodo;
            (*fila)->primeiro = (*fila)->primeiro->elo;
            free(ptaux);
            if (!((*fila)->primeiro)) // testa se a fila ficou vazia
                (*fila)->ultimo = NULL;
            return 1;
        }
    } else {
        printf("descritor nao alocado");
        return 0;
    }
    return 0;
}


void imprimir_fila(Fila *fila) {
    TipoFila *ptaux;
    if (fila) {
        if (fila->primeiro) {
            puts("---Imprimindo fila---");
            for (ptaux = fila->primeiro; ptaux != NULL; ptaux = ptaux->elo)
                printf("\"%s\"\n", PALAVRA_OU_NULL_DE(ptaux->nodo));
            puts("-------Fim fila------");
        }
    } else
        puts("Fila vazia");
}


void destruir_fila(Fila **fila) {
    TipoFila *ptaux;
    while ((*fila)->primeiro) {
        ptaux = (*fila)->primeiro; // guarda o endereço do primeiro
        (*fila)->primeiro = (*fila)->primeiro->elo; // o próximo passa a ser o topo
        free(ptaux); // libera o que estava no topo
    }
    free(*fila);
    *fila = NULL;
}
