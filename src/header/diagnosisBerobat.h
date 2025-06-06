#ifndef DIAGNOSIS_BEROBAT_H
#define DIAGNOSIS_BEROBAT_H

#include "../header/queueAntri.h"
#include "../header/dataCheckup.h"
#include "../header/listDenah.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMA_OBAT 50
#define MAX_OBAT 10
#define MAX_LEN_PENYAKIT 100
#define MAX_PENYAKIT 20

typedef struct {
    int id;
    char namaPenyakit[MAX_LEN_PENYAKIT];
    float suhu_min, suhu_max;
    int sistol_min, sistol_max;
    int diastol_min, diastol_max;
    int detak_min, detak_max;
    float saturasi_min, saturasi_max;
    int gula_min, gula_max;
    float berat_min, berat_max;
    int tinggi_min, tinggi_max;
    int kolesterol_min, kolesterol_max;
    int trombosit_min, trombosit_max;
} DataPenyakit;

typedef struct {
    int idObat;
    char namaObat[MAX_NAMA_OBAT];
} DataObat;

typedef struct {
    int idPenyakit;
    int idObat;
    int urutan;
} MapPenyakitObat;

void initPenyakit();
void initObat();
const char* getNamaPenyakit(int id);
const char* getNamaObat(int id);
void diagnosisPasien(User* dokter,Denah* denah,MapDokterRuangan* mapDokter,UserSet* set);
void berobatPasien(User* dokter,Denah* denah,MapDokterRuangan* mapDokter,UserSet* set) ;

#endif // DIAGNOSIS_BEROBAT_H