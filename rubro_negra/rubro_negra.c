#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rubro_negra.h"

Nodo *criar(char *palavra) {
    Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
    if (nodo == NULL) {
        printf("Erro ao alocar novo nodo, memoria insuficiente.\n");
        return NULL;
    }
    PALAVRA_DE(nodo) = palavra;
    COR_DE(nodo) = RUBRO; // novos nodos são vermelhos
    ESQUERDA_DE(nodo) = NULL;
    DIREITA_DE(nodo) = NULL;
    PAI_DE(nodo) = NULL;
    return nodo;
}


/**
 * @breaf Realiza rotação simples à esquerda.
 *
 * Rotação simples à esquerda (avô->direita->direita == nodo).
 * Como o pai é vermelho e o tio é preto deve-se fazer uma rotação simples
 * á esquerda e alterar cores do pai e do irmão (antigo avô).
 * @code
 *    {b}                 {b}
 *     |                   |
 *    (a)                 (p)
 *   /   \               /   \
 * [t]  (p)     =>     (a)  [N]
 *      / \            / \
 *    [i] [N]        [t] [i]
 * @endcode
 *
 * O nodo filho, [N], está à direita de seu pai, (p), que, por sua vez, está à direita do avô, (a), de [N].
 *
 * @param [in,out] raiz Raíz da árvore
 * @param [in,out] nodo Nodo filho na rotação
 */
void rotacao_simples_esquerda(Nodo **raiz, Nodo **nodo) {
    /// 1. Rotaciona para a esquerda
    Nodo *irmao = ESQUERDA_DE(PAI_DE(*nodo));
    int avo_era_raiz = EH_RAIZ(AVO_DE(*nodo));

    ESQUERDA_DE(PAI_DE(*nodo)) = PAI_DE(PAI_DE(*nodo)); /// (p,esq)->(a), avô agora é o irmão
    DIREITA_DE(ESQUERDA_DE(PAI_DE(*nodo))) = irmao; /// (a,dir)->[i], irmão agora é o sobrinho
    if (irmao) // irmão pode não existir
        PAI_DE(irmao) = DIREITA_DE(ESQUERDA_DE(PAI_DE(*nodo))); /// [i,pai]->(a), pai do sobrinho é o irmão
    PAI_DE(PAI_DE(*nodo)) = PAI_DE(ESQUERDA_DE(PAI_DE(*nodo))); /// (p,pai)->{b}, bisavô agora é o avô
    // avô pode não existir
    if (PAI_DE(PAI_DE(*nodo))) {
        /// {b,dir/esq}->(p), filho do bisavô agora é o pai
        if (ESQUERDA_DE(PAI_DE(PAI_DE(*nodo))) == ESQUERDA_DE(PAI_DE(*nodo))) {
            // pai está na esquerda do avô
            ESQUERDA_DE(PAI_DE(PAI_DE(*nodo))) = PAI_DE(*nodo);
        } else {
            // pai está na direita do avô
            DIREITA_DE(PAI_DE(PAI_DE(*nodo))) = PAI_DE(*nodo);
        }
    }
    PAI_DE(ESQUERDA_DE(PAI_DE(*nodo))) = PAI_DE(*nodo); /// (a,pai)->(p), pai do irmão agora é o pai

    /// 2. Troca cores do pai e do irmão (antigo avô)
    COR_DE(PAI_DE(*nodo)) = NEGRO;
    COR_DE(ESQUERDA_DE(PAI_DE(*nodo))) = RUBRO;

    /// 3. Atualiza raíz se necessário
    if (avo_era_raiz)
        *raiz = PAI_DE(*nodo);
}

