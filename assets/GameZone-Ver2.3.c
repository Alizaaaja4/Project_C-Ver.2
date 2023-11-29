#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//general
void header();
void menu_devcus();
void menu_developer();
void menu_customer();
void dasbord_customer();

//developer
void developer_login();
void developer_addgame();
void developer_viewgame();
void developer_delategame();
void developer_searchgame();
void developer_viewfeedback();

//customer
void customer_registration();
void customer_login();
void view_profil();
void customer_feedback();
void customer_buygame();
void customer_stockMygame();


//method
void bubblesortGame();
void viewbubblesortGame();
void sequentialsearchGame();
void viewprofil_notbubble();
void bubblesort_game();
void tampilan_bubblesort_game();

//FILE
FILE *ListUserAccount;
FILE *ListUSerAccount_backup;

FILE *ListStockGame;
FILE *ListStockGame_backup;

FILE *ListStockGame_Bucket;

FILE *Feedbackgame;

//Developer
char username[20], pass[20];

//User
struct DataUser{
    char name[50], phone[20], email[30], username[20], password[20], judulGame[100], judulGame2[100], feedback[100];
    int topUp, saldo;
}useraccount[1000];

struct DataUser temp;
struct DataUser User;

//Game
struct DataGame{
    char name[100], rate[20], description[1000];
    long int price;
}gamedatabase[1000];

struct DataGame temp2;
struct DataGame Game;

//order
struct DataOrder{
    char namaGame[50], namaGame2[50], feedback[100], namapembeli[50], usia[20], email[50];
}listorder[1000];

struct DataOrder temp3;
struct DataOrder order;

char IdBarang[50];

int percobaan;

//------------------GENERAL---------------------
void main(){
    menu_devcus();
}

void header(){
    printf("========================================\n");
    printf("     _____   _   _   _____   _   _     \n");
    printf("    |  ___| | | | | |  _  | | | | |    \n");
    printf("    | |___  | |_| | | |_| | | | | |    \n");
    printf("    |_____| |_____| |_____| |_| |_|    \n\n");
    printf("         Welcome to GameZone!          \n");
    printf("     Your Ultimate Gaming Platform     \n");
    printf("========================================\n");
}

void header2(){
    printf("====================================================\n");
    printf("           _____   _   _   _____   _   _     \n");
    printf("          |  ___| | | | | |  _  | | | | |    \n");
    printf("          | |___  | |_| | | |_| | | | | |    \n");
    printf("          |_____| |_____| |_____| |_| |_|    \n\n");
    printf("               Welcome to GameZone!          \n");
    printf("            Your Ultimate Gaming Platform     \n");
    printf("====================================================\n");
}

void menu_devcus(){ //menu utama
    int menu;
    system("cls");
    fflush(stdin);
    header();
    printf("-----------------------------------------\n");
    printf("-- [1]. Developer                      --\n");
    printf("-- [2]. Player                         --\n");
    printf("-----------------------------------------\n");
    printf("/> "); scanf("%d", &menu);
    switch(menu){
        case 1: developer_login(); break;
        
        case 2: menu_customer(); break;
        
        default: printf("Unavailable option !!!\n");
                system("pause");
                system("cls");
                menu_devcus();
                break;
    }
}

void developer_login(){
    system("cls");
    fflush(stdin);

    printf("============ LOGIN DEVELOPER ============\n");
    printf("-- Username : "); gets(username);
    printf("-- Password : "); gets(pass);
    printf("-----------------------------------------\n");

    if(strcmp(username,"admin")==0 && strcmp(pass, "123")==0){
        printf("Login Success !!\n\n");
        system("pause");
        system("cls");
        menu_developer();
    }
    else{
        printf("No Valid, please try again !!\n");
        system("pause");
        system("cls");
        developer_login();
    }

}
void menu_developer(){
    int menu;
    fflush(stdin);
    system("cls");
    header();
    printf("-----------------------------------------\n");
    printf("-- [1]. Add Games                      --\n");
    printf("-- [2]. Delete Games                   --\n");
    printf("-- [3]. View Games                     --\n");
    printf("-- [4]. View Feedback                  --\n");
    printf("-- [5]. Exit                           --\n");
    printf("-----------------------------------------\n");
    printf("/> "); scanf("%d", &menu);

    switch(menu){
        case 1: developer_addgame(); break;
        case 2: developer_delategame(); break;
        case 3: developer_viewgame(); break;
        case 4: developer_viewfeedback(); break;
        case 5: menu_devcus(); break;
        default: printf("Unavailable option !!!\n");
                system("pause");
                system("cls");
                menu_developer();
                break;
    }
}

