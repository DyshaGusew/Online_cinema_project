#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

//������ ����� � ���������� ��� ��������� ��������
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //������� ������ ��� ������� � �������� ��� ��������
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //��� ��������� ������
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//����� ������������ ������
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");
    struct film* current = list_root;   //����������, �������� ����� �������� ��������(��� ������ - �������) ��� ������������ �� ���� ���������
    char n = (char)191;

    //27 �������� �� ������ �����
    printf("                                      ");                              printf("%c=====================================?\n");
    printf("                                      ");                              printf("||                                     ||\n");
    printf("%c��������������--------�����������?   ", n);                           printf("||                                     ||   ");                        printf("%c�����--------��������������������?\n", n);
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 |\n");
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 |\n");
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 |\n");
    out_str_center(list_root->previous->name, 33);printf("   |");out_str_center(list_root->name, 37);      printf("|   ");      out_str_center(list_root->next->name, 33);printf("\n");
    out_str_center(list_root->previous->genres, 33);printf("   |");out_str_center(list_root->genres, 37);      printf("|   ");      out_str_center(list_root->next->genres, 33);printf("\n");
    printf("|           ������� %.1f           |   ", list_root->previous->rating); printf("||             ������� %.1f             ||   ", list_root->rating);    printf("|           ������� %.1f           | \n", list_root->next->rating);
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 | \n");
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 | \n");
    printf("|                                 |   ");                               printf("||                                     ||   ");                        printf("|                                 | \n");
    printf("?��������������������������-------?   ");                               printf("||                                     ||   ");                        printf("?����������������������---------��? \n");
    printf("                                      ");                               printf("||                                     ||\n");
    printf("                                      ");                                printf("%c=====================================?\n");
}

void out_str_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //���������� ���������� ��������
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

    printf("%s", string);   //��������

    while(space_right!=0){    //������ �����
        printf(" ");
        space_right--;
    }


    if((leight_str-i)%2 != 0 ){          //�������� �� ��������� ��������������
        printf(" |");
    }
    else{
        printf("|");
    }

};

//�������� ����������� ��������� ������ �������(�������)
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //������� �����(���������� �� ������� ������ �� ������)

    //���������� �������� ��������� �������
    char null[3];                //���������� ��� �������� �� ����� ������
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //���������� ����
    //������������ � �������� �������� ������ � ��������, � ���� �� ��� ������, ����� ���, ������ �� �����
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //�������� ��������� �������
            i++;
        }
        name_film[i]=0;
        //�������� ��� ��������� �������
        fscanf(films_storage, "%d", &year_issue);
        fgets(null, 3, films_storage);           //������� �� ����� ������, �� ����� fscanf �� �����������(�������)


        fgets(country, 50, films_storage);
        i =0;
        while(country[i] != '\n'){                      //�������� ��������� �������
            i++;
        }
        country[i]=0;

        fgets(genres, 50, films_storage);
        i =0;
        while(genres[i] != '\n'){       //�������� ��������� �������
            i++;
        }
        genres[i]=0;


        fgets(null, 3, films_storage);

        fscanf(films_storage, "%f", &rating);
        fgets(null, 3, films_storage);

        film_read = create_film(name_film, year_issue, country, genres, rating);   //������ �����
        adding_end(list_root, film_read);                              //�������� � ������
    }
    deletion_start(list_root);                                                     //������ ��������� ������� root

    list_root->previous = film_read;                                               //� ������� �������� ������ ����������(���������)
    film_read->next=list_root;                                                     //� � ���������� �����������(������)
}

//���������� �������� � �����
void adding_end(struct  film* list_root, struct  film* added_element){
    struct film* current = list_root;
    while(current->next != NULL){
        current = current -> next;
    }
    current->next = added_element;      //���������� � ����������
    added_element->previous = current;  //�������� � ���������� �������� ����������
}

//�������� ������� ��������
void deletion_start(struct film* list_root){
    //������� ��� �������� ������� �������� � ������
    list_root->year_issue = list_root->next->year_issue;
    list_root->rating = list_root->next->rating;
    for(int i = 0; i <50; i++){
        list_root->name[i] = list_root->next->name[i];       //�.� char, �� ������� ������ �������
        list_root->genres[i]= list_root->next->genres[i];
        list_root->country[i] = list_root->next->country[i];
    }


    //������ ������ �������, ��� ��� ��� ��� ������ ��������� � list root
    free(list_root->next);

    //������ ������ ������� �������� ������
    //��� ����������� ������� ����� 3 ������� ���� ����
    list_root->next = list_root->next->next;
    list_root->next->previous = list_root->next;
}


