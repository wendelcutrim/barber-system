#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cliente_bib.h"
#include "produtos_bib.h"
#include "servicos_bib.h"
#include "data_bib.h"

int cont_produtos = 0;
int quantidade_produto = 0;
produto produto_x[20];
double quantidade_itens[20];
cliente cliente_x;


double realizarVendas(double valorAcumulado) {

    int contador;
    int op;

    system("cls");

        do {
            back_add_product :
            system("cls");
            printf("Adicionar produtos : \n");
            produto_x[cont_produtos] = retornarProduto();
            if (produto_x[cont_produtos].codigo != -1 && produto_x[cont_produtos].quantidade > 0) {
                imprimirProduto(produto_x[cont_produtos]);
                do {
                    printf("Digite a quantidade do produto : ");
                    scanf("%lf", &quantidade_itens[cont_produtos]);
                    fflush(stdin);
                    if (quantidade_itens[cont_produtos] > produto_x[cont_produtos].quantidade) {
                        printf("\nQuantidade entrada excede estoque.\n");
                    }
                } while (quantidade_itens[cont_produtos] > produto_x[cont_produtos].quantidade);
                valorAcumulado += (produto_x[cont_produtos].valorVenda) * quantidade_itens[cont_produtos];
                cont_produtos++;
                printf("Valor total : R$  %.2lf\n", valorAcumulado);
                printf("Deseja adicionar mais produtos? < 0 - NAO | 1 - SIM > ");
                scanf("%d", &op);
                fflush(stdin);
                if (op < 0 || op > 1) {
                    printf("\nValor invalido\n");
                }

            } else {
                do {
                    if(produto_x[cont_produtos].quantidade == 0){
                        printf("\nProduto sem estoque\n");
                    }else {
                        printf("\nProduto nao encontrado\n");
                    }
                    printf("Digitar novamente? < 0 - NAO | 1 - SIM > ");
                    scanf("%d", &op);
                    fflush(stdin);
                    if (op < 0 || op > 1) {
                        printf("Valor invalido");
                        system("pause");
                    }
                } while (op < 0 || op > 1);
                if (op == 1) {
                    goto back_add_product;
                }
            }
        } while (op == 1 || op < 0 || op > 1);

    do {
        printf("Finalizar venda? < 0 - CANCELAR | 1 - SIM | 2 - ADICIONAR PRODUTOS >");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 2) {
            printf("\nValor invalido\n");
        }
    } while (op < 0 || op > 2);
    if (op == 2) {
        goto back_add_product;
    } else if (op == 1) {
        printf("Valor total : R$ %.2lf\n", valorAcumulado);
        return valorAcumulado;
    }
    exit:

    return valorAcumulado;
}

