#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "cliente_bib.h"
#include <stdbool.h>

FILE *arq_clientes;
FILE *arq_contador_clientes;
FILE *arq_ID_clientes;

int manipularCliente() {

    int op, menu = 0;
    inicio:
    do {
        system("cls");
        printf("Digite a operacao desejada : \n\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Imprimir lista de clientes\n");
        printf("3 - Editar cliente\n");
        printf("4 - Pesquisar cliente\n");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        switch (op) {
            case 0 :
                goto exit;
                break;
            case 1 :
                cadastrarClientes();
                break;
            case 2 :
                gerarListaClientes();
                system("pause");
                break;
            case 3 :
                editarCliente();
                break;
            case 4 :
                pesquisarCliente();
                system("pause");
                break;
            default :
                printf("Opção invalída!\n\n");
                system("pause");
                goto inicio;
                break;

        }
    } while (menu == 0);
    exit:
    return 0;
}


void cadastrarClientes() {
    setlocale(LC_ALL, "portuguese");
    int op;
    int contador, id;
    cliente x;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    //fwrite(&contador,sizeof(contador),1,arq_contador_clientes);
    fclose(arq_contador_clientes);

    arq_ID_clientes = fopen("arq_ID_clientes.dat", "rb");
    fread(&id, sizeof(id), 1, arq_ID_clientes);
    //fwrite(&id,sizeof(id),1,arq_ID_clientes);
    fclose(arq_ID_clientes);

    x.ID = id;
    x.pontos = 0;

    system("cls");
    printf("Digite o cpf do cliente : ");
    gets(x.cpf);
    if (isThereCustomerAlready(x.cpf)) {
        printf("\nCliente ja cadastrado!\n");
        system("pause");
        goto exit;
    }

    printf("Digite o nome do cliente : ");
    gets(x.nome);
    strupr(x.nome);// funcao converte string para letras maiúsculas
    printf("Digite o numero de telefone : ");
    gets(x.telefone);
    printf("Digite a idade : ");
    scanf("%d", &x.idade);
    fflush(stdin);


    do {
        system("cls");
        printf("Deseja adicionar uma observacao? <0 - Nao | 1 - Sim> \n");
        scanf("%d", &op);
        fflush(stdin);
        if (op == 1) {
            printf("Digite uma observacao.\n");
            gets(x.obs);
        }
        if (op < 0 || op > 1) {
            printf("\nValor invalido\n");
            system("pause");
        }
    } while (op < 0 || op > 1);
    do {
        system("cls");
        printf("Deseja salvar? <0 - Nao | 1 - Sim>\n");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 1) {
            printf("\nValor invalido!\n");
        }
    } while (op < 0 || op > 1);

    if (op == 1) {
        x.ativo = 1;
        arq_clientes = fopen("arq_clientes.dat", "ab");
        fwrite(&x, sizeof(cliente), 1, arq_clientes);
        fclose(arq_clientes);

        contador++;
        id++;

        arq_contador_clientes = fopen("arq_contador_clientes.dat", "wb");
        fwrite(&contador, sizeof(contador), 1, arq_contador_clientes);
        fclose(arq_contador_clientes);

        arq_ID_clientes = fopen("arq_ID_clientes.dat", "wb");
        fwrite(&id, sizeof(id), 1, arq_ID_clientes);
        fclose(arq_ID_clientes);

        organizar();
    }
    exit:
    return;
}

void imprimirCliente(cliente x) {
    setlocale(LC_ALL, "portuguese");
    printf("ID : %d\n", x.ID);
    printf("Nome  : %s\n", x.nome);
    printf("Idade : %d\n", x.idade);
    printf("Telefone : %s\n", x.telefone);
    printf("CPF : %s\n", x.cpf);
    printf("Pontos : %d\n", x.pontos);
    printf("Observacao : %s\n", x.obs);
    printf("\n----------------------------------------\n");

}

