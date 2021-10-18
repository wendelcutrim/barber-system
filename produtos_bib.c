#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "produtos_bib.h"
#include <stdbool.h>

//implementar um bloco de codigo que não permite adicionar o produto se a quantidade no estoque for igual a 0
//e permite digitar novamente ou sair.

FILE *arq_produtos;
FILE *arq_contador_produtos;


int manipularProdutos() {

    int op, menu = 0;

    //int contador = 0;

    //arq_contador_produtos = fopen("arq_contador_produtos.dat","wb");
    //fwrite(&contador,sizeof(contador),1,arq_contador_produtos);
    //fclose(arq_contador_produtos);

    inicio:


    do {

        system("cls");
        printf("Digite a operacao desejada : \n\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar produtos\n");
        printf("2 - Pesquisar produtos\n");
        printf("3 - Imprimir lista de produtos\n");
        printf("4 - Editar produtos\n");
        //printf("4 - Pesquisar cliente\n");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        switch (op) {
            case 0 :
                return 0;
                break;
            case 1 :
                cadastrarProduto();
                break;
            case 2 :
                pesquisarProduto();
                system("pause");
                break;
            case 3 :
                gerarListaProdutos();
                system("pause");
                break;
            case 4 :
                editarProduto();
                break;
            default :
                printf("Opção invalida!\n\n");
                system("pause");
                goto inicio;
                break;

        }
    } while (menu == 0);
}

void cadastrarProduto() {

    produto x;
    int contador, op;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    system("cls");
    printf("Digite o codigo do produto: \n");
    scanf("%d", &x.codigo);
    fflush(stdin);
    if (isThereProductAlready(x.codigo)) {
        printf("\nCodigo ja cadastrado\n");
        system("pause");
        getchar();
        goto exit;
    }

    printf("Digite a descricao do produto\n");
    gets(x.descricao);
    strupr(x.descricao);
    printf("Digite o preco de entrada:\n");
    scanf("%lf", &x.valorEntrada);
    fflush(stdin);
    x.valorVenda = calcularValorVenda(x.valorEntrada);
    printf("Digite a validade do produto.\n");
    scanf("%d""%d""%d", &x.validade.dia, &x.validade.mes, &x.validade.ano);
    printf("Digite a quantidade : ");
    scanf("%lf", &x.quantidade);
    fflush(stdin);
    x.precoPromo = 0;

    printf("\nDeseja salvar as informacoes dos produtos? < 0 - NAO | 1 - SIM >\n");
    scanf("%d", &op);
    fflush(stdin);

    if (op == 1) {

        arq_produtos = fopen("arq_produtos.dat", "ab");
        fwrite(&x, sizeof(produto), 1, arq_produtos);
        fclose(arq_produtos);

        contador++;

        arq_contador_produtos = fopen("arq_contador_produtos.dat", "wb");
        fwrite(&contador, sizeof(contador), 1, arq_contador_produtos);
        fclose(arq_contador_produtos);
    }
    exit:
    return;
}

void imprimirProduto(produto x) {

    printf("Descricao :    %s\n", x.descricao);
    printf("Codigo                :    %d\n", x.codigo);
    printf("Valor de entrada      :    %.2lf\n", x.valorEntrada);
    printf("Valor de venda        :    %.2lf\n", x.valorVenda);
    printf("Valor promocional     :    %.2lf\n", x.precoPromo);
    printf("Data de validade      :    %d/%d/%d\n", x.validade.dia, x.validade.mes, x.validade.ano);
    printf("Quantidade em estoque :    %.2lf\n\n", x.quantidade);
    printf("---------------------------------------------\n");

}

double calcularValorVenda(double valor) {
    return valor *= 1.30;
}

void pesquisarProduto() {
    char pesquisa[60];
    int contador;
    char *pt_pesquisa;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    printf("Digite o codigo ou descricao do produto : ");
    gets(pesquisa);
    strupr(pesquisa);

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);
    int i;
    int j = 0;
    for (i = 0; i < contador; i++) {
        if ((pt_pesquisa = strstr(x[i].descricao, pesquisa)) != NULL) {
            if (&x[i].descricao[0] == pt_pesquisa) {
                imprimirProduto(x[i]);
                j++;
            }

        } else if (atoi(pesquisa) == x[i].codigo) {
            imprimirProduto(x[i]);
            j++;
        }

    }
    if (j == 0) {
        printf("\nNenhum registro encontrado\n");
    }
}

void gerarListaProdutos() {
    int contador;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);

    for (int i = 0; i < contador; i++) {
        imprimirProduto(x[i]);
    }

}

