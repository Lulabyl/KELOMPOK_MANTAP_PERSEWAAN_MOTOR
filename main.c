#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Loading animation
void loadingAnimation() {
    system("cls");
    gotoxy(45, 10);
    printf("Loading sistem persewaan motor...");
    gotoxy(30, 12);
    for(int i = 0; i < 40; i++) {
        printf("%c", 219);
        Sleep(50);
    }
}

typedef struct {
    char username[30];
    char password[30];
} User;

User currentUser;
int isLoggedIn = 0;

void clearScreen();
void tampilanMainMenu();
void registerUser();
void loginUser();

int main() {
    system("color F0");
    int pilihan;

    currentUser.username[0] = '\0';
    currentUser.password[0] = '\0';
    do {
            clearScreen();
            tampilanMainMenu();
            gotoxy(25, 14);
            printf("Masukkan Pilihan Anda : ");
            scanf("%d", &pilihan);
            getchar();

            switch (pilihan) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loginUser();
                    break;
                case 0:
                gotoxy(30, 15);
                    printf("\nTerima kasih telah menggunakan program Sewa Motor SatuHati.\n");
                    break;
                default:
                gotoxy(30, 15);
                    printf("\nPilihan tidak valid. Yang benar saja!.\n");
                    break;
            }

             if (pilihan != 0){
                gotoxy(25, 17);
                printf("\nTekan ENTER untuk melanjutkan...");
                getchar();
                printf("\n");
             }
    }while (pilihan != 0);

    return 0;
}


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
    system("clear");
    #endif
}

void tampilanMainMenu(){
    gotoxy(25, 3);
    printf("=================================================");
    gotoxy(25, 4);
    printf("=    SELAMAT DATANG DI SEWA MOTOR SATUHATI      =");
    gotoxy(25, 5);
    printf("=================================================");
    gotoxy(25, 6);
    printf("=   	           1.REGISTER                    =");
    gotoxy(25, 7);
    printf("=                 2.LOGIN                       =");
    gotoxy(25, 8);
    printf("=                 0.EXIT                        =");
    gotoxy(25, 9);
    printf("=================================================");
    gotoxy(25, 10);
    printf("= Dari Kami, Untuk Perjalanan Tak Terlupakanmu. =");
    gotoxy(25, 11);
    printf("=================================================");
}

void registerUser() {
    clearScreen();
    gotoxy(25, 15);
     if (strlen(currentUser.username) > 0) {
            gotoxy(25, 15);
            printf("\nMaaf, hanya satu atmin yang bisa diregistrasi untuk saat ini.\n");
            gotoxy(25, 16);
            printf("User '%s' sudah terdaftar.\n", currentUser.username);
            return;
     }
     gotoxy(25, 5);
      printf("\n--- REGISTRASI USER BARU ---\n");
     gotoxy(25, 7); 
      printf("Masukkan Username: ");

    fgets(currentUser.username, sizeof(currentUser.username), stdin);
    currentUser.username[strcspn(currentUser.username, "\n")] = '\0';
 
    gotoxy(25, 8);
    printf("Masukkan Password: ");
    fgets(currentUser.password, sizeof(currentUser.password), stdin);
    currentUser.password[strcspn(currentUser.password, "\n")] = '\0';

    gotoxy(25, 10);
    printf("Registrasi berhasil! Sekarang Anda bisa LOGIN.\n");
}

void loginUser() {
    clearScreen();
    if (isLoggedIn) {
        gotoxy(25, 15);
        printf("\nAnda sudah login sebagai '%s'. Silakan logout terlebih dahulu.\n", currentUser.username);
        return;
    }

    if (strlen(currentUser.username) == 0) {
        gotoxy(25, 15);
        printf("\nBelum ada user yang terdaftar. Silakan REGISTER terlebih dahulu.\n");
        return;
    }

    char inputUsername[30];
    char inputPassword[30];

    gotoxy(25, 5);
    printf("\n--- LOGIN ---\n");
    gotoxy(25, 7);
    printf("Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    gotoxy(25, 8);
    printf("Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';


    if (strcmp(inputUsername, currentUser.username) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        loadingAnimation(); 
        isLoggedIn = 1;
        gotoxy(25, 15);
        printf("Selamat datang Sang Atmin!");
    } else {
        gotoxy(25, 10);
        printf("Username atau password salah. Coba lagi.");
    }
}
