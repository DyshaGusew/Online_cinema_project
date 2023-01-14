#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>


//����������� ������� ��� �������� ������
//�������� ��������� ������ �� ������� ��������
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //��������� ������ ��� ������
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //��������� �������� � ��������� ������
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);  //��� ���� ��� �����
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//�������� ������ �������
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //����������� �����

    //���������� ��� ����������
    char null[3];
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //�������� �������� � ����� � ����� � ��������� ������.
    //������������ � �������� � ��������, � ���� �� ��� ���������
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //������ �������� �� ����� ������ ���������� �� 0
            i++;
        }
        name_film[i]=0;

        //��� ��� ���������� ���� �������
        fscanf(films_storage, "%d", &year_issue);
        fgets(null, 3, films_storage);           //������� �� ����� ������, �� fscanf ����� �� ������


        fgets(country, 50, films_storage);
        i =0;
        while(country[i] != '\n'){                       //������ ������� �� ����� ������ ���������� �� 0
            i++;
        }
        country[i]=0;

        fgets(genres, 50, films_storage);
        i =0;
        while(genres[i] != '\n'){                     //������ ������� �� ����� ������ ���������� �� 0
            i++;
        }
        genres[i]=0;

        fscanf(films_storage, "%f", &rating);   //��������� �� ����� ������

        fgets(null, 3, films_storage);

        film_read = create_film(name_film, year_issue, country, genres, rating);   //��������� �������� � ���������
        adding_end(list_root, film_read);                              //���������� � root ����� ���������
    }
    deletion_start(list_root);                                                     //�������� ��������(����������) ��������

    list_root->previous = film_read;                                               //���������� � ������� ����� ����������
    film_read->next=list_root;                                                     //��������� � ���������� ����� �������
}

//���������� �������� � �����
void adding_end(struct  film* list_root, struct  film* added_element){
    struct film* current = list_root;
    while(current->next != NULL){
        current = current -> next;
    }
    current->next = added_element;      //���������� �������� � ������������ ��������
    added_element->previous = current;  //���������� �������� �� ����������
}

//�������� ������� ��������
void deletion_start(struct film* list_root){
    //������ ��� �� ������� � ������
    list_root->year_issue = list_root->next->year_issue;
    list_root->rating = list_root->next->rating;
    for(int i = 0; i <50; i++){
        list_root->name[i] = list_root->next->name[i];
        list_root->genres[i]= list_root->next->genres[i];
        list_root->country[i] = list_root->next->country[i];
    }


    //��������� � ���������� � ������� ����� �� ��������� � ���������� � �������
    list_root->next = list_root->next->next;
    //���������� � ���������� ����� ���������
    list_root->next->previous = list_root;
}

//-------------------------------------------------------------------

//������� ������ �������� � ����������
//����� �������� �������� �������
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");

    //� ����, ������ ������, �� ����������
    printf("                                                         ����");
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
    printf("|            ������� %.1f            |   ", list_root->previous->rating); printf("||            ������� %.1f            ||   ", list_root->rating);    printf("|            ������� %.1f            |\n", list_root->next->rating);
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("\\-----------------------------------/   ");                               printf("||                                   ||   ");                        printf("\\-----------------------------------/\n");
    printf("                                        ");                               printf("||                                   ||\n");
    printf("                                        ");     printf("\\");      printf("\\===================================//\n");
    printf("                                            �������� ����� � ��������� - 'e'\n");
    printf("                                                           %c\n", (char)25);
    printf("                                                  ��������� ����������\n");


}

//����� ��������� ���������� � ������
void out_detailed_films(struct film* list_root){
    printf("                              /---------------------------------------------------------\\\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              ");out_str_center(list_root->name, 57); printf("\n");
    printf("                              |                                                         |\n");
    printf("                              |                       ������� %.1f                       |\n", list_root->rating);
    printf("                              ");out_str_genres_center(list_root->genres, 57);printf("\n");
    printf("                              ");out_str_country_center(list_root->country, 57);printf("\n");
    printf("                              |                    ��� �������: %d                    |\n", list_root->year_issue);
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              \\---------------------------------------------------------/\n");

}


