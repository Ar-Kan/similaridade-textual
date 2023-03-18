/** @file fila.h */

#include <stdio.h>
#include <stdlib.h>

#include "rubro_negra/rubro_negra.h"

/// Retorna o primeiro item na fila
#define PRIMEIRO_DE(f) ((f)->primeiro)
/// Retorna o último item na fila
#define ULTIMO_DE(f) ((f)->ultimo)
/// Retorna a quantidade de elementos existentes na fila
#define QUANTIDADE_DE_ELEMENTOS_DE(f) ((f)->quantidade_de_elementos)
/// Retorna o nodo existente no elemento da fila
#define NODO_DE(t) ((t)->nodo)
/// Retorna o elo do nodo
#define ELO_DE(t) ((t)->elo)

typedef struct TipoFila {
    Nodo *nodo;
    struct TipoFila *elo;
} TipoFila;

typedef struct Fila {
    int quantidade_de_elementos;
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
 * Itera sobre a fila para contar a quantidade de elementos existentes
 *
 * @see fila.h::QUANTIDADE_DE_ELEMENTOS_DE()
 *
 * @param fila
 * @return
 */
int tamanho_da_fila(Fila *fila);

/**
 * Remove o próximo item da fila retornando-o
 * @param fila
 * @return Retorna o próximo item
 */
Nodo *remover_da_fila(Fila **fila);

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