/**
 * @breaf Realiza rotação simples à direita.
 *
 * Rotação simples à direita (avô->esquerda->esquerda == nodo).
 * Como o pai é vermelho e o tio é preto deve-se fazer uma rotação simples
 * á direita e alterar cores do pai e do irmão (antigo avô).
 * @code
 *      {b}            {b}
 *       |              |
 *      (a)            (p)
 *     /   \          /   \
 *    (p) [t]   =>  [N]  (a)
 *    / \                / \
 *  [N] [i]            [i] [t]
 * @endcode
 *
 * O nodo filho, [N], está à esquerda de seu pai, (p), que, por sua vez, está à esquerda do avô, (a), de [N].
 *
 * @param [in,out] raiz Raíz da arvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_simples_direita(Nodo **raiz, Nodo **nodo) {
    /// 1. Rotaciona para a direita
    Nodo *irmao = DIREITA_DE(PAI_DE(*nodo));
    int avo_era_raiz = EH_RAIZ(AVO_DE(*nodo));

    DIREITA_DE(PAI_DE(*nodo)) = PAI_DE(PAI_DE(*nodo)); /// (p,dir)->(a), avô agora é o irmão
    ESQUERDA_DE(DIREITA_DE(PAI_DE(*nodo))) = irmao; /// (a,esq)->[i], irmão agora é o sobrinho
    if (irmao) // irmão pode não existir
        PAI_DE(irmao) = ESQUERDA_DE(DIREITA_DE(PAI_DE(*nodo))); /// [i,pai]->(a), pai do sobrinho é o irmão
    PAI_DE(PAI_DE(*nodo)) = PAI_DE(DIREITA_DE(PAI_DE(*nodo))); /// (p,pai)->{b}, bisavô agora é o avô
    // novo avô pode não existir
    if (PAI_DE(PAI_DE(*nodo))) {
        /// {b,dir/esq}->(a), filho do bisavô agora é o pai
        if (ESQUERDA_DE(PAI_DE(PAI_DE(*nodo))) == ESQUERDA_DE(PAI_DE(*nodo))) {
            // pai está na esquerda do avô
            ESQUERDA_DE(PAI_DE(PAI_DE(*nodo))) = PAI_DE(*nodo);
        } else {
            // pai está na direita do avô
            DIREITA_DE(PAI_DE(PAI_DE(*nodo))) = PAI_DE(*nodo);
        }
    }
    PAI_DE(DIREITA_DE(PAI_DE(*nodo))) = PAI_DE(*nodo); /// (a,pai)->(p), pai do irmão agora é o pai

    /// 2. Troca cores do pai (p) e irmão (a) (antigo avô)
    COR_DE(PAI_DE(*nodo)) = NEGRO;
    COR_DE(DIREITA_DE(PAI_DE(*nodo))) = RUBRO;

    /// 3. Atualiza raíz se necessário
    if (avo_era_raiz)
        *raiz = PAI_DE(*nodo);
}

/**
 * @breaf Realiza rotação dupla à direita.
 *
 * Rotação dupla à esquerda (avô->esquerda->direita == nodo).
 * Como o pai é vermelho e o tio é preto deve-se fazer uma rotação simples
 * á esquerda e depois uma rotação simples à direita (rotação dupla à direita)
 * e alterar cores do próprio nodo e do filho direito (antigo avô).
 *
 * @code
 *      {b}                 {b}
 *       |                   |
 *      (a)                 (N)
 *      / \                /   \
 *    (p) [t]            (p)    (a)
 *    / \         =>     / \    / \
 *  [i](N)             [i][n1][n2][t]
 *     / \
 *  [n1] [n2]
 * @endcode
 *
 * O nodo filho, (N), está à direita de seu pai, (p), que, por sua vez, está à esquerda do avô, (a), de (N).
 *
 * @param [in,out] raiz Raíz da árvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_dupla_direrita(Nodo **raiz, Nodo **nodo) {
    Nodo *pai = PAI_DE(*nodo); // (p)
    Nodo *avo = PAI_DE(PAI_DE(*nodo)); // (a)

    /// 1. Faz rotação dupla
    int avo_era_raiz = EH_RAIZ(avo);
    if (!avo_era_raiz) {
        /// (b,esq/dir)->(N)
        if (ESQUERDA_DE(PAI_DE(avo)) == avo)
            ESQUERDA_DE(PAI_DE(avo)) = *nodo;
        else
            DIREITA_DE(PAI_DE(avo)) = *nodo;
    }
    PAI_DE(*nodo) = PAI_DE(avo); /// (N,pai)->(b)
    DIREITA_DE(pai) = ESQUERDA_DE(*nodo); /// (p,dir)->(n1)
    ESQUERDA_DE(*nodo) = pai; /// (N,esq)->(p)
    if (DIREITA_DE(pai))
        PAI_DE(DIREITA_DE(pai)) = pai; /// (n1,pai)->(p)
    ESQUERDA_DE(avo) = DIREITA_DE(*nodo); /// (a,esq)->(n2)
    if (ESQUERDA_DE(avo))
        PAI_DE(ESQUERDA_DE(avo)) = avo; /// (n2,pai)->(a)
    DIREITA_DE(*nodo) = avo; /// (N,dir)->(a)
    PAI_DE(avo) = *nodo; /// (a,pai)->(N)
    PAI_DE(pai) = *nodo; /// (p,pai)->(N)

    /// 2. Troca cores do nodo e do novo filho direito (antigo avô)
    COR_DE(*nodo) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raíz se necessário
    if (avo_era_raiz)
        *raiz = PAI_DE(PAI_DE(*nodo));

}

/**
 * @breaf Realiza rotação dupla à esquerda.
 *
 * Rotação dupla à direita (avô->direita->esquerda == nodo)
 * Como o pai é vermelho e o tio é preto deve-se fazer uma rotação simples
 * á direita e depois uma rotação simples à esquerda (rotação dupla à esquerda)
 * e alterar cores do próprio nodo e do filho direito (antigo avô).
 * @code
 *      {b}                  {b}
 *       |                    |
 *      (a)                  (N)
 *      / \                 /   \
 *    [t] (p)             (p)    (a)
 *        / \      =>     / \    / \
 *      (N) [i]         [i][n1][n2][t]
 *      / \
 *   [n1] [n2]
 * @endcode
 *
 * O nodo filho, (N), está à esquerda de seu pai, (p), que, por sua vez, está à direita de do avô, (a), de (N).
 *
 * @param [in,out] raiz Raíz da árvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_dupla_esquerda(Nodo **raiz, Nodo **nodo) {
    Nodo *pai = PAI_DE(*nodo); // (p)
    Nodo *avo = PAI_DE(PAI_DE(*nodo)); // (a)

    /// 1. Faz rotação dupla
    int avo_era_raiz = EH_RAIZ(avo);
    if (!avo_era_raiz) {
        /// (b,esq/dir)->(N)
        if (ESQUERDA_DE(PAI_DE(avo)) == avo)
            ESQUERDA_DE(PAI_DE(avo)) = *nodo;
        else
            DIREITA_DE(PAI_DE(avo)) = *nodo;
    }
    PAI_DE(*nodo) = PAI_DE(avo); /// (N,pai)->(b)
    ESQUERDA_DE(pai) = DIREITA_DE(*nodo); /// (p,esq)->(n1)
    DIREITA_DE(*nodo) = pai; /// (N,dir)->(p)
    if (ESQUERDA_DE(pai))
        PAI_DE(ESQUERDA_DE(pai)) = pai; /// (n1,pai)->(p)
    DIREITA_DE(avo) = ESQUERDA_DE(*nodo); /// (a,dir)->(n2)
    if (DIREITA_DE(avo))
        PAI_DE(ESQUERDA_DE(avo)) = avo; /// (n2,pai)->(a)
    ESQUERDA_DE(*nodo) = avo; /// (N,esq)->(a)
    PAI_DE(avo) = *nodo; /// (a,pai)->(N)
    PAI_DE(pai) = *nodo; /// (p,pai)->(N)

    /// 2. Troca cores do nodo e do filho direito (antigo avô)
    COR_DE(*nodo) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raíz se necessário
    if (avo_era_raiz)
        *raiz = PAI_DE(PAI_DE(*nodo));
}

/**
 * @breaf Altera as cores do pai tio e avô do nodo
 *
 * Quando o pai é vermelho e tio é vermelho deve-se alterar cores do pai, tio e avô (exceto raiz)
 * @param nodo Nodo que é filho na transformação
 */