void developer_addgame(){
    fflush(stdin);
    system("cls");
    header();
    ListStockGame = fopen("Game Database.dat", "ab");

    printf("============ ++ DEVELOPER ============\n");
    printf("-- Title       : "); gets(Game.name);
    printf("-- Rate        : "); gets(Game.rate);
    printf("-- Description : "); gets(Game.description);
    printf("-- Sales Price : Rp. "); scanf("%ld", &Game.price); getchar();
    printf("---------------------------------------\n");
    printf("\n");

    fwrite(&Game, sizeof(struct DataGame), 1, ListStockGame);

    fclose(ListStockGame);

    printf("Games have been added!!\n");

    system("pause");
    system("cls");

    menu_developer();
}

void developer_delategame(){
    char delategame[100];
    int found =0;
    fflush(stdin);
    system("cls");

    header();

    ListStockGame = fopen("Game Database.dat", "rb");
    ListStockGame_backup = fopen("Game Database Backup.dat", "wb");

    printf("Enter the title of the game you want to remove\n");
    printf("/>"); gets(delategame);

    while(fread(&Game, sizeof(struct DataGame), 1, ListStockGame)==1){
        if(strcmp(Game.name, delategame)!=0){
            fwrite(&Game, sizeof(struct DataGame), 1, ListStockGame_backup);
        } else{
            found =1;
        }
    }

    fclose(ListStockGame);
    fclose(ListStockGame_backup);

    remove("Game Database.dat");
    rename("Game Database Backup.dat", "Game Database.dat");

    if(found == 1){
        printf("= = = = = = = = = = = = = = = = = = = =\n");
        printf("%s game has been successfully removed !!\n", delategame);
    }else{
        printf("= = = = = = = = = = = = = = = = = = = =\n");
        printf("%s game does not exist in the database !!", delategame);
    }

    system("pause");
    system("cls");

    menu_developer();
}

void developer_viewgame(){
    int data = 0;

    fflush(stdin);
    system("cls");

    header();

    ListStockGame = fopen("Game Database.dat", "rb");

    if(ListStockGame == NULL){
        printf("The game hasn't been added yet !!\n");
        system("pause");

        menu_developer();
    }

    while(fread(&gamedatabase[data], sizeof(struct DataGame), 1, ListStockGame)==1){
        data++;
    }

    fclose (ListStockGame);

    bubblesortGame(data, gamedatabase);

    printf("\nList of GameZone\n");
    viewbubblesortGame(data, gamedatabase);

    system("pause");
    system("cls");

    menu_developer();
}

void bubblesortGame(int data, struct DataGame gamedatabase[]){
    int i, j;

    for(i=0; i<data; i++){
        for(j=0; j<data; j++){
            if(strcmp(gamedatabase[j].rate, gamedatabase[j+1].rate)>0){
                temp2 = gamedatabase[j];
                gamedatabase[j] = gamedatabase[j+1];
                gamedatabase[j+1]=temp2;
            }
        }
    }
}

void viewbubblesortGame(int data, struct DataGame gamedatabase[]){
    int i;

    for(i=0; i<data; i++){
        printf("%d. ------------- GAMEZONE -------------\n", i+1);
        printf("-- Title        : %s\n", gamedatabase[i].name);
        printf("-- Rate         : %s\n", gamedatabase[i].rate);
        printf("-- Description  : %s\n", gamedatabase[i].description);
        printf("-- Sales Price  : Rp. %ld\n", gamedatabase[i].price);
        printf("-----------------------------------------\n");
        printf("\n");

    }
}

void developer_searchgame(){
    fflush(stdin);
    system("cls");

    header();

    char search[50];
    int found = 0;

    ListStockGame = fopen("Game Database.dat", "rb");

    printf("Input the game title\n");
    printf("/> "); gets(search);
    

    while(fread(&Game, sizeof(struct DataGame), 1, ListStockGame)==1){
        if(strcmp(Game.name, search)==0){
             printf("\n------------- GAMEZONE -------------\n");
             printf("-- Title        : %s\n", Game.name);
             printf("-- Rate         : %s\n", Game.rate);
             printf("-- Description  : %s\n", Game.description);
             printf("-- Sales Price  : Rp. %ld\n", Game.price);
             printf("-----------------------------------------\n");
             printf("\n");
             found = 1;
        }
    }

    if(!found){
        printf("\n==========================================\n");
        printf("%s game nowhere to be found\n", search);

         dasbord_customer();

    }

    fclose(ListStockGame);
    system("pause");
    system("cls");

    dasbord_customer();
}

