#include "../header/daftarCheckUp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//validasi input tipe data floar
float getPositiveFloat(const char* inputF){
    float value;
    char buff[100];
    while (true) {
        printf("%s: ", inputF);
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            printf("Gagal membaca input.\n");
            return -1.0f;
        }

        if (sscanf(buff, "%f", &value) == 1) {
            if (value > 0) {
                return value;
            } else {
                printf("Input tidak valid. Silakan masukkan angka positif.\n");
            }
        } else {
            printf("Input tidak valid. Silakan masukkan angka.\n");
        }
    }
}

//validasi input tipe data int
int getPositiveInt(const char* inputI){
    int value;
    char buff[100];
    while (true) {
        printf("%s: ", inputI);
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            printf("Gagal membaca input.\n");
            return -1;
        }

        if (sscanf(buff, "%d", &value) == 1) {
            if (value > 0) {
                return value;
            } else {
                printf("Input tidak valid. Silakan masukkan angka positif.\n");
            }
        } else {
            printf("Input tidak valid. Silakan masukkan angka.\n");
        }
    }
}

//validasi input tekanan darah
void getPositiveTekananDarah(const char* inputTD, int* sistol, int* diastol){
    char buff[100];
    int tempsistol, tempdiastol;
    int item;

    while (true) {
        printf("%s: ", inputTD);
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            printf("Gagal membaca input.\n");
            *sistol = -1;
            *diastol = -1;
            return;
        }

        item = sscanf(buff, "%d %d", &tempsistol, &tempdiastol);
        if (item == 2) {
            if (tempsistol > 0 && tempdiastol > 0) {
                *sistol = tempsistol;
                *diastol = tempdiastol;
                return;
            } else {
                printf("Input tidak valid. Silakan masukkan angka positif.\n");
            }
        } else {
            printf("Input tidak valid. Silakan masukkan dua angka (sistol diastol).\n");
        }
    }
}

//cek apakah pasien terdaftar
bool isPasienTerdaftar(Denah* denah, int idPasien){
    if (denah == NULL || idPasien <= 0) {
        return false;
    }
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        if (getPosisiPasien(&denah->ruangan[i].antrianPasien, idPasien) != -1) {
            return true;
        }
    }

    return false;
}

