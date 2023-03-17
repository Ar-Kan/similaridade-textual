#include <stdio.h>

#include "rubro_negra.h"


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
 * @param [in,out] raiz Raiz da árvore
 * @param [in,out] nodo Nodo filho na rotação
 */
void rotacao_simples_esquerda(Nodo **raiz, Nodo **nodo) {
    /// 1. Rotaciona para a esquerda
    Nodo *irmao = ESQUERDA_DE(PAI_DE(*nodo)); // i
    Nodo *avo = AVO_DE(*nodo); // a
    int avo_era_raiz = EH_RAIZ(AVO_DE(*nodo));

    ESQUERDA_DE(PAI_DE(*nodo)) = avo; // (p,esq)->(a)
    DIREITA_DE(avo) = irmao; // (a,dir)->[i]
    if (irmao) // irmão pode não existir
        PAI_DE(irmao) = avo; // [i,pai]->(a)
    AVO_DE(*nodo) = PAI_DE(avo); // (p,pai)->{b}
    // novo avô (antigo bisavô) pode não existir
    if (AVO_DE(*nodo)) {
        // {b,dir/esq}->(p)
        if (ESQUERDA_DE(AVO_DE(*nodo)) == avo) {
            // pai está na esquerda do avô
            ESQUERDA_DE(AVO_DE(*nodo)) = PAI_DE(*nodo);
        } else {
            // pai está na direita do avô
            DIREITA_DE(AVO_DE(*nodo)) = PAI_DE(*nodo);
        }
    }
    PAI_DE(avo) = PAI_DE(*nodo); // (a,pai)->(p)

    /// 2. Troca cores do pai e do irmão (antigo avô)
    COR_DE(PAI_DE(*nodo)) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raiz se necessário
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
 * @param [in,out] raiz Raiz da arvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_simples_direita(Nodo **raiz, Nodo **nodo) {
    /// 1. Rotaciona para a direita
    Nodo *irmao = DIREITA_DE(PAI_DE(*nodo)); // i
    Nodo *avo = AVO_DE(*nodo); // a
    int avo_era_raiz = EH_RAIZ(avo);

    DIREITA_DE(PAI_DE(*nodo)) = avo; // (p,dir)->(a)
    ESQUERDA_DE(avo) = irmao; // (a,esq)->[i]
    if (irmao) // irmão pode não existir
        PAI_DE(irmao) = avo; // [i,pai]->(a)
    AVO_DE(*nodo) = PAI_DE(avo); // (p,pai)->{b}
    // novo avô (antigo bisavô) pode não existir
    if (AVO_DE(*nodo)) {
        // {b,dir/esq}->(a)
        if (ESQUERDA_DE(AVO_DE(*nodo)) == avo) {
            // pai está na esquerda do avô
            ESQUERDA_DE(AVO_DE(*nodo)) = PAI_DE(*nodo);
        } else {
            // pai está na direita do avô
            DIREITA_DE(AVO_DE(*nodo)) = PAI_DE(*nodo);
        }
    }
    PAI_DE(avo) = PAI_DE(*nodo); // (a,pai)->(p)

    /// 2. Troca cores do pai (p) e irmão (a) (antigo avô)
    COR_DE(PAI_DE(*nodo)) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raiz se necessário
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
 * @param [in,out] raiz Raiz da árvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_dupla_direrita(Nodo **raiz, Nodo **nodo) {
    Nodo *pai = PAI_DE(*nodo); // (p)
    Nodo *avo = AVO_DE(*nodo); // (a)

    /// 1. Faz rotação dupla
    int avo_era_raiz = EH_RAIZ(avo);
    if (!avo_era_raiz) {
        // (b,esq/dir)->(N)
        if (ESQUERDA_DE(PAI_DE(avo)) == avo)
            ESQUERDA_DE(PAI_DE(avo)) = *nodo;
        else
            DIREITA_DE(PAI_DE(avo)) = *nodo;
    }
    PAI_DE(*nodo) = PAI_DE(avo); // (N,pai)->(b)
    DIREITA_DE(pai) = ESQUERDA_DE(*nodo); // (p,dir)->(n1)
    ESQUERDA_DE(*nodo) = pai; // (N,esq)->(p)
    if (DIREITA_DE(pai))
        PAI_DE(DIREITA_DE(pai)) = pai; // (n1,pai)->(p)
    ESQUERDA_DE(avo) = DIREITA_DE(*nodo); // (a,esq)->(n2)
    if (ESQUERDA_DE(avo))
        PAI_DE(ESQUERDA_DE(avo)) = avo; // (n2,pai)->(a)
    DIREITA_DE(*nodo) = avo; // (N,dir)->(a)
    PAI_DE(avo) = *nodo; // (a,pai)->(N)
    PAI_DE(pai) = *nodo; // (p,pai)->(N)

    /// 2. Troca cores do nodo e do novo filho direito (antigo avô)
    COR_DE(*nodo) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raiz se necessário
    if (avo_era_raiz)
        *raiz = *nodo;

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
 * @param [in,out] raiz Raiz da árvore
 * @param [in,out] nodo Nodo que é filho na rotação
 */
void rotacao_dupla_esquerda(Nodo **raiz, Nodo **nodo) {
    Nodo *pai = PAI_DE(*nodo); // (p)
    Nodo *avo = AVO_DE(*nodo); // (a)

    /// 1. Faz rotação dupla
    int avo_era_raiz = EH_RAIZ(avo);
    if (!avo_era_raiz) {
        // (b,esq/dir)->(N)
        if (ESQUERDA_DE(PAI_DE(avo)) == avo)
            ESQUERDA_DE(PAI_DE(avo)) = *nodo;
        else
            DIREITA_DE(PAI_DE(avo)) = *nodo;
    }
    PAI_DE(*nodo) = PAI_DE(avo); // (N,pai)->(b)
    ESQUERDA_DE(pai) = DIREITA_DE(*nodo); // (p,esq)->(n1)
    DIREITA_DE(*nodo) = pai; // (N,dir)->(p)
    if (ESQUERDA_DE(pai))
        PAI_DE(ESQUERDA_DE(pai)) = pai; // (n1,pai)->(p)
    DIREITA_DE(avo) = ESQUERDA_DE(*nodo); // (a,dir)->(n2)
    if (DIREITA_DE(avo))
        PAI_DE(ESQUERDA_DE(avo)) = avo; // (n2,pai)->(a)
    ESQUERDA_DE(*nodo) = avo; // (N,esq)->(a)
    PAI_DE(avo) = *nodo; // (a,pai)->(N)
    PAI_DE(pai) = *nodo; // (p,pai)->(N)

    /// 2. Troca cores do nodo e do filho direito (antigo avô)
    COR_DE(*nodo) = NEGRO;
    COR_DE(avo) = RUBRO;

    /// 3. Atualiza raiz se necessário
    if (avo_era_raiz)
        *raiz = *nodo;
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

void balancear(Nodo **raiz, Nodo **nodo) {
    if (!VERMELHO(PAI_DE(*nodo))) {
        /// Pai preto: nada a se fazer
        return;
    }

    if (VERMELHO(TIO_DE(*nodo))) {
        /// Pai vermelho e tio vermelho: alterar cores
        alterar_cores(&(*nodo));
        if (EH_RAIZ(AVO_DE(*nodo))) return;
        /// se o avô não é raiz, verificar se não se deve balancear a subarvore superior
        balancear(raiz, &AVO_DE(*nodo));
        return;
    }

    // se chegou aqui o avô existe
    int pai_esta_na_esquerda_do_avo = ESQUERDA_OU_NULL_DE(AVO_DE(*nodo)) == PAI_DE(*nodo);
    int nodo_esta_na_esquerda_do_pai = ESQUERDA_DE(PAI_DE(*nodo)) == *nodo;

    /// Pai vermelho e tio preto: rotacionar e alterar cores
    if (pai_esta_na_esquerda_do_avo) {
        if (nodo_esta_na_esquerda_do_pai) {
            rotacao_simples_direita(raiz, &(*nodo));
        } else {
            rotacao_dupla_direrita(raiz, &(*nodo));
        }
    } else {
        if (nodo_esta_na_esquerda_do_pai) {
            rotacao_dupla_esquerda(raiz, &(*nodo));
        } else {
            rotacao_simples_esquerda(raiz, &(*nodo));
        }
    }
}
