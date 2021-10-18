#ifndef CLIENTE_BIB_H
#define CLIENTE_BIB_H
#include <stdbool.h>


typedef struct Clientes
{
    int ID;
    int idade;
    int pontos;
    int ativo;
    char cpf[15];
    char obs[100];
    char telefone[16];
    char nome[50];

} cliente;

void cadastrarClientes();
void imprimirCliente(cliente x);
void pesquisarCliente();
void gerarListaClientes();
void editarCliente();
void organizar();
int manipularCliente();
bool isThereCustomerAlready(char teste[15]);
cliente retornarCliente();
void adicionarPontos(char cpf[15]);



/*
22/10/2020

 - criamos a bibloteca clientes
 - descobrimos como imprimir lista de cliente sem incrementar ciclo for
 - tentamos fazer gerar ID automaticamente, mas falhamos
*/

//legenda
//0 - nao importante
//1 - muito importante
//2 - prioridade media
//3 - prioridade baixa

//Lista to do implementacoes clientes

//1 - Corrigir ID para atualizar automatico - OK
//1 - Corrigir contador de cliente para atualizar automatico - OK
//2 - Fazer op��o de editar as informa��es do cliente - OK
//2 - Fazer op��o para excluir o cliente - OK
//1 - Pesquisar por substring ou seja se digitar o primeiro nome vai mostrar todos os cliente com esse nome - OK
//0 - Descobrir por que o executavel n�o mostra as informa��es salvas - OK
//0 - Tentar organizar em ordem alfab�tica - OK
//2 - Descobrir porqur ao gerar lista repete o ultimo cadastro - OK

#endif
