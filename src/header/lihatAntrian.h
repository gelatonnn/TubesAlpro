#ifndef LIHAT_ANTRIAN_H
#define LIHAT_ANTRIAN_H

#include "auth.h"
#include "listDenah.h"
#include "mapAssignDokter.h"

void lihatSemuaAntrian(const Denah* denah, const UserSet* set, const MapDokterRuangan* mapDokter);

#endif // LIHAT_ANTRIAN_H