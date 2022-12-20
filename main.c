#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include "move_functions.h"


int main() {

    //Локализация
    setlocale(LC_ALL, "Russian");
    //Считывание всех фильмов кинотеатра
    FILE *films_storage = fopen("films.txt", "r");

    //Создание каталога из всех фильмов
    struct film* root_film_catalog;
    root_film_catalog = create_film("Null", 0, "NULL", "NULL", 0.0f);
    create_list_films(films_storage, root_film_catalog);

    out_list_films(root_film_catalog);

    //Потом необходимо добавсить условие выхода
    while(1){
        char sim = getch();
        if(sim == 'd'){
            system( "cls" );
            out_list_films(root_film_catalog->next);
            root_film_catalog = root_film_catalog->next;
        }
        if(sim == 'a'){
            system( "cls" );
            out_list_films(root_film_catalog->previous);
            root_film_catalog = root_film_catalog->previous;
        }
    }



    fclose(films_storage);
    return 0;
}
