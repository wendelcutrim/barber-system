#include <stdlib.h>
#include <stdio.h>
#include "login.h"
#include <stdbool.h>
#include <string.h>

usuario source = {"BarberSys","steve9880"};

bool realizarLogin(){

    usuario login;
    system("cls");
    printf("Digite o login : ");
    gets(login.login);
    printf("Digite a senha : ");
    gets(login.senha);

    if(!strcmp(source.login,login.login) && !strcmp(source.senha,login.senha)){
        return true;
    }else{
        return false;
    }
}