void editarCliente() {
    char pesquisa[50];
    int contador, op;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

    printf("Digite um nome ou cpf para pesquisa : ");
    gets(pesquisa);
    strupr(pesquisa);

    int i;
    for (i = 0; i < contador; i++) {
        if ((!(strcmp(pesquisa, x[i].nome)) || !(strcmp(pesquisa, x[i].cpf))) && x[i].ativo == 1) {
            break;
        }
    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
        system("pause");
    } else {
        imprimirCliente(x[i]);
        do {
            printf("\nDeseja editar o cliente? <0 - NAO | 1 - SIM> \n");
            scanf("%d", &op);
            fflush(stdin);
            if (op < 0 || op > 1) {
                printf("Valor invalido!\n");
            }
        } while (op < 0 || op > 1);
        if (op == 1) {
            int op_2 = 0;
            do {
                do {
                    printf("Selecione a informacao que deseja alterar.\n");

                    printf("0 - Sair\n1 - Nome\n2 - idade\n3 - Telefone\n4 - CPF\n5 - Pontos\n6 - Observacao\n7 - Excluir cliente\n");
                    scanf("%d", &op);
                    fflush(stdin);
                    if (op < 0 || op > 7) {
                        printf("\nValor invalido!\n");
                    }
                } while (op < 0 || op > 7);
                switch (op) {
                    case 0 :
                        break;
                    case 1 :
                        printf("Digite o novo nome : ");
                        gets(x[i].nome);
                        strupr(x[i].nome);
                        break;
                    case 2 :
                        printf("Digite a nova idade : ");
                        scanf("%d", &x[i].idade);
                        fflush(stdin);
                        break;
                    case 3 :
                        printf("Digite o novo telefone : ");
                        gets(x[i].telefone);
                        break;
                    case 4 :
                        printf("Digite o novo cpf : ");
                        gets(x[i].cpf);
                        if (isThereCustomerAlready(x[i].cpf)) {
                            printf("\nCliente ja cadastrado!\n");
                            system("pause");
                            goto exit;
                        }
                        break;
                    case 5 :
                        printf("Digite nova quantidade de pontos : ");
                        scanf("%d", &x[i].pontos);
                        fflush(stdin);
                        break;
                    case 6 :
                        printf("Digite a nova observacao : ");
                        gets(x[i].obs);
                        break;
                    case 7 :
                        do {
                            printf("Tem certeza que deseja excluir o cliente? < 0 - NAO | 1 - SIM > ");
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
                            arq_contador_clientes = fopen("arq_contador_clientes.dat", "wb");
                            fwrite(&contador, sizeof(contador), 1, arq_contador_clientes);
                            fclose(arq_contador_clientes);
                        }
                        break;
                }
                do {
                    printf("\nDeseja alterar mais alguma informacao? < 0 - NAO | 1 - SIM > ");
                    scanf("%d", &op_2);
                    fflush(stdin);
                    if (op_2 < 0 || op_2 > 1) {
                        printf("\nValor invalido!\n");
                    }
                } while (op_2 < 0 || op_2 > 1);

            } while (op_2 == 1);
            do {
                printf("Deseja salvar as informacoes? < 0 - NAO | 1 - SIM >\n");
                scanf("%d", &op);

                if (op < 0 || op > 1) {
                    printf("\nValor invalido!\n");
                }
            } while (op < 0 || op > 1);

            if (op == 1) {

                arq_clientes = fopen("arq_clientes.dat", "wb");
                fwrite(x, sizeof(cliente), contador, arq_clientes);
                fclose(arq_clientes);
            }
        }

    }
    exit:
    return;
}

void gerarListaClientes() {
    int contador;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x;

    arq_clientes = fopen("arq_clientes.dat", "rb");


    for (int i = 0; i < contador; i++) {
        fread(&x, sizeof(cliente), 1, arq_clientes);
        imprimirCliente(x);
    }
    fclose(arq_clientes);

}

void pesquisarCliente() {
    char pesquisa[50];
    char *pt_nome;
    printf("Digite um nome para pesquisa : ");
    gets(pesquisa);
    strupr(pesquisa);

    int contador, op;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);
    int i;
    int j = 0;
    for (i = 0; i < contador; i++) {
        if ((pt_nome = strstr(x[i].nome, pesquisa)) != NULL) {
            if (&x[i].nome[0] == pt_nome) {
                imprimirCliente(x[i]);
                j++;
            }
        }
    }
    if (j == 0) {
        printf("\nNenhum registro encontrado\n");
    }
}

void organizar() {
    int contador;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];
    cliente temp;

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

    for (int i = (contador - 1); i > 0; i--) {

        if (strcmp(x[i - 1].nome, x[i].nome) > 0) {

            temp = x[i];
            x[i] = x[i - 1];
            x[i - 1] = temp;

        } else {
            break;
        }
    }


    arq_clientes = fopen("arq_clientes.dat", "wb");
    fwrite(x, sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

}

bool isThereCustomerAlready(char teste[15]) {
    int contador;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(x, sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

    int i;
    for (i = 0; i <= contador; i++) {
        if (!strcmp(x[i].cpf, teste)) {
            return true;
        }
    }
    return false;
}

cliente retornarCliente() {
    char pesquisa[50];
    printf("Digite um nome ou cpf do cliente : ");
    gets(pesquisa);
    strupr(pesquisa);

    int contador, op;

    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

    int i;

    for (i = 0; i <= contador; i++) {
        if (!(strcmp(x[i].nome, pesquisa)) || !(strcmp(x[i].cpf, pesquisa))) {
            return x[i];
        }


    }
    if (i >= contador) {
        printf("\nNenhum registro encontrado\n");
        cliente y;
        y.ativo = -1;
        return y;
    }
}

void adicionarPontos(char cpf[15]) {
    int contador;
    arq_contador_clientes = fopen("arq_contador_clientes.dat", "rb");
    fread(&contador, sizeof(contador), 1, arq_contador_clientes);
    fclose(arq_contador_clientes);

    cliente x[contador];

    arq_clientes = fopen("arq_clientes.dat", "rb");
    fread(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);

    for (int i = 0; i < contador; i++) {
        if (!(strcmp(cpf, x[i].cpf))) {
            x[i].pontos += 1;
            break;
        }
    }

    arq_clientes = fopen("arq_clientes.dat", "wb");
    fwrite(&x[0], sizeof(cliente), contador, arq_clientes);
    fclose(arq_clientes);
}