void realizarServico(){

    FILE * arq_relatorio;
    double valorTotal = 0;
    int cont_servico = 0;

    data data_atual;
    data_atual = retornarDataAtual();
    servico servico_x[20];

    int op,op_2;
    do {
        printf("Cliente cadastrado? < 0 - NAO | 1 - SIM > | 2 - SAIR > ");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 2) {
            printf("\nValor invalido\n");
            system("pause");
        }
    } while (op < 0 || op > 2);

    if (op == 1) {
        do {
            back_to_add_customer:
            system("cls");
            cliente_x = retornarCliente();
            if (cliente_x.ativo == -1) {
                do {
                    printf("Cliente nao encontrado\n\nDeseja digitar novamente? < 0 - NAO | 1 - SIM > ");
                    scanf("%d", &op);
                    fflush(stdin);
                    if (op < 0 || op > 1) {
                        printf("\nValor invalido\n");
                    }
                } while (op < 0 || op > 1);
                if (op == 1) {
                    goto back_to_add_customer;
                } else {
                    op = 2;
                }
            } else {
                imprimirCliente(cliente_x);
                printf("Adicionar cliente? <0 - NAO | 1 - SIM | 2 - SAIR > \n");
                scanf("%d", &op);
                fflush(stdin);
                if (op < 0 || op > 2) {
                    printf("\nValor invalido\n");
                }
            }

        } while (op == 0 || op < 0 || op > 2);
        if (op == 2) {
            do {
                printf("Deseja continuar sem cliente? < 0 - NAO | 1 - SIM | 2 - CANCELAR > \n");
                scanf("%d", &op);
                fflush(stdin);
                if (op == 0) {
                    goto back_to_add_customer;
                } else {
                    strcpy(cliente_x.nome, "Nao cadastrado");
                    strcpy(cliente_x.cpf, "Nao cadastrado");
                }
                if (op < 0 || op > 2) {
                    printf("\nValor invalido\n");
                }
            } while (op < 0 || op > 2);
        }
    } else if (op == 0) {
        strcpy(cliente_x.nome, "Nao cadastrado");
        strcpy(cliente_x.cpf, "Nao cadastrado");
    } else {
        goto exit;
    }
    do {
        printf("Confirmar? < 0 - NAO | 1 - SIM >");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 1) {
            printf("\nValor invalido\n");
        }
    } while (op < 0 || op > 1);

    if (op == 0) {
        goto back_to_add_customer;
    }
    do {
        printf("Adicionar servico? < 0 - NAO | 1 - SIM > \n");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 0 || op > 1) {
            printf("\nValor invalido\n");
            system("pause");
        }
    } while (op < 0 || op > 1);

    if (op == 1) {
    back:
    system("cls");
    servico_x[cont_servico] = retornarServico();
    if (servico_x[cont_servico].codigo != -1) {
        imprimirServicos(servico_x[cont_servico]);
        do {
            printf("Confirmar servico? < 0 - NAO | 1 - SIM > ");
            scanf("%d", &op);
            fflush(stdin);
            if (op < 0 || op > 1) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 0 || op > 1);
        if (op == 1) {
            valorTotal += servico_x[cont_servico].valor;
            printf("Valor total : R$ %.2lf\n", valorTotal);
            do {
                printf("Adicionar mais servicos? < 0 - NAO | 1 - SIM >");
                scanf("%d", &op);
                fflush(stdin);
                if (op == 1) {
                    cont_servico++;
                    goto back;
                }
                if (op < 0 || op > 1) {
                    printf("\nValor invalido\n");
                }
            } while (op < 0 || op > 1);

        }
    } else {
        do {
            printf("Deseja digitar novamente? < 0 NAO | 1 - SIM > ");
            scanf("%d", &op);
            fflush(stdin);
            if (op < 0 || op > 1) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 0 || op > 1);
        if (op == 1) {
            goto back;
        }
    }
}
    do{
        printf("Deseja adicionar produtos para venda? < 0 - NAO | 1 - SIM > ");
        scanf("%d",&op_2);
        fflush(stdin);
        if(op_2 < 0 || op_2 > 1){
            printf("\nValor invalido\n");
            system("pause");
        }
    }while(op_2 < 0 || op_2 > 1);

    if(op_2 == 1){
        double temp = 0;
          temp += realizarVendas(valorTotal);
          valorTotal = temp;
    }
    if(op == 0 && op_2 == 0){
        goto exit;
    }


    if(valorTotal > 0) {

        arq_relatorio = fopen("arq_relatorio.txt","a");
        fprintf(arq_relatorio,"--------------------------------------------------------------------\n");
        fprintf(arq_relatorio,"Data        : %d/%d/%d\n",data_atual.dia,data_atual.mes,data_atual.ano);

        fprintf(arq_relatorio,"Cliente     : %s \n",cliente_x.nome);
        for(int i = 0;i <= cont_servico;i++) {
            fprintf(arq_relatorio,"Servico     : %s | Valor : R$ %.2lf\n", servico_x[i].tipo, servico_x[i].valor);
        }

       for(int i = 0;i < cont_produtos;i++){
            fprintf(arq_relatorio,"Produto     : %s | Quantidade : %.1lf | Valor unitario : R$ %.2lf\n",produto_x[i].descricao,quantidade_itens[i],produto_x[i].valorVenda);
        }
        fprintf(arq_relatorio,"Valor total : R$   %.2lf\n",valorTotal);
        fclose(arq_relatorio);

        adicionarPontos(cliente_x.cpf);
        descontarEstoque(produto_x, quantidade_itens, cont_produtos);

        do {
            system("cls");
            printf("Valor total : R$ %.2lf\n", valorTotal);
            printf("Qual forma de pagamento? < 1 - Dinheiro | 2 - Cartao > \n");
            scanf("%d", &op);
            if (op < 1 || op > 2) {
                printf("\nValor invalido\n");
                system("pause");
            }
        } while (op < 1 || op > 2);
        if (op == 1) {
            double valorRecebido = 0;
            do {
                printf("Digite o valor recebido : ");
                scanf("%lf", &valorRecebido);
                fflush(stdin);
                if (valorRecebido < valorTotal) {
                    printf("\nValor invalido\n");
                }
            } while (valorRecebido < valorTotal);

            double troco = valorRecebido - valorTotal;
            printf("Troco : R$ %.2lf\n", troco);
            system("pause");
        } else if (op == 2) {
            printf("Insira o cartao...\n");
            system("pause");
            printf("Digite a senha...\n");
            system("pause");
            printf("Transacao aprovada.\n");
            system("pause");
        }
    }

    exit:
    return;
}