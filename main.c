#include <stdio.h>
#include <string.h>
#include <time.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra/testes/rubro_negra_teste.h"
#include "rubro_negra/fila_rubro_negra.h"

int computa_jacard(char *caminho_texto_base, char *caminho_texto_de_busca, char *caminho_stopwords) {

    char *palavra, linhas[1000];
    char separadores[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    FILE *entrada_stream;

    clock_t start, end;
    float tempo_total = 0;

    start = clock();

    // Stopwords
    if ((entrada_stream = fopen(caminho_stopwords, "r")) == NULL) {
        perror(caminho_stopwords);
        printf("Erro ao abrir o arquivo: \"%s\"\n", caminho_stopwords);
        return 1;
    }
    Nodo *stopwords = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            inserir(&stopwords, strlwr(palavra));
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    // texto base
    if ((entrada_stream = fopen(caminho_texto_base, "r")) == NULL) {
        perror(caminho_texto_base);
        printf("Erro ao abrir o arquivo: \"%s\"\n", caminho_texto_base);
        return 1;
    }
    Nodo *texto_base = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(stopwords, palavra)) {
                inserir(&texto_base, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    // texto de busca
    if ((entrada_stream = fopen(caminho_texto_de_busca, "r")) == NULL) {
        perror(caminho_texto_de_busca);
        printf("Erro ao abrir o arquivo: \"%s\"\n", caminho_texto_de_busca);
        return 1;
    }
    Nodo *texto_de_busca = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(stopwords, palavra)) {
                inserir(&texto_de_busca, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    Fila *fila = listar_nodos(texto_de_busca);
    Nodo *proximo = NULL;
    int palavras_em_comum = 0;
    while (!fila_esta_vazia(fila)) {
        remover_da_fila(&fila, &proximo);
        if (pesquisar(texto_base, PALAVRA_DE(proximo))) {
            palavras_em_comum++;
        }
    }

    end = clock();
    tempo_total = (float) (end - start) / CLOCKS_PER_SEC * 1000;


    printf("- %d stopwords carregadas\n", contar_nodos(stopwords));
    printf("- %d palavras carregadas para o texto: \"%s\"\n", contar_nodos(texto_base), caminho_texto_base);
    printf("- %d palavras carregadas para o texto: \"%s\"\n", contar_nodos(texto_de_busca), caminho_texto_de_busca);

    printf("- %d palavras em comum\n", palavras_em_comum);

    int total_de_palavras = (contar_nodos(texto_base) + contar_nodos(texto_de_busca)) - palavras_em_comum;
    printf("- %d total de palavras\n", total_de_palavras);

    printf("Indice de Jacard: %f\n", palavras_em_comum * 1.0 / total_de_palavras);

    printf("Tempo: %.5f ms\n", tempo_total);

    return 0;
}


int main(int argc, char *argv[]) {

    if (argc == 2) {
        executa_testes();
        return 0;
    }

    if (argc != 4) {
        printf("Numero incorreto de parametros.\n");
        printf("Para chamar o programa digite: exemplo <arq_base> <arq_busca> <arq_stopwords>\n");
        return 1;
    }

    computa_jacard(argv[1], argv[2], argv[3]);
    return 0;
}
