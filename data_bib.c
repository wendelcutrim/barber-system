#include "data_bib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

data retornarDataAtual(){
    struct tm *pt_data;
    time_t seg;
    time(&seg);

    pt_data = localtime(&seg);

    data data_atual;
    data_atual.dia = pt_data->tm_mday;
    data_atual.mes = (pt_data->tm_mon)+1;
    data_atual.ano = (pt_data->tm_year)+1900;

    return data_atual;
}

hora retornarHora(){
    struct tm *pt_hora;
    time_t seg;
    time(&seg);

    pt_hora = localtime(&seg);

    hora hora_atual;
    hora_atual.horas = pt_hora->tm_hour;
    hora_atual.minutos = pt_hora->tm_min;
    hora_atual.segundos = pt_hora->tm_sec;

    return hora_atual;
}

void imprimirData(data x){
    printf("%d/%d/%d",x.dia,x.mes,x.ano);
}

void imprimirHora(hora x){
    printf("%d:%d:%d",x.horas,x.minutos,x.segundos);
}



