#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "rubro_negra.h"
#include "rubro_negra/fila/fila.h"

Nodo *criar(char *palavra) {
    Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
    if (nodo == NULL) {
        printf("Erro ao alocar novo nodo, memoria insuficiente.\n");
        return NULL;
    }
    COR_DE(nodo) = RUBRO; // novos nodos são vermelhos
    ESQUERDA_DE(nodo) = NULL;
    DIREITA_DE(nodo) = NULL;
    PAI_DE(nodo) = NULL;
    PALAVRA_DE(nodo) = malloc(strlen(palavra) + 1);
    strcpy(PALAVRA_DE(nodo), palavra);
    return nodo;
}


/**
 * Função recursiva auxiliar, para inserir o nodo na árvore
 * @param [in,out] subarvore Raiz da subarvore
 * @param [in,out] nodo Nodo que será inserido
 * @return 1 se foi inserido com sucesso, 0 caso a palavra já exista
 */
int _inserir(Nodo **subarvore, Nodo **nodo) {
    int comparacao = strcmp(PALAVRA_DE(*nodo), PALAVRA_DE(*subarvore));
    if (comparacao == 0) return 0;
    if (comparacao < 0) {
        if (ESQUERDA_DE(*subarvore) == NULL) {
            PAI_DE(*nodo) = *subarvore;
            ESQUERDA_DE(*subarvore) = *nodo;
            return 1;
        }
        return _inserir(&ESQUERDA_DE(*subarvore), nodo);
    } else {
        if (DIREITA_DE(*subarvore) == NULL) {
            PAI_DE(*nodo) = *subarvore;
            DIREITA_DE(*subarvore) = *nodo;
            return 1;
        }
        return _inserir(&DIREITA_DE(*subarvore), nodo);
    }
}

void inserir(Nodo **raiz, char *palavra) {
    if (!palavra) return;

    Nodo *nodo = criar(palavra);
    if (!(*raiz)) {
        COR_DE(nodo) = NEGRO; // raiz é de cor preta
        *raiz = nodo;
        return;
    }
    int inserido = _inserir(raiz, &nodo);
    if (inserido)
        balancear(raiz, nodo);
}

Nodo *jump_search_arvore(Nodo *raiz, char *palavra, int quantidade_de_nodos) {
    int amplitude = floor(sqrt(quantidade_de_nodos));
    int inicio;
    int final = amplitude;

//    printf("palavra buscada: %s\n", palavra);
//    printf("final: %d\n", final);
//    printNthNode(raiz, final);
//    iterative_inorder(raiz, final);
    Nodo *nodo_no_final = NULL;// iterative_inorder(raiz, final);
    while (strcmp(PALAVRA_DE(nodo_no_final), palavra) < 0 && final < quantidade_de_nodos) {
        inicio = final;
        final += amplitude;
        if (final > quantidade_de_nodos - 1)
            final = quantidade_de_nodos;
        nodo_no_final = NULL;// iterative_inorder(raiz, final);
//        printf("final: %d\n", final);
//        printf("palavra: %s\n", palavra);
//        printf("palavra nodo: %s\n", PALAVRA_DE(nodo_no_final));
    }

    Nodo *nodo_atual = NULL;
    for (int i = inicio; i < final; i++) {
        nodo_atual = NULL;// iterative_inorder(raiz, i);
        if (strcmp(PALAVRA_DE(nodo_atual), palavra) == 0)
            return nodo_atual;
    }
    return NULL;
}

Nodo *pesquisar(Nodo *raiz, char *palavra) {
    if (!raiz)
        return NULL;

    int comparacao = strcmp(palavra, PALAVRA_DE(raiz));
    if (comparacao == 0)
        return raiz;
    else if (comparacao < 0)
        return pesquisar(ESQUERDA_DE(raiz), palavra);
    else
        return pesquisar(DIREITA_DE(raiz), palavra);
}

int contar_nodos(Nodo *raiz) {
    if (raiz) {
        return 1 + contar_nodos(ESQUERDA_DE(raiz)) + contar_nodos(DIREITA_DE(raiz));
    }
    return 0;
}

/**
 * Função recursiva auxiliar, para fazer o imprimir_arvore da árvore
 * @param nodo Nodo atual
 * @param contador Contador da posição atual
 * @param posicao Se esquerda (E), direita (D) ou origem (O)
 */
void imprimir_arvore_auxiliar(Nodo *nodo, const int contador, const char *posicao) {
    if (nodo) {
        imprimir_arvore_auxiliar(DIREITA_DE(nodo), contador + 1, "D");
        printf("%*s", 8 * contador, "");
        if (posicao)
            printf("%s: ", posicao);
        printf("%s", PALAVRA_DE(nodo));
        printf(" (%s)\n", COR_DE(nodo) == RUBRO ? "r" : "n");
        imprimir_arvore_auxiliar(ESQUERDA_DE(nodo), contador + 1, "E");
    }
}

void imprimir_arvore(Nodo *nodo) {
    imprimir_arvore_auxiliar(nodo, 0, "o");
}

char *nodo_str(Nodo *nodo) {
    if (!nodo)
        return "Nodo{NULL}";

    return nodo_str_auxiliar(
            PALAVRA_DE(nodo),
            COR_DE(nodo) == NEGRO ? "NEGRO" : "RUBRO",
            PALAVRA_OU_NULL_DE(ESQUERDA_DE(nodo)),
            PALAVRA_OU_NULL_DE(DIREITA_DE(nodo)),
            PALAVRA_OU_NULL_DE(PAI_DE(nodo))
    );
}


char *nodo_str_auxiliar(char *palavra, char *cor, char *esquerda, char *direita, char *pai) {
    char retorno[100] = "";
    strcat(retorno, "Nodo{.palavra=\"");
    strcat(retorno, palavra);
    strcat(retorno, "\", .cor=");
    strcat(retorno, cor);
    strcat(retorno, ", .esquerda=");
    if (esquerda == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, esquerda);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .direita=");
    if (direita == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, direita);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .pai=");
    if (pai == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, pai);
        strcat(retorno, "\"");
    }
    strcat(retorno, "}");
    char *str = malloc(sizeof(retorno));
    strcpy(str, retorno);
    return str;
}
