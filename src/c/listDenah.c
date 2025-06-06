#include "../header/listDenah.h"

//inisialisasi denah
void initDenah(Denah* denah, int jumlahRuangan, int kapasitas){
    if (denah == NULL) {
        return; //pointer ke null
    }

    if (jumlahRuangan < 0 || kapasitas < 0) { //invalid
        denah->jumlahRuangan = 0;
        return;
    } 

    denah->jumlahRuangan = jumlahRuangan;
    denah->kapasitas = kapasitas;

    for (int i = 0; i < jumlahRuangan; i++) {
        denah->ruangan[i].idDokter = ID_INVALID;
        denah->ruangan[i].idRuangan = i + 1; // ID ruangan mulai dari 1
        initQueue(&denah->ruangan[i].antrianPasien);
    }
}


//fungsi get panjang denah
int getPanjangDenah(const Denah* denah){
    if (denah == NULL) {
        return 0;
    }
    return denah->jumlahRuangan;
}

//fungsi get kapasitas denah
int getKapasitasDenah(const Denah* denah){
    if (denah == NULL) {
        return 0;
    }
    return denah->kapasitas;
}

//fungsi untuk menampilkan denah
void lihatDenah(const Denah *denah){
    if (denah == NULL || denah->jumlahRuangan == 0) {
        printf("Tidak ada ruangan\n");
        return;
    }

    printf(">>> LIHAT_DENAH\n");
    //atas
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        printf("+-----");
    }
    printf("+\n");

    //isi
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        printf("|  %d  ", i+1);
    }
    printf("|\n");

    //bawah
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        printf("+-----");
    }
    printf("+\n");
}

void lihatRuangan(Denah *denah, int idRuangan, const UserSet* set, const MapDokterRuangan* map){
    if (denah == NULL || set == NULL || map == NULL) {
        return;
    }
    
    int idxRuangan = idRuangan - 1;

    printf(">>> LIHAT_RUANGAN %d\n", idRuangan);
    printf("\n--- Detail Ruangan %d ---\n", idRuangan);
    printf("Kapasitas  : %d\n", denah->kapasitas);

    int idDokterdiRuangan = getDokterByRuangan(map, idRuangan);
    //dokter
    printf("Dokter     : ");
    if (idDokterdiRuangan != ID_INVALID) {
        User* dokter = findUserById(set, idDokterdiRuangan);
        if (dokter != NULL) {
            printf("Dokter %s\n", dokter->username);
        }
    } else {
        printf("-\n");
    }

    const Ruangan* ruangPasien = &denah->ruangan[idxRuangan];
    Node* current = ruangPasien->antrianPasien.front;
    int nomorAntri = 0;
    
    printf("\nPasien di dalam ruangan :\n");
    for (int i = 0; current != NULL && i < denah->kapasitas; i++) {
        User* pasien = findUserById(set, current->data.idPasien);
        if (pasien != NULL) {
            printf("  %d. %s\n", i + 1, pasien->username);
            nomorAntri++;
        } else {
            printf("  %d. (Data pasien ID: %d tidak ditemukan)\n", i + 1, current->data.idPasien);
        }
        current = current->next;
    }

    if (nomorAntri == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    
    printf("------------------------------\n");
}

