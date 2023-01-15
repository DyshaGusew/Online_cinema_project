#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <locale.h>
//#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include "move_functions.h"

int main(){
    //Локализация
    setlocale(LC_ALL, "Russian");

    //Создание каталога из всех фильмов
    FILE *films_storage = fopen("films.txt", "r");

    struct film* root_film_catalog;     //Начальный элемент каталога
    root_film_catalog = create_film("Null", 0, "NULL", "NULL", 0.0f);
    create_list_films(films_storage, root_film_catalog);

    fclose(films_storage);

    //Вывожу три карточки первый раз
    system( "cls" );                 //Очистка консоли
    out_list_films(root_film_catalog);

    //Флаг полного выхода из программы
    int flag_out_program = 0;

    //Флаги, отслеживающие в каком мы сейчас блоке
    int flag_line_card = 1;
    int flag_info = 0;

    //Главный цикл взаимодействия с карточками и меню
    while(flag_out_program == 0){
        //Считывание введенного символа
        char sim = getch();

        //Перемещение вправо(все взаимодействия могут проходить только если мы не в меню)
        if(sim == 'd'){          //Очищаем консоль и выводим все, когда в середине правый элемент, перемещаем root
            system( "cls" );
            flag_line_card = 1;                 //Всегда указываем в каком мы блоке
            root_film_catalog = root_film_catalog->next;      //Делаем начальным элементом правый
            out_list_films(root_film_catalog);        //Выводим триплет
        }

        //Перемещение влево
        if(sim == 'a'){    //Очищаем консоль и выводим все, когда в середине левый элемент, перемещаем root
            system( "cls" );
            flag_line_card = 1;
            root_film_catalog = root_film_catalog->previous;
            out_list_films(root_film_catalog);
        }

        //Вывод подробной информации
        if(sim == 's' & flag_line_card == 1){ //Проверка на текущее наличие подробной информации(если она уже показывается, то 2 раз не надо)
            flag_line_card = 0;     //Уже не в линии, а в блоке информации о фильме
            flag_info = 1;
            out_detailed_films(root_film_catalog);           //Функция вывода подробной информации
        }

        //Если пользователь не в меню (т.е. в подробной информации или просто в линии карточек), он может добавить фильм в избранное
        if(sim == 'e'){
          //return_film_favorites(root_film_catalog);        //Функция, принимает значение возвращаемого фильма

            //Добавляю надпись и потом ее убираю
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


        //Открытие меню(пользователь находится на линии карточек)
        if(sim == 'w' & flag_line_card == 1){
            //Функция одновременно выполняет что-либо и выдает значение
            flag_out_program = out_menu(root_film_catalog);
        }

        //Закрытие подробной информации(пользователь находится на просмотре подробной информации)
        else if(sim == 'w' & flag_info == 1){
            flag_line_card = 1;
            flag_info = 0;
            system( "cls" );
            out_list_films(root_film_catalog);
        }
    }

    //registration();
    return 0;
}
