#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define MAX_MOTOR 100

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

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

typedef struct {
    char nama[30];
    int stok;
    float hargaPerHari;
} Motor;

Motor daftarMotor[MAX_MOTOR];
int jumlahMotor = 0;

typedef struct {
    char namaPenyewa[50];
    char namaMotor[30];
    int durasiSewa;
} Penyewa;

Penyewa daftarPenyewa[100];
int jumlahPenyewa = 0;


void clearScreen();
void tampilanMainMenu();
void registerUser();
void loginUser();
void tampilanMenuMasuk();
void menuMasuk(int a);
void tambahMotor();
void stockMotor();
void dataPenyewa();
void kalkulasiHarga();
void cetakStruk();
void author();
void getPassword(char *password, int max_length) {
    int i = 0;
    char ch;
    
    while (1) {
        ch = _getch(); 
        
        if (ch == 13) { 
            password[i] = '\0';
            break;
        } else if (ch == 8) { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else if (i < max_length - 1) {
            password[i] = ch;
            i++;
            printf("*"); 
        }
    }
}

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
                    author();
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
void tampilanMenuMasuk(){
    gotoxy(25, 3);
    printf("=================================================");
    gotoxy(25, 4);
    printf("=    SELAMAT DATANG DI SEWA MOTOR SATUHATI      =");
    gotoxy(25, 5);
    printf("=================================================");
    gotoxy(25, 7);
    printf("   	      Tambah Stok Motor               ");
    gotoxy(25, 8);
    printf("             Semua Jenis Motor               ");
    gotoxy(25, 9);
    printf("             Tambah Data Penyewa             ");
    gotoxy(25, 10);
    printf("             Kalkulasi Harga                 ");
    gotoxy(25, 11);
    printf("             Cetak Struk                     ");
    gotoxy(25, 12);
    printf("             LOGOUT                          ");
    gotoxy(25, 13);
    printf("=================================================");
    gotoxy(25, 14);
    printf("= Dari Kami, Untuk Perjalanan Tak Terlupakanmu. =");
    gotoxy(25, 15);
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
    printf("--- REGISTRASI USER BARU ---");

    gotoxy(25, 7); 
    printf("Masukkan Username: ");
    fgets(currentUser.username, sizeof(currentUser.username), stdin);
    currentUser.username[strcspn(currentUser.username, "\n")] = '\0';

    gotoxy(25, 8);
    printf("Masukkan Password: ");
    getPassword(currentUser.password, sizeof(currentUser.password));
    currentUser.password[strcspn(currentUser.password, "\n")] = '\0';
    
    gotoxy(25, 10);
    printf("Registrasi berhasil! Sekarang Anda bisa LOGIN.\n");
}

void menuMasuk(int a) {
    int pos = 1;
    int key;

    do {
        clearScreen();
        tampilanMenuMasuk();

        for(int i = 1; i <= 6; i++) {
            gotoxy(20, 6 + i);
            if(i == pos) {
                printf("--> ");
            } else {
                printf("    ");
            }
        }

        key = getch();
        if(key == 0 || key == 224) { 
            key = getch();
            switch(key) {
                case 72: // arrow atas
                    pos--;
                    if(pos < 1) pos = 6;
                    break;
                case 80: // arrow atas
                    pos++;
                    if(pos > 6) pos = 1;
                    break;
            }
        }

        if(key == 13) { // Enter 
            clearScreen();
            switch(pos) {
                case 1:
                    tambahMotor();
                    break;
                case 2:
                    stockMotor();
                    break;
                case 3:
                    dataPenyewa();
                    break;
                case 4:
                    kalkulasiHarga();
                    break;
                case 5:
                    cetakStruk();
                    break;
                case 6:
                    isLoggedIn = 0;
                    gotoxy(25, 20);
                    printf("Logout berhasil.\n");
                    break;
            }

            if(pos != 6) {
                gotoxy(25, 22);
                printf("Tekan ENTER untuk kembali...");
                getchar();
            }
        }
    } while (pos != 6 || key != 13);
}

void tambahMotor() {
    clearScreen();
    if (jumlahMotor >= MAX_MOTOR) {
        gotoxy(25, 15);
        printf("Kapasitas data motor penuh.\n");
        return;
    }

    Motor m;

    gotoxy(25, 5);
    printf("--- TAMBAH DATA MOTOR ---");

    gotoxy(25, 7);
    printf("Nama Motor: ");
    fgets(m.nama, sizeof(m.nama), stdin);
    m.nama[strcspn(m.nama, "\n")] = '\0';

    gotoxy(25, 8);
    printf("Jumlah Stok: ");
    scanf("%d", &m.stok);
    getchar();

    gotoxy(25, 9);
    printf("Harga Sewa per Hari: ");
    scanf("%f", &m.hargaPerHari);
    getchar();

    daftarMotor[jumlahMotor] = m;
    jumlahMotor++;

    gotoxy(25, 11);
    printf("Motor berhasil ditambahkan!\n");
}

void stockMotor() {
    clearScreen();
    if (jumlahMotor == 0) {
        gotoxy(25, 10);
        printf("Belum ada data motor yang ditambahkan.\n");
        return;
    }

    gotoxy(25, 5);
    printf("--- DAFTAR STOK MOTOR ---");

    for (int i = 0; i < jumlahMotor; i++) {
        gotoxy(25, 7 + (i*5));
        printf("Motor ke-%d", i + 1);
        gotoxy(25, 8 + (i*5));
        printf("Nama Motor        : %s", daftarMotor[i].nama);
        gotoxy(25, 9 + (i*5));
        printf("Jumlah Stok       : %d", daftarMotor[i].stok);
        gotoxy(25, 10 + (i*5));
        printf("Harga per Hari    : Rp %.2f", daftarMotor[i].hargaPerHari);
        gotoxy(25, 11 + (i*5));
        printf("-----------------------------------");
    }
}

void dataPenyewa() {
    clearScreen();
    if (jumlahMotor == 0) {
        gotoxy(25, 10);
        printf("Belum ada data motor yang tersedia untuk disewa.\n");
        return;
    }

    Penyewa p;

    gotoxy(25, 5);
    printf("--- INPUT DATA PENYEWA ---");

    gotoxy(25, 7);
    printf("Nama Penyewa: ");
    fgets(p.namaPenyewa, sizeof(p.namaPenyewa), stdin);
    p.namaPenyewa[strcspn(p.namaPenyewa, "\n")] = '\0';

    gotoxy(25, 9);
    printf("Pilih motor yang ingin disewa:");
    for (int i = 0; i < jumlahMotor; i++) {
        gotoxy(25, 10 + i);
        printf("%d. %s (Stok: %d, Harga/hari: Rp %.2f)", i + 1,
               daftarMotor[i].nama, daftarMotor[i].stok, daftarMotor[i].hargaPerHari);
    }

    int pilihan;
    gotoxy(25, 11 + jumlahMotor);
    printf("Masukkan nomor motor: ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan < 1 || pilihan > jumlahMotor) {
        gotoxy(25, 13 + jumlahMotor);
        printf("Pilihan tidak valid.\n");
        return;
    }

    if (daftarMotor[pilihan - 1].stok == 0) {
        gotoxy(25, 13 + jumlahMotor);
        printf("Maaf, motor ini sedang kosong.\n");
        return;
    }

    strcpy(p.namaMotor, daftarMotor[pilihan - 1].nama);

    gotoxy(25, 13 + jumlahMotor);
    printf("Lama sewa (hari): ");
    scanf("%d", &p.durasiSewa);
    getchar();

    daftarMotor[pilihan - 1].stok--;

    daftarPenyewa[jumlahPenyewa] = p;
    jumlahPenyewa++;

    gotoxy(25, 15 + jumlahMotor);
    printf("Data penyewa berhasil disimpan!\n");
}

void kalkulasiHarga() {
    clearScreen();
    if (jumlahPenyewa == 0) {
        gotoxy(25, 10);
        printf("Belum ada data penyewa.\n");
        return;
    }

    gotoxy(25, 5);
    printf("--- KALKULASI HARGA SEWA ---");

    
    for (int i = 0; i < jumlahPenyewa; i++) {
        gotoxy(25, 7 + (i*4));
        printf("Penyewa ke-%d", i + 1);
        gotoxy(25, 8 + (i*4));
        printf("Nama Penyewa  : %s", daftarPenyewa[i].namaPenyewa);
        gotoxy(25, 9 + (i*4));
        printf("Motor Disewa  : %s (%d hari)", daftarPenyewa[i].namaMotor, daftarPenyewa[i].durasiSewa);
        gotoxy(25, 10 + (i*4));
        printf("-----------------------------------");
    }

    int pilihan;
    gotoxy(25, 11 + (jumlahPenyewa*4));
    printf("Pilih penyewa untuk kalkulasi (nomor): ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan < 1 || pilihan > jumlahPenyewa) {
        gotoxy(25, 13 + (jumlahPenyewa*4));
        printf("Pilihan tidak valid.\n");
        return;
    }

        float hargaPerHari = 0;
    for (int i = 0; i < jumlahMotor; i++) {
        if (strcmp(daftarMotor[i].nama, daftarPenyewa[pilihan-1].namaMotor) == 0) {
            hargaPerHari = daftarMotor[i].hargaPerHari;
            break;
        }
    }

    float totalHarga = hargaPerHari * daftarPenyewa[pilihan-1].durasiSewa;

    clearScreen();
    gotoxy(25, 5);
    printf("--- HASIL KALKULASI HARGA ---");
    gotoxy(25, 7);
    printf("Nama Penyewa  : %s", daftarPenyewa[pilihan-1].namaPenyewa);
    gotoxy(25, 8);
    printf("Motor Disewa  : %s", daftarPenyewa[pilihan-1].namaMotor);
    gotoxy(25, 9);
    printf("Durasi Sewa   : %d hari", daftarPenyewa[pilihan-1].durasiSewa);
    gotoxy(25, 10);
    printf("Harga per Hari: Rp %.2f", hargaPerHari);
    gotoxy(25, 11);
    printf("Total Harga   : Rp %.2f", totalHarga);
    gotoxy(25, 13);
    printf("===================================");
}

void cetakStruk() {
    clearScreen();
    if (jumlahPenyewa == 0) {
        gotoxy(25, 10);
        printf("Belum ada data penyewa.\n");
        return;
    }

    gotoxy(25, 5);
    printf("--- CETAK STRUK SEWA ---");

       for (int i = 0; i < jumlahPenyewa; i++) {
        gotoxy(25, 7 + (i*4));
        printf("Penyewa ke-%d", i + 1);
        gotoxy(25, 8 + (i*4));
        printf("Nama Penyewa  : %s", daftarPenyewa[i].namaPenyewa);
        gotoxy(25, 9 + (i*4));
        printf("Motor Disewa  : %s", daftarPenyewa[i].namaMotor);
        gotoxy(25, 10 + (i*4));
        printf("-----------------------------------");
    }

    int pilihan;
    gotoxy(25, 11 + (jumlahPenyewa*4));
    printf("Pilih penyewa untuk cetak struk (nomor): ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan < 1 || pilihan > jumlahPenyewa) {
        gotoxy(25, 13 + (jumlahPenyewa*4));
        printf("Pilihan tidak valid.\n");
        return;
    }

        float hargaPerHari = 0;
    for (int i = 0; i < jumlahMotor; i++) {
        if (strcmp(daftarMotor[i].nama, daftarPenyewa[pilihan-1].namaMotor) == 0) {
            hargaPerHari = daftarMotor[i].hargaPerHari;
            break;
        }
    }

    float totalHarga = hargaPerHari * daftarPenyewa[pilihan-1].durasiSewa;

    clearScreen();
    gotoxy(20, 3);
    printf("================================================");
    gotoxy(20, 4);
    printf("=               STRUK SEWA MOTOR               =");
    gotoxy(20, 5);
    printf("=           SEWA MOTOR SATUHATI                =");
    gotoxy(20, 6);
    printf("================================================");
    gotoxy(20, 8);
    printf(" Nama Penyewa   : %s", daftarPenyewa[pilihan-1].namaPenyewa);
    gotoxy(20, 9);
    printf(" Motor Disewa   : %s", daftarPenyewa[pilihan-1].namaMotor);
    gotoxy(20, 10);
    printf(" Durasi Sewa    : %d hari", daftarPenyewa[pilihan-1].durasiSewa);
    gotoxy(20, 11);
    printf(" Harga per Hari : Rp %.2f", hargaPerHari);
    gotoxy(20, 12);
    printf("-----------------------------------------------");
    gotoxy(20, 13);
    printf(" Total Harga    : Rp %.2f", totalHarga);
    gotoxy(20, 15);
    printf("================================================");
    gotoxy(20, 16);
    printf("= Terima kasih telah menggunakan layanan kami  =");
    gotoxy(20, 17);
    printf("=      Dari Kami, Untuk Perjalananmu           =");
    gotoxy(20, 18);
    printf("================================================");
    
    gotoxy(20, 20);
    printf("Struk telah dicetak!");
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
    printf("--- LOGIN ---");

    gotoxy(25, 7);
    printf("Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    gotoxy(25, 8);
    printf("Password: ");
    getPassword(inputPassword, sizeof(inputPassword)); // Ganti sensor() dengan ini
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(inputUsername, currentUser.username) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        loadingAnimation(); 
        isLoggedIn = 1;
        gotoxy(25, 15);
        printf("Selamat datang Sang Atmin!");
         menuMasuk(0);
    } else {
        gotoxy(25, 10);
        printf("Username atau password salah. Coba lagi.");
    }
}

void author() {
	system("cls");
	gotoxy(20,8);
    printf("Created by");

    gotoxy(20, 10);
    printf("Yosua Setiawan Hemus - 672024016");

    gotoxy(20, 11);
    printf("Willbert Marvelous Tedevince - 672024035");

    gotoxy(20, 12);
    printf("Xavier Calvin Kurnia Wijaya - 672024216");

    gotoxy(20, 13);
    printf("Matthew Dustin Sukiat - 672024260");

    gotoxy(20, 14);
    printf("Karrel Valenta Putra Chrishananda - 672024261");
}