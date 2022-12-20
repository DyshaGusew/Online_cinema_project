#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include "move_functions.h"


int main() {
    //�����������
    setlocale(LC_ALL, "Russian");

    //�������� �������� �� ���� �������
    FILE *films_storage = fopen("films.txt", "r");
    struct film* root_film_catalog;     //��������� ������� ��������
    root_film_catalog = create_film("Null", 0, "NULL", "NULL", 0.0f);
    create_list_films(films_storage, root_film_catalog);

    //������ ��� �������� ������ ���
    system( "cls" );                 //������� �������
    out_list_films(root_film_catalog);


    //������� ���� �������������� � ���������� � ����
    int flag_line_card = 1;       //�����, ������������� � ����� �� ������ �����
    int flag_menu = 0;
    while(1){
        //���������� ���������� �������
        char sim = getch();

        //����������� ������(��� �������������� ����� ��������� ������ ���� �� �� � ����)
        if(sim == 'd' & flag_menu == 0){          //������� ������� � ������� ���, ����� � �������� ������ �������, ���������� root
            system( "cls" );
            flag_line_card = 1;
            out_list_films(root_film_catalog->next);
            root_film_catalog = root_film_catalog->next;

        }

        //����������� �����
        if(sim == 'a' & flag_menu == 0){    //������� ������� � ������� ���, ����� � �������� ����� �������, ���������� root
            system( "cls" );
            flag_line_card = 1;
            out_list_films(root_film_catalog->previous);
            root_film_catalog = root_film_catalog->previous;
        }

        //����� ��������� ����������
        if(sim == 's' & flag_line_card == 1 & flag_menu == 0){ //�������� �� ������� ������� ��������� ����������(���� ��� ��� ������������, �� 2 ��� �� ����) + ��������, ��� �� �� � ����
            flag_line_card = 0;     //��� �� � �����
            out_detailed_films(root_film_catalog);
        }



        //���� ������������ �� � ���� (�.�. � ��������� ���������� ��� ������ � ����� ��������), �� ����� �������� ����� � ���������
        if(sim == 'e' & flag_menu == 0){
            return_film_favorites(root_film_catalog);        //������ �������, ��������� �������� ������������� ������
            printf("                                               ����� �������� � ���������");
            sleep(2);
            system( "cls" );

            if(flag_line_card == 1){           //� ����������� �� ���� � ����� �����, ��������� ������ ����� ��� ��������� ����������
                out_list_films(root_film_catalog);
            }
            else{
                out_list_films(root_film_catalog);
                out_detailed_films(root_film_catalog);
            }
        }



        //�������� ��������� ����������(������������ ��������� �� ��������� ��������� ����������)
        if(sim == 'w' & flag_line_card == 0 & flag_menu == 0){
            flag_line_card = 1;
            system( "cls" );
            out_list_films(root_film_catalog);
        }

        //�������� ����(������������ ��������� �� ����� ��������)
        else if(sim == 'w' & flag_line_card == 1){
            flag_line_card = 0;
            flag_menu = 1;
            system( "cls" );
            out_menu();
        }

        //������� ������, ���������� ����������� ����� ����
        if(sim == 'q'){
            break;
        }
    }



    fclose(films_storage);
    return 0;
}
