#include <locale.h>
#include <stdio.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra_teste/rubro_negra_teste.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    executa_testes();

    return 0;
}
