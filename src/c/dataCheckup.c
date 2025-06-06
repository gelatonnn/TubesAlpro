#include "../header/dataCheckup.h"

DataCheckUp createDataCheckUp(id idPasien){
    DataCheckUp data;
    data.idPasien = idPasien;
    data.suhuTubuh = 0.0;
    data.tekananDarahSistol = 0;
    data.tekananDarahDiastol = 0;
    data.detakJantung = 0;
    data.saturasiOksigen = 0.0;
    data.kadarGulaDarah = 0;
    data.beratBadan = 0.0;
    data.tinggiBadan = 0.0;
    data.kadarKolesterolTotal = 0;
    data.kadarKolesterolLDL = 0;
    data.trombosit = 0;
    return data;
}

bool setDataCheckUp(DataCheckUp *data, float suhuTubuh, int tekananDarahSistol, int tekananDarahDiastol, int detakJantung, float saturasiOksigen, int kadarGulaDarah, float beratBadan, float tinggiBadan, int kadarKolesterolTotal, int kadarKolesterolLDL, int trombosit){
    if (data == NULL) {
        return false;
    }
    data->suhuTubuh = suhuTubuh;
    data->tekananDarahSistol = tekananDarahSistol;
    data->tekananDarahDiastol = tekananDarahDiastol;
    data->detakJantung = detakJantung;
    data->saturasiOksigen = saturasiOksigen;
    data->kadarGulaDarah = kadarGulaDarah;
    data->beratBadan = beratBadan;
    data->tinggiBadan = tinggiBadan;
    data->kadarKolesterolTotal = kadarKolesterolTotal;
    data->kadarKolesterolLDL = kadarKolesterolLDL;
    data->trombosit = trombosit;

    return true;
}
