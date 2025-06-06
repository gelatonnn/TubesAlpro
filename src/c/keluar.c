#include <stdio.h>
#include <stdlib.h> 
#include "../header/keluar.h"

void keluar() {
    char input;

    while (1) {
        printf("Apakah Anda sudah selesai menggunakan layanan ini? (y/n) ");
        scanf(" %c", &input);  

        if (input == 'y' || input == 'Y') {
            break;
        } else if (input == 'n' || input == 'N') {
            break;
        } else {
            printf("Input tidak valid. Harap masukkan 'y' atau 'n'.\n");
        }
    }
    printf("Terima kasih telah menggunakan sistem rumah sakit Nimons. Sampai jumpa!\n");
    exit(0); 
}
