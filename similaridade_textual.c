#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>


#include "similaridade_textual.h"

int cria_arvore(char *caminho_texto_base, char *caminho_texto_de_busca, char *caminho_stopwords) {

    char *palavra, linhas[1000];
    char separadores[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    FILE *entrada;

    entrada = fopen(caminho_stopwords, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo base \"%s\"", caminho_texto_base);
        return 1;
    }

    Nodo *stopwords = NULL;
    while (fgets(linhas, 1000, entrada)) {
        palavra = strtok(linhas, separadores);
        while (palavra != NULL) {
            inserir(&stopwords, strlwr(palavra));
            palavra = strtok(NULL, separadores);
            print(stopwords);
        }
    }
    printf("nodos: %d\n", contar_nodos(stopwords));
    print(stopwords);

    return 0;
}
