#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

//Создание структуры фильма из входных значений
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //Выделение памяти для фильма
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //Занесение значений в структуру фильма
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//Вывод триплета карточек фильмов
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");

    //О боже, сложно понять, но попробуйте
    printf("                                        ");                              printf("//===================================\\");printf("\\ \n");
    printf("                                        ");                              printf("||                                   ||\n");
    printf("/-----------------------------------\\   ");                              printf("||                                   ||   ");                        printf("/-----------------------------------");printf("\\ ");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    out_str_center(list_root->previous->name, 35);printf("   |");out_str_center(list_root->name, 35);      printf("|   ");      out_str_center(list_root->next->name, 35);printf("\n");
    out_str_center(list_root->previous->genres, 35);printf("   |");out_str_center(list_root->genres, 35);      printf("|   ");      out_str_center(list_root->next->genres, 35);printf("\n");
    printf("|            Рейтинг %.1f            |   ", list_root->previous->rating); printf("||            Рейтинг %.1f            ||   ", list_root->rating);    printf("|            Рейтинг %.1f            |\n", list_root->next->rating);
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("\\-----------------------------------/   ");                               printf("||                                   ||   ");                        printf("\\-----------------------------------/\n");
    printf("                                        ");                               printf("||                                   ||\n");
    printf("                                        ");     printf("\\");      printf("\\===================================//\n");
}

//Вывод строки в середине указанного диапазона
void out_str_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Подсчет символов
        i++;
    }

    int space = (leight_str-i)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Левая часть
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("%s", string);   //Центр

    while(space_right!=0){    //Правая часть
        printf(" ");
        space_right--;
    }


    if((leight_str-i)%2 != 0 ){          //Проверка на нечетность строки и сдвиг по необходимости
        printf(" |");
    }
    else{
        printf("|");
    }

};

//Создание списка фильмов
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //??????? ?????(?????????? ?? ??????? ?????? ?? ??????)

    //Переменные для считывания
    char null[3];                //?????????? ??? ???????? ?? ????? ??????
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //Считываю значения с файла и ввожу в структуру фильма
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //Символ переход на новую строку заменяется на 0
            i++;
        }
        name_film[i]=0;

        //Это для перехода новую строку
        fscanf(films_storage, "%d", &year_issue);

        fgets(null, 3, films_storage);           //Переход на новую строку, тк после fscanf этого не делает


        fgets(country, 50, films_storage);
        i =0;
        while(country[i] != '\n'){                       //Символ переход на новую строку заменяется на 0
            i++;
        }
        country[i]=0;

        fgets(genres, 50, films_storage);
        i =0;
        while(genres[i] != '\n'){                     //Символ переход на новую строку заменяется на 0
            i++;
        }
        genres[i]=0;

        fscanf(films_storage, "%f", &rating);   //Переходим на новую строку

        fgets(null, 3, films_storage);

        film_read = create_film(name_film, year_issue, country, genres, rating);   //Занесение значения в структуру
        adding_end(list_root, film_read);                              //Добавление к root новых элементов
    }
    deletion_start(list_root);                                                     //Удаление нулевого элемента

    list_root->previous = film_read;                                               //Предыдущий у первого равен последнему
    film_read->next=list_root;                                                     //Следующий у последнего равен первому
}

//Добавление элемента в конец
void adding_end(struct  film* list_root, struct  film* added_element){
    struct film* current = list_root;
    while(current->next != NULL){
        current = current -> next;
    }
    current->next = added_element;      //Добавление указания к последующему элементу
    added_element->previous = current;  //Добавление указания на предыдущий
}

//Удаление первого элемента
void deletion_start(struct film* list_root){
    //Заношу все из второго в первый
    list_root->year_issue = list_root->next->year_issue;
    list_root->rating = list_root->next->rating;
    for(int i = 0; i <50; i++){
        list_root->name[i] = list_root->next->name[i];
        list_root->genres[i]= list_root->next->genres[i];
        list_root->country[i] = list_root->next->country[i];
    }


    //Следующий и предыдущий у первого меняю на следующий и предыдущий у второго
    list_root->next = list_root->next->next;
    //Предыдущий у следующего равен нынешнему
    list_root->next->previous = list_root;
}



