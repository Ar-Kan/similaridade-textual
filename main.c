#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra/testes/rubro_negra_teste.h"
#include "rubro_negra/fila_rubro_negra.h"

/// Implementação de strlwr para executar o programa no Linux,
/// uma vez que esta função não é uma função padrão do c
char *strlwr(char *str) {
    if (!str) return NULL;
    unsigned char *p = (unsigned char *) str;
    while (*p) {
        *p = tolower((unsigned char) *p);
        p++;
    }
    return str;
}

float computa_jaccard(char *texto_a, char *texto_b, char *stopwords, float *tempo_de_execucao) {

    char *palavra, linhas[1000];
    char separadores[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    FILE *entrada_stream;

    clock_t start, end;

    start = clock();

    // Stopwords
    if ((entrada_stream = fopen(stopwords, "r")) == NULL) {
        perror(stopwords);
        printf("Erro ao abrir o arquivo: \"%s\"\n", stopwords);
        exit(1);
    }
    Nodo *arvore_stops = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            inserir(&arvore_stops, strlwr(palavra));
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    // texto base
    if ((entrada_stream = fopen(texto_a, "r")) == NULL) {
        perror(texto_a);
        printf("Erro ao abrir o arquivo: \"%s\"\n", texto_a);
        exit(1);
    }
    Nodo *arvore_a = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(arvore_stops, palavra)) {
                inserir(&arvore_a, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    // texto de busca
    if ((entrada_stream = fopen(texto_b, "r")) == NULL) {
        perror(texto_b);
        printf("Erro ao abrir o arquivo: \"%s\"\n", texto_b);
        exit(1);
    }
    Nodo *arvore_b = NULL;
    while (fgets(linhas, 1000, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(arvore_stops, palavra)) {
                inserir(&arvore_b, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    fclose(entrada_stream);

    Fila *fila = NULL;
    Nodo *arvore_pesquisa = NULL;
    if (tamanho_arvore(arvore_a) <= tamanho_arvore(arvore_b)) {
        fila = listar_nodos(arvore_a);
        arvore_pesquisa = arvore_b;
    } else {
        fila = listar_nodos(arvore_b);
        arvore_pesquisa = arvore_a;
    }
    int palavras_em_comum = 0;
    while (QUANTIDADE_DE_ELEMENTOS_DE(fila)) {
        Nodo *proximo_nodo = remover_da_fila(&fila);
        if (pesquisar(arvore_pesquisa, PALAVRA_DE(proximo_nodo))) {
            palavras_em_comum++;
        }
    }

    end = clock();
    *tempo_de_execucao = ((float) (end - start) / CLOCKS_PER_SEC * 1000);

    int total_de_palavras = (tamanho_arvore(arvore_a) + tamanho_arvore(arvore_b)) - palavras_em_comum;
    float jaccard = palavras_em_comum * 1.0 / total_de_palavras;

#if 0
    // Debug
    printf("- %d arvore_stops carregadas\n", tamanho_arvore(arvore_stops));
    printf("- %d palavras carregadas para o texto: \"%s\"\n", tamanho_arvore(arvore_a), texto_a);
    printf("- %d palavras carregadas para o texto: \"%s\"\n", tamanho_arvore(arvore_b), texto_b);
    printf("- %d palavras em comum\n", palavras_em_comum);
    printf("- %d total de palavras\n", total_de_palavras);
    printf("Indice de Jacard: %f\n", palavras_em_comum * 1.0 / total_de_palavras);
    printf("Tempo: %.5f ms\n", *tempo_de_execucao);
#endif

    return jaccard;
}


int main(int argc, char *argv[]) {

    if (argc == 2) {
        executa_testes();
        return 0;
    }

    if (argc != 4) {
        printf("Numero incorreto de parametros.\n");
        printf("Para chamar o programa digite: exemplo <arq_a> <arq_b> <arq_stopwords>\n");
        return 1;
    }

    float tempo_de_execucao = 0;
    float tempo_total = 0;
    float jaccard = computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;
    (void) computa_jaccard(argv[1], argv[2], argv[3], &tempo_de_execucao);
    tempo_total += tempo_de_execucao;

    printf("Indice de Jacard: %f\n", jaccard);
    printf("Tempo medio de execucao: %.5f ms\n", tempo_total / 8.0);
    return 0;
}
