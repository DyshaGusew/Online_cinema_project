#ifndef MOVE_MOVE_FUNCTIONS_H
#define MOVE_MOVE_FUNCTIONS_H
#include <stdio.h>
#include <locale.h>

//Структура элемента фильма
struct film{
    char name[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;
    struct film* next;
    struct film* previous;
};

struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating);

void create_list_films(FILE *films_storage, struct film* list_root);

void adding_end(struct  film* list_root, struct  film* added_element);

void  deletion_start(struct film* list_root);



void out_list_films(struct film* list_root);

void out_detailed_films(struct film* list_root);


void out_str_center(char string[], int leight_str);

void out_str_genres_center(char string[], int leight_str);

void out_str_country_center(char string[], int leight_str);



void return_film_favorites(struct film* film_favorites);


void out_menu();


#endif
