#include <stdlib.h>
#include <stdio.h>

#include "rubro_negra_teste.h"
#include "util.h"

/**
 * Testa a mudança de cores na árvore, após uma inserção.
 *
 * Estrutura esperada:
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "e");
 * inserir(&raiz, "g");
 * inserir(&raiz, "b");
 * inserir(&raiz, "a");
 * print(raiz);
 *
 * // estrutura esperada
 *          D: g (n)
 *  o: e (n)
 *          E: b (n)
 *                  E: a (r)
 * @endcode
 *
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_troca_de_cores() {
    Nodo *raiz = NULL;
    inserir(&raiz, "e");
    inserir(&raiz, "g");
    inserir(&raiz, "b");
    inserir(&raiz, "a");

    NodoTeste t1 = {.palavra="e", .cor=NEGRO, .esquerda="b", .direita="g", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;

    Nodo *nodo = ESQUERDA_DE(raiz);
    NodoTeste t2 = {.palavra="b", .cor=NEGRO, .esquerda="a", .direita=NULL, .pai="e"};
    if (compara_nodos(nodo, &t2)) return 1;

    nodo = ESQUERDA_DE(nodo);
    NodoTeste t3 = {.palavra="a", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="b"};
    if (compara_nodos(nodo, &t3)) return 1;

    nodo = DIREITA_DE(raiz);
    NodoTeste t4 = {.palavra="g", .cor=NEGRO, .esquerda=NULL, .direita=NULL, .pai="e"};
    if (compara_nodos(nodo, &t4)) return 1;

    return 0;
}

/**
 * Testa a rotação simples à esquerda, após uma inserção.
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "e");
 * inserir(&raiz, "h");
 * inserir(&raiz, "i");
 * print(raiz);
 *
 * // estrutura esperada
 *          D: i (r)
 *  o: h (n)
 *          E: e (r)
 *
 * @endcode
 *
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_rotacao_simples_esquerda() {
    Nodo *raiz = NULL;
    inserir(&raiz, "e");
    inserir(&raiz, "h");
    inserir(&raiz, "i");

    NodoTeste t1 = {.palavra="h", .cor=NEGRO, .esquerda="e", .direita="i", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;

    Nodo *nodo = ESQUERDA_DE(raiz);
    NodoTeste t2 = {.palavra="e", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="h"};
    if (compara_nodos(nodo, &t2)) return 1;

    nodo = DIREITA_DE(raiz);
    NodoTeste t3 = {.palavra="i", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="h"};
    if (compara_nodos(nodo, &t3)) return 1;

    return 0;
}

/**
 * Testa a rotação simples à direita, após uma inserção.
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "e");
 * inserir(&raiz, "b");
 * inserir(&raiz, "a");
 * print(raiz);
 *
 * // estrutura esperada
 *          D: e (r)
 *  o: b (n)
 *          E: a (r)
 * @endcode
 *
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_rotacao_simples_direita() {
    Nodo *raiz = NULL;
    inserir(&raiz, "e");
    inserir(&raiz, "b");
    inserir(&raiz, "a");

    NodoTeste t1 = {.palavra="b", .cor=NEGRO, .esquerda="a", .direita="e", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;

    Nodo *nodo = ESQUERDA_DE(raiz);
    NodoTeste t2 = {.palavra="a", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="b"};
    if (compara_nodos(nodo, &t2)) return 1;

    nodo = DIREITA_DE(raiz);
    NodoTeste t3 = {.palavra="e", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="b"};
    if (compara_nodos(nodo, &t3)) return 1;

    return 0;
}

/**
 * Testa a rotação dupla à esquerda, após uma inserção.
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "e");
 * inserir(&raiz, "b");
 * inserir(&raiz, "a");
 * inserir(&raiz, "c");
 * inserir(&raiz, "d");
 * print(raiz);
 *
 * // estrutura esperada:
 *                  D: e (r)
 *          D: d (n)
 *                  E: c (r)
 *  o: b (n)
 *          E: a (n)
 * @endcode
 *
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_rotacao_dupla_esquerda() {
    Nodo *raiz = NULL;
    inserir(&raiz, "e");
    inserir(&raiz, "b");
    inserir(&raiz, "a");
    inserir(&raiz, "c");
    inserir(&raiz, "d");

    NodoTeste t1 = {.palavra="b", .cor=NEGRO, .esquerda="a", .direita="d", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;

    Nodo *nodo = ESQUERDA_DE(raiz);
    NodoTeste t2 = {.palavra="a", .cor=NEGRO, .esquerda=NULL, .direita=NULL, .pai="b"};
    if (compara_nodos(nodo, &t2)) return 1;

    nodo = DIREITA_DE(raiz);
    NodoTeste t3 = {.palavra="d", .cor=NEGRO, .esquerda="c", .direita="e", .pai="b"};
    if (compara_nodos(nodo, &t3)) return 1;

    nodo = DIREITA_DE(DIREITA_DE(raiz));
    NodoTeste t4 = {.palavra="e", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="d"};
    if (compara_nodos(nodo, &t4)) return 1;

    nodo = ESQUERDA_DE(DIREITA_DE(raiz));
    NodoTeste t5 = {.palavra="c", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="d"};
    if (compara_nodos(nodo, &t5)) return 1;

    return 0;
}

/**
 * Testa a rotação dupla à direita, após uma inserção.
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "q");
 * inserir(&raiz, "m");
 * inserir(&raiz, "h");
 * inserir(&raiz, "j");
 * inserir(&raiz, "i");
 * print(raiz);
 *
 * // estrutura esperada:
 *         D: q (n)
 * o: m (n)
 *                 D: j (r)
 *         E: i (n)
 *                 E: h (r)
 * @endcode
 *
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_rotacao_dupla_direita() {
    Nodo *raiz = NULL;
    inserir(&raiz, "q");
    inserir(&raiz, "m");
    inserir(&raiz, "h");
    inserir(&raiz, "j");
    inserir(&raiz, "i");

    NodoTeste t1 = {.palavra="m", .cor=NEGRO, .esquerda="i", .direita="q", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;

    Nodo *nodo = DIREITA_DE(raiz);
    NodoTeste t2 = {.palavra="q", .cor=NEGRO, .esquerda=NULL, .direita=NULL, .pai="m"};
    if (compara_nodos(nodo, &t2)) return 1;

    nodo = ESQUERDA_DE(raiz);
    NodoTeste t3 = {.palavra="i", .cor=NEGRO, .esquerda="h", .direita="j", .pai="m"};
    if (compara_nodos(nodo, &t3)) return 1;

    nodo = DIREITA_DE(ESQUERDA_DE(raiz));
    NodoTeste t4 = {.palavra="j", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="i"};
    if (compara_nodos(nodo, &t4)) return 1;

    nodo = ESQUERDA_DE(ESQUERDA_DE(raiz));
    NodoTeste t5 = {.palavra="h", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="i"};
    if (compara_nodos(nodo, &t5)) return 1;

    return 0;
}

int executa_testes_de_transformacao() {
    printf("Testando \"troca de cores\"\n");
    if (teste_troca_de_cores()) {
        printf_vermelho("Teste de \"troca de cores\" terminou com erros");
        return 1;
    }
    printf("Testando \"rotacao simples esquerda\"\n");
    if (teste_rotacao_simples_esquerda()) {
        printf_vermelho("Teste de \"rotacao simples esquerda\" terminou com erros");
        return 1;
    }
    printf("Testando \"rotacao simples direita\"\n");
    if (teste_rotacao_simples_direita()) {
        printf_vermelho("Teste de \"rotacao simples direita\" terminou com erros");
        return 1;
    }
    printf("Testando \"rotacao dupla esquerda\"\n");
    if (teste_rotacao_dupla_esquerda()) {
        printf_vermelho("Teste de \"rotacao dupla esquerda\" terminou com erros");
        return 1;
    }
    printf("Testando \"rotacao dupla direita\"\n");
    if (teste_rotacao_dupla_direita()) {
        printf_vermelho("Teste de \"rotacao dupla direita\" terminou com erros");
        return 1;
    }
    return 0;
}