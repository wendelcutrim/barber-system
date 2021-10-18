#ifndef PROJETO_BARBEARIA_CLION_V1_0_DATA_BIB_H
#define PROJETO_BARBEARIA_CLION_V1_0_DATA_BIB_H

typedef struct Data
{
    int dia;
    int mes;
    int ano;

}data;

typedef struct Hora{
    int horas;
    int minutos;
    int segundos;
}hora;


data retornarDataAtual();
hora retornarHora();
void imprimirData(data x);
void imprimirHora(hora x);

#endif //PROJETO_BARBEARIA_CLION_V1_0_DATA_BIB_H
