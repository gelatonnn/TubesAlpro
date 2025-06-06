#include "../header/antrian.h"

void lihatStatusAntrian(UserSet* set, Denah* denah, MapDokterRuangan* mapDokter, User* currentUser) {
    if (currentUser == NULL || set == NULL || denah == NULL || mapDokter == NULL) {
        printf("Ndak iso :(\n");
        return;
    }

    if (currentUser->role != PASIEN) {
        printf("Selain pasien tidak bisa melihat status antrian\n");
        return;
    }

    printf(">>> ANTRIAN\n\n");

    bool found = false;

    for (int i = 0; i < denah->jumlahRuangan; i++) {
        Queue* antrian = &denah->ruangan[i].antrianPasien;

        if (isQueueEmpty(antrian)) {
            continue;
        }

        int posisi = getPosisiPasien(antrian, currentUser->id); 
        if (posisi != -1) {
            int total = getSize(antrian);
            int kapasitas = denah->kapasitas;
            int idDokter = getDokterByRuangan(mapDokter, denah->ruangan[i].idRuangan);
            User* dokter = findUserById(set, idDokter);

            
            printf("Status antrian Anda:\n");
            printf("Dokter: %s%s\n",
                   (dokter && dokter->role == DOKTER) ? "Dr. " : "",
                   dokter ? dokter->username : "???");

            
            printf("Ruangan: %d\n",
                   denah->ruangan[i].idRuangan);

            
            if (posisi <= kapasitas) {
                printf("Anda sedang berada di dalam ruangan dokter!\n"); //revisi
            } else {
                printf("Posisi antrian: %d dari %d\n", posisi - kapasitas, total - kapasitas);
            }

            found = true;
            break;
        }
    }

    if (!found) {
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }
}
