#include "../header/diagnosisBerobat.h"

DataPenyakit daftarPenyakit[MAX_PENYAKIT];
int jumlahPenyakit = 0;
DataObat daftarObat[MAX_OBAT];
int jumlahObat = 0;
MapPenyakitObat daftarMapObat[MAX_OBAT];
int jumlahMapObat = 0;

//bonus AURA
int idDokterYangBertugas = ID_INVALID; // ID Dokter yang sedang bertugas

//inisialisasi penyakit
//translasi dari daftar Penyakit.csv
void initPenyakit(){
    jumlahPenyakit = 0;

    //penyakit 1 : influenza
    if (jumlahPenyakit < MAX_PENYAKIT) {
        DataPenyakit *p = &daftarPenyakit[jumlahPenyakit++];
        p->id = 1;
        strcpy(p->namaPenyakit, "Influenza");
        p->suhu_min = 36.0f; p->suhu_max = 38.5f;
        p->sistol_min = 90; p->sistol_max = 120;
        p->diastol_min = 60; p->diastol_max = 80;
        p->detak_min = 60; p->detak_max = 100;
        p->saturasi_min = 95.0f; p->saturasi_max = 100.0f;
        p->gula_min = 70; p->gula_max = 140;
        p->berat_min = 45.0f; p->berat_max = 90.0f;
        p->tinggi_min = 150; p->tinggi_max = 185;
        p->kolesterol_min = 150; p->kolesterol_max = 240;
        p->trombosit_min = 150; p->trombosit_max = 450;
    }

    //penyakit 2 : COVID 19
    if (jumlahPenyakit < MAX_PENYAKIT) {
        DataPenyakit *p = &daftarPenyakit[jumlahPenyakit++];
        p->id = 2;
        strcpy(p->namaPenyakit, "COVID 19");
        p->suhu_min = 36.0f; p->suhu_max = 39.0f;
        p->sistol_min = 90; p->sistol_max = 130;
        p->diastol_min = 60; p->diastol_max = 85;
        p->detak_min = 60; p->detak_max = 120;
        p->saturasi_min = 90.0f; p->saturasi_max = 100.0f;
        p->gula_min = 70; p->gula_max = 180;
        p->berat_min = 45.0f; p->berat_max = 90.0f;
        p->tinggi_min = 150; p->tinggi_max = 185;
        p->kolesterol_min = 150; p->kolesterol_max = 240;
        p->trombosit_min = 150; p->trombosit_max = 450;
    }

    //penyakit 3 : hipertensi
    if (jumlahPenyakit < MAX_PENYAKIT) {
        DataPenyakit *p = &daftarPenyakit[jumlahPenyakit++];
        p->id = 3;
        strcpy(p->namaPenyakit, "Hipertensi");
        p->suhu_min = 36.0f; p->suhu_max = 37.5f;
        p->sistol_min = 140; p->sistol_max = 180;
        p->diastol_min = 90; p->diastol_max = 120;
        p->detak_min = 60; p->detak_max = 100;
        p->saturasi_min = 90.0f; p->saturasi_max = 100.0f;
        p->gula_min = 70; p->gula_max = 140;
        p->berat_min = 45.0f; p->berat_max = 90.0f;
        p->tinggi_min = 150; p->tinggi_max = 185;
        p->kolesterol_min = 150; p->kolesterol_max = 240;
        p->trombosit_min = 150; p->trombosit_max = 450;
    }

    //penyakit 4 : diabetes mellitus
    if (jumlahPenyakit < MAX_PENYAKIT) {
        DataPenyakit *p = &daftarPenyakit[jumlahPenyakit++];
        p->id = 4;
        strcpy(p->namaPenyakit, "Diabetes Mellitus");
        p->suhu_min = 36.0f; p->suhu_max = 37.5f;
        p->sistol_min = 90; p->sistol_max = 140;
        p->diastol_min = 60; p->diastol_max = 90;
        p->detak_min = 60; p->detak_max = 100;
        p->saturasi_min = 90.0f; p->saturasi_max = 100.0f;
        p->gula_min = 126; p->gula_max = 200;
        p->berat_min = 45.0f; p->berat_max = 90.0f;
        p->tinggi_min = 150; p->tinggi_max = 185;
        p->kolesterol_min = 150; p->kolesterol_max = 240;
        p->trombosit_min = 150; p->trombosit_max = 450;
    }

    if (jumlahPenyakit < MAX_PENYAKIT) {
        DataPenyakit *p = &daftarPenyakit[jumlahPenyakit++];
        p->id = 5;
        strcpy(p->namaPenyakit, "Anemia");
        p->suhu_min = 36.0f; p->suhu_max = 37.0f;
        p->sistol_min = 90; p->sistol_max = 120;
        p->diastol_min = 60; p->diastol_max = 80;
        p->detak_min = 60; p->detak_max = 100;
        p->saturasi_min = 95.0f; p->saturasi_max = 100.0f;
        p->gula_min = 70; p->gula_max = 140;
        p->berat_min = 45.0f; p->berat_max = 90.0f;
        p->tinggi_min = 150; p->tinggi_max = 185;
        p->kolesterol_min = 150; p->kolesterol_max = 240;
        p->trombosit_min = 150; p->trombosit_max = 450;
    }
}