//����� ������ � �������� ���������� ���������
void out_str_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //������� ��������
        i++;
    }

    int space = (leight_str-i)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //����� �����
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("%s", string);   //�����

    while(space_right!=0){    //������ �����
        printf(" ");
        space_right--;
    }


    if((leight_str-i)%2 != 0 ){          //�������� �� ���������� ������ � ����� �� �������������
        printf(" |");
    }
    else{
        printf("|");
    }

};

//����� ������ ����� � �������� ���������� ���������
void out_str_genres_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //������� ��������
        i++;
    }

    //-6 �� ������� "����: " �������� 6 ��������
    int space = (leight_str-i-6)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //����� �����
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("����: %s", string);   //�����

    while(space_right!=0){    //������ �����
        printf(" ");
        space_right--;
    }


    if((leight_str-i-6)%2 != 0 ){          //�������� �� ���������� ������ � ����� �� �������������
        printf(" |");
    }
    else{
        printf("|");
    }

};

//����� ������ ������ � �������� ���������� ���������
void out_str_country_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //������� ��������
        i++;
    }

    //-19 �� ������� "������(�) �������: " �������� 19 ��������
    int space = (leight_str-i-19)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //����� �����
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("������(�) �������: %s", string);   //�����

    while(space_right!=0){    //������ �����
        printf(" ");
        space_right--;
    }


    if((leight_str-i-19)%2 != 0 ){          //�������� �� ���������� ������ � ����� �� �������������
        printf(" |");
    }
    else{
        printf("|");
    }

};

//---------------------------------------------------------------

//������� ����������

//������� ����������
//void return_film_favorites(struct film* film_favorites, struct user* current_user){
//    //printf("��������� ����� - %s\n", film_favorites->name);
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
//������� ����
int out_menu(struct film* list_root) {
    //������������ � ������ ������� �� ��� ������ ����� ���� ����� ����� ������������ ������ s � w, ����� � ��� �����������������(������ ����� s ��������� ������, ���� ������� ����������� ����� ����)
    int flag_out_program = 0;
    char sim;

    //����� �������� �������������(�������)
    int mode = 0;
    //����� �� ����
    int flag_out = 0;

    out_str_menu(mode);
    while (flag_out == 0) {
        sim = getch();

        //�������� ����
        if (sim == 's') {
            mode++;
            if (mode == 4) {
                mode = 0;
            }
            //����������� ��������� ���������
            out_str_menu(mode);
        }

        //�������� �����
        if (sim == 'w') {
            mode--;
            if (mode == -1) {
                mode = 3;
            }
            //����������� ��������� ���������
            out_str_menu(mode);
        }

        //������� ����
       if(sim == '\n' || sim == ' ') {
           if (mode == 0){
               system("cls");
               out_list_films(list_root);
               flag_out = 1;
           }

           else if (mode == 1) {
               system("cls");
               flag_out = 1;
               printf("---------������� ������ ����������---------\n");

           } else if (mode == 2) {
               system("cls");
               flag_out = 1;
               printf("---------������� ������� ��������---------\n");
           }

           else if (mode == 3) {
               flag_out_program = 1;
           }
           return flag_out_program;
       }
    }

}

//����� ������ ��������� ��������� � ����
void out_str_menu(int mode) {
        if (mode == 0) {
            printf("                                                            ����\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||    ��������� � �������� ������� *      ||\n");
            printf("                                        ");   printf("||      ���������� ������ ����������      ||\n");
            printf("                                        ");   printf("||         ������� ������ �������         ||\n");
            printf("                                        ");   printf("||           ����� �� ���������           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 1) {
            printf("                                                            ����\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      ��������� � �������� �������      ||\n");
            printf("                                        ");   printf("||    ���������� ������ ���������� *      ||\n");
            printf("                                        ");   printf("||         ������� ������ �������         ||\n");
            printf("                                        ");   printf("||           ����� �� ���������           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 2) {
            printf("                                                            ����\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      ��������� � �������� �������      ||\n");
            printf("                                        ");   printf("||      ���������� ������ ����������      ||\n");
            printf("                                        ");   printf("||       ������� ������ ������� *         ||\n");
            printf("                                        ");   printf("||           ����� �� ���������           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        } else if (mode == 3) {
            printf("                                                            ����\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      ��������� � �������� �������      ||\n");
            printf("                                        ");   printf("||      ���������� ������ ����������      ||\n");
            printf("                                        ");   printf("||         ������� ������ �������         ||\n");
            printf("                                        ");   printf("||        ����� �� ��������� *            ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        }
    }

