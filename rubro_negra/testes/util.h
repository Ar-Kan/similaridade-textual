#ifndef UTIL
#define UTIL

/**
 * \struct Representação de um nodo para testes
 */
typedef struct NodoTeste {
    /// Palavra esperada do nodo
    char *palavra;
    /// Cor esperada do nodo
    int cor;
    /// Palavra esperada da subarvore esquerda
    char *esquerda;
    /// Palavra esperada da subarvore direita
    char *direita;
    /// Palavra esperada do pai do nodo
    char *pai;
} NodoTeste;

/**
 * Função "nodo_str" para o tipo NodoTeste
 *
 * @see rubro_negra.h::nodo_str()
 *
 * @param nodo Nodo que se quer representar
 * @return Nodo em forma de string
 */
char *nodoTeste_str(NodoTeste *nodo);

/**
 * Função auxiliar para comarar nodos
 * @param recebido O nodo "real" que pode existir numa árvore
 * @param esperado O nodo de teste
 * @return Retorna 0 se não houve erros, 1 caso contrário
 */
int compara_nodos(Nodo *recebido, NodoTeste *esperado);

void printf_vermelho(char *mensagem);

void printf_verde(char *mensagem);

#endif //UTIL
