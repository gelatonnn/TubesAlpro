#ifndef DATA_CHECKUP_H
#define DATA_CHECKUP_H

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef int id;

typedef struct {
    id idPasien;
    float suhuTubuh;
    int tekananDarahSistol;
    int tekananDarahDiastol;
    int detakJantung;
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan;
    float tinggiBadan;
    int kadarKolesterolTotal;
    int kadarKolesterolLDL;
    int trombosit;
} DataCheckUp;

typedef struct {
    int idPasien;
    int nomorAntri;
    DataCheckUp dataCheckUp;
    int idPenyakit; // -1 jika tidak terdiagnosis penyakit
} EntriAntrianCheckup;

DataCheckUp createDataCheckUp(id idPasien);
bool setDataCheckUp(DataCheckUp *data, float suhuTubuh, int tekananDarahSistol, int tekananDarahDiastol, int detakJantung, float saturasiOksigen, int kadarGulaDarah, float beratBadan, float tinggiBadan, int kadarKolesterolTotal, int kadarKolesterolLDL, int trombosit);

#endif // DATA_CHECKUP_H
