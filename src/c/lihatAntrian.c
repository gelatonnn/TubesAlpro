#include "../header/lihatAntrian.h"
#include <stdio.h>
#include <string.h>

void lihatSemuaAntrian(const Denah* denah, const UserSet* set, const MapDokterRuangan* mapDokter){
    if (denah == NULL || set == NULL || mapDokter == NULL) {
        return;
    }

    printf(">>> LIHAT_SEMUA_ANTRIAN\n\n");

    //tampilkan denah
    printf("Denah Ruangan:\n");
    lihatDenah(denah);
    printf("\n");

    if (denah->jumlahRuangan == 0) {
        printf("Tidak ada ruangan yang tersedia.\n");
        return;
    }

    //detail ruangan yang tidak kosong
    bool adaDetailRuangan = false;
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        const Ruangan* ruang = &denah->ruangan[i];
        int idRuangan = ruang->idRuangan;
        int idDokter = getDokterByRuangan(mapDokter, idRuangan);

        //ada dokter ATAU ada pasien di dalam ATAU ada pasien di antrian
        if ((idDokter != ID_INVALID) || !isQueueEmpty(&(ruang->antrianPasien))) {
            adaDetailRuangan = true;
            printf("===========%d===========\n", ruang->idRuangan);
            printf("Kapasitas  : %d\n", denah->kapasitas);

            //dokter
            printf("Dokter     : ");
            if (idDokter != ID_INVALID) {
                User* dokter = findUserById(set, idDokter);
                if (dokter != NULL) {
                    printf("Dr. %s\n", dokter->username);
                } else {
                    printf("-\n");
                }
            } else {
                printf("-\n");
            }

            //pasien di dalam ruangan
            Node* current = ruang->antrianPasien.front;
            int nomorAntri = 0;

            printf("\nPasien di dalam ruangan:\n");
            int loopTampil = 0;

            for (nomorAntri = 0; current != NULL && loopTampil < denah->kapasitas; nomorAntri++) {
                User* pasien = findUserById(set, current->data.idPasien);
                if (pasien != NULL) {
                    printf("  %d. %s\n", nomorAntri + 1, pasien->username);
                    loopTampil++;
                }
                current = current->next;
            }

            if (loopTampil == 0) {
                printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
            }

            //pasien di antrian
            printf("\nPasien di antrian:\n");
            int loopAntri = 1;
            bool adaAntrian = false;
            while (current != NULL) {
                User* pasienAntri = findUserById(set, current->data.idPasien);
                if (pasienAntri != NULL) {
                    printf("  %d. %s\n", loopAntri, pasienAntri->username);
                    adaAntrian = true;
                }
                current = current->next;
                loopAntri++;
            }

            if (!adaAntrian) {
                printf("  Tidak ada pasien di antrian saat ini.\n");
            }
            printf("------------------------------\n\n");
        }
    }

    if (!adaDetailRuangan && denah->jumlahRuangan > 0) {
        printf("Semua ruangan tidak ditemukan atau kosong.\n");
    }
}