void daftarCheckUp(UserSet* set,Denah* denah, MapDokterRuangan* mapDokter, User* currentUser){
    if (current_user == NULL) {
        printf("Anda harus login terlebih dahulu.\n");
        return;
    }

    if (current_user->role != PASIEN) {
        printf("Hanya pasien yang dapat melakukan pendaftaran check-up.\n");
        return;
    }

    printf(">>> DAFTAR CHECK-UP\n\n");

    //KASUS 2 : pasien udah terdaftar
    if (isPasienTerdaftar(denah, current_user->id)) {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    //KASUS 1 dan 3 : pasien belum terdaftar
    printf("Silakan masukkan data check-up Anda:\n");
    DataCheckUp dataInput = createDataCheckUp(current_user->id);
    float suhuTubuh, saturasi, beratBadan, tinggiBadan;
    int sistol, diastol, detakJantung, kadarGula, kolesterolTotal, kolesterolLDL, trombosit;

    //validasi input
    suhuTubuh = getPositiveFloat("Suhu Tubuh (Celcius)");
    if (suhuTubuh == -1.0f) {
        return;
    }

    getPositiveTekananDarah("Tekanan Darah (Sistol/Diastol, contoh 120 80)", &sistol, &diastol);
    if (sistol == -1 || diastol == -1) {
        return;
    }

    detakJantung = getPositiveInt("Detak Jantung (bpm)");
    if (detakJantung == -1) {
        return;
    }

    saturasi = getPositiveFloat("Saturasi Oksigen (%)");
    if (saturasi == -1.0f) {
        return;
    }

    kadarGula = getPositiveInt("Kadar Gula Darah (mg/dL)");
    if (kadarGula == -1) {
        return;
    }

    beratBadan = getPositiveFloat("Berat Badan (kg)");
    if (beratBadan == -1.0f) {
        return;
    }

    tinggiBadan = getPositiveInt("Tinggi Badan (cm)");
    if (tinggiBadan == -1.0) {
        return;
    }

    kolesterolTotal = getPositiveInt("Kadar Kolesterol Total (mg/dL)");
    if (kolesterolTotal == -1) {
        return;
    }

    kolesterolLDL = getPositiveInt("Kadar Kolesterol LDL (mg/dL)");
    if (kolesterolLDL == -1) {
        return;
    }

    trombosit = getPositiveInt("Trombosit (ribu/µL)");
    if (trombosit == -1) {
        return;
    }

    //set data checkup
    setDataCheckUp(&dataInput, suhuTubuh, sistol, diastol, detakJantung, saturasi, kadarGula, beratBadan, tinggiBadan, kolesterolTotal, kolesterolLDL, trombosit);

    //menampilkan dokter yang tersedia   
    printf("\nBerikut adalah daftar dokter yang tersedia:\n");
    int dokterTersedia = 0;
    int listDokterTersedia[MAX_DOKTER];
    int listRuanganTersedia[MAX_DOKTER];

    for (int i = 0; i < set->jumlahUser; i++) {
        if (set->users[i].role == DOKTER) {
            User dokter = set->users[i];
            int idRuangan = getRuanganByDokter(mapDokter, dokter.id);
            
            //cek dokter keassign ke ruangan yang valid
            if (idRuangan != ID_INVALID && idRuangan > 0 && idRuangan <= denah->jumlahRuangan) {
                dokterTersedia++;
                if (dokterTersedia < MAX_DOKTER) {
                    listDokterTersedia[dokterTersedia - 1] = dokter.id;
                    listRuanganTersedia[dokterTersedia - 1] = idRuangan;

                    //akses queue pasien
                    Ruangan* ruanganDokter = &denah->ruangan[idRuangan - 1];
                    int jumlahAntrianPasien = getSize(&(ruanganDokter->antrianPasien));
                    printf("%d. Dr. %s - Spesialisasi Umum - Ruangan %d (Antrian: %d orang) - Aura %d\n",
                           dokterTersedia, dokter.username, idRuangan, jumlahAntrianPasien, dokter.aura);
                } else {
                    break;
                }
            }
        }
    }

    if (dokterTersedia == 0) {
        printf("Maaf, tidak ada dokter yang tersedia saat ini.\n");
        return;
    }

    //pilih dokter
    int pilihanDokter;
    while (true) {
        printf("\nPilih dokter (1-%d): ", dokterTersedia);
        char buffPilihan[20];
        if (fgets(buffPilihan, sizeof(buffPilihan), stdin) == NULL) {
            printf("Gagal membaca input.\n");
            return;
        }

        if (sscanf(buffPilihan, "%d", &pilihanDokter) == 1 && pilihanDokter >= 1 && pilihanDokter <= dokterTersedia) {
            break;
        } else {
            printf("Input tidak valid. Silakan pilih dokter yang tersedia.\n");
        }
    }

    int idDokterDipilih = listDokterTersedia[pilihanDokter - 1];
    int idRuanganDipilih = listRuanganTersedia[pilihanDokter - 1];
    User* dokterDipilih = findUserById(set, idDokterDipilih); //getter nama dokter
    Ruangan* ruanganDipilih = &denah->ruangan[idRuanganDipilih - 1]; //getter ruangan

    //assign ruangan atau antrian
    EntriAntrianCheckup entriPasien;
    entriPasien.idPasien = current_user->id;

    entriPasien.nomorAntri = getSize(&(ruanganDipilih->antrianPasien)) + 1;
    entriPasien.dataCheckUp = dataInput;
    entriPasien.idPenyakit = -1;

    if (enqueue(&(ruanganDipilih->antrianPasien), entriPasien)) {
        printf("\nPendaftaran check-up berhasil!\n");
        if (dokterDipilih != NULL) {
            printf("Anda telah terdaftar untuk check-up dengan Dr. %s di Ruangan %d.\n", 
                dokterDipilih->username, idRuanganDipilih);
            printf("Posisi antrian Anda: %d\n", entriPasien.nomorAntri);
        }
    } else {
        printf("Gagal mendaftar ke dalam antrian.\n");
        return;
    }
}