void alterar_cores(Nodo **nodo) {
    COR_DE(PAI_DE(*nodo)) = NEGRO;
    COR_DE(TIO_DE(*nodo)) = NEGRO; // como é vermelho, sabemos que o tio não é nulo
    if (!EH_RAIZ(AVO_DE(*nodo)))
        COR_DE(AVO_DE(*nodo)) = RUBRO;

}

/**
 * Realiza o balanceamento da árvore
 * @param [in,out] raiz Raíz da árvore
 * @param [in,out] nodo O novo nodo inserido na árvore
 */
void balancear(Nodo **raiz, Nodo **nodo) {
    if (!VERMELHO(PAI_DE(*nodo))) {
        /// Pai preto: nada a se fazer
        return;
    }

    if (VERMELHO(TIO_DE(*nodo))) {
        /// Pai vermelho e tio vermelho: alterar cores
        alterar_cores(&(*nodo));
        // TODO: se o avô não é raíz, verificar se não se deve rotacionar
        return;
    }

    // se chegou aqui o avô existe
    int pai_esta_na_esquerda_do_avo = ESQUERDA_OU_NULL_DE(AVO_DE(*nodo)) == PAI_DE(*nodo);
    int nodo_esta_na_esquerda_do_pai = ESQUERDA_DE(PAI_DE(*nodo)) == *nodo;

    /// Pai vermelho e tio preto: rotacionar e alterar cores
    if (pai_esta_na_esquerda_do_avo) {
        if (nodo_esta_na_esquerda_do_pai)
            rotacao_simples_direita(raiz, &(*nodo));
        else
            rotacao_dupla_direrita(raiz, &(*nodo));
    } else {
        if (nodo_esta_na_esquerda_do_pai)
            rotacao_dupla_esquerda(raiz, &(*nodo));
        else
            rotacao_simples_esquerda(raiz, &(*nodo));
    }
}

