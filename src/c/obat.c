#include "../header/obat.h"
#include "../header/diagnosisBerobat.h" // Untuk getNamaObat
#include <stdio.h>
#include <stdlib.h> // Untuk clear buffer jika perlu

// Fungsi helper untuk membersihkan input buffer (jika belum ada yang global)
static void clearInputBufferFiturObat() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void F16_MinumObat(User* pasien_login) {
    if (pasien_login == NULL || pasien_login->role != PASIEN) {
        printf("Fungsi ini hanya untuk pasien.\n");
        return;
    }

    printf(">>> MINUM_OBAT\n");
    if (isListInventoryEmpty(&(pasien_login->inventory_obat))) {
        printf("Inventaris obat Anda kosong! Tidak ada obat untuk diminum.\n");
        return;
    }

    printf("============ DAFTAR OBAT DI INVENTORY ============\n");
    NodeObatInventory* current_inv = pasien_login->inventory_obat.head;
    int i = 0;
    while (current_inv != NULL) {
        const char* nama_obat = getNamaObat(current_inv->data.obat_id);
        printf("%d. %s\n", i + 1, nama_obat ? nama_obat : "Obat Tidak Dikenal");
        current_inv = current_inv->next;
        i++;
    }
    printf("===============================================\n");

    int pilihan;
    printf("Pilih obat untuk diminum (masukkan nomor): ");
    if (scanf("%d", &pilihan) != 1) {
        clearInputBufferFiturObat();
        printf("Input tidak valid.\n");
        return;
    }
    clearInputBufferFiturObat();

    if (pilihan < 1 || pilihan > pasien_login->inventory_obat.count) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }

    ItemObatPasien obat_diminum;
    // Hapus dari inventory berdasarkan indeks (pilihan - 1 karena 0-based)
    if (deleteAtListInventory(&(pasien_login->inventory_obat), pilihan - 1, &obat_diminum)) {
        // Masukkan ke perut
        pushStackPerut(&(pasien_login->perut_pasien), obat_diminum);
        const char* nama_obat_diminum = getNamaObat(obat_diminum.obat_id);
        printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", nama_obat_diminum ? nama_obat_diminum : "Obat");
    } else {
        printf("Gagal mengambil obat dari inventaris.\n"); // Seharusnya tidak terjadi jika validasi pilihan benar
    }

    printf("\nSisa obat di inventory:\n");
    if (isListInventoryEmpty(&(pasien_login->inventory_obat))) {
        printf("Inventaris obat Anda sekarang kosong.\n");
    } else {
        current_inv = pasien_login->inventory_obat.head;
        i = 0;
        while (current_inv != NULL) {
            const char* nama_obat = getNamaObat(current_inv->data.obat_id);
            printf("%d. %s\n", i + 1, nama_obat ? nama_obat : "Obat Tidak Dikenal");
            current_inv = current_inv->next;
            i++;
        }
    }
    printf("===============================================\n");
}

void F17_MinumPenawar(User* pasien_login) {
    if (pasien_login == NULL || pasien_login->role != PASIEN) {
        printf("Fungsi ini hanya untuk pasien.\n");
        return;
    }

    printf(">>> PENAWAR\n");
    if (isStackPerutEmpty(&(pasien_login->perut_pasien))) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    ItemObatPasien obat_dikeluarkan;
    if (popStackPerut(&(pasien_login->perut_pasien), &obat_dikeluarkan)) {
        // Kembalikan ke inventory
        insertLastListInventory(&(pasien_login->inventory_obat), obat_dikeluarkan);
        const char* nama_obat_dikeluarkan = getNamaObat(obat_dikeluarkan.obat_id);
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", nama_obat_dikeluarkan ? nama_obat_dikeluarkan : "Obat");
    } else {
        printf("Gagal mengeluarkan obat dari perut.\n"); // Seharusnya tidak terjadi jika tidak kosong
    }
}