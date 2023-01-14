#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

void registration(){
    char d[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    char p[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    char n[] = {1,2,3,4,5,6,7,8,9,0};
    int tmp = 0;
    user user;
    FILE *users_info = fopen("users_info.txt", "w");
    while (tmp == 0) {
    printf("Введите логин(от 3 до 20 символов латинского алфавита): ");
    scanf("%s", user.login);
    for(int i = 0; i < strlen(user.login); i++)
    {
        tmp = 0;
        for(int j = 0; j < 52; j++)
        {
            if(user.login[i] == d[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0) {
        printf("Вы ввели неправильные символы\n");
        break;
      }
    }
    }
    fprintf(users_info, "%s\n", user.login);
  tmp = 0;
  while (tmp == 0) {
    printf("Введите пароль(от 6 до 20 символов): ");
    scanf("%s", user.password);
    for(int i = 0; i < strlen(user.password); i++)
    {
        tmp = 0;
        for(int j = 0; j < 62; j++)
        {
            if(user.password[i] == p[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0) {
        printf("Вы ввели неправильные символы\n");
        break;
      }
    }
  }
  fprintf(users_info, "%s\n", user.password);
  tmp = 0;
  /*while (tmp == 0) {
    printf("Введите номер карты (16 символов): ");
    scanf("%s", user.card_number);
    for(int i = 0; i < 15; i++)
    {
        tmp = 0;
        for(int j = 0; j < 9; j++)
        {
            if(user.card_number[i] == n[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0 || strlen(user.card_number) != 16) {
        printf("Вы ввели неправильные символы или неправильное их количество\n");
        break;
      }
    }
    }*/
  printf("Введите номер карты (16 символов): ");
  scanf("%s", user.card_number);
  fprintf(users_info, "%s\n", user.card_number);
  }