#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include "move_functions.h"


int main() {
    //Локализация
    setlocale(LC_ALL, "Russian");

    //Создание каталога из всех фильмов
    FILE *films_storage = fopen("films.txt", "r");
    struct film* root_film_catalog;     //Начальный элемент каталога
    root_film_catalog = create_film("Null", 0, "NULL", "NULL", 0.0f);
    create_list_films(films_storage, root_film_catalog);

    //Вывожу три карточки первый раз
    system( "cls" );                 //Очистка консоли
    out_list_films(root_film_catalog);


    //Главный цикл взаимодействия с карточками и меню
    int flag_line_card = 1;       //Флаги, отслеживающие в каком мы сейчас блоке
    int flag_menu = 0;
    while(1){
        //Считывание введенного символа
        char sim = getch();

        //Перемещение вправо(все взаимодействия могут проходить только если мы не в меню)
        if(sim == 'd' & flag_menu == 0){          //Очищаем консоль и выводим все, когда в середине правый элемент, перемещаем root
            system( "cls" );
            flag_line_card = 1;
            out_list_films(root_film_catalog->next);
            root_film_catalog = root_film_catalog->next;

        }

        //Перемещение влево
        if(sim == 'a' & flag_menu == 0){    //Очищаем консоль и выводим все, когда в середине левый элемент, перемещаем root
            system( "cls" );
            flag_line_card = 1;
            out_list_films(root_film_catalog->previous);
            root_film_catalog = root_film_catalog->previous;
        }

        //Вывод подробной информации
        if(sim == 's' & flag_line_card == 1 & flag_menu == 0){ //Проверка на текущее наличие подробной информации(если она уже показывается, то 2 раз не надо) + проверка, что мы не в меню
            flag_line_card = 0;     //Уже не в линии
            out_detailed_films(root_film_catalog);
        }



        //Если пользователь не в меню (т.е. в подробной информации или просто в линии карточек), он может добавить фильм в избранное
        if(sim == 'e' & flag_menu == 0){
            return_film_favorites(root_film_catalog);        //Пустая функция, принимает значение возвращаемого фильма
            printf("                                               Фильм добавлен в избранное");
            sleep(2);
            system( "cls" );

            if(flag_line_card == 1){           //В зависимости от того в каком блоке, выводится только линия или подробная информация
                out_list_films(root_film_catalog);
            }
            else{
                out_list_films(root_film_catalog);
                out_detailed_films(root_film_catalog);
            }
        }



        //Закрытие подробной информации(пользователь находится на просмотре подробной информации)
        if(sim == 'w' & flag_line_card == 0 & flag_menu == 0){
            flag_line_card = 1;
            system( "cls" );
            out_list_films(root_film_catalog);
        }

        //Открытие меню(пользователь находится на линии карточек)
        else if(sim == 'w' & flag_line_card == 1){
            flag_line_card = 0;
            flag_menu = 1;
            system( "cls" );
            out_menu();
        }

        //Условие выхода, желательно реализовать через меню
        if(sim == 'q'){
            break;
        }
    }



    fclose(films_storage);
    return 0;
}