void editarProduto() {
    char pesquisa[60];
    int contador;
    int op, op_2;
    setlocale(LC_ALL, "Portuguese");
    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);

    printf("Digite o codigo ou descricao do produto : ");
    gets(pesquisa);
    strupr(pesquisa);
    int i;
    for (i = 0; i < contador; i++) {
        if (!strcmp(x[i].descricao, pesquisa) || atoi(pesquisa) == x[i].codigo) {
            break;
        }
    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
    } else {
        imprimirProduto(x[i]);
        do {
            printf("Deseja editar o produto? < 0 - NAO | 1 - SIM > \n");
            scanf("%d", &op);
            fflush(stdin);
            if (op < 0 || op > 1) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 0 || op > 1);

        if (op == 1) {
            do {
                back :
                printf("Selecione a informacao que deseja editar:\n\n");
                printf("0 - Sair\n1 - Codigo\n2 - Descricao\n3 - Valor de entrada\n"
                       "4 - Valor de venda\n5 - Valor promocional\n"
                       "6 - Quantidade em estoque\n7 - Data de validade\n8 - Excluir produto\n");
                scanf("%d", &op);
                fflush(stdin);
                switch (op) {
                    case 1:
                        system("cls");
                        printf("Digite o novo codigo: \n");
                        scanf("%d", &x[i].codigo);
                        fflush(stdin);
                        if (isThereProductAlready(x[i].codigo)) {
                            printf("\nCodigo ja cadastrado\n");
                            system("pause");
                            goto exit;
                        }

                        break;
                    case 2:
                        printf("Digite a nova descricao : \n");
                        gets(x[i].descricao);
                        strupr(x[i].descricao);
                        break;

                    case 3:
                        printf("Digite novo valor de entrada : \n");
                        scanf("%lf", &x[i].valorEntrada);
                        fflush(stdin);
                        x[i].valorVenda = calcularValorVenda(x[i].valorEntrada);
                        break;
                    case 4:
                        printf("Digite novo valor de venda : \n");
                        scanf("%lf", &x[i].valorVenda);
                        fflush(stdin);
                        break;
                    case 5:
                        printf("Digite o novo valor promocional : \n");
                        scanf("%lf", &x[i].precoPromo);
                        fflush(stdin);
                        break;
                    case 6:
                        printf("Digite a nova quantidade : \n");
                        scanf("%lf", &x[i].quantidade);
                        fflush(stdin);
                        break;
                    case 7:
                        printf("Digite a nova data de validade : \n");
                        scanf("%d""%d""%d", &x[i].validade.dia, &x[i].validade.mes, &x[i].validade.ano);
                        break;
                    case 8:
                        do {
                            printf("Tem certeza que deseja excluir o produto? < 0 - NAO | 1 - SIM > ");
                            scanf("%d", &op);
                            fflush(stdin);
                            if (op < 0 || op > 1) {
                                printf("\nValor invalido\n");
                            }
                        } while (op < 0 || op > 1);
                        if (op == 1) {
                            for (int j = i; j < contador; j++) {
                                if (j < contador) {
                                    x[j] = x[j + 1];
                                }
                            }
                            contador--;
                            arq_contador_produtos = fopen("arq_contador_produtos.dat", "wb");
                            fwrite(&contador, sizeof(contador), 1, arq_contador_produtos);
                            fclose(arq_contador_produtos);
                        }
                        break;
                    default:
                        printf("\nValor invalido\n");
                        system("pause");
                        goto back;
                }
                do {
                    system("cls");
                    printf("Deseja continuar editando? < 0 - NAO | 1 - SIM > \n");
                    scanf("%d", &op_2);
                    fflush(stdin);
                    if (op_2 < 0 || op_2 > 1) {
                        printf("\nValor invalido\n");
                        system("pause");
                    }
                } while (op_2 < 0 || op_2 > 1);
            } while (op_2 == 1);

        }
        do {
            printf("Deseja salvar as informacoes? < 0 - NAO | 1 - SIM > ");
            scanf("%d", &op);
            fflush(stdin);
            if (op < 0 || op > 1) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 0 || op > 1);

        if (op == 1) {
            arq_produtos = fopen("arq_produtos.dat", "wb");
            fwrite(x, sizeof(produto), contador, arq_produtos);
            fclose(arq_produtos);
        }
    }
    exit:
    return;
}

produto retornarProduto() {

    char pesquisa[60];
    int contador;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    printf("Digite o codigo ou descricao do produto : ");
    gets(pesquisa);
    strupr(pesquisa);

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);
    int i;
    for (i = 0; i <= contador; i++) {
        if (!strcmp(x[i].descricao, pesquisa) || atoi(pesquisa) == x[i].codigo) {
            return x[i];
        }
    }
    if (i >= contador) {
        produto x;
        x.codigo = -1;
        return x;
    }
}

bool isThereProductAlready(int code) {
    int contador;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_produtos);
    fclose(arq_produtos);

    int i;
    for (i = 0; i <= contador; i++) {
        if (x[i].codigo == code) {
            return true;
        }
    }
    return false;

}

void descontarEstoque(produto y[], double quantidade[], int tamanho) {

    int contador;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < contador; j++) {
            if (y[i].codigo == x[j].codigo) {
                x[j].quantidade -= quantidade[i];
            }
        }
    }

    arq_produtos = fopen("arq_produtos.dat", "wb");
    fwrite(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);
}

void imprimirProdutosParaClientes(produto x){
    printf("Descricao        :    %s\n", x.descricao);
    printf("Valor de venda   : R$ %.2lf\n", x.valorVenda);
    printf("Data de validade :    %d/%d/%d\n", x.validade.dia, x.validade.mes, x.validade.ano);
    printf("-------------------------------------------------\n");
}

void gerarListaProdutosCliente(){
    int contador;

    arq_contador_produtos = fopen("arq_contador_produtos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_produtos);
    fclose(arq_contador_produtos);

    produto x[contador];

    arq_produtos = fopen("arq_produtos.dat", "rb");
    fread(x, sizeof(produto), contador, arq_contador_produtos);
    fclose(arq_produtos);

    for (int i = 0; i < contador; i++) {
        if(x[i].quantidade > 0) {
            imprimirProdutosParaClientes(x[i]);
        }
    }
}