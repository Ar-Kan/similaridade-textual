#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rubro_negra.h"

Nodo *criar(char *palavra) {
    Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
    if (!nodo) {
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
int inserir_auxiliar(Nodo **subarvore, Nodo **nodo) {
    int comparacao = strcmp(PALAVRA_DE(*nodo), PALAVRA_DE(*subarvore));
    if (comparacao == 0) return 0;
    if (comparacao < 0) {
        if (!ESQUERDA_DE(*subarvore)) {
            PAI_DE(*nodo) = *subarvore;
            ESQUERDA_DE(*subarvore) = *nodo;
            return 1;
        }
        return inserir_auxiliar(&ESQUERDA_DE(*subarvore), nodo);
    } else {
        if (!DIREITA_DE(*subarvore)) {
            PAI_DE(*nodo) = *subarvore;
            DIREITA_DE(*subarvore) = *nodo;
            return 1;
        }
        return inserir_auxiliar(&DIREITA_DE(*subarvore), nodo);
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
    int inserido = inserir_auxiliar(raiz, &nodo);
    if (inserido)
        balancear(raiz, nodo);
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

int tamanho_arvore(Nodo *raiz) {
    if (raiz) {
        return 1 + tamanho_arvore(ESQUERDA_DE(raiz)) + tamanho_arvore(DIREITA_DE(raiz));
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
    if (!esquerda) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, esquerda);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .direita=");
    if (!direita) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, direita);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .pai=");
    if (!pai) {
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
