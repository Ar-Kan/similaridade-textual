#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rubro_negra/rubro_negra.h"
#include "util.h"

char *nodoTeste_str(NodoTeste *nodo) {
    if (!nodo)
        return "Nodo{NULL}";
    return nodo_str_auxiliar(
            PALAVRA_DE(nodo),
            COR_DE(nodo) == NEGRO ? "NEGRO" : "RUBRO",
            ESQUERDA_DE(nodo),
            DIREITA_DE(nodo),
            PAI_DE(nodo)
    );
}

int compara_nodos(Nodo *recebido, NodoTeste *esperado) {
    int erro = 0;
    if (recebido != NULL && esperado == NULL) {
        printf("Recebido nodo nao-nulo\n");
        erro = 1;
    }
    if (recebido == NULL && esperado != NULL) {
        printf("Recebido nodo nulo\n");
        erro = 1;
    }
    if (strcmp(PALAVRA_DE(recebido), PALAVRA_DE(esperado)) != 0) {
        printf("Palavra nao corresponde ao esperado\n");
        erro = 1;
    }
    if (COR_DE(recebido) != COR_DE(esperado)) {
        printf("Cor nao corresponde ao esperado\n");
        erro = 1;
    }
    if (PALAVRA_OU_NULL_DE(DIREITA_DE(recebido)) != DIREITA_DE(esperado)) {
        printf("Direira nao corresponde ao esperado\n");
        erro = 1;
    }
    if (PALAVRA_OU_NULL_DE(ESQUERDA_DE(recebido)) != ESQUERDA_DE(esperado)) {
        printf("Esquerda nao corresponde ao esperado\n");
        erro = 1;
    }
    if (PALAVRA_OU_NULL_DE(PAI_DE(recebido)) != PAI_DE(esperado)) {
        printf("Pai nao corresponde ao esperado\n");
        erro = 1;
    }

    if (erro) {
        printf("recebido: ");
        printf("%s\n", nodo_str(recebido));
        printf("esperado: ");
        printf("%s\n", nodoTeste_str(esperado));
        return 1;
    }

    return 0;
}

void printf_vermelho(char *mensagem) {
    printf("\x1b[31m%s\x1b[0man", mensagem);
}

void printf_verde(char *mensagem) {
    printf("\x1b[32m%s\x1b[0m\n", mensagem);
}
