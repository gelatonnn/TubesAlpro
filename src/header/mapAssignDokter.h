#ifndef MAP_ASSIGN_DOKTER_H
#define MAP_ASSIGN_DOKTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_DOKTER 100
#define ID_INVALID -1
#define USERNAME_KOSONG ""

typedef struct {
    int idDokter;
    int idRuangan;
} DokterRuangan;

typedef struct {
    DokterRuangan map[MAX_DOKTER];
    int jumlahDokter;
} MapDokterRuangan;

void initMapDokterRuangan(MapDokterRuangan* map);
bool assignDokterToRuangan(MapDokterRuangan* map, int idDokter, int idRuangan);
bool unassignDokterFromRuangan(MapDokterRuangan* map, int idDokter);
int getRuanganByDokter(const MapDokterRuangan* map, int idDokter);
int getDokterByRuangan(const MapDokterRuangan* map, int idRuangan);
bool isDokterAssignedToRuangan(const MapDokterRuangan* map, int idDokter);
bool isRuanganAssignedToDokter(const MapDokterRuangan* map, int idRuangan);

#endif