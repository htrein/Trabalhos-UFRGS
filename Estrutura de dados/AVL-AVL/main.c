#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"");

    clock_t start, end;

    //entradas
    FILE * entrada1;
    FILE * entrada2;
    FILE * stopwords;

    //vari�veis
    char* word, buffer[MAX];
    char* new_word;
    int ok = 0;
    int i;
    int uniao = 0;
    float jaccard;
    int interseccao = 0;
    char separador[] = {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    //inicializa��o das �rvores
    pNodoA* avl1 = NULL;
    pNodoA* avl2 = NULL;
    pNodoA* avlstp = NULL;

    if(argc != 4)//caso n�o haja os argumentos necess�rios
    {
        printf("N�mero incorreto de par�metros. Digite: <nome.exe> <arq.txt> <arq.txt> <arqstpwrds.txt>");
        return 1;
    }
    else
    {
        entrada1 = fopen (argv[1], "r");
        entrada2 = fopen (argv[2], "r");
        stopwords = fopen (argv[3], "r");

        //verifica as aberturas dos arquivos, e sinaliza, caso der erro de abertura, qual foi que demonstrou erro
        if(entrada1 == NULL)
        {
            printf("Erro ao abrir o primeiro arquivo!\n");
            return 1;
        }
        if(entrada2 == NULL)
        {
            printf("Erro ao abrir o segundo arquivo!\n");
            return 1;
        }
        if(stopwords == NULL)
        {
            printf("Erro ao abrir o arquivo das stopwords!\n");
            return 1;
        }

        start = clock(); //come�a a contagem do tempo de execu��o
        while(fgets(buffer, MAX, stopwords)) // colocar no buffer 999 caracteres do arquivo das stopwords ou at� encontrar a quebra de linha (�\n�)
        {
            word = strtok(buffer, separador); //captura o token proveniente da fun��o strtok com os separadores declarados no inicio do c�digo
            while(word != NULL)
            {
                new_word = (char*)malloc(strlen(word)+1); //aloca espa�o din�mico para uma palavra
                for(i = 0; i < strlen(word); i++)
                    new_word[i] = tolower(word[i]);        //transforma ela pra min�scula
                new_word[strlen(word)] = '\0';              //adiciona sinal de final de string
                avlstp =  InsereAVL(avlstp, new_word, &ok); //adiciona a nova palavra na �rvore de stopwords
                word = strtok(NULL, separador);             //repete o processo at� que n�o haja mais palavras
            }
        }
        fclose(stopwords);

        while(fgets(buffer, MAX, entrada1))
        {
            word = strtok(buffer, separador);
            while(word != NULL)
            {
                new_word = (char*)malloc(strlen(word)+1);
                for(i = 0; i < strlen(word); i++)
                    new_word[i] = tolower(word[i]);
                new_word[strlen(word)] = '\0';              //mesma l�gica acima, por�m

                if(consultaAVL(avlstp, new_word)== 0)       //a palavra s� � adicionada na �rvore caso ela n�o esteja na �rvore de stopwords e nem j� tenha sido adicionada
                {
                    avl1 =  InsereAVL(avl1, new_word, &ok);
                }
                word = strtok(NULL, separador);
            }
        }
        fclose(entrada1);

        while(fgets(buffer, MAX, entrada2))
        {
            word = strtok(buffer, separador);
            while(word != NULL)
            {
                new_word = (char*)malloc(strlen(word)+1);
                for(i = 0; i < strlen(word); i++)
                    new_word[i] = tolower(word[i]);
                new_word[strlen(word)] = '\0';
                //mesma l�gica acima
                if(consultaAVL(avlstp, new_word) == 0)
                {
                    avl2 =  InsereAVL(avl2, new_word, &ok);
                }
                word = strtok(NULL, separador);
            }
        }
        fclose(entrada2);

        //c�lculo de Jaccard
        uniao = abs((num_nodos(avl1) + num_nodos(avl2)) - palavrasComum(avl1, avl2));
        interseccao = abs(palavrasComum(avl1, avl2));
        jaccard = ((float)interseccao)/((float)uniao);
        printf("Coeficiente de Jaccard: %.2f\n", jaccard);

        //finaliza contagem de execu��o
        end = clock();
        float cpu_time = (float)(end - start)/CLOCKS_PER_SEC * 1000;
        printf("Tempo: %.5f ms\n", cpu_time);
    }

    return 0;
}

