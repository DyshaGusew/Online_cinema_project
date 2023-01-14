#ifndef MOVE_MOVE_FUNCTIONS_H
#define MOVE_MOVE_FUNCTIONS_H
#include <stdio.h>
#include <locale.h>
#include <limits.h>

typedef struct user{
    char login[20];
    char password[20];
    char card_number[16];
    int siseOfFavorites;
    int admin;
} user;

void registration();
#endif