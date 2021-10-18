//
// Created by giova on 12/11/2020.
//

#ifndef PROJETO_BARBEARIA_CLION_V1_0_SERVICOS_BIB_H
#define PROJETO_BARBEARIA_CLION_V1_0_SERVICOS_BIB_H
#include <stdbool.h>
typedef struct Servicos
{
    int codigo;
    double valor;
    char tipo[50];

}servico;

int menuServicos();
void cadastrarServicos();
void pesquisarServicos();
void editarServicos();
void gerarListaServicos();
void imprimirServicos(servico x);
servico retornarServico();
bool isThereCodeAlready(int code);


#endif //PROJETO_BARBEARIA_CLION_V1_0_SERVICOS_BIB_H
