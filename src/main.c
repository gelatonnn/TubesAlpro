#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#include "header/auth.h"
#include "header/daftarCheckUp.h"
#include "header/lihatAntrian.h"
#include "header/dataCheckup.h"
#include "header/listDenah.h"
#include "header/mapAssignDokter.h"
#include "header/tambahDokter.h"
#include "header/queueAntri.h"  
#include "header/keluar.h"
#include "header/help.h"
#include "header/diagnosisBerobat.h"
#include "header/obat.h"
#include "header/antrian.h"
#include "header/adt_list_obat.h"
#include "header/adt_stack_obat.h"
#include "header/manager.h"
#include "header/pulangDok.h"

UserSet generateDataPengguna;
Denah generateDataDenah;
MapDokterRuangan generateDataMap;


void tampilanBanner() {
    printf("\n");
    printf("██████╗░░██████╗  ███╗░░██╗██╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗ \n");
    printf("██╔══██╗██╔════╝  ████╗░██║██║████╗░████║██╔══██╗████╗░██║██╔════╝\n");
    printf("██████╔╝╚█████╗░  ██╔██╗██║██║██╔████╔██║██║░░██║██╔██╗██║╚█████╗░\n");
    printf("██╔══██╗░╚═══██╗  ██║╚████║██║██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗\n");
    printf("██║░░██║██████╔╝  ██║░╚███║██║██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝\n");
    printf("╚═╝░░╚═╝╚═════╝░  ╚═╝░░╚══╝╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░\n");
    printf("+----------------------------------------------------------------+\n");
    printf("                        Ⲣⲟⲱⲉꞅⲉⲇ ⲃⲩ ⲕⲉ𝓵ⲟⲙⲣⲟⲕ 𝓛                        \n");
    printf("                            𝐊𝟎𝟒 - 𝐒𝐓𝐈                                \n");
    printf("\n");
}

void tampilkanMenuUtama() {
    if (current_user == NULL) {
        printf("\nSelamat datang! Silakan pilih opsi:\n");
        printf("1. LOGIN\n"); //F01
        printf("2. REGISTER PASIEN\n"); //F02
        printf("4. LUPA PASSWORD\n"); // F04
        printf("5. HELP\n"); // F05
        printf("0. KELUAR\n"); //F18
    } else {
        printf("\nHalo, %s %s!\n", roleToStr(current_user->role), current_user->username);
        printf("--------------------------------------\n");
        printf("Menu yang Tersedia:\n");
        printf("1. LIHAT DENAH\n");     // F06
        printf("2. LIHAT RUANGAN\n");    // F06     

        if (current_user->role == MANAGER) {
            printf("3. LIHAT USER\n"); // F07
            printf("31. LIHAT PASIEN\n"); // F07
            printf("32. LIHAT DOKTER\n"); // F07
            printf("4. CARI USER\n"); // F08
            printf("41. CARI PASIEN\n"); // F08
            printf("42. CARI DOKTER\n"); // F08
            printf("5. LIHAT SEMUA ANTRIAN\n"); // F09
            printf("6. TAMBAH DOKTER\n"); // F10
            printf("7. ASSIGN DOKTER\n"); // F10
        } else if (current_user->role == DOKTER) {
            printf("8. DIAGNOSIS PASIEN\n"); // F11
            printf("9. BERI PENGOBATAN\n"); // F12
        } else if (current_user->role == PASIEN) {
            printf("10. SELESAI CHECK-UP/PULANG\n"); // F13
            printf("11. DAFTAR CHECK-UP\n"); // F14
            printf("12. LIHAT ANTRIAN\n"); // F15
            printf("13. MINUM OBAT\n"); // F16
            printf("14. MINUM PENAWAR\n"); //F17
        }
        printf("98. HELP\n"); // F05
        printf("99. LOGOUT \n");   // F03
        printf("0. EXIT\n"); // F18
    }
    printf("--------------------------------------\n");
    printf("Pilihan Anda: ");
}

