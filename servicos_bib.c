#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "servicos_bib.h"
#include <stdbool.h>

FILE *arq_servicos;
FILE *arq_contador_servicos;

int menuServicos() {
    int op;
    int menu = 0;
    while (menu == 0) {

        system("cls");
        printf("Digite a operacao desejada : \n\n");
        printf("0 - Sair\n1 - Cadastrar um servico\n2 - Imprimir lista de servicos\n3 - Pesquisar servicos\n4 - Editar Servicos\n");
        scanf("%d", &op);
        fflush(stdin);

        switch (op) {
            case 0:
                return 0;
                break;
            case 1:
                cadastrarServicos();
                break;
            case 2:
                system("cls");
                gerarListaServicos();
                system("pause");
                break;
            case 3:
                pesquisarServicos();
                system("pause");
                break;
            case 4:
                editarServicos();
                break;
            default:
                printf("\nValor invalido\n");
                break;
        }
    }
}

void cadastrarServicos() {
    servico x;
    int contador;
    int op;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    system("cls");
    printf("Digite o codigo do servico : ");
    scanf("%d", &x.codigo);
    fflush(stdin);
    if (isThereCodeAlready(x.codigo)) {
        printf("\nCodigo ja cadastrado!\n");
        system("pause");
        goto exit;
    }
    printf("Digite o tipo do servico : ");
    gets(x.tipo);
    strupr(x.tipo);
    printf("Digite o valor do servico : ");
    scanf("%lf", &x.valor);
    fflush(stdin);

    do {
        printf("\nDeseja salvar as informacoes? < 0 - NAO | 1 - SIM > ");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 1) {
            printf("\nValor invalido\n");
            system("pause");
        }
    } while (op < 0 || op > 1);

    if (op == 1) {
        contador++;

        arq_contador_servicos = fopen("arq_contador_servicos.dat", "wb");
        fwrite(&contador, sizeof(contador), 1, arq_contador_servicos);
        fclose(arq_contador_servicos);

        arq_servicos = fopen("arq_servicos.dat", "ab");
        fwrite(&x, sizeof(servico), 1, arq_servicos);
        fclose(arq_servicos);
    }
    exit:
    return;
}

void imprimirServicos(servico x) {
    printf("\nCodigo : %d\n", x.codigo);
    printf("Tipo   : %s\n", x.tipo);
    printf("Valor  : %.2lf\n", x.valor);
    printf("\n------------------------------------------------\n");
}

void gerarListaServicos() {
    int contador;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    servico x[contador];

    arq_servicos = fopen("arq_servicos.dat", "rb");
    fread(x, sizeof(servico), contador, arq_servicos);
    fclose(arq_servicos);

    for (int i = 0; i < contador; i++) {
        imprimirServicos(x[i]);
    }
}

void pesquisarServicos() {
    char *pt_pesquisa;
    char pesquisa[50];
    int contador;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    servico x[contador];

    arq_servicos = fopen("arq_servicos.dat", "rb");
    fread(x, sizeof(servico), contador, arq_servicos);
    fclose(arq_servicos);

    system("cls");
    printf("Digite tipo ou codigo do servico : ");
    gets(pesquisa);
    strupr(pesquisa);
    int i;
    for (i = 0; i <= contador; i++) {
        if ((pt_pesquisa = strstr(x[i].tipo, pesquisa)) != NULL) {
            break;

        } else if (atoi(pesquisa) == x[i].codigo) {
            break;
        }
    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
    } else {
        imprimirServicos(x[i]);
    }
}

