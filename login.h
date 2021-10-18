#ifndef PROJETO_BARBEARIA_CLION_V1_0_LOGIN_H
#define PROJETO_BARBEARIA_CLION_V1_0_LOGIN_H
#include <stdbool.h>

typedef struct Usuario
{
    char login[15];
    char senha[10];

}usuario;

bool realizarLogin();


#endif //PROJETO_BARBEARIA_CLION_V1_0_LOGIN_H
