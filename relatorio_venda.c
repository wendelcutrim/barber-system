#include "produtos_bib.h"
#include "cliente_bib.h"
#include "servicos_bib.h"
#include "data_bib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "relatorio_venda.h"

void chamarRelatorio() {

    char inicio[12];
    char fim[12];
    do {
        printf("Digite a data inicial no formato dd/mm/aaaa : ");
        gets(inicio);
        if (!isValidDate(inicio)) {
            printf("\n Data invalida\n");
            system("pause");
        }
    } while (!isValidDate(inicio));

    do {
        printf("Digite a data final no formato dd/mm/aaaa : ");
        gets(fim);
        if (!isValidDate(fim)) {
            printf("\n Data invalida\n");
            system("pause");
        }
    } while (!isValidDate(fim));

    imprimirRelatorio(inicio, fim);

}

bool isDate(char compara[]) {
    char *achou;

    if ((achou = strstr(compara, "Data")) != NULL) {
        return true;
    } else {
        return false;
    }
}

//A função abaixo procura um data inicial se achar retorna true, se não procura a data final se não achar retorna true
//A intensão é usar esses valores para controlar o fluxo de impressão do relatorio

bool isInsideOfTheRange(char inicio[], char fim[], char compara[]) {
    char *achou;
    char *achou1;

    if (((achou = strstr(compara, inicio)) != NULL) && (achou1 = strstr(compara, fim)) == NULL) {
        return true;
    } else {
        return false;
    }
}

bool isValidDate(char teste[]) {
    data data_atual;
    int tamanho = strlen(teste);
    char dia[2],mes[2],ano[4];
    dia[0] = teste [0];
    dia[1] = teste [1];
    mes[0] = teste [3];
    mes[1] = teste [4];
    ano[0] = teste [6];
    ano[1] = teste [7];
    ano[2] = teste [8];
    ano[3] = teste [9];

    
    for (int i = 0; i < tamanho; i++) {
        if (teste[i] == '0' || teste[i] == '1' || teste[i] == '2' || teste[i] == '3' ||
            teste[i] == '4' || teste[i] == '5' || teste[i] == '6' || teste[i] == '7' || teste[i] == '8'
            || teste[i] == '9' || teste[i] == '/') {
            return true;
        }
    }
    return false;
}

void imprimirRelatorio(char inicio[], char fim[]) {
    FILE *arq_relatorio;
    char recebe_str_arq[150];
    char *pt_char;
    int cont = 0;
    double temp;
    double acumulado = 0;
    arq_relatorio = fopen("arq_relatorio.txt", "r");
    fgets(recebe_str_arq, 150, arq_relatorio);
    system("cls");
    if(strcmp(inicio,fim)) {
        do {
            if ((pt_char = strstr(recebe_str_arq, inicio)) != NULL) {
                cont++;
                do {
                    printf("%s", recebe_str_arq);
                    if(isTotalValue(recebe_str_arq)){
                        fseek(arq_relatorio,-10,SEEK_CUR);
                        fscanf(arq_relatorio,"%lf",&temp);
                        acumulado += temp;
                    }
                    fgets(recebe_str_arq, 150, arq_relatorio);
                } while ((pt_char = strstr(recebe_str_arq, fim)) == NULL && !feof(arq_relatorio));
            } else {
                fgets(recebe_str_arq, 150, arq_relatorio);
            }

            if ((pt_char = strstr(recebe_str_arq, fim)) != NULL) {
                do {
                    printf("%s", recebe_str_arq);
                    if(isTotalValue(recebe_str_arq)){
                        fseek(arq_relatorio,-10,SEEK_CUR);
                        fscanf(arq_relatorio,"%lf",&temp);

                        acumulado += temp;
                    }
                    fgets(recebe_str_arq, 150, arq_relatorio);
                } while (!isDate(recebe_str_arq) && (pt_char = strstr(recebe_str_arq, fim)) == NULL && !feof(arq_relatorio));
                goto exit;
            }

        } while (!feof(arq_relatorio));
    }else {
        do {
            if ((pt_char = strstr(recebe_str_arq, inicio)) != NULL) {
                cont++;
                do {
                    printf("%s",recebe_str_arq);
                    fgets(recebe_str_arq,150,arq_relatorio);
                    if(isTotalValue(recebe_str_arq)){
                        fseek(arq_relatorio,-10,SEEK_CUR);
                        fscanf(arq_relatorio,"%lf",&temp);
                        acumulado += temp;
                    }
                } while (!isDate(recebe_str_arq) && (pt_char = strstr(recebe_str_arq, inicio)) == NULL &&
                         !feof(arq_relatorio));
            }else{
                fgets(recebe_str_arq,150,arq_relatorio);
            }
        } while (!feof(arq_relatorio));
    }

if (cont == 0) {
        printf("\nNenhum registro encontrado\n");
        system("pause");
    }
fclose(arq_relatorio);

    exit:
    printf("\nValor total vendido para o periodo : %.2lf\n",acumulado);
    system("pause");
}

bool isTotalValue(char teste[]){
    char *achou;

    if ((achou = strstr(teste, "Valor total")) != NULL) {
        return true;
    } else {
        return false;
    }
}
