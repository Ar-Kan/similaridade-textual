/** @file rubro_negra.h */

#ifndef RUBRO_NEGRA
#define RUBRO_NEGRA

/// Representação da cor vermelha
#define RUBRO 0
/// Representação da cor preta
#define NEGRO 1

/// Retorna verdadeiro se o pai é nulo, ou seja, é raiz
#define EH_RAIZ(t) ((t)->pai == NULL ? 1 : 0)
/// Retorna a subarvore esquerda
#define ESQUERDA_DE(t) ((t)->esquerda)
/// Retorna a subarvore direita
#define DIREITA_DE(t) ((t)->direita)
/// Retorna a cor do nodo
#define COR_DE(t) ((t)->cor)
/// Retorna a palavra no nodo
#define PALAVRA_DE(t) ((t)->palavra)

/// Retorna verdadeiro se o nodo não é nulo ou é vermelho
#define VERMELHO(t) (t == NULL ? 0 : (t)->cor == RUBRO)

/// Retorna a subarvore esquerda se existir, nulo caso contrário
#define ESQUERDA_OU_NULL_DE(t) (t == NULL ? NULL : ESQUERDA_DE(t))
/// Retorna a subarvore direita se existir, nulo caso contrário
#define DIREITA_OU_NULL_DE(t) (t == NULL ? NULL : DIREITA_DE(t))
/// Retorna a palavra guardada no nodo, se o nodo existir, null caso contrário
#define PALAVRA_OU_NULL_DE(t) (t == NULL ? NULL : PALAVRA_DE(t))

/// Retorna o pai do nodo
#define PAI_DE(t) ((t)->pai)

/// Retorna o avô do nodo
/// @attention Se o nodo não possuir pai gerará um erro
#define AVO_DE(t) (PAI_DE(PAI_DE(t)))

/// Retorna o tio do nodo se existir, nulo caso contrário
/// @attention Se o nodo não possuir pai gerará um erro
#define TIO_DE(t) (                             \
    ESQUERDA_OU_NULL_DE(AVO_DE(t)) == PAI_DE(t) \
        ? DIREITA_OU_NULL_DE(AVO_DE(t))         \
        : ESQUERDA_OU_NULL_DE(AVO_DE(t)))


/**
 * \struct Estrutura de um nodo
 */
typedef struct Nodo {
    /// Palavra do nodo
    char *palavra;
    /// Cor do nodo
    int cor;
    /// Subarvore esquerda
    struct Nodo *esquerda;
    /// Subarvore direita
    struct Nodo *direita;
    /// Pai do nodo
    struct Nodo *pai;
} Nodo;

/**
 * Cria um nodo
 * @param [in] palavra Palavra que será inserida no nodo
 * @return Nodo
 */
Nodo *criar(char *palavra);

/**
 * Insere uma palavra na árvore
 * @param [in,out] raiz ponteiro para a raiz
 * @param [in] palavra palavra que será inserida
 */
void inserir(Nodo **raiz, char *palavra);

/**
 * Realiza o balanceamento da árvore
 * @param [in,out] raiz Raiz da árvore
 * @param [in,out] nodo O nodo que é base na base da subarvore
 */
void balancear(Nodo **raiz, Nodo **nodo);

/**
 * Pesquisa uma palavra na árvore
 * @param [in] raiz ponteiro para a raiz
 * @param [in] palavra palavra que se deseja buscar
 * @return Nulo se não foi encontrado, caso contrário retorna o raiz no qual a palavra se encontra
 */
Nodo *pesquisar(Nodo *raiz, char *palavra);

/**
 * Retorna a quantidade de nodos existentes na árvore
 * @param raiz Raiz da árvore ou subarvore
 * @return Quantidade de nodos
 */
int contar_nodos(Nodo *raiz);

/**
 * @breaf Printa a árvore usando o caminhamento direita central.
 *
 * Indica a cor do nodo através das letras "r" (rubro), "n" (negro) e "o" representa a origem,
 * além da posição do nodo, se esquerda (E) ou direita (D).
 *
 * @param [in] nodo Raiz da árvore
 */
void print(Nodo *nodo);

/**
 * Cria uma representação em forma de string do tipo Nodo
 *
 * @code
 * // Exemplo
 * Nodo{.palavra="b", .cor=NEGRO, .esquerda="a", .direita=NULL, .pai="e"}
 * @endcode
 *
 * @param [in] nodo Nodo que se quer representar
 * @return Nodo em forma de string
 */
char *nodo_str(Nodo *nodo);

/**
 * Função auxiliar para a representação do tipo Nodo em formato de string
 * @param [in] palavra Palavra do nodo em questão
 * @param [in] cor Cor em formato de string do nodo
 * @param [in] esquerda Palavra do filho esquerdo
 * @param [in] direita Palavra do filho direito
 * @param [in] pai Palavra do pai
 * @return Nodo em forma de string
 */
char *nodo_str_auxiliar(char *palavra, char *cor, char *esquerda, char *direita, char *pai);

#endif // RUBRO_NEGRA
