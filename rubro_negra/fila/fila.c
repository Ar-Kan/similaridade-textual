#include <stdio.h>
#include <stdlib.h>

#include "fila.h"


Fila *inicializar_fila() {
    Fila *fila = (Fila *) malloc(sizeof(Fila)); // aloca descritor de fila

    if (fila) { // testa se conseguiu alocar o descritor
        PRIMEIRO_DE(fila) = NULL; // inicializa ponteiros
        ULTIMO_DE(fila) = NULL;
    }
    return fila;
}

int fila_esta_vazia(Fila *fila) {
    if (!fila) {
        printf("descritor nao alocado");
        return -1;
    } else if (!PRIMEIRO_DE(fila))
        return 1;
    else
        return 0;

}

Nodo *consultar_fila(Fila *fila) {
    if (!fila) {
        printf("descritor nao alocado");
        return 0;
    }
    if (!PRIMEIRO_DE(fila))
        return 0;
    else
        return NODO_DE(PRIMEIRO_DE(fila));

}

int inserir_na_fila(Fila **fila, Nodo *nodo) {
    if (!nodo) return 0;

    TipoFila *novo;
    if (*fila) { // testa se o descritor foi alocado
        novo = (TipoFila *) malloc(sizeof(TipoFila));
        NODO_DE(novo) = nodo;
        ELO_DE(novo) = NULL;
        if (!PRIMEIRO_DE(*fila)) // vai ser o primeiro da fila
            PRIMEIRO_DE(*fila) = novo;
        else
            ELO_DE(ULTIMO_DE(*fila)) = novo; // insere no final
        ULTIMO_DE(*fila) = novo;
        return 1;
    } else {
        printf("descritor nao alocado");
        return 0;
    }
}

int tamanho_da_fila(Fila *fila) {
    TipoFila *ptaux;
    if (fila) {
        int tamanho = 0;
        if (PRIMEIRO_DE(fila)) {
            for (ptaux = PRIMEIRO_DE(fila); ptaux != NULL; ptaux = ELO_DE(ptaux)) {
                tamanho++;
            }
        }
        return tamanho;
    } else
        return 0;
}

int remover_da_fila(Fila **fila, Nodo **nodo) {
    TipoFila *ptaux;
    if (*fila) { //testa se o descritor foi alocado
        if (PRIMEIRO_DE(*fila)) { // testa se tem algum elemento na fila
            ptaux = PRIMEIRO_DE(*fila);
            *nodo = NODO_DE(PRIMEIRO_DE(*fila));
            PRIMEIRO_DE(*fila) = ELO_DE(PRIMEIRO_DE(*fila));
            free(ptaux);
            if (!PRIMEIRO_DE(*fila)) // testa se a fila ficou vazia
                ULTIMO_DE(*fila) = NULL;
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
        if (PRIMEIRO_DE(fila)) {
            puts("---Imprimindo fila---");
            for (ptaux = PRIMEIRO_DE(fila); ptaux != NULL; ptaux = ELO_DE(ptaux))
                printf("%s\n", nodo_str(NODO_DE(ptaux)));
            puts("-------Fim fila------");
        }
    } else
        puts("Fila vazia");
}

void destruir_fila(Fila **fila) {
    TipoFila *ptaux;
    while (PRIMEIRO_DE(*fila)) {
        ptaux = PRIMEIRO_DE(*fila); // guarda o endereço do primeiro
        PRIMEIRO_DE(*fila) = ELO_DE(PRIMEIRO_DE(*fila)); // o próximo passa a ser o topo
        free(ptaux); // libera o que estava no topo
    }
    free(*fila);
    *fila = NULL;
}
