#include <stdio.h>
#include <string.h>
#include "../header/help.h"

void help() {
    printf("=========== HELP ===========\n");
    if (current_user == NULL) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("2. REGISTER: Membuat akun baru\n");
    } else {
        switch (current_user->role) {
            case MANAGER:
                printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan:\n", current_user->username);
                printf("1. LOGOUT: Keluar dari akun\n");
                printf("2. TAMBAH_DOKTER: Menambahkan dokter baru\n");
                printf("3. LIHAT_USER: Melihat seluruh user\n");
                printf("4. EXIT: Keluar dari sistem\n");
                break;
            case DOKTER:
                printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan:\n", current_user->username);
                printf("1. LOGOUT: Keluar dari akun\n");
                printf("2. DIAGNOSIS: Melakukan diagnosis pasien\n");
                printf("3. NGOBATIN: Memberikan obat\n");
                printf("4. EXIT: Keluar dari sistem\n");
                break;
            case PASIEN:
                printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan:\n", current_user->username);
                printf("1. LOGOUT: Keluar dari akun\n");
                printf("2. DAFTAR_CHECKUP: Daftar untuk pemeriksaan\n");
                printf("3. MINUM_OBAT: Minum obat\n");
                printf("4. PULANGDOK: Meminta izin pulang\n");
                printf("5. EXIT: Keluar dari sistem\n");
                break;
            default:
                printf("Role tidak dikenali.\n");
                break;
        }
    }

    printf("\nFootnote:\n1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n");
}