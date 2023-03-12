#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>


/* Exemplo de uso dos argumentos para main
O programa lê um arquivo texto como entrada e gera um arquivo como saída com o conteúdo do arquivo de entrada convertido para letras maiúsculas
Para chamar, digite "exemplo entrada.txt saida.txt" */




int main(int argc, char *argv[]) // argc conta o número de parâmetros e argv armazena as ‘strings’ correspondentes aos parâmentros digitados
{

    setlocale(LC_ALL, ""); // para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; // para contar o tempo decorrido

    FILE *entrada;
    FILE *saida;

    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc != 3) { // o número de parametros esperado é 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
        printf("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }

    entrada = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] é o primeiro parâmetro após o nome do arquivo.
    if (entrada == NULL) { // se não conseguiu abrir o arquivo
        printf("Erro ao abrir o arquivo %s", argv[1]);
        return 1;
    }
    saida = fopen(argv[2], "w"); // abre o arquivo para saida -- argv[2] é o segundo parâmetro após o nome do arquivo.

    start = clock(); // inicia a contagem do tempo

    while (fgets(linha, 1000, entrada)) {
        palavra = strtok(linha, separador);
        while (palavra != NULL) {
            fprintf(saida, "%s ", strlwr(palavra));
            palavra = strtok(NULL, separador);
        }
    }

    printf("\nArquivo %s gerado com sucesso.\n", argv[2]);

    end = clock(); // finaliza contagem do tempo
    float miliseconds = (float) (end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
    printf("Tempo: %.5f ms\n", miliseconds);

    fclose(entrada); //fecha os arquivos
    fclose(saida);

    return 0;
}
