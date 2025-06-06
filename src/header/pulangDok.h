#ifndef PULANGDOK_H
#define PULANGDOK_H

#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "antrian.h"
#include "listDenah.h"
#include "mapAssignDokter.h"
#include "adt_stack_obat.h"
#include "adt_list_obat.h"
#include "diagnosisBerobat.h"
#include "obat.h"


void F13_PulangDok(User* pasien_login, UserSet* set, Denah* denah);
EntriAntrianCheckup* getEntriPasien(Denah* denah, int idPasien);
bool hapusDariQueue(Queue* q, int index);
void resetDiagnosis(Denah* denah, int idPasien);
bool isObatSama(StackPerutObat* perut, int* resep, int len);
void getResepObat(const char* penyakit, int* resep, int* len);
void clearListInventory(ListInventoryObat* list);

#endif