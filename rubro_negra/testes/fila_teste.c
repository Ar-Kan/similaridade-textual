#include <stdlib.h>
#include <stdio.h>

#include "rubro_negra_teste.h"
#include "util.h"
#include "rubro_negra/fila_rubro_negra.h"

/**
                 D: d (r)
        D: c (n)
o: b (n)
        E: a (n)
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_insere_na_fila() {
    Nodo *raiz = NULL;
    inserir(&raiz, "a");
    inserir(&raiz, "b");
    inserir(&raiz, "c");
    inserir(&raiz, "d");

    Fila *fila = listar_nodos(raiz);

    if (fila_esta_vazia(fila)) {
        printf("A fila esta vazia");
        return 1;
    }

    Nodo *proximo = NULL;

    remover_da_fila(&fila, &proximo);
    NodoTeste t4 = {.palavra="a", .cor=NEGRO, .esquerda=NULL, .direita=NULL, .pai="b"};
    if (compara_nodos(proximo, &t4)) return 1;

    remover_da_fila(&fila, &proximo);
    NodoTeste t3 = {.palavra="b", .cor=NEGRO, .esquerda="a", .direita="c", .pai=NULL};
    if (compara_nodos(proximo, &t3)) return 1;

    remover_da_fila(&fila, &proximo);
    NodoTeste t2 = {.palavra="c", .cor=NEGRO, .esquerda=NULL, .direita="d", .pai="b"};
    if (compara_nodos(proximo, &t2)) return 1;

    remover_da_fila(&fila, &proximo);
    NodoTeste t1 = {.palavra="d", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="c"};
    if (compara_nodos(proximo, &t1)) return 1;

    if (!fila_esta_vazia(fila)) {
        printf("A fila nao se esvaziou apos a remocao dos seus itens");
        return 1;
    }

    return 0;
}

int executa_testes_de_fila() {
    printf("Testando \"fila\"\n");
    if (teste_insere_na_fila()) {
        printf_vermelho("Teste de \"fila\" terminou com erros");
        return 1;
    }
    return 0;
}
