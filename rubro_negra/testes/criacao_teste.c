#include <stdio.h>
#include <string.h>

#include "rubro_negra_teste.h"
#include "util.h"


/**
 * Testa a criação de nodos
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_criar_nodo() {
    Nodo *receido = criar("a");
    NodoTeste esperado = {.palavra="a", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai=NULL};
    if (compara_nodos(receido, &esperado)) return 1;
    return 0;
}

/**
 * Testa a inserção de nodos na árvore
 * @code
 * // execução
 * Nodo *raiz = NULL;
 * inserir(&raiz, "a");
 * inserir(&raiz, "b");
 * inserir(&raiz, "a");
 * imprimir_arvore(raiz);
 *
 * // estrutura esperada:
 *         D: b (r)
 * o: a (n)
 * @endcode
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_inserir() {
    Nodo *raiz = NULL;
    inserir(&raiz, "a");
    inserir(&raiz, "b");
    inserir(&raiz, "a");

    NodoTeste t1 = {.palavra="a", .cor=NEGRO, .esquerda=NULL, .direita="b", .pai=NULL};
    if (compara_nodos(raiz, &t1)) return 1;
    NodoTeste t2 = {.palavra="b", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="a"};
    if (compara_nodos(DIREITA_DE(raiz), &t2)) return 1;

    return 0;
}

/**
 * Testa a pesquisa de nodos na árvore
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_pesquisar() {
    Nodo *raiz = NULL;
    inserir(&raiz, "a");
    inserir(&raiz, "b");

    NodoTeste t1 = {.palavra="a", .cor=NEGRO, .esquerda=NULL, .direita="b", .pai=NULL};
    if (compara_nodos(pesquisar(raiz, "a"), &t1)) return 1;
    NodoTeste t2 = {.palavra="b", .cor=RUBRO, .esquerda=NULL, .direita=NULL, .pai="a"};
    if (compara_nodos(pesquisar(raiz, "b"), &t2)) return 1;
    if (compara_nodos(pesquisar(raiz, "c"), NULL)) return 1;

    return 0;
}

/**
 * Testa a representação de um tipo Nodo em string
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_nodo_str() {
    Nodo *t1 = criar("a");
    Nodo *t2 = criar("b");
    Nodo *t3 = criar("c");
    PAI_DE(t3) = t1;
    ESQUERDA_DE(t3) = t2;
    NodoTeste e1 = {.palavra="c", .cor=RUBRO, .esquerda="b", .direita=NULL, .pai="a"};
    char *recebido = nodo_str(t3);
    char *esperado = nodoTeste_str(&e1);
    if (strcmp(recebido, esperado) != 0) {
        printf("Teste de \"nodo string\"\n");
        printf("recebido: ");
        printf("%s\n", recebido);
        printf("eseprado: ");
        printf("%s\n", esperado);
        return 1;
    }
    recebido = nodo_str(NULL);
    esperado = nodoTeste_str(NULL);
    if (strcmp(recebido, esperado) != 0) {
        printf("Teste de \"nodo string\"\n");
        printf("recebido: ");
        printf("%s\n", recebido);
        printf("esperado: ");
        printf("%s\n", esperado);
        return 1;
    }
    return 0;
}

/**
 * Testa a contagem de nodos de uma árvore
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int teste_contar_nodos() {
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

    int nodos = tamanho_arvore(raiz);
    if (nodos != 12) {
        printf("Quantidade de nodos nao corresponde ao esperado\n");
        printf("recebido: %d\n", nodos);
        printf("esperado: 12\n");
        return 1;
    }
    return 0;
}

int executa_testes_de_criacao() {
    printf("Testando \"criar nodo\"\n");
    if (teste_criar_nodo()) {
        printf_vermelho("Teste de \"criar nodo\" terminou com erros");
        return 1;
    }
    printf("Testando \"inserir nodo\"\n");
    if (teste_inserir()) {
        printf_vermelho("Teste de \"inserir nodo\" terminou com erros");
        return 1;
    }
    printf("Testando \"pesqusar nodo\"\n");
    if (teste_pesquisar()) {
        printf_vermelho("Teste de \"pesquisar nodo\" terminou com erros");
        return 1;
    }
    printf("Testando \"contar nodos\"\n");
    if (teste_contar_nodos()) {
        printf_vermelho("Teste de \"contar nodos\" terminou com erros");
        return 1;
    }
    printf("Testando \"nodo string\"\n");
    if (teste_nodo_str()) {
        printf_vermelho("Teste de \"nodo string\" terminou com erros");
        return 1;
    }
    return 0;
}
