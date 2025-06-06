#include "../header/tambahDokter.h"

//daftarin dokter
void managerTambahDokter(UserSet* set){
    if (set == NULL) {
        return;
    }

    char username[MAX_LEN];
    char password[MAX_LEN];

    printf(">>> TAMBAH_DOKTER\n");

    printf("Username: ");
    if (fgets(username, MAX_LEN, stdin) == NULL) {
        printf("Gagal membaca input.\n");
        return;
    }
    username[strcspn(username, "\n")] = '\0';

    //cek di hard codednya
    User* existingUser = findUserByUsername(set, username);
    if (existingUser != NULL) {
        if (existingUser->role == DOKTER) {
            printf("Username %s sudah terdaftar sebagai dokter.\n", username);
        } else {
            printf("Username %s sudah terdaftar.\n", username);
        }
        return;
    }

    printf("Password: ");
    if (fgets(password, MAX_LEN, stdin) == NULL) {
        printf("Gagal membaca input.\n");
        return;
    }
    password[strcspn(password, "\n")] = '\0';
    
    //berhasil daftar
    registerUser(set, username, password, DOKTER);
}

//assign dokter ke ruangan with check
void assignDokter(MapDokterRuangan* map, Denah* denah, UserSet* set){

    char username[MAX_LEN];
    int idRuangan;

    printf(">>> ASSIGN_DOKTER\n");
    printf("Username: ");
    if (fgets(username, MAX_LEN, stdin) == NULL) {
        printf("Gagal membaca input.\n");
        return;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("ID Ruangan : ");
    scanf("%d", &idRuangan);

    //validasi dokter
    User* dokter = findUserByUsername(set, username);
    if (dokter == NULL || dokter->role != DOKTER) {
        printf("Dokter dengan username %s tidak ditemukan.\n", username);
        return;
    }

    if (dokter->role != DOKTER) {
        printf("Username %s bukan dokter.\n", username);
        return;
    }

    //validasi ruangan
    Ruangan *ruangan = &denah->ruangan[idRuangan - 1];
    if (ruangan == NULL) {
        printf("Ruangan dengan ID %d tidak ditemukan.\n", idRuangan);
        return;
    }

    //yang ada di map
    int ruanganSekarang = getRuanganByDokter(map, dokter->id);
    int dokterSekarang = getDokterByRuangan(map, idRuangan);
    User* dokterDiRuanganItu = findUserById(set, dokterSekarang);
    const char* namaDokterDiRuanganItu = (dokterDiRuanganItu != NULL) ? dokterDiRuanganItu->username : "";

    //KASUS 4 :
    //ruangan udah ditempatin dokter lain dan dokter yang diinput udah di tempat lain
    if (ruanganSekarang != ID_INVALID && dokterSekarang != ID_INVALID) {
        printf("\nDokter %s sudah ada di ruangan %d!\n", dokter->username, ruanganSekarang);
        printf("Ruangan %d juga sudah ditempati dokter %s!\n", idRuangan, namaDokterDiRuanganItu);
        return;
    }

    //KASUS 2 :
    //dokter sudah bertugas di ruangan lain
    //ruangan kosong
    if (ruanganSekarang != ID_INVALID) {
        printf("\nDokter %s sudah diassign ke ruangan %d!\n", dokter->username, ruanganSekarang);
        return;
    }

    //KASUS 3 :
    //ruangan sudah ditempati dokter lain
    //dokter kosong
    if (dokterSekarang != ID_INVALID && dokterSekarang != dokter->id) {
        printf("\nDokter %s sudah menempati ruangan %d!\n", namaDokterDiRuanganItu, idRuangan);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", dokter->username);
        return;
    }

    //KASUS 1 :
    //berhasil assign
    if (assignDokterToRuangan(map, dokter->id, idRuangan)) {
        printf("\nDokter %s berhasil diassign ke ruangan %d!\n", username, idRuangan);
    }
}