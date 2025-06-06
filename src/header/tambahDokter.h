#ifndef TAMBAH_DOKTER_H
#define TAMBAH_DOKTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/listDenah.h"
#include "../header/mapAssignDokter.h"
#include "../header/auth.h"

#define MAX_LEN 50

void managerTambahDokter(UserSet* set);
void assignDokter(MapDokterRuangan* map, Denah* denah, UserSet* set);

#endif // TAMBAH_DOKTER_H