void developer_viewfeedback(){
    system("cls");
    fflush(stdin);

    int i=0;

        printf("\n=-=-=-=-=-=-=-=-= FEEDBACK -=-=-=-=-=-=-=-=\n");
        printf("=============================================\n");

    Feedbackgame = fopen("Feedback database.dat", "rb");

    while(fread(&User, sizeof(User), 1, Feedbackgame)==1){
        printf("-= %d. Game     : %s\n", i+1, User.judulGame2);
        printf("-=    Feedback  : %s\n\n", User.feedback);
        i++;
    }

    fclose(Feedbackgame);

    system("pause");
    system("cls");

    menu_developer();
}
void menu_customer(){
    int menu;
    system("cls");
    header();

    printf("-----------------------------------------\n");
    printf("-- [1]. Sign Up                        --\n");
    printf("-- [2]. Sign In                        --\n");
    printf("-- [3]. Exit                           --\n");
    printf("-----------------------------------------\n");
    printf("/> "); scanf("%d", &menu); getchar();

    switch(menu){
        case 1: system("cls"); customer_registration(); break;
        case 2: system("cls"); customer_login(); break;
        case 3: system("cls"); menu_devcus(); break;
        default: printf("Unavailable option !!!\n");
                 system("pause");
                 system("cls");
                 menu_customer();
                 break;
    }
}

void customer_registration(){
    fflush(stdin);

    ListUserAccount = fopen("Daftar Akun User.dat", "ab");

    header();
    printf("-------------- REGISTRATION -------------\n");
    printf("-----------------------------------------\n");
    printf("== Full Name    : "); gets(User.name);
    printf("== Phone Number : "); gets(User.phone);
    printf("== Email        : "); gets(User.email);
    printf("------------------------------------------\n");
    printf("== username     : "); gets(User.username);
    printf("== Password     : "); gets(User.password);
    printf("------------------------------------------\n");
    printf("n");

    fwrite(&User, sizeof(struct DataUser), 1, ListUserAccount);

    fclose(ListUserAccount);

    printf("=====================================\n");
    printf("|| User Account added successfully ||\n");
    printf("=====================================\n");

    system("pause");
    system("cls");

    menu_customer();
}

void customer_login(){
    fflush(stdin);

    ListUserAccount = fopen("Daftar Akun User.dat", "rb");

    char username[50], password[50];
    int banyakuser = 0, berhasil = 0, i;
    
    header();
    
    if(ListUserAccount == NULL){
        printf("Database you did not find !!\n");
        
        system("pause");
    }

    printf("--------------- LOGIN USER ---------------\n");
    printf("------------------------------------------\n");
    printf("== username     : "); gets(username);
    printf("== Password     : "); gets(password);
    printf("------------------------------------------\n");
    
    while (fread(&useraccount[banyakuser],sizeof(struct DataUser), 1, ListUserAccount)==1)
    { 
        banyakuser++;
    }
        
    for (i = 0; i < banyakuser; i++)
    {
        if (strcmp(useraccount[i].username, username)==0 && strcmp(useraccount[i].password, password)==0)
        {
            strcpy(IdBarang,username);
            berhasil = 1;
        } 
    } 

    fclose(ListUserAccount);

    if (berhasil == 1)
    {
        printf("\n=========================================\n");
        printf("You have successfully logged in as a User!!\n");
        system("pause");
        system("cls");
        dasbord_customer();
        
    } else
    {
        printf("\n===============================\n");
        printf("You failed to login!! %d Again!! Username or Password is incorrect!! \n", 3-percobaan);

        if (percobaan < 3)
        {
            system("pause");
            system("cls");
            customer_login(percobaan+1);
        } else
        {
            printf("===============================\n");
            printf("You have tried too many attempts to login\n Your account has been secured. Thank you!!\n");
            system("pause");
            menu_customer();
        }
    }
}

