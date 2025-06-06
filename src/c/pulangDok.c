#include "../header/diagnosisBerobat.h"

extern MapPenyakitObat daftarMapObat[MAX_OBAT]; 
extern int jumlahMapObat; 
extern int idDokterYangBertugas; // ID Dokter yang sedang bertugas

EntriAntrianCheckup* getEntriPasien(Denah* denah, int idPasien) {
    if (denah == NULL || idPasien <= 0) {
        return NULL;
    }

    for (int i = 0; i < denah->jumlahRuangan; i++) {
        Queue* antrian = &denah->ruangan[i].antrianPasien;
        if (isQueueEmpty(antrian)) {
            continue;
        }
        Node* current = antrian->front;
        while (current != NULL) {
            if (current->data.idPasien == idPasien) {
                return &(current->data);
            }
            current = current->next;
        }
    }
    return NULL;
}

bool hapusDariQueue(Queue* q, int index) {
    if (q == NULL || isQueueEmpty(q) || index < 0 || index >= getSize(q)) {
        return false;
    }

    int size = getSize(q);
    bool success = false;

    for (int i = 0; i < size; i++) {
        EntriAntrianCheckup pasien;
        dequeue(q, &pasien);

        if (i == index) {
            success = true;
        } else {
            enqueue(q, pasien);
        }
    }

    return success;
}

void resetDiagnosis(Denah* denah, int idPasien) {
    EntriAntrianCheckup* entri = getEntriPasien(denah, idPasien);
    if (entri != NULL) {
        entri->idPenyakit = -1;
    }
}

bool isObatSama(StackPerutObat* perut, int* resep, int len) {
    if (getCountStackPerut(perut) != len) {
        return false;
    }
    NodeObatPerut* curr = perut->top;
    for (int i = len - 1; i >= 0; i--) {
        if (curr == NULL || curr->data.obat_id != resep[i]) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

void getResepObat(int penyakit, int* resep, int* len) {
    *len = 0;
    if (penyakit == ID_INVALID) {
        return;
    }

    for (int urutanKe = 1; urutanKe <= MAX_OBAT && *len < MAX_OBAT; urutanKe++) {
        for (int i = 0; i < jumlahMapObat; i++) {
            if (daftarMapObat[i].idPenyakit == penyakit && 
                daftarMapObat[i].urutan == urutanKe) {
                resep[(*len)++] = daftarMapObat[i].idObat;
                break;
            }
        }
    }
}

void clearListInventory(ListInventoryObat* list) {
    if (list == NULL) {
        return;
    }

    while (!isListInventoryEmpty(list)) {
        ItemObatPasien dummy;
        deleteAtListInventory(list, 0, &dummy);
    }
}

void F13_PulangDok(User* pasien_login, UserSet* set, Denah* denah) {
    printf(">>> PULANGDOK\n\n");

    if (pasien_login->diagnosisSekarang == ID_INVALID) {
        printf("Kamu belum menerima diagnosis dari dokter atau sesi pengobatan sudah selesai.\n");
        if (isListInventoryEmpty(&pasien_login->inventory_obat) && isStackPerutEmpty(&(pasien_login->perut_pasien))) {
            printf("Tidak ada resep aktif dan perut kosong. Kamu sudah boleh pulang.\n");
        }
        return;
    }

    if (!isListInventoryEmpty(&(pasien_login->inventory_obat))) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        printf("(Masih ada %d obat di inventory)\n\n", getCountListInventory(&(pasien_login->inventory_obat)));
        return;
    }


    int resep[100]; int nResep = 0;
    getResepObat(pasien_login->diagnosisSekarang, resep, &nResep);

    const char* namaPenyakit = getNamaPenyakit(pasien_login->diagnosisSekarang);
    if (namaPenyakit == NULL) {
        printf("Penyakit tidak valid\n");
    }

    if (nResep == 0 && isStackPerutEmpty(&(pasien_login->perut_pasien))) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Kamu sudah tidak memiliki obat yang harus diminum. Silahkan pulang!\n");
        return;
    } else if (!isObatSama(&(pasien_login->perut_pasien), resep, nResep)) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Maaf, tapi kamu belum minum obat sesuai resep!\n\n");

        printf("Urutan peminuman obat yang diharapkan:\n");
        if (nResep == 0) {
            printf("Tidak ada obat yang harus diminum.\n");
            return;
        } else {
            for (int i = 0; i < nResep; i++) {
                const char* namaObat = getNamaObat(resep[i]);
                printf("%s", namaObat ? namaObat : "Obat Tidak Dikenal");
                if (i < nResep - 1) {
                    printf(" -> "); 
                }  
            }
            printf("\n");
        }

        printf("\nUrutan obat yang kamu minum:\n");
        if (isStackPerutEmpty(&(pasien_login->perut_pasien))) {
            printf("Perut kosong.\n");
        } else {
            ItemObatPasien obatDiminumTemp[MAX_OBAT]; //temp copy stack urutan minum obat
            int jumlahObatDiminum = getCountStackPerut(&(pasien_login->perut_pasien));

            NodeObatPerut* curr = pasien_login->perut_pasien.top;
            int idxArray = jumlahObatDiminum - 1;

            while (curr != NULL && idxArray >= 0) {
                obatDiminumTemp[idxArray--] = curr->data;
                curr = curr->next;
            }

            for (int k = 0; k < jumlahObatDiminum; k++) {
                const char* namaObatDiPerut = getNamaObat(obatDiminumTemp[k].obat_id);
                printf("%s", namaObatDiPerut ? namaObatDiPerut : "Obat tidak valid");
                if (k < jumlahObatDiminum - 1) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
        printf("\n\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        return;
    } else {
        printf("Dokter sedang memeriksa keadaanmu...\n\n");
        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
    }

    initStackPerut(&(pasien_login->perut_pasien));
    //clearListInventory(&(pasien_login->inventory_obat));
    resetDiagnosis(denah, pasien_login->id);
    initListInventory(&(pasien_login->inventory_obat));

    pasien_login->diagnosisSekarang = ID_INVALID; // Reset diagnosis pasien

    //bonus AURA
    User* dokterYangBertugas = findUserById(set, idDokterYangBertugas);
    if (dokterYangBertugas != NULL && dokterYangBertugas->role == DOKTER) {
        dokterYangBertugas->aura ++; // bonus aura untuk dokter
    }

}