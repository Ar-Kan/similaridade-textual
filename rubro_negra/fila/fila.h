#include <stdio.h>
#include <stdlib.h>

#include "rubro_negra/rubro_negra.h"

typedef struct TipoFila {
    Nodo *nodo;
    struct TipoFila *elo;
} TipoFila;


typedef struct Fila {
    struct TipoFila *primeiro;
    struct TipoFila *ultimo;
} Fila;


/**
 * Inicializa a fila
 * @param fila
 * @return A fila inicializada
 */
Fila *inicializar_fila();

/**
 * Verifica se a fila contém registros
 * @param fila
 * @return O próximo nodo
 */
Nodo *consultar_fila(Fila *fila);

/**
 * Imprime a fila no console
 * @param fila
 */
void imprimir_fila(Fila *fila);

/**
 * Insere um nodo na fila
 * @param fila
 * @param nodo
 * @return 1 se inseriu com sucesso, zero caso contrário
 */
int inserir_na_fila(Fila **fila, Nodo *nodo);

/**
 * Remove o próximo item da fila, retornando o nodo passado como parâmetro
 * @param fila
 * @param nodo Próximo item na fila
 * @return 0 se a fila não possui mais itens, 1 caso contrário
 */
int remover_da_fila(Fila **fila, Nodo **nodo);

/**
 * Destroi a lista
 * @param fila
 */
void destruir_fila(Fila **fila);

/**
 * Verifica se a lista está vazia
 * @param fila
 * @return 1 se a fila está vazia, 0 caso contrário
 */
int fila_esta_vazia(Fila *fila);
