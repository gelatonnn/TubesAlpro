#ifndef DAFTAR_CHECK_UP_H
#define DAFTAR_CHECK_UP_H

#include "auth.h"
#include "dataCheckup.h"
#include "listDenah.h"
#include "mapAssignDokter.h"
#include "queueAntri.h"

void clearInputBuffer();
float getPositiveFloat(const char* inputF);
int getPositiveInt(const char* inputI);
void getPositiveTekananDarah(const char* inputTD, int* sistol, int* diastol);
bool isPasienTerdaftar(Denah* denah, int idPasien);
void daftarCheckUp(UserSet* set,
                   Denah* denah,
                   MapDokterRuangan* mapDokter,
                   User* currentUser);//user yg login

#endif // DAFTAR_CHECK_UP_H