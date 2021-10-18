#ifndef PROJETO_BARBEARIA_CLION_V1_0_PRODUTOS_BIB_H
#define PROJETO_BARBEARIA_CLION_V1_0_PRODUTOS_BIB_H
#include "data_bib.h"
#include "stdbool.h"
typedef struct Produtos
{
    int codigo;
    double valorEntrada;
    double valorVenda;
    double quantidade;
    double precoPromo;
    data validade;
    char descricao[60];

}produto;

void cadastrarProduto();
void editarProduto();
void pesquisarProduto();
void imprimirProduto();
double calcularValorVenda(double valor);
int manipularProdutos();
void gerarListaProdutos();
produto retornarProduto();
bool isThereProductAlready(int code);
void descontarEstoque(produto y[],double quantidade[],int tamanho);
void imprimirProdutosParaClientes(produto x);
void gerarListaProdutosCliente();


#endif //PROJETO_BARBEARIA_CLION_V1_0_PRODUTOS_BIB_H
