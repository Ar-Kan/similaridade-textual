#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rubro_negra/rubro_negra.h"
#include "util.h"

/// Safe string compare
int sstrcmp(char *str1, char *str2) {
    if (!str1 && !str2) return 0;
    if (!str1 || !str2) return 1;
    return strcmp(str1, str2);
}


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
    if (!recebido && !esperado) {
        return 0;
    }
    if (recebido != NULL && esperado == NULL) {
        printf("Recebido nodo nao-nulo, mas era esperado nulo\n");
        erro = 1;
    }
    if (recebido == NULL && esperado != NULL) {
        printf("Recebido nodo nulo, mas era esperado não nulo\n");
        erro = 1;
    }
    if (strcmp(PALAVRA_DE(recebido), PALAVRA_DE(esperado)) != 0) {
        printf("Palavra do nodo nao corresponde ao esperado\n");
        erro = 1;
    }
    if (COR_DE(recebido) != COR_DE(esperado)) {
        printf("Cor do nodo nao corresponde ao esperado\n");
        erro = 1;
    }
    if (sstrcmp(PALAVRA_OU_NULL_DE(DIREITA_DE(recebido)), DIREITA_DE(esperado)) != 0) {
        printf("Direira do nodo nao corresponde ao esperado\n");
        erro = 1;
    }
    if (sstrcmp(PALAVRA_OU_NULL_DE(ESQUERDA_DE(recebido)), ESQUERDA_DE(esperado)) != 0) {
        printf("Esquerda do nodo nao corresponde ao esperado\n");
        erro = 1;
    }
    if (sstrcmp(PALAVRA_OU_NULL_DE(PAI_DE(recebido)), PAI_DE(esperado)) != 0) {
        printf("Pai do nodo nao corresponde ao esperado\n");
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
    printf("\x1b[31m%s\x1b[0man\n", mensagem);
}

void printf_verde(char *mensagem) {
    printf("\x1b[32m%s\x1b[0m\n", mensagem);
}
