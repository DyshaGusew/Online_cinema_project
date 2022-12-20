#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

//Создаю фильм и присваиваю ему указанные значения
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //Выделил память под элемент и присвоил ему значение
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //Все параметры фильма
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//Вывод бесконечного списка
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");
    struct film* current = list_root;   //Переменная, хранящая адрес текущего элемента(для начала - первого) она перемещается по всем элементам

    //27 символов не считая полей
    printf("                                        ");                              printf("//===================================\\");printf("\\ \n");
    printf("                                        ");                              printf("||                                   ||\n");
    printf("/––––––––––––––--------–––––--–-––––\\   ");                              printf("||                                   ||   ");                        printf("/–––––----------––––––––––––––––––––\\\n");
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
    printf("\\––––––––––––––––––––––––––---------/   ");                              printf("||                                   ||   ");                        printf("\\––––––––––––––––––––––-----------––/\n");
    printf("                                        ");                               printf("||                                   ||\n");
    printf("                                        ");     printf("\\");      printf("\\===================================//\n");
}

void out_str_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Считывание количества символов
        i++;
    }

    int space = (leight_str-i)/2;
    int space_left = space;
    int space_right = space;

    printf("|");
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("%s", string);   //Середина

    while(space_right!=0){    //Правая часть
        printf(" ");
        space_right--;
    }


    if((leight_str-i)%2 != 0 ){          //Проверка на идеальную серединчатость
        printf(" |");
    }
    else{
        printf("|");
    }

};

//Создание двусвязного кругового списка фильмов(каталог)
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //Текущий фильм(проходится по каждому фильму из списка)

    //Переменные хранящие параметры фильмов
    char null[3];                //Переменная для перехода на новую строку
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //Гениальная вещь
    //Одновременно и считываю название фильма и проверяю, а есть ли оно вообще, когда нет, выхожу из цикла
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //Удаление ненужного символа
            i++;
        }
        name_film[i]=0;
        //Считываю все параметры фильмов
        fscanf(films_storage, "%d", &year_issue);
        fgets(null, 3, films_storage);           //Переход на новую строку, тк после fscanf не переносится(костыль)


        fgets(country, 50, films_storage);
        i =0;
        while(country[i] != '\n'){                      //Удаление ненужного символа
            i++;
        }
        country[i]=0;

        fgets(genres, 50, films_storage);
        i =0;
        while(genres[i] != '\n'){       //Удаление ненужного символа
            i++;
        }
        genres[i]=0;


        fgets(null, 3, films_storage);

        fscanf(films_storage, "%f", &rating);
        fgets(null, 3, films_storage);

        film_read = create_film(name_film, year_issue, country, genres, rating);   //Создаю фильм
        adding_end(list_root, film_read);                              //Добавляю в список
    }
    deletion_start(list_root);                                                     //Удаляю начальный нулевой root

    list_root->previous = film_read;                                               //У первого элемента создаю предыдущий(последний)
    film_read->next=list_root;                                                     //А у последнего последующий(первый)
}

//Добавление элемента в конец
void adding_end(struct  film* list_root, struct  film* added_element){
    struct film* current = list_root;
    while(current->next != NULL){
        current = current -> next;
    }
    current->next = added_element;      //Добавление к последнему
    added_element->previous = current;  //Сохраняю у последнего элемента предыдущий
}

//Удаление первого элемента
void deletion_start(struct film* list_root){
    //Передал все значения второго элемента в первый
    list_root->year_issue = list_root->next->year_issue;
    list_root->rating = list_root->next->rating;
    for(int i = 0; i <50; i++){
        list_root->name[i] = list_root->next->name[i];       //Т.к char, то заменяю каждый элемент
        list_root->genres[i]= list_root->next->genres[i];
        list_root->country[i] = list_root->next->country[i];
    }


    //Теперь второй элемент замещает первый
    //Его последующий элемент равен 3 старого лист рута
    list_root->next = list_root->next->next;
    list_root->next->previous = list_root->previous;
}



