#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra/fila_rubro_negra.h"
#include "rubro_negra/testes/rubro_negra_teste.h"

#define EXECUTA_MEDIA 1
#define USA_MINGW 0

#if !USA_MINGW
// Implementação própria de 'strlwr'

#include <ctype.h>

/**
 * @breaf Implementação da função strlwr
 *
 * @details Essa função foi inicialmente inserida para executar
 * o programa no linux, uma fez que strlwr não é uma função padrão do c,
 * estando presente no pacote MinGW.
 * Acabou que este código é mais performático que o existente no gcc,
 * reduzindo o tempo de execução do programa.
 *
 * @param string Char array que será convertido para minúsculo
 * @return Retorna a palavra convertida para minúscula
 */
char *strlwr(char *string) {
    if (!string) return NULL;
    unsigned char *p_string = (unsigned char *) string;
    while (*p_string) {
        *p_string = tolower((unsigned char) *p_string);
        p_string++;
    }
    return string;
}

#endif

#define MAX_COUNT 1000

float computa_jaccard(char *texto_a, char *texto_b, char *stopwords, float *tempo_de_execucao) {

    char *palavra, linhas[MAX_COUNT];
    char separadores[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    FILE *entrada_stream;

    clock_t start, end;

    start = clock();

    // Stopwords
    entrada_stream = fopen(stopwords, "r");
    if (!entrada_stream) {
        perror(stopwords);
        printf("Erro ao abrir o arquivo: \"%s\"\n", stopwords);
        exit(1);
    }
    Nodo *arvore_stops = NULL;
    while (fgets(linhas, MAX_COUNT, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            inserir(&arvore_stops, strlwr(palavra));
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    (void) fclose(entrada_stream);

    // texto base
    entrada_stream = fopen(texto_a, "r");
    if (!entrada_stream) {
        perror(texto_a);
        printf("Erro ao abrir o arquivo: \"%s\"\n", texto_a);
        exit(1);
    }
    Nodo *arvore_a = NULL;
    while (fgets(linhas, MAX_COUNT, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(arvore_stops, palavra)) {
                inserir(&arvore_a, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    (void) fclose(entrada_stream);

    // texto de busca
    entrada_stream = fopen(texto_b, "r");
    if (!entrada_stream) {
        perror(texto_b);
        printf("Erro ao abrir o arquivo: \"%s\"\n", texto_b);
        exit(1);
    }
    Nodo *arvore_b = NULL;
    while (fgets(linhas, MAX_COUNT, entrada_stream)) {
        palavra = strlwr(strtok(linhas, separadores));
        while (palavra != NULL) {
            if (!pesquisar(arvore_stops, palavra)) {
                inserir(&arvore_b, palavra);
            }
            palavra = strlwr(strtok(NULL, separadores));
        }
    }
    (void) fclose(entrada_stream);

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

#if !EXECUTA_MEDIA
    // Debug
    printf("- %d arvore_stops carregadas\n", tamanho_arvore(arvore_stops));
    printf("- %d palavras carregadas para o texto: \"%s\"\n", tamanho_arvore(arvore_a), texto_a);
    printf("- %d palavras carregadas para o texto: \"%s\"\n", tamanho_arvore(arvore_b), texto_b);
    printf("- %d palavras em comum\n", palavras_em_comum);
    printf("- %d total de palavras\n", total_de_palavras);
    printf("Indice de Jacard: %.2f\n", roundf(jaccard * 1000) / 1000);
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

#if EXECUTA_MEDIA
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

    printf("Indice de Jacard: %.2f\n", roundf(jaccard * 1000) / 1000);
    printf("Tempo medio de execucao: %.5f ms\n", tempo_total / 8.0);
#endif

    return 0;
}
