#include "move_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

void registration(){
    char d[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    char p[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    char n[] = {1,2,3,4,5,6,7,8,9,0};
    int tmp = 0;
    user user;
    FILE *users_info = fopen("users_info.txt", "w");
    while (tmp == 0) {
    printf("Введите логин(от 3 до 20 символов латинского алфавита): ");
    scanf("%s", user.login);
    for(int i = 0; i < strlen(user.login); i++)
    {
        tmp = 0;
        for(int j = 0; j < 52; j++)
        {
            if(user.login[i] == d[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0) {
        printf("Вы ввели неправильные символы\n");
        break;
      }
    }
    }
    fprintf(users_info, "%s\n", user.login);
  tmp = 0;
  while (tmp == 0) {
    printf("Введите пароль(от 6 до 20 символов): ");
    scanf("%s", user.password);
    for(int i = 0; i < strlen(user.password); i++)
    {
        tmp = 0;
        for(int j = 0; j < 62; j++)
        {
            if(user.password[i] == p[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0) {
        printf("Вы ввели неправильные символы\n");
        break;
      }
    }
  }
  fprintf(users_info, "%s\n", user.password);
  tmp = 0;
  /*while (tmp == 0) {
    printf("Введите номер карты (16 символов): ");
    scanf("%s", user.card_number);
    for(int i = 0; i < 15; i++)
    {
        tmp = 0;
        for(int j = 0; j < 9; j++)
        {
            if(user.card_number[i] == n[j]) 
            {
                tmp++;
            }
        }
      if (tmp == 0 || strlen(user.card_number) != 16) {
        printf("Вы ввели неправильные символы или неправильное их количество\n");
        break;
      }
    }
    }*/
  printf("Введите номер карты (16 символов): ");
  scanf("%s", user.card_number);
  fprintf(users_info, "%s\n", user.card_number);
  }

//Òåõíè÷åñêèå ôóíêöèè äëÿ ñîçäàíèÿ ñïèñêà
//Ñîçäàíèå ñòðóêòóðû ôèëüìà èç âõîäíûõ çíà÷åíèé
struct film* create_film(char name_film[50], int year_issue, char country[50], char genres[50], float rating){
    //Âûäåëåíèå ïàìÿòè äëÿ ôèëüìà
    struct film* film = (struct film*) malloc(sizeof(struct film));

    //Çàíåñåíèå çíà÷åíèé â ñòðóêòóðó ôèëüìà
    strcpy(film->name, name_film);
    film -> year_issue = year_issue;
    strcpy(film->country, country);  //Òàê íàäî äëÿ ñòðîê
    strcpy(film->genres, genres);
    film->rating = rating;
    film -> next = NULL;
    film -> previous = NULL;

    return film;
}

//Ñîçäàíèå ñïèñêà ôèëüìîâ
void create_list_films(FILE *films_storage, struct film *list_root) {
    struct film* film_read;      //Ñ÷èòûâàåìûé ôèëüì

    //Ïåðåìåííûå äëÿ ñ÷èòûâàíèÿ
    char null[3];
    char name_film[50];
    int year_issue;
    char country[50];
    char genres[50];
    float rating;

    //Ñ÷èòûâàþ çíà÷åíèÿ ñ ôàéëà è ââîæó â ñòðóêòóðó ôèëüìà.
    //Îäíîâðåìåííî è ñ÷èòûâàþ è ïðîâåðÿþ, à åñòü ëè ÷òî ñ÷èòûâàòü
    while(fgets(name_film, 50, films_storage) != NULL){
        int i = 0;
        while(name_film[i] != '\n'){                 //Ñèìâîë ïåðåõîäà íà íîâóþ ñòðîêó çàìåíÿåòñÿ íà 0
            i++;
        }
        name_film[i]=0;

        //Ýòî äëÿ ñ÷èòûâàíèÿ ãîäà âûïóñêà
        fscanf(films_storage, "%d", &year_issue);
        fgets(null, 3, films_storage);           //Ïåðåõîä íà íîâóþ ñòðîêó, òê fscanf ýòîãî íå äåëàåò


        fgets(country, 50, films_storage);
        i =0;
        while(country[i] != '\n'){                       //Ñèìâîë ïåðåõîä íà íîâóþ ñòðîêó çàìåíÿåòñÿ íà 0
            i++;
        }
        country[i]=0;

        fgets(genres, 50, films_storage);
        i =0;
        while(genres[i] != '\n'){                     //Ñèìâîë ïåðåõîä íà íîâóþ ñòðîêó çàìåíÿåòñÿ íà 0
            i++;
        }
        genres[i]=0;

        fscanf(films_storage, "%f", &rating);   //Ïåðåõîäèì íà íîâóþ ñòðîêó

        fgets(null, 3, films_storage);

        film_read = create_film(name_film, year_issue, country, genres, rating);   //Çàíåñåíèå çíà÷åíèÿ â ñòðóêòóðó
        adding_end(list_root, film_read);                              //Äîáàâëåíèå ê root íîâûõ ýëåìåíòîâ
    }
    deletion_start(list_root);                                                     //Óäàëåíèå íóëåâîãî(íà÷àëüíîãî) ýëåìåíòà

    list_root->previous = film_read;                                               //Ïðåäûäóùèé ó ïåðâîãî ðàâåí ïîñëåäíåìó
    film_read->next=list_root;                                                     //Ñëåäóþùèé ó ïîñëåäíåãî ðàâåí ïåðâîìó
}

//Äîáàâëåíèå ýëåìåíòà â êîíåö
void adding_end(struct  film* list_root, struct  film* added_element){
    struct film* current = list_root;
    while(current->next != NULL){
        current = current -> next;
    }
    current->next = added_element;      //Äîáàâëåíèå óêàçàíèÿ ê ïîñëåäóþùåìó ýëåìåíòó
    added_element->previous = current;  //Äîáàâëåíèå óêàçàíèÿ íà ïðåäûäóùèé
}

//Óäàëåíèå ïåðâîãî ýëåìåíòà
void deletion_start(struct film* list_root){
    //Çàíîøó âñå èç âòîðîãî â ïåðâûé
    list_root->year_issue = list_root->next->year_issue;
    list_root->rating = list_root->next->rating;
    for(int i = 0; i <50; i++){
        list_root->name[i] = list_root->next->name[i];
        list_root->genres[i]= list_root->next->genres[i];
        list_root->country[i] = list_root->next->country[i];
    }


    //Ñëåäóþùèé è ïðåäûäóùèé ó ïåðâîãî ìåíÿþ íà ñëåäóþùèé è ïðåäûäóùèé ó âòîðîãî
    list_root->next = list_root->next->next;
    //Ïðåäûäóùèé ó ñëåäóþùåãî ðàâåí íûíåøíåìó
    list_root->next->previous = list_root;
}

//-------------------------------------------------------------------

//Ôóíêöèè âûâîäà êàðòî÷åê è èçáðàííîãî
//Âûâîä òðèïëåòà êàðòî÷åê ôèëüìîâ
void out_list_films(struct film* list_root){
    setlocale(LC_ALL, "Russian");

    //Î áîæå, ñëîæíî ïîíÿòü, íî ïîïðîáóéòå
    printf("                                                         Ìåíþ");
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
    printf("|            Ðåéòèíã %.1f            |   ", list_root->previous->rating); printf("||            Ðåéòèíã %.1f            ||   ", list_root->rating);    printf("|            Ðåéòèíã %.1f            |\n", list_root->next->rating);
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("|                                   |   ");                               printf("||                                   ||   ");                        printf("|                                   |\n");
    printf("\\-----------------------------------/   ");                               printf("||                                   ||   ");                        printf("\\-----------------------------------/\n");
    printf("                                        ");                               printf("||                                   ||\n");
    printf("                                        ");     printf("\\");      printf("\\===================================//\n");
    printf("                                            Äîáàâèòü ôèëüì â èçáðàííîå - 'e'\n");
    printf("                                                           %c\n", (char)25);
    printf("                                                  Ïîäðîáíàÿ èíôîðìàöèÿ\n");


}

//Âûâîä ïîäðîáíîé èíôîðìàöèè î ôèëüìå
void out_detailed_films(struct film* list_root){
    printf("                              /---------------------------------------------------------\\\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              ");out_str_center(list_root->name, 57); printf("\n");
    printf("                              |                                                         |\n");
    printf("                              |                       Ðåéòèíã %.1f                       |\n", list_root->rating);
    printf("                              ");out_str_genres_center(list_root->genres, 57);printf("\n");
    printf("                              ");out_str_country_center(list_root->country, 57);printf("\n");
    printf("                              |                    Ãîä âûïóñêà: %d                    |\n", list_root->year_issue);
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              |                                                         |\n");
    printf("                              \\---------------------------------------------------------/\n");

}


//Âûâîä ñòðîêè â ñåðåäèíå óêàçàííîãî äèàïàçîíà
void out_str_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Ïîäñ÷åò ñèìâîëîâ
        i++;
    }

    int space = (leight_str-i)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Ëåâàÿ ÷àñòü
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("%s", string);   //Öåíòð

    while(space_right!=0){    //Ïðàâàÿ ÷àñòü
        printf(" ");
        space_right--;
    }


    if((leight_str-i)%2 != 0 ){          //Ïðîâåðêà íà íå÷åòíîñòü ñòðîêè è ñäâèã ïî íåîáõîäèìîñòè
        printf(" |");
    }
    else{
        printf("|");
    }

};

//Âûâîä ñòðîêè æàíðà â ñåðåäèíå óêàçàííîãî äèàïàçîíà
void out_str_genres_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Ïîäñ÷åò ñèìâîëîâ
        i++;
    }

    //-6 òê íàäïèñü "æàíð: " çàíèìàåò 6 ñèìâîëîâ
    int space = (leight_str-i-6)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Ëåâàÿ ÷àñòü
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("Æàíð: %s", string);   //Öåíòð

    while(space_right!=0){    //Ïðàâàÿ ÷àñòü
        printf(" ");
        space_right--;
    }


    if((leight_str-i-6)%2 != 0 ){          //Ïðîâåðêà íà íå÷åòíîñòü ñòðîêè è ñäâèã ïî íåîáõîäèìîñòè
        printf(" |");
    }
    else{
        printf("|");
    }

};

//Âûâîä ñòðîêè ñòðàíû â ñåðåäèíå óêàçàííîãî äèàïàçîíà
void out_str_country_center(char string[], int leight_str){
    int i = 0;
    while(string[i] != 0){                 //Ïîäñ÷åò ñèìâîëîâ
        i++;
    }

    //-19 òê íàäïèñü "Ñòðàíà(û) âûïóñêà: " çàíèìàåò 19 ñèìâîëîâ
    int space = (leight_str-i-19)/2;
    int space_left = space;
    int space_right = space;

    printf("|");  //Ëåâàÿ ÷àñòü
    while(space_left!=0){
        printf(" ");
        space_left--;
    }

    printf("Ñòðàíà(û) âûïóñêà: %s", string);   //Öåíòð

    while(space_right!=0){    //Ïðàâàÿ ÷àñòü
        printf(" ");
        space_right--;
    }


    if((leight_str-i-19)%2 != 0 ){          //Ïðîâåðêà íà íå÷åòíîñòü ñòðîêè è ñäâèã ïî íåîáõîäèìîñòè
        printf(" |");
    }
    else{
        printf("|");
    }

};

//---------------------------------------------------------------

//Ôóíêöèè èçáðàííîãî

//Ôóíêöèè èçáðàííîãî
//void return_film_favorites(struct film* film_favorites, struct user* current_user){
//    //printf("Èçáðàííûé ôèëüì - %s\n", film_favorites->name);
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
//Ôóíêöèè Ìåíþ
int out_menu(struct film* list_root) {
    //Âîçâðàùàòüñÿ ê ñïèñêó ôèëüìîâ ìû óæå äîëæíû ÷åðåç ìåíþ ìîæíî îïÿòü èñïîëüçîâàòü êíîïêè s è w, ÷òîáû â íåì âçàèìîäåéñòâîâàòü(ïðîñòî ÷åðåç s âåðíóòüñÿ íåëüçÿ, íàäî âûáðàòü íåîáõîäèìûé ïóíêò ìåíþ)
    int flag_out_program = 0;
    char sim;

    //Ðåæèì ïðèíÿòûé ïîëüçîâàòåëåì(êîìàíäà)
    int mode = 0;
    //Âûõîä èç ìåíþ
    int flag_out = 0;

    out_str_menu(mode);
    while (flag_out == 0) {
        sim = getch();

        //Ëèñòàíèå âíèç
        if (sim == 's') {
            mode++;
            if (mode == 4) {
                mode = 0;
            }
            //Îòîáðàæåíèå ñîñòîÿíèÿ çâåçäî÷êè
            out_str_menu(mode);
        }

        //Ëèñòàíèå ââåðõ
        if (sim == 'w') {
            mode--;
            if (mode == -1) {
                mode = 3;
            }
            //Îòîáðàæåíèå ñîñòîÿíèÿ çâåçäî÷êè
            out_str_menu(mode);
        }

        //Êîìàíäû ìåíþ
       if(sim == '\n' || sim == ' ') {
           if (mode == 0){
               system("cls");
               out_list_films(list_root);
               flag_out = 1;
           }

           else if (mode == 1) {
               system("cls");
               flag_out = 1;
               printf("---------Ôóíêöèÿ ñïèñêà èçáðàííîãî---------\n");

           } else if (mode == 2) {
               system("cls");
               flag_out = 1;
               printf("---------Ôóíêöèÿ ëè÷íîãî êàáèíåòà---------\n");
           }

           else if (mode == 3) {
               flag_out_program = 1;
           }
           return flag_out_program;
       }
    }

}

//Âûâîä ðàçíûõ ïîëîæåíèé óêàçàòåëÿ â ìåíþ
void out_str_menu(int mode) {
        if (mode == 0) {
            printf("                                                            Ìåíþ\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||    Âåðíóòüñÿ ê êàòàëîãó ôèëüìîâ *      ||\n");
            printf("                                        ");   printf("||      Ïîñìîòðåòü ñïèñîê èçáðàííîãî      ||\n");
            printf("                                        ");   printf("||         Îòêðûòü ëè÷íûé êàáèíåò         ||\n");
            printf("                                        ");   printf("||           Âûéòè èç ïðîãðàììû           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 1) {
            printf("                                                            Ìåíþ\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Âåðíóòüñÿ ê êàòàëîãó ôèëüìîâ      ||\n");
            printf("                                        ");   printf("||    Ïîñìîòðåòü ñïèñîê èçáðàííîãî *      ||\n");
            printf("                                        ");   printf("||         Îòêðûòü ëè÷íûé êàáèíåò         ||\n");
            printf("                                        ");   printf("||           Âûéòè èç ïðîãðàììû           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("\\");      printf("\\========================================//\n");
        } else if (mode == 2) {
            printf("                                                            Ìåíþ\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Âåðíóòüñÿ ê êàòàëîãó ôèëüìîâ      ||\n");
            printf("                                        ");   printf("||      Ïîñìîòðåòü ñïèñîê èçáðàííîãî      ||\n");
            printf("                                        ");   printf("||       Îòêðûòü ëè÷íûé êàáèíåò *         ||\n");
            printf("                                        ");   printf("||           Âûéòè èç ïðîãðàììû           ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        } else if (mode == 3) {
            printf("                                                            Ìåíþ\n");
            printf("                                        ");   printf("//========================================\\");printf("\\ \n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||                                        ||\n");
            printf("                                        ");   printf("||      Âåðíóòüñÿ ê êàòàëîãó ôèëüìîâ      ||\n");
            printf("                                        ");   printf("||      Ïîñìîòðåòü ñïèñîê èçáðàííîãî      ||\n");
            printf("                                        ");   printf("||         Îòêðûòü ëè÷íûé êàáèíåò         ||\n");
            printf("                                        ");   printf("||        Âûéòè èç ïðîãðàììû *            ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");                              printf("||                                        ||\n");
            printf("                                        ");     printf("\\");      printf("\\========================================//\n");
        }
    }
