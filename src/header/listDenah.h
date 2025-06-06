#ifndef LIST_DENAH_H
#define LIST_DENAH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "queueAntri.h"
#include "mapAssignDokter.h"
#include "dataCheckup.h"

#define MAX_PASIEN 100 // Asumsi maksimal jumlah pasien
#define MAX_RUANGAN 100 // Asumsi maksimal jumlah ruangan
#define ID_INVALID -1

typedef struct {
    int idRuangan;
    int idDokter;
    Queue antrianPasien;
} Ruangan;

typedef struct {
    Ruangan ruangan[MAX_RUANGAN];
    int jumlahRuangan; // Panjang list ruangan
    int kapasitas; // Kapasitas maksimum list ruangan
} Denah;

void initDenah(Denah* denah, int jumlahRuangan, int kapasitas);
int getPanjangDenah(const Denah* denah);
int getKapasitasDenah(const Denah* denah);
void lihatDenah(const Denah *denah);
void lihatRuangan(Denah *denah, int idRuangan, const UserSet* set, const MapDokterRuangan* map);

#endif