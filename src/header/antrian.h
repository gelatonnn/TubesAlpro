#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "auth.h"             
#include "queueAntri.h"            
#include "listDenah.h"            
#include "mapAssignDokter.h"       

//lihat antrian
void lihatStatusAntrian(UserSet* set, Denah* denah, MapDokterRuangan* mapDokter, User* currentUser);

#endif
