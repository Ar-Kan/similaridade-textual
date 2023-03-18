#include "fila_rubro_negra.h"

void listar_nodos_auxiliar(Nodo *nodo, Fila **fila) {
    if (nodo) {
        listar_nodos_auxiliar(ESQUERDA_DE(nodo), fila);
        inserir_na_fila(fila, nodo);
        listar_nodos_auxiliar(DIREITA_DE(nodo), fila);
    }
}

Fila *listar_nodos(Nodo *raiz) {
    Fila *fila = inicializar_fila();
    listar_nodos_auxiliar(raiz, &fila);
    return fila;
}