void dasbord_customer(){
    char menu;

    system("cls");
    header();

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("||         [A]. View Profile         ||\n");
    printf("||         [B]. Search Games         ||\n");
    printf("||         [C]. Donwload Games       ||\n");
    printf("||         [D]. My Game              ||\n");
    printf("||         [E]. Feedback             ||\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("||         [F]. Logout               ||\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("/> "); scanf("%c", &menu); getchar();

    switch(menu){
        case 'A': 
        case 'a': system("cls"); view_profil(); break;

        case 'B': 
        case 'b': system("cls"); developer_searchgame(); break;

        case 'C': 
        case 'c': system("cls"); customer_buygame(); break;
        
        case 'D': 
        case 'd': system("cls"); customer_stockMygame(); break;

        case 'E': 
        case 'e': system("cls"); customer_feedback(); break;

        case 'F': 
        case 'f': system("cls"); menu_customer(); break;

        default: printf("Unavailable option !!!\n");
                 system("pause");
                 system("cls");
                 dasbord_customer();
                 break;

    }
}

void view_profil() {
    fflush(stdin);
    system("cls");
    header2(); // Pastikan fungsi header() telah didefinisikan

    FILE *ListUserAccount = fopen("Daftar Akun User.dat", "rb");

    if (ListUserAccount != NULL) {
        if (fread(&User, sizeof(struct DataUser), 1, ListUserAccount) == 1) {
            printf("====================================================\n");
            printf("-- Username : %s          || -- Password : %s       \n", User.username, User.password);
            printf("====================================================\n");
            printf("-- User Account : %s\n", User.name);
            printf("-- Phone Number : %s\n", User.phone);
            printf("----------------------------------------------------\n");
            printf("-- Email Game   : %s\n", User.email);
            printf("====================================================\n");
            printf("\n");

            fclose(ListUserAccount);
        } else {
            printf("Failed to read user account information.\n");
            fclose(ListUserAccount);
        }
    } else {
        printf("Failed to open file or no user accounts found.\n");
    }

    system("pause");
    system("cls");
    dasbord_customer();
}

void customer_buygame() {
    system("cls");
    header();
    
    int x =0;
    ListStockGame = fopen("Game Database.dat", "rb");

    printf("\n Please enter a game title !! \n");
    printf("=> Input Game : "); gets(order.namaGame);

    while(fread(&Game, sizeof(Game), 1, ListStockGame)==1){
        if(strcmp(order.namaGame, Game.name)==0){
            x=1;
        }
    }

    if(x==1){
        ListStockGame_Bucket = fopen("Donwloded Game.dat", "ab");

        printf("\nGame found, please complete the following registration <");
        printf("\n                 >Game purchases<\n");
        printf("=========================================================\n");
        printf("-- Username     : "); gets(order.namapembeli);
        printf("-- Email        : "); gets(order.email);
        printf("----------------------------------------------------------\n");
        printf("-- Game         : "); gets(order.namaGame2);
        printf("----------------------------------------------------------\n");
        fwrite(&order, sizeof(order), 1, ListStockGame_Bucket);
        fclose(ListStockGame_Bucket);

        printf("\n Games successfully install !!");
        system("pause");
        system("cls");

        dasbord_customer();
    }
    else{
        printf("\n Game failure to be found, download canceled");
        printf("NEXT --> ENTER");
        getchar();
        fclose(ListStockGame);
        dasbord_customer();
    }
    fclose(ListStockGame);
}



void customer_stockMygame(){
    
    fflush(stdin);
    header();
    int banyakorder=0;

    ListStockGame_Bucket = fopen("Donwloded Game.dat", "rb");

    if(ListStockGame_Bucket == NULL){
        printf("You don't have any games !!\n");
        system("pause");

        dasbord_customer();
    }
    while(fread(&listorder[banyakorder], sizeof(struct DataOrder), 1, ListStockGame_Bucket)==1){
        banyakorder++;
    }
    fclose(ListStockGame_Bucket);

    bubblesort_game(banyakorder, listorder);

    printf("\n================= YOUR GAME ================\n");
    tampilan_bubblesort_game(banyakorder, listorder);

    system("pause");
    system("cls");

    dasbord_customer();
}

void bubblesort_game(int banyakorder, struct DataOrder listorder[]){
    int i, j;

    for(i=0; i<banyakorder; i++){
        for(j=0; j<banyakorder -i -1; j++){
            
            if(strcmp(listorder[j].namaGame2, listorder[j+1].namaGame2)>0){
                temp3 = listorder[j];
                listorder[j] = listorder[ j+1];
                listorder[j+1] = temp3;
            }
        }
    }
}

void tampilan_bubblesort_game(int banyakorder, struct DataOrder listorder[]){
    int i;

    for(i=0; i<banyakorder; i++){
        printf("%d. Game    : %s\n", i+1, listorder[i].namaGame2);
    }
}
void customer_feedback(){
    system("cls");
    fflush(stdin);

    header();

    Feedbackgame = fopen("Feedback database.dat", "ab");

    printf("\n=-=-=-=-=-=-=-=-= SEND FEEDBACK -=-=-=-=-=-=-=-=\n");
    printf("==================================================\n");
    printf("-- Game     :   "); gets(User.judulGame2);
    printf("==================================================\n");
    printf("-- Feedback : "); gets(User.feedback);

    fwrite(&User, sizeof(User), 1, Feedbackgame);
    fclose(Feedbackgame);

    printf("\nFeedback sent successfully\n");
    system("pause");
    
    dasbord_customer();
}