//inisialisasi obat
//translasi dari daftar Obat.csv
void initObat() {
    jumlahObat = 0;

    //obat 1 
    if (jumlahObat < MAX_OBAT) {
        DataObat *o = &daftarObat[jumlahObat++];
        o->idObat = 1;
        strcpy(o->namaObat, "Oseltamivir");
    }

    //obat 2
    if (jumlahObat < MAX_OBAT) {
        DataObat *o = &daftarObat[jumlahObat++];
        o->idObat = 2;
        strcpy(o->namaObat, "Vitamin C"); 
    }

    //obat 3
    if (jumlahObat < MAX_OBAT) {
        DataObat *o = &daftarObat[jumlahObat++];
        o->idObat = 3;
        strcpy(o->namaObat, "Remdesivir");
    }

    //obat 4
    if (jumlahObat < MAX_OBAT) {
        DataObat *o = &daftarObat[jumlahObat++];
        o->idObat = 4;
        strcpy(o->namaObat, "Lisinopril");
    }

    //obat 5
    if (jumlahObat < MAX_OBAT) {
        DataObat *o = &daftarObat[jumlahObat++];
        o->idObat = 5;
        strcpy(o->namaObat, "Metformin");
    }

    jumlahMapObat = 0;
    //mapping penyakit ke obat
    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 1;
        map->idObat = 1;
        map->urutan = 1;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 1;
        map->idObat = 2;
        map->urutan = 2;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 2;
        map->idObat = 3;
        map->urutan = 1;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 3;
        map->idObat = 4;
        map->urutan = 1;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 4;
        map->idObat = 5;
        map->urutan = 1;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 5;
        map->idObat = 3;
        map->urutan = 1;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 5;
        map->idObat = 4;
        map->urutan = 3;
    }

    if (jumlahMapObat < MAX_OBAT) {
        MapPenyakitObat *map = &daftarMapObat[jumlahMapObat++];
        map->idPenyakit = 5;
        map->idObat = 5;
        map->urutan = 2;
    }
}

//getter nama penyakit
const char* getNamaPenyakit(int id){
    for (int i = 0; i < jumlahPenyakit; i++) {
        if (daftarPenyakit[i].id == id) {
            return daftarPenyakit[i].namaPenyakit;
        }
    }
    return NULL;
}

//getter nama obat
const char* getNamaObat(int id){
    for (int i = 0; i < jumlahObat; i++) {
        if (daftarObat[i].idObat == id) {
            return daftarObat[i].namaObat;
        }
    }
    return NULL;
}


void diagnosisPasien(User* dokter,Denah* denah, MapDokterRuangan* mapDokter,UserSet* set){
    if (dokter == NULL || denah == NULL || mapDokter == NULL || set == NULL) {
        return; //
    }

    printf(">>> DIAGNOSIS\n");

    int idRuangan = getRuanganByDokter(mapDokter, dokter->id);
    if (idRuangan == ID_INVALID || idRuangan > denah->jumlahRuangan) {
        printf("Anda tidak memiliki ruangan yang valid!\n");
        return; 
    }

    Ruangan* ruangan = &denah->ruangan[idRuangan - 1];
    Queue* antrian = &ruangan->antrianPasien;
    if (isQueueEmpty(antrian)) {
        printf("Tidak ada pasien untuk diperiksa!\n");
        return;
    }

    EntriAntrianCheckup* pasien = &antrian->front->data;
    DataCheckUp d = pasien->dataCheckUp;
    pasien->idPenyakit = ID_INVALID; // ID penyakit yang didiagnosis 
    char namaPenyakit[MAX_LEN_PENYAKIT] = "";

    for (int i = 0; i < jumlahPenyakit; i++) {
        DataPenyakit p = daftarPenyakit[i];
        bool suhuCocok = (d.suhuTubuh >= p.suhu_min && d.suhuTubuh <= p.suhu_max);
        bool sistolCocok = (d.tekananDarahSistol >= p.sistol_min && d.tekananDarahSistol <= p.sistol_max);
        bool diastolCocok = (d.tekananDarahDiastol >= p.diastol_min && d.tekananDarahDiastol <= p.diastol_max);
        bool detakCocok = (d.detakJantung >= p.detak_min && d.detakJantung <= p.detak_max);
        bool saturasiCocok = (d.saturasiOksigen >= p.saturasi_min && d.saturasiOksigen <= p.saturasi_max);
        bool gulaCocok = (d.kadarGulaDarah >= p.gula_min && d.kadarGulaDarah <= p.gula_max);
        bool beratCocok = (d.beratBadan >= p.berat_min && d.beratBadan <= p.berat_max);
        bool tinggiCocok = (d.tinggiBadan >= p.tinggi_min && d.tinggiBadan <= p.tinggi_max);
        bool kolesterolCocok = (d.kadarKolesterolTotal >= p.kolesterol_min && d.kadarKolesterolTotal <= p.kolesterol_max);
        bool kolesterolLDLCocok = (d.kadarKolesterolLDL >= p.kolesterol_min && d.kadarKolesterolLDL <= p.kolesterol_max);
        bool trombositCocok = (d.trombosit >= p.trombosit_min && d.trombosit <= p.trombosit_max);

        if (suhuCocok && sistolCocok && diastolCocok && detakCocok && saturasiCocok && gulaCocok && beratCocok && tinggiCocok && kolesterolCocok && kolesterolLDLCocok && trombositCocok) {
            pasien->idPenyakit = p.id;
            strcpy(namaPenyakit, p.namaPenyakit);
            break;
        }
    }

    User* infoPasien = findUserById(set, pasien->idPasien);
    if (infoPasien != NULL) {
        infoPasien->diagnosisSekarang = pasien->idPenyakit; // Update diagnosis terakhir pasien
        if (pasien->idPenyakit != ID_INVALID) { 
            printf("%s terdiagnosa penyakit %s!\n", infoPasien->username, namaPenyakit);
        } else {
            printf("%s tidak terdiagnosis penyakit apapun!\n", infoPasien->username);
        }
    }
}
    
