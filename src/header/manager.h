#ifndef MANAGER_H
#define MANAGER_H

#include "auth.h"
#include "dataCheckup.h"
#include "diagnosisBerobat.h"


typedef enum {
    SORT_BY_ID,
    SORT_BY_NAME,
    SORT_BY_AURA //bonus AURA
} SortKey;

typedef enum {
    ASC,
    DESC
} SortOrder;

// Viewing
void lihatUser(UserSet *userSet, SortKey sortKey, SortOrder order);
void lihatPasien(UserSet *userSet, SortKey sortKey, SortOrder order);
void lihatDokter(UserSet *userSet, SortKey sortKey, SortOrder order);

// Searching interactive
void cariUser(UserSet *userSet);
void cariPasien(UserSet *userSet);
void cariDokter(UserSet *userSet);

// Internal search helpers
void cariUserById(UserSet *userSet, int id, bool hanyaPasien);
void cariUserByName(UserSet *userSet, const char *name, bool hanyaPasien);
void cariPasienByPenyakit(UserSet *userSet, const char *penyakit);
void cariDokterById(UserSet *userSet, int id);
void cariDokterByName(UserSet *userSet, const char *name);


#endif
