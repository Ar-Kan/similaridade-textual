#include <stdio.h>
#include <string.h>
#include <time.h>

#include "rubro_negra/rubro_negra.h"
#include "rubro_negra/testes/rubro_negra_teste.h"
#include "rubro_negra/fila_rubro_negra.h"


//Nodo *findNthElement(int n, Nodo *tree) {
//    if (tree == NULL) {
//        return NULL;
//    }
//    int currentNum = tree->esquerda == NULL ? 1 : tree->esquerda->nodeCount + 1;
//    return n == currentNum ? tree // Found it!
//                           : n < currentNum ? findNthElement(n, tree->direita)
//                                            : findNthElement(n - currentNum, tree->direita);
//}

Nodo *iterative_inorder(Nodo *nodo, int posicao) {
//    printf("posicao: %d\n", posicao);
    Fila *fila = inicializar_fila();
//    while (!fila_esta_vazia(fila) || nodo != NULL) {
    int contador = 0;
    while (!fila_esta_vazia(fila) || nodo != NULL) {
        if (nodo != NULL) {
            inserir_na_fila(&fila, nodo);
            nodo = nodo->esquerda;
        } else {
            remover_da_fila(&fila, &nodo);
            nodo = nodo->direita;
        }
        contador++;
        if (contador == posicao) break;
    }
    Nodo *nodo_final = fila->ultimo->nodo;
    char *pal = PALAVRA_DE(nodo_final);
    return nodo_final;
}

Nodo *nthNode(Nodo *root, int N) {
    if (root == NULL)
        return NULL;
    static int index = 0;
    Nodo *resultado_esquerda = nthNode(root->esquerda, N);
    if (resultado_esquerda) {
//        printf("resultado_esquerda: %s\n", root->palavra);
        return resultado_esquerda;
    }
    if (++index == N) {
//        printf("++index == N: %s\n", root->palavra);
        return root;
    }
    Nodo *resultado_direita = nthNode(root->direita, N);
    if (resultado_direita) {
//        printf("resultado_direita: %s\n", root->palavra);
        return resultado_direita;
    }
    return NULL;
}

Nodo *nodo_na_posicao_auxiliar(Nodo *nodo, int posicao, int contador) {
    if (ESQUERDA_OU_NULL_DE(nodo)) {
//        printf("esq posicao aux: %d\n", posicao);
//        printf("esq contador aux: %d\n", contador);
        Nodo *resultado_esquerda = nodo_na_posicao_auxiliar(ESQUERDA_DE(nodo), posicao, contador++);
        if (resultado_esquerda) {
            return resultado_esquerda;
        }
    }
//    printf("palavra atual: %s\n", PALAVRA_OU_NULL_DE(nodo));
    if (posicao == contador) {
        return nodo;
    }
    if (DIREITA_OU_NULL_DE(nodo)) {
//        printf("dir posicao aux: %d\n", posicao);
//        printf("esq contador aux: %d\n", contador);
        return nodo_na_posicao_auxiliar(DIREITA_DE(nodo), posicao, contador++);
    }
    return NULL;
}

Nodo *nodo_na_posicao(Nodo *nodo, int posicao) {
    int contador = 0;
    Nodo *encontrado = nodo_na_posicao_auxiliar(nodo, posicao, contador);
    return encontrado;
}

/// teste
void busca_n_esimo_nodo() {
    Nodo *raiz = NULL;
    inserir(&raiz, "r");
    inserir(&raiz, "e");
    inserir(&raiz, "d");
    inserir(&raiz, "b");
    inserir(&raiz, "l");
    inserir(&raiz, "a");
    inserir(&raiz, "c");
    inserir(&raiz, "k");
    inserir(&raiz, "t");
    inserir(&raiz, "g");
    inserir(&raiz, "s");
    inserir(&raiz, "f");

//    imprimir_fila(listar_nodos(raiz));

    printf("tamanho arvore: %d\n", contar_nodos(raiz));

//    printf("primeiro (a): %s\n", nodo_str(iterative_inorder(raiz, 1)));
//    printf("ultimo (t): %s\n", nodo_str(iterative_inorder(raiz, 12)));
//    printf("terceiro (c): %s\n", nodo_str(iterative_inorder(raiz, 3)));
//    printf("quinto (e): %s\n", nodo_str(iterative_inorder(raiz, 5)));
//    printf("oitavo (k): %s\n", nodo_str(iterative_inorder(raiz, 8)));
//    printf("decimo (r): %s\n", nodo_str(iterative_inorder(raiz, 10)));

//    printf("primeiro (a): %s\n", nodo_str(nthNode(raiz, 1)));
//    printf("ultimo (t): %s\n", nodo_str(nthNode(raiz, 12)));
//    printf("terceiro (c): %s\n", nodo_str(nthNode(raiz, 3)));
//    printf("quinto (e): %s\n", nodo_str(nthNode(raiz, 5)));
//    printf("oitavo (k): %s\n", nodo_str(nthNode(raiz, 8)));
//    printf("decimo (r): %s\n", nodo_str(nthNode(raiz, 10)));

    printf("primeiro (a): %s\n", nodo_str(nodo_na_posicao(raiz, 1)));
    printf("ultimo (t): %s\n", nodo_str(nodo_na_posicao(raiz, 12)));
    printf("terceiro (c): %s\n", nodo_str(nodo_na_posicao(raiz, 3)));
    printf("quinto (e): %s\n", nodo_str(nodo_na_posicao(raiz, 5)));
    printf("oitavo (k): %s\n", nodo_str(nodo_na_posicao(raiz, 8)));
    printf("decimo (r): %s\n", nodo_str(nodo_na_posicao(raiz, 10)));

    printf("\n");
    imprimir_arvore(raiz);
}


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
    int quantidade_nodos_base = contar_nodos(texto_base);
    while (!fila_esta_vazia(fila)) {
        remover_da_fila(&fila, &proximo);
//        if (pesquisar(texto_base, PALAVRA_DE(proximo))) {
        if (jump_search_arvore(texto_base, PALAVRA_DE(proximo), quantidade_nodos_base)) {
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
    busca_n_esimo_nodo();

#if 0
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
#endif
    return 0;
}
