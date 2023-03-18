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
 * imprimir_arvore(raiz);
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
 * imprimir_arvore(raiz);
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
 * imprimir_arvore(raiz);
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
 * imprimir_arvore(raiz);
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
 * imprimir_arvore(raiz);
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

int verifica_integridade_auxiliar(Nodo *nodo) {
    if (nodo) {
        if (VERMELHO(nodo) && VERMELHO(PAI_DE(nodo))) {
            printf("Foi encontrado um nodo vermelho com pai vermelho\n");
            printf("nodo: ");
            printf("%s\n", nodo_str(nodo));
            printf("pai: ");
            printf("%s\n", nodo_str(PAI_DE(nodo)));
            return 1;
        }
        if (verifica_integridade_auxiliar(DIREITA_DE(nodo))) return 1;
        if (verifica_integridade_auxiliar(ESQUERDA_DE(nodo))) return 1;
    }
    return 0;
}

/**
 * Verifica se nenhum nodo vermelho possui pai vermelho
 *
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "r");
 * inserir(&raiz, "e");
 * inserir(&raiz, "d");
 * inserir(&raiz, "b");
 * inserir(&raiz, "l");
 * inserir(&raiz, "a");
 * inserir(&raiz, "c");
 * inserir(&raiz, "k");
 * inserir(&raiz, "t");
 * inserir(&raiz, "g");
 * inserir(&raiz, "s");
 * inserir(&raiz, "f");
 *
 * // estrutura esperada:
 *                         D: t (r)
 *                 D: s (n)
 *                         E: r (r)
 *         D: l (r)
 *                         D: k (r)
 *                 E: g (n)
 *                         E: f (r)
 * o: e (n)
 *                 D: d (n)
 *                         E: c (r)
 *         E: b (r)
 *                 E: a (n)
 * @endcode
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_integriadade_da_arvore() {
    Nodo *raiz = NULL;
    inserir(&raiz, "r");
    inserir(&raiz, "e");
    inserir(&raiz, "d");
    inserir(&raiz, "b");
    inserir(&raiz, "l");
    inserir(&raiz, "a");
    inserir(&raiz, "c");
    inserir(&raiz, "k");
    inserir(&raiz, "t");
    inserir(&raiz, "g");
    inserir(&raiz, "s");
    inserir(&raiz, "f");

    int nodos = contar_nodos(raiz);
    if (nodos != 12) {
        printf("Quantidade de nodos nao corresponde ao esperado\n");
        printf("recebido: %d\n", nodos);
        printf("esperado: 12\n");
        return 1;
    }

    return verifica_integridade_auxiliar(raiz);
}

int executa_testes_de_balanceamento() {
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
    printf("Testando \"integridade da arvore\"\n");
    if (teste_integriadade_da_arvore()) {
        printf_vermelho("Teste de \"integridade da arvore\" terminou com erros");
        return 1;
    }
    return 0;
}