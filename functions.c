#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>


//Технические функции для создания списка
//Создание структуры фильма из входных значений
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //Выделение памяти для фильма
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //Занесение значений в структуру фильма
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);  //Так надо для строк
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//Создание списка фильмов
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //Считываемый фильм

    //Переменные для считывания
    char null[3];
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //Считываю значения с файла и ввожу в структуру фильма.
    //Одновременно и считываю и проверяю, а есть ли что считывать
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //Символ перехода на новую строку заменяется на 0
            i++;
        }
        name_film[i]=0;

        //Это для считывания года выпуска
        fscanf(films_storage, "%d", &year_issue);
        fgets(null, 3, films_storage);           //Переход на новую строку, тк fscanf этого не делает


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
    deletion_start(list_root);                                                     //Удаление нулевого(начального) элемента

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

//-------------------------------------------------------------------

//Функции вывода карточек и избранного
//Вывод триплета карточек фильмов
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");

    //О боже, сложно понять, но попробуйте
    printf("                                                         Меню");
    printf("                                                                                                                      %c\n", (char)24);
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
    printf("                                            Добавить фильм в избранное - 'e'\n");
    printf("                                                           %c\n", (char)25);
    printf("                                                  Подробная информация\n");


}

//Вывод подробной информации о фильме
void out_detailed_films(struct film* list_root){
    printf("                              /---------------------------------------------------------\\\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              ");out_str_center(list_root->name, 57); printf("\n");
    printf("                              |                                                         |\n");
    printf("                              |                       Рейтинг %.1f                       |\n", list_root->rating);
    printf("                              ");out_str_genres_center(list_root->genres, 57);printf("\n");
    printf("                              ");out_str_country_center(list_root->country, 57);printf("\n");
    printf("                              |                    Год выпуска: %d                    |\n", list_root->year_issue);
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              \\---------------------------------------------------------/\n");

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

//Вывод строки жанра в середине указанного диапазона
void out_str_genres_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Подсчет символов
        i++;
    }

    //-6 тк надпись "жанр: " занимает 6 символов
    int space = (leight_str-i-6)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Левая часть
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("Жанр: %s", string);   //Центр

    while(space_right!=0){    //Правая часть
        printf(" ");
        space_right--;
    }


    if((leight_str-i-6)%2 != 0 ){          //Проверка на нечетность строки и сдвиг по необходимости
        printf(" |");
    }
    else{
        printf("|");
    }

};

//Вывод строки страны в середине указанного диапазона
void out_str_country_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Подсчет символов
        i++;
    }

    //-19 тк надпись "Страна(ы) выпуска: " занимает 19 символов
    int space = (leight_str-i-19)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Левая часть
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("Страна(ы) выпуска: %s", string);   //Центр

    while(space_right!=0){    //Правая часть
        printf(" ");
        space_right--;
    }


    if((leight_str-i-19)%2 != 0 ){          //Проверка на нечетность строки и сдвиг по необходимости
        printf(" |");
    }
    else{
        printf("|");
    }

};

//---------------------------------------------------------------

//Функции избранного

//Функции избранного
//void return_film_favorites(struct film* film_favorites, struct user* current_user){
//    //printf("Избранный фильм - %s\n", film_favorites->name);
//    struct film* new_film = malloc(sizeof(struct film));
//    *new_film = *film_favorites;
//    if (current_user->favorites != NULL){
//        new_film->next = current_user->favorites->next;
//        new_film->next->previous = new_film;
//        new_film->previous = current_user->favorites;
//        current_user->favorites->next = new_film;
//    }
//    else {
//        new_film->next = new_film;
//        new_film->previous = new_film;
//    }
//    current_user->favorites = new_film;
//}
//
//void deletion_favorites(struct user* current_user, char film_name[50]){
//    struct film* current_film = current_user->favorites;
//    if (current_film == NULL){
//        return;
//    }
//    if (strcmp(current_film->name, film_name) == 0){
//        if(current_film == current_film->next){
//            current_user->favorites = NULL;
//            free(current_film);
//            return;
//        }
//        current_user->favorites = current_film->next;
//        current_film->previous->next = current_film->next;
//        current_film->next->previous = current_film->previous;
//        free(current_film);
//        return;
//    }
//    while (current_film->next != current_user->favorites){
//        current_film = current_film->next;
//        if (strcmp(current_film->name, film_name) == 0){
//            current_film->previous->next = current_film->next;
//            current_film->next->previous = current_film->previous;
//            free(current_film);
//            return;
//        }
//    }
//}

/*void save_favorites (struct user* current_user){
    FILE* favorites = fopen();

}*/




//--------------------------------------------------------------
//Функции Меню
int out_menu(struct film* list_root) {
    //Возвращаться к списку фильмов мы уже должны через меню можно опять использовать кнопки s и w, чтобы в нем взаимодействовать(просто через s вернуться нельзя, надо выбрать необходимый пункт меню)
    int flag_out_program = 0;
    char sim;

    //Режим принятый пользователем(команда)
    int mode = 0;
    //Выход из меню
    int flag_out = 0;

    out_str_menu(mode);
    while (flag_out == 0) {
        sim = getch();

        //Листание вниз
        if (sim == 's') {
            mode++;
            if (mode == 4) {
                mode = 0;
            }
            //Отображение состояния звездочки
            out_str_menu(mode);
        }

        //Листание вверх
        if (sim == 'w') {
            mode--;
            if (mode == -1) {
                mode = 3;
            }
            //Отображение состояния звездочки
            out_str_menu(mode);
        }

        //Команды меню
       if(sim == '\n' || sim == ' ') {
           if (mode == 0){
               system("cls");
               out_list_films(list_root);
               flag_out = 1;
           }

           else if (mode == 1) {
               system("cls");
               flag_out = 1;
               printf("---------Функция списка избранного---------\n");

           } else if (mode == 2) {
               system("cls");
               flag_out = 1;
               printf("---------Функция личного кабинета---------\n");
           }

           else if (mode == 3) {
               flag_out_program = 1;
           }
           return flag_out_program;
       }
    }

}

//Вывод разных положений указателя в меню
void out_str_menu(int mode) {
        if (mode == 0) {
            printf("                                                            Меню\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||    Вернуться к каталогу фильмов *      ||\n");
            printf("                                        ");   printf("||      Посмотреть список избранного      ||\n");
            printf("                                        ");   printf("||         Открыть личный кабинет         ||\n");
            printf("                                        ");   printf("||           Выйти из программы           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 1) {
            printf("                                                            Меню\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Вернуться к каталогу фильмов      ||\n");
            printf("                                        ");   printf("||    Посмотреть список избранного *      ||\n");
            printf("                                        ");   printf("||         Открыть личный кабинет         ||\n");
            printf("                                        ");   printf("||           Выйти из программы           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 2) {
            printf("                                                            Меню\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Вернуться к каталогу фильмов      ||\n");
            printf("                                        ");   printf("||      Посмотреть список избранного      ||\n");
            printf("                                        ");   printf("||       Открыть личный кабинет *         ||\n");
            printf("                                        ");   printf("||           Выйти из программы           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        } else if (mode == 3) {
            printf("                                                            Меню\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Вернуться к каталогу фильмов      ||\n");
            printf("                                        ");   printf("||      Посмотреть список избранного      ||\n");
            printf("                                        ");   printf("||         Открыть личный кабинет         ||\n");
            printf("                                        ");   printf("||        Выйти из программы *            ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        }
    }