void editarServicos() {
    char pesquisa[50];
    int contador;
    int op, op_2;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    servico x[contador];

    arq_servicos = fopen("arq_servicos.dat", "rb");
    fread(x, sizeof(servico), contador, arq_servicos);
    fclose(arq_servicos);
    system("cls");
    printf("Digite tipo ou codigo do servico : ");
    gets(pesquisa);
    strupr(pesquisa);
    int i;
    for (i = 0; i <= contador; i++) {
        if (!strcmp(x[i].tipo, pesquisa) || atoi(pesquisa) == x[i].codigo) { break; }
    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
        system("pause");
    } else {
        do {
            imprimirServicos(x[i]);
            printf("\nDeseja editar o servico? < 0 - NAO | 1 - SIM > ");
            scanf("%d", &op);
            if (op < 0 || op > 1) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 0 || op > 1);

        if (op == 1) {
            do {
                back :
                system("cls");
                imprimirServicos(x[i]);
                printf("\nSelecione a informação que deseja alterar : \n");
                printf("0 - Sair\n1 - Codigo\n2 - Tipo\n3 - Valor\n4 - Excluir\n");
                scanf("%d", &op_2);
                fflush(stdin);

                switch (op_2) {
                    case 0 :
                        break;
                    case 1 :
                        printf("Digite o novo codigo : ");
                        scanf("%d", &x[i].codigo);
                        fflush(stdin);
                        if (isThereCodeAlready(x[i].codigo)) {
                            printf("\nCodigo ja cadastrado!\n");
                            system("pause");
                            goto exit;
                        }
                        break;
                    case 2:
                        printf("Digite o novo tipo : ");
                        gets(x[i].tipo);
                        strupr(x[i].tipo);
                        break;
                    case 3:
                        printf("Digite o novo valor : ");
                        scanf("%lf", &x[i].valor);
                        break;
                    case 4:
                        printf("Tem certeza que deseja excluir o produto? < 0 - NAO | 1 - SIM > ");
                        scanf("%d", &op);
                        if (op == 1) {
                            for (int j = i; j < contador; j++) {
                                if (j < contador) {
                                    x[j] = x[j + 1];
                                }
                            }
                            contador--;

                            arq_contador_servicos = fopen("arq_contador_servicos.dat", "wb");
                            fwrite(&contador, sizeof(contador), 1, arq_contador_servicos);
                            fclose(arq_contador_servicos);
                            goto atalho_salvar;

                        } else {
                            break;
                        }
                    default:
                        printf("\nValor invalido\n");
                        goto back;
                }
                do {
                    printf("\nDeseja continuar editando? < 0 NAO | 1 - SIM > ");
                    scanf("%d", &op_2);
                    fflush(stdin);
                    if (op < 0 || op > 1) {
                        printf("\nValor invalido\n");
                        system("pause");
                    }
                } while (op < 0 || op > 1);
                if (op_2 == 0) {
                    do {
                        printf("\nDeseja salvar as informacoes? < 0 NAO | 1 - SIM > ");
                        scanf("%d", &op);
                        fflush(stdin);
                        if (op < 0 || op > 1) {
                            printf("\nValor invalido\n");
                            system("pause");
                        }
                    } while (op < 0 || op > 1);
                    if (op == 1) {
                        atalho_salvar:
                        arq_servicos = fopen("arq_servicos.dat", "wb");
                        fwrite(x, sizeof(servico), contador, arq_servicos);
                        fclose(arq_servicos);
                    }
                }

            } while (op_2 == 1);
        }
    }
    exit:
    return;
}

servico retornarServico() {
    char pesquisa[50];
    int contador;
    int op;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    servico x[contador];

    arq_servicos = fopen("arq_servicos.dat", "rb");
    fread(x, sizeof(servico), contador, arq_servicos);
    fclose(arq_servicos);

    printf("Digite tipo ou codigo do servico : ");
    gets(pesquisa);
    strupr(pesquisa);
    int i;
    for (i = 0; i <= contador; i++) {
        if (!strcmp(x[i].tipo, pesquisa) || atoi(pesquisa) == x[i].codigo) {
            break;
        }
    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
        system("pause");
        servico y;
        y.codigo = -1;
        return y;
    } else {
        return x[i];
    }
}

bool isThereCodeAlready(int code) {
    int contador;

    arq_contador_servicos = fopen("arq_contador_servicos.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_servicos);
    fclose(arq_contador_servicos);

    servico x[contador];

    arq_servicos = fopen("arq_servicos.dat", "rb");
    fread(x, sizeof(servico), contador, arq_servicos);
    fclose(arq_servicos);

    int i;
    for (i = 0; i <= contador; i++) {
        if (x[i].codigo == code) {
            return true;
        }
    }
    return false;
}