int main() {
    tampilanBanner();

    initUserSet(&generateDataPengguna);
    initMapDokterRuangan(&generateDataMap);
    initPenyakit();
    initObat();
    
    int jumlahRuangan, kapasitas;
    printf("Masukkan jumlah ruangan: ");
    if (scanf("%d", &jumlahRuangan) != 1) {
        printf("Input tidak valid. Masukkan jumlah ruangan.\n");
        return 1;
    }
    clearInputBuffer();

    printf("Masukkan kapasitas ruangan: ");
    if (scanf("%d", &kapasitas) != 1) {
        printf("Input tidak valid. Masukkan kapasitas ruangan.\n");
        return 1;
    }
    clearInputBuffer();

    initDenah(&generateDataDenah, jumlahRuangan, kapasitas);

    int pilihan;
    int sortKey, sortOrder;
    char usernameInput[MAX_LEN];
    char passwordInput[MAX_LEN];
    int idRuanganInput;


    do {
        tampilkanMenuUtama();
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Masukkan nomor pilihan.\n");
            clearInputBuffer();
            pilihan = -1; 
            continue;
        }
        clearInputBuffer();

        if (current_user == NULL) { // Belum Login
            switch (pilihan) {
                case 1: // F01
                    printf(">>> LOGIN\n");
                    printf("Username : ");
                    fgets(usernameInput, MAX_LEN, stdin);
                    usernameInput[strcspn(usernameInput, "\n")] = 0;
                    printf("Password : ");
                    fgets(passwordInput, MAX_LEN, stdin);
                    passwordInput[strcspn(passwordInput, "\n")] = 0;
                    loginUser(&generateDataPengguna, usernameInput, passwordInput);
                    break;
                case 2: // F02
                    printf(">>> REGISTER\n");
                    printf("Username : ");
                    fgets(usernameInput, MAX_LEN, stdin);
                    usernameInput[strcspn(usernameInput, "\n")] = 0;
                    printf("Password : ");
                    fgets(passwordInput, MAX_LEN, stdin);
                    passwordInput[strcspn(passwordInput, "\n")] = 0;
                    registerUser(&generateDataPengguna, usernameInput, passwordInput, PASIEN);
                    break;
                case 4: // F04
                    lupaPassword(&generateDataPengguna);
                    break;
                case 5: // F05
                    printf(">>> HELP\n");
                    help();
                    break;
                case 0: // F18
                    keluar();
                    break;
                default:
                    printf("Pilihan tidak valid.\n");
            }
        } else { // Sudah Login
            switch (pilihan) {
                case 1: // F06
                    lihatDenah(&generateDataDenah);
                    break;
                case 2: // F06
                    printf("Masukkan ID Ruangan yang ingin dilihat : ");
                    if (scanf("%d", &idRuanganInput) == 1) {
                        clearInputBuffer();
                        lihatRuangan(&generateDataDenah, idRuanganInput, &generateDataPengguna, &generateDataMap);
                    } else {
                        printf("Input ID Ruangan tidak valid.\n");
                        clearInputBuffer();
                    }
                    break;

            //----FITUR MANAGER----
                case 3: //f07
                    if (current_user->role == MANAGER) {
                        printf("Sort berdasarkan?\n1. ID\n2. Username\n>>> ");      
                        scanf("%d", &sortKey);
                        getchar(); // Clear newline character
                        printf("Urutan?\n1. ASC\n2. DESC\n>>> ");
                        scanf("%d", &sortOrder);
                        getchar(); // Clear newline character
                        lihatUser(&generateDataPengguna,
                            sortKey == 1 ? SORT_BY_ID : SORT_BY_NAME, 
                            sortOrder == 1 ? ASC : DESC);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 31: //f07
                    if (current_user->role == MANAGER) {
                        printf("Sort berdasarkan?\n1. ID\n2. Username\n>>> ");      
                        scanf("%d", &sortKey);
                        getchar(); // Clear newline character
                        printf("Urutan?\n1. ASC\n2. DESC\n>>> ");
                        scanf("%d", &sortOrder);
                        getchar(); // Clear newline character
                        lihatPasien(&generateDataPengguna,
                            sortKey == 1 ? SORT_BY_ID : SORT_BY_NAME, 
                            sortOrder == 1 ? ASC : DESC);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 32: //f07
                    if (current_user->role == MANAGER) {
                        printf("Sort berdasarkan?\n1. ID\n2. Username\n3. Aura\n>>> ");      
                        scanf("%d", &sortKey);
                        SortKey actualSortkey;
                        if (sortKey == 1) {
                            actualSortkey = SORT_BY_ID;
                        } else if (sortKey == 2) {
                            actualSortkey = SORT_BY_NAME;
                        } else if (sortKey == 3) {
                            actualSortkey = SORT_BY_AURA; // bonus AURA
                        }
                        getchar(); // Clear newline character
                        printf("Urutan?\n1. ASC\n2. DESC\n>>> ");
                        scanf("%d", &sortOrder);
                        getchar(); // Clear newline character
                        lihatDokter(&generateDataPengguna, actualSortkey,
                            sortOrder == 1 ? ASC : DESC);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 4: //f08
                    if (current_user->role == MANAGER) {
                        cariUser(&generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 41: //f08
                    if (current_user->role == MANAGER) {
                        cariPasien(&generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 42: //f08
                    if (current_user->role == MANAGER) {
                        cariDokter(&generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 5: //f09
                    if (current_user->role == MANAGER) {
                        lihatSemuaAntrian(&generateDataDenah, &generateDataPengguna, &generateDataMap);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 6: //f10
                    if (current_user->role == MANAGER) {
                        managerTambahDokter(&generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 7: //f10
                    if (current_user->role == MANAGER) {
                        assignDokter(&generateDataMap, &generateDataDenah, &generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;

            //----FITUR DOKTER----
                case 8: // F11
                    if (current_user->role == DOKTER) {
                        diagnosisPasien(current_user, &generateDataDenah, &generateDataMap, &generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 9: // F12
                    if (current_user->role == DOKTER) {
                        berobatPasien(current_user, &generateDataDenah, &generateDataMap, &generateDataPengguna);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;

            //----FITUR PASIEN----
                case 10: // F13
                    if (current_user->role == PASIEN) {
                        F13_PulangDok(current_user, &generateDataPengguna, &generateDataDenah);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;             
                case 11: //F14
                    if (current_user->role == PASIEN) {
                        daftarCheckUp(&generateDataPengguna, &generateDataDenah, &generateDataMap, current_user);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 12: // F15
                    if (current_user->role == PASIEN) {
                        lihatStatusAntrian(&generateDataPengguna, &generateDataDenah, &generateDataMap, current_user);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 13: //F16
                    if (current_user->role == PASIEN) {
                        F16_MinumObat(current_user);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;
                case 14: //F17
                    if (current_user->role == PASIEN) {
                        F17_MinumPenawar(current_user);
                    } else {
                        printf("Anda tidak memiliki akses untuk fitur ini.\n");
                    }
                    break;

                case 98: // F05
                    printf(">>> HELP\n");
                    help();
                    break;
                case 99: // F03
                    logoutUser();
                    break;
                case 0: // F18
                    printf(">>> EXIT\n");
                    keluar();
                    break;
                default:
                    printf("Pilihan tidak valid.\n");
            }
        }
    } while (pilihan != 0);

    printf("Terima kasih telah menggunakan sistem rumah sakit Nimons. Sampai jumpa!\n");
    return 0;
}
