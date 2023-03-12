#include <stdio.h>


#include "rubro_negra_teste.h"
#include "util.h"


int executa_testes() {
    printf_verde(". Iniciando testes");
    printf("\n");

    if (executa_testes_de_criacao()) {
        printf_vermelho(". Testes de criacao terminaram com erro");
        return 1;
    }

    if (executa_testes_de_transformacao()) {
        printf_vermelho(". Testes de transformacao terminaram com erro");
        return 1;
    }

    printf("\n");
    printf_verde(". Testes executaram com sucesso");

    return 0;
}
