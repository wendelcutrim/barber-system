#ifndef PROJETO_BARBEARIA_CLION_V1_0_RELATORIO_VENDA_H
#define PROJETO_BARBEARIA_CLION_V1_0_RELATORIO_VENDA_H
#include "cliente_bib.h"
#include "produtos_bib.h"
#include "servicos_bib.h"

typedef struct Relatorios
{
    cliente x;
    produto y[20];
    servico z[10];
    double valorVendido;
    data dataRelatorio;

}relatorio;

void chamarRelatorio();
bool isDate(char compara[]);
bool isInsideOfTheRange(char inicio[],char fim[],char compara[]);
bool isValidDate(char teste[]);
void imprimirRelatorio(char inicio[],char fim[]);
bool isTotalValue(char teste[]);

#endif //PROJETO_BARBEARIA_CLION_V1_0_RELATORIO_VENDA_H
