#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "cliente_bib.h"
#include "logo.h"
#include "data_bib.h"
#include "produtos_bib.h"
#include "servicos_bib.h"
#include "vendas_bib.h"
#include "login.h"
#include "relatorio_venda.h"



typedef struct Fornecedores
{
    char cnpj[18];
    char nome[50];
    char telefone[16];
    char email[20];
    char endereco[60];

}fornecedor;


typedef struct Agendamentos
{
    data dataAgendamento;
    char horario[10];
    cliente clienteAgendamento;

}agendamento;



typedef struct Lazer
{
    servico servicoLazer;
    int quantidadeFichas;

}lazer;


int main() {
    setlocale(LC_ALL, "Portuguese");
    //FILE* arq;
    //int contador = 0;
    //arq = fopen("arq_contador_servicos.dat","wb");
    //fwrite(&contador,sizeof(contador),1,arq);
    //fclose(arq);
    printLogo();
    system("pause");

    int op, menu = 0;
    inicio:
    do {
        system("cls");
        printf("Selecione uma opcao : \n\n");
        printf("0 - Sair\n");
        printf("1 - Login para gerenciamento do sistema\n");
        printf("2 - Ver precos dos produtos\n");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 2) {
            printf("\nValor invalido\n");
            system("pause");
        }
    } while (op < 0 || op > 2);

    if (op == 0) {
        goto exit;
    } else if (op == 2) {
        system("cls");
        gerarListaProdutosCliente();
        system("pause");
    } else if (op == 1) {


    if (realizarLogin()) {
        do {

            system("cls");
            printf("Digite a operacao desejada : \t\t\t\t\t\t\t\t\t\t     ");
            imprimirData(retornarDataAtual());
            printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t     ");
            imprimirHora(retornarHora());
            printf("\n");

            printf("0 - Sair\n");
            printf("1 - Manipular clientes\n");
            printf("2 - Manipular produtos\n");
            printf("3 - Manipular servicos\n");
            printf("4 - Realizar servico/venda\n");
            printf("5 - Gerar relatorio\n");
            scanf("%d", &op);
            fflush(stdin);

            system("cls");
            switch (op) {
                case 0 :
                    menu = 1;
                    break;
                case 1 :
                    manipularCliente();
                    break;
                case 2 :
                    manipularProdutos();
                    break;
                case 3 :
                    menuServicos();
                    break;
                case 4 :
                    realizarServico();
                    break;
                case 5:
                    chamarRelatorio();
                    break;
                default :
                    printf("Opcao invalída!\n\n");
                    system("pause");
                    menu = 0;
                    break;
            }
        } while (menu == 0);
    }
}else{
        printf("\nLogin ou senha invalido\n");
        system("pause");
        goto inicio;
    }
    goto inicio;
    exit:
    return 0;
}






