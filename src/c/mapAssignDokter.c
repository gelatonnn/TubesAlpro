#include "../header/mapAssignDokter.h"

//inisialisasi map dokter ruangan
void initMapDokterRuangan(MapDokterRuangan* map){
    if (map == NULL) {
        return; //invalid
    }

    map->jumlahDokter = 0;
    for (int i =0; i < MAX_DOKTER; i++) {
        map->map[i].idDokter = ID_INVALID;
        map->map[i].idRuangan = ID_INVALID;
    }
}

//nambah dokter ke ruangan
// buat command manager
bool assignDokterToRuangan(MapDokterRuangan* map, int idDokter, int idRuangan){
    if (map == NULL || idDokter == ID_INVALID || idRuangan == ID_INVALID) {
        return false; // invalid
    }

    if (map->jumlahDokter >= MAX_DOKTER) {
        return false; // full
    }

    if (isDokterAssignedToRuangan(map, idDokter)) {
        return false; // dokter sudah ada di ruangan
    }

    if (isRuanganAssignedToDokter(map, idRuangan)) {
        return false; // ruangan sudah ada di dokter
    }

    map->map[map->jumlahDokter].idDokter = idDokter;
    map->map[map->jumlahDokter].idRuangan = idRuangan;
    map->jumlahDokter++;

    return true;
}

// hapus dokter dari ruangan
bool unassignDokterFromRuangan(MapDokterRuangan* map, int idDokter){
    if (map == NULL || idDokter == ID_INVALID) {
        return false; // invalid
    }

    int idxFound = -1;
    for (int i = 0; i < map->jumlahDokter; i++) {
        if (map->map[i].idDokter == idDokter) {
            idxFound = i;
            break;
        }
    }

    if (idxFound != -1) {
        if (idxFound < map->jumlahDokter - 1) {
            map->map[idxFound] = map->map[map->jumlahDokter - 1];
        }
        map->map[map->jumlahDokter - 1].idDokter = ID_INVALID;
        map->map[map->jumlahDokter - 1].idRuangan = ID_INVALID;
        map->jumlahDokter--;
        return true;
    } else {
        return false;
    }
}

// getter id ruangan berdasarkan id dokter
int getRuanganByDokter(const MapDokterRuangan* map, int idDokter){
    if (map == NULL || idDokter == ID_INVALID) {
        return ID_INVALID; // invalid
    }

    for (int i = 0; i < map->jumlahDokter; i++) {
        if (map->map[i].idDokter == idDokter) {
            return map->map[i].idRuangan;
        }
    }

    return ID_INVALID;
}

// getter id dokter berdasarkan id ruangan
int getDokterByRuangan(const MapDokterRuangan* map, int idRuangan){
    if (map == NULL || idRuangan == ID_INVALID) {
        return ID_INVALID; // invalid
    }

    for (int i = 0; i < map->jumlahDokter; i++) {
        if (map->map[i].idRuangan == idRuangan) {
            return map->map[i].idDokter;
        }
    }

    return ID_INVALID;
}

//cek apakah dokter ada di ruangan
bool isDokterAssignedToRuangan(const MapDokterRuangan* map, int idDokter){
    return getRuanganByDokter(map, idDokter) != ID_INVALID;
}

//cek apakah ruangan ada di dokter
bool isRuanganAssignedToDokter(const MapDokterRuangan* map, int idRuangan){
    return getDokterByRuangan(map, idRuangan) != ID_INVALID;
}