void berobatPasien(User* dokter,Denah* denah,MapDokterRuangan* mapDokter,UserSet* set){
    if (dokter == NULL || set == NULL || mapDokter == NULL || denah == NULL) {
        return;
    }

    printf(">>> BEROBAT\n");
    printf("Dokter sedang mengobati pasien!\n");

    int idRuangan = getRuanganByDokter(mapDokter, dokter->id);
    if (idRuangan == ID_INVALID || idRuangan > denah->jumlahRuangan) {
        return;
    }

    Ruangan* ruangan = &denah->ruangan[idRuangan - 1];
    Queue* antrian = &ruangan->antrianPasien;
    if (isQueueEmpty(antrian)) {
        printf("Tidak ada pasien dalam antrian!\n");
        return;
    }

    EntriAntrianCheckup pasien;

    if (!dequeue(antrian, &pasien)) {
        printf("Gagal mendapatkan pasien dari antrian!\n");
        return; 
    }


    User* infoPasien = findUserById(set, pasien.idPasien);
    if (infoPasien == NULL) {
        printf("Pasien tidak ditemukan!\n");
        return; 
    }

    if (pasien.idPenyakit == ID_INVALID) {
        printf("Pasien tidak memiliki penyakit!\n");
        printf("Pasien belum di diagnosis!\n");
        initListInventory(&(infoPasien->inventory_obat));
    } else {
        const char* namaPenyakit = getNamaPenyakit(pasien.idPenyakit);
        if (infoPasien != NULL && namaPenyakit != NULL) {
            printf("Pasien %s memiliki penyakit %s.\n",
                   infoPasien->username, namaPenyakit);
        } 

        printf("Obat yang harus diberikan:\n");

        initListInventory(&(infoPasien->inventory_obat));

        bool adaResepObat = false; //checker
        for (int urutanObat = 1; urutanObat <= MAX_OBAT; urutanObat++) {
            for (int i = 0; i < jumlahMapObat; i++) {
                if (daftarMapObat[i].idPenyakit == pasien.idPenyakit && daftarMapObat[i].urutan == urutanObat) {
                    ItemObatPasien itemResep;
                    itemResep.obat_id = daftarMapObat[i].idObat;
                    insertLastListInventory(&(infoPasien->inventory_obat), itemResep);

                    //print obat yang diresepkan
                    adaResepObat = true;
                    printf(" %d. %s\n", urutanObat, getNamaObat(daftarMapObat[i].idObat));
                    break;
                }
            }
        }
    
        if (!adaResepObat) {
            printf("Tidak ada obat yang diresepkan untuk penyakit ini.\n");
        } //checker placeholder
    }

    if (infoPasien != NULL) {
        if (pasien.idPenyakit != ID_INVALID){
            printf("Pasien %s telah selesai berobat.\n", infoPasien->username);
        } else {
            printf("Pasien %s tidak memiliki penyakit yang terdiagnosis.\n", infoPasien->username);
        }
    }

    idDokterYangBertugas = dokter->id; // Update ID Dokter yang sedang bertugas
}