/**
 * Função recursiva auxiliar, para inserir o nodo na árvore
 * @param [in,out] subarvore Raiz da subarvore
 * @param [in,out] nodo Nodo que será inserido
 * @return 1 se foi inserido com sucesso, 0 caso a palavra já exista
 */
int _inserir(Nodo **subarvore, Nodo **nodo) {
    int comparacao = strcmp(PALAVRA_DE(*nodo), PALAVRA_DE(*subarvore));
    if (comparacao == 0) return 0;
    if (comparacao < 0) {
        if (ESQUERDA_DE(*subarvore) == NULL) {
            PAI_DE(*nodo) = *subarvore;
            ESQUERDA_DE(*subarvore) = *nodo;
            return 1;
        }
        return _inserir(&ESQUERDA_DE(*subarvore), nodo);
    } else {
        if (DIREITA_DE(*subarvore) == NULL) {
            PAI_DE(*nodo) = *subarvore;
            DIREITA_DE(*subarvore) = *nodo;
            return 1;
        }
        return _inserir(&DIREITA_DE(*subarvore), nodo);
    }
}

void inserir(Nodo **raiz, char *palavra) {
    Nodo *nodo = criar(palavra);
    if (!(*raiz)) {
        COR_DE(nodo) = NEGRO; // raíz é de cor preta
        *raiz = nodo;
        return;
    }
    int inserido = _inserir(raiz, &nodo);
    if (inserido)
        balancear(raiz, &nodo);
}

Nodo *pesquisar(Nodo *raiz, char *palavra) {
    if (!raiz)
        return NULL;

    int comparacao = strcmp(palavra, PALAVRA_DE(raiz));
    if (comparacao == 0)
        return raiz;
    else if (comparacao < 0)
        return pesquisar(ESQUERDA_DE(raiz), palavra);
    else
        return pesquisar(DIREITA_DE(raiz), palavra);
}

/**
 * Função recursiva auxiliar, para fazer o print da árvore
 * @param nodo Nodo atual
 * @param contador Contador da posição atual
 * @param posicao Se esquerda (E), direita (D) ou origem (O)
 */
void _print(Nodo *nodo, const int contador, const char *posicao) {
    if (nodo) {
        _print(DIREITA_DE(nodo), contador + 1, "D");
        printf("%*s", 8 * contador, "");
        if (posicao)
            printf("%s: ", posicao);
        printf("%s", PALAVRA_DE(nodo));
        printf(" (%s)\n", COR_DE(nodo) == RUBRO ? "r" : "n");
        _print(ESQUERDA_DE(nodo), contador + 1, "E");
    }
}

void print(Nodo *nodo) {
    _print(nodo, 0, "o");
}

char *nodo_str(Nodo *nodo) {
    if (!nodo)
        return "Nodo{NULL}";

    return nodo_str_auxiliar(
            PALAVRA_DE(nodo),
            COR_DE(nodo) == NEGRO ? "NEGRO" : "RUBRO",
            PALAVRA_OU_NULL_DE(ESQUERDA_DE(nodo)),
            PALAVRA_OU_NULL_DE(DIREITA_DE(nodo)),
            PALAVRA_OU_NULL_DE(PAI_DE(nodo))
    );
}


char *nodo_str_auxiliar(char *palavra, char *cor, char *esquerda, char *direita, char *pai) {
    char retorno[100] = "";
    strcat(retorno, "Nodo{.palavra=\"");
    strcat(retorno, palavra);
    strcat(retorno, "\", .cor=");
    strcat(retorno, cor);
    strcat(retorno, ", .esquerda=");
    if (esquerda == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, esquerda);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .direita=");
    if (direita == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, direita);
        strcat(retorno, "\"");
    }
    strcat(retorno, ", .pai=");
    if (pai == NULL) {
        strcat(retorno, "NULL");
    } else {
        strcat(retorno, "\"");
        strcat(retorno, pai);
        strcat(retorno, "\"");
    }
    strcat(retorno, "}");
    char *str = malloc(sizeof(retorno));
    strcpy(str, retorno);
    return str;
}
