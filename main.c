#include <locale.h>
#include <stdio.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra/testes/rubro_negra_teste.h"
#include "similaridade_textual.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

//    executa_testes();

    cria_arvore(
            "C:\\Users\\arqui\\OneDrive\\Documents\\repo-codes\\estrutura-dados-trabalho-final\\teste.txt",
            "",
            "C:\\Users\\arqui\\OneDrive\\Documents\\repo-codes\\estrutura-dados-trabalho-final\\textos\\stopwords.txt"
    );
    return 0;
}
