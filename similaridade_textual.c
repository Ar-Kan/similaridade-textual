#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>


#include "similaridade_textual.h"

int cria_arvore(char *caminho_texto_base, char *caminho_texto_de_busca, char *caminho_stopwords) {

    char *palavra, linhas[1000];
    char separadores[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    FILE *entrada_stream;

    if ((entrada_stream = fopen(caminho_stopwords, "r")) == NULL) {
        perror(caminho_stopwords);
        printf("Erro ao abrir o arquivo de stopwords: %s\n", caminho_stopwords);
        return 1;
    }

    Nodo *stopwords = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strtok(linhas, separadores);
        while (palavra != NULL) {
            inserir(&stopwords, strlwr(palavra));
            palavra = strtok(NULL, separadores);
        }
    }
    printf("nodos: %d\n", contar_nodos(stopwords));
//    print(stopwords);

    if ((entrada_stream = fopen(caminho_stopwords, "r")) == NULL) {
        perror(caminho_stopwords);
        printf("Erro ao abrir o arquivo de stopwords: %s\n", caminho_stopwords);
        return 1;
    }
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strtok(linhas, separadores);
        while (palavra != NULL) {
            if (!pesquisar(stopwords, palavra)) {
                printf("palavra nao inserida: %s\n", palavra);
            }
            palavra = strtok(NULL, separadores);
        }
    }
    printf("finish");

    return 0;
}
