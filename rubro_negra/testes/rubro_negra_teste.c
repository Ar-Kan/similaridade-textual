#include <stdio.h>


#include "rubro_negra_teste.h"
#include "util.h"


int executa_testes() {
    printf_verde(". Iniciando testes");

    printf("\n");
    printf(". Iniciando testes de criacao\n");
    if (executa_testes_de_criacao()) {
        printf_vermelho(". Testes de criacao terminaram com erro");
        return 1;
    }
    printf(". Testes de criacao executaram com sucesso\n");

    printf("\n");
    printf(". Iniciando testes de balanceamento\n");
    if (executa_testes_de_balanceamento()) {
        printf_vermelho(". Testes de transformacao terminaram com erro");
        return 1;
    }
    printf(". Testes de balanceamento executaram com sucess\n");

    printf("\n");
    printf_verde(". Testes executaram com sucesso");
    return 0;
}
