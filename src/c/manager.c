#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/manager.h"

static SortKey currentSortKey; 
// Utility: Compare function for qsort
static int compareUsers(const void *a, const void *b) {
    const User *ua = (const User *)a;
    const User *ub = (const User *)b;
    if (currentSortKey == SORT_BY_ID) {
        return ua->id - ub->id;
    } else if (currentSortKey == SORT_BY_AURA) {
        return ua->aura - ub->aura;
    }
    return strcasecmp(ua->username, ub->username);
}


void sortUsers(User users[], int n, SortKey key, SortOrder order) {
    currentSortKey = key;
    qsort(users, n, sizeof(User), compareUsers);

    if (order == DESC) {
        for (int i = 0; i < n / 2; ++i) {
            User temp = users[i];
            users[i] = users[n - 1 - i];
            users[n - 1 - i] = temp;
        }
    }
}


// Get penyakit name from antrian
const char *getPenyakitFromAntrian(int userId, EntriAntrianCheckup *antrian, int antrianCount) {
    for (int i = 0; i < antrianCount; ++i) {
        if (antrian[i].idPasien == userId) {
            const char *penyakit = getNamaPenyakit(antrian[i].idPenyakit);
            return penyakit ? penyakit : "-";
        }
    }
    return "-";
}

void printUserTableHeader() {
    printf("  ID   Username   Role     Penyakit   \n");
}

void printUserTableHeaderDokter() {
    printf(" ID    Username  Role     Aura \n");
}

void printUserRow(User *user, const char *penyakit) {
    printf("  %-2d   %-8s   %-6s   %-9s  \n", 
           user->id, 
           user->username, 
           user->role == DOKTER ? "Dokter" : "Pasien",
           penyakit);
}

void printUserRowDokter(User *user) {
    printf(" %-2d   %-8s   %-6s   %-4d \n", 
           user->id, 
           user->username, 
           user->role == DOKTER ? "Dokter" : "Pasien",
           user->aura);
}

// View all users
// View all users
void lihatUser(UserSet *userSet, SortKey sortKey, SortOrder order) {
    printf(">>> LIHAT USER\n");
    User *copy = malloc(userSet->jumlahUser * sizeof(User));
    memcpy(copy, userSet->users, userSet->jumlahUser * sizeof(User));
    sortUsers(copy, userSet->jumlahUser, sortKey, order);

    printUserTableHeader();
    for (int i = 0; i < userSet->jumlahUser; ++i) {
        const char *penyakit = "-";
        if (copy[i].role == PASIEN && copy[i].diagnosisSekarang != ID_INVALID) {
            penyakit = getNamaPenyakit(copy[i].diagnosisSekarang);
            if (penyakit == NULL) {
                penyakit = "-";
            }
        }
        printUserRow(&copy[i], penyakit);
    }
    free(copy);
}

void lihatPasien(UserSet *userSet, SortKey sortKey, SortOrder order) {
    printf(">>> LIHAT PASIEN\n");
    User *temp = malloc(userSet->jumlahUser * sizeof(User));
    int count = 0;
    for (int i = 0; i < userSet->jumlahUser; ++i) {
        if (userSet->users[i].role == PASIEN)
            temp[count++] = userSet->users[i];
    }
    sortUsers(temp, count, sortKey, order);

    printUserTableHeader();
    for (int i = 0; i < count; ++i) {
        const char *penyakit = "-";
        if (temp[i].diagnosisSekarang != ID_INVALID) {
            penyakit = getNamaPenyakit(temp[i].diagnosisSekarang);
            if (penyakit == NULL) {
                penyakit = "-";
            }
        }
        printUserRow(&temp[i], penyakit);
    }
    free(temp);
}

void lihatDokter(UserSet *userSet, SortKey sortKey, SortOrder order) {
    printf(">>> LIHAT DOKTER\n");
    User *temp = malloc(userSet->jumlahUser * sizeof(User));
    int count = 0;
    for (int i = 0; i < userSet->jumlahUser; ++i) {
        if (userSet->users[i].role == DOKTER)
            temp[count++] = userSet->users[i];
    }
    sortUsers(temp, count, sortKey, order);

    printUserTableHeaderDokter();
    for (int i = 0; i < count; ++i) {
        printUserRowDokter(&temp[i]);
    }
    free(temp);
}


// Interactive search
void cariUser(UserSet *userSet) {
    printf(">>> CARI USER\n");
    int method;
    printf("Cari berdasarkan:\n1. ID\n2. Nama\n>>> ");
    scanf("%d", &method); getchar();

    if (method == 1) {
        int id;
        printf("Masukkan ID: ");
        scanf("%d", &id); getchar();
        cariUserById(userSet, id, false);
    } else {
        char name[50];
        printf("Masukkan Nama: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;
        cariUserByName(userSet, name, false);
    }
}

void cariPasien(UserSet *userSet) {
    printf(">>> CARI PASIEN\n");
    int method;
    printf("Cari pasien berdasarkan:\n1. ID\n2. Nama\n3. Penyakit\n>>> ");
    scanf("%d", &method); getchar();

    if (method == 1) {
        int id;
        printf("Masukkan ID: ");
        scanf("%d", &id); getchar();
        cariUserById(userSet,id, true);
    } else if (method == 2) {
        char name[50];
        printf("Masukkan Nama: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;
        cariUserByName(userSet,name, true);
    } else {
        char penyakit[50];
        printf("Masukkan nama penyakit: ");
        fgets(penyakit, 50, stdin);
        penyakit[strcspn(penyakit, "\n")] = 0;
        cariPasienByPenyakit(userSet,penyakit);
    }
}

void cariDokter(UserSet *userSet) {
    printf(">>> CARI DOKTER\n");
    int method;
    printf("Cari dokter berdasarkan:\n1. ID\n2. Nama\n>>> ");
    scanf("%d", &method); getchar();

    if (method == 1) {
        int id;
        printf("Masukkan ID: ");
        scanf("%d", &id); getchar();
        cariDokterById(userSet, id);
    } else {
        char name[50];
        printf("Masukkan Nama: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;
        cariDokterByName(userSet, name);
    }
}

// Search helpers
void cariUserById(UserSet *userSet, int id, bool hanyaPasien) {
    User *user = NULL;
    for (int i = 0; i < userSet->jumlahUser; i++) {
        if (userSet->users[i].id == id) {
            user = &userSet->users[i];
            break;
        }
    }

    if (user) {
        if (hanyaPasien && user->role != PASIEN) {
            printf("User dengan ID %d bukan pasien.\n", id);
            return;
        }
        const char *penyakit = "-";
        if (user->role == PASIEN && user->diagnosisSekarang != ID_INVALID) {
            penyakit = getNamaPenyakit(user->diagnosisSekarang);
            if (penyakit == NULL) {
                penyakit = "-";
            }
        }
        printUserTableHeader();
        printUserRow(user, penyakit);
    } else {
        printf("User dengan ID %d tidak ditemukan.\n", id);
    }
}

void cariUserByName(UserSet *userSet, const char *name, bool hanyaPasien) {
    bool found = false;
    printUserTableHeader();
    for (int i = 0; i < userSet->jumlahUser; i++) {
        if (strstr(userSet->users[i].username, name)) {
            if (hanyaPasien && userSet->users[i].role != PASIEN) {
                continue; // Skip non-pasien users
            }
            const char *penyakit = "-";
            if (userSet->users[i].role == PASIEN && userSet->users[i].diagnosisSekarang != ID_INVALID) {
                penyakit = getNamaPenyakit(userSet->users[i].diagnosisSekarang);
                if (penyakit == NULL) {
                    penyakit = "-";
                }
            }
            printUserRow(&userSet->users[i], penyakit);
            found = true;
        }
    }
    if (!found) {
        printf("Tidak ditemukan user dengan nama mengandung \"%s\".\n", name);
    }
}


void cariPasienByPenyakit(UserSet *userSet, const char *penyakitCari) {
    bool found = false;
    printUserTableHeader();
    for (int i = 0; i < userSet->jumlahUser; i++) {
        if (userSet->users[i].role == PASIEN && userSet->users[i].diagnosisSekarang != ID_INVALID) {
            const char* penyakit = getNamaPenyakit(userSet->users[i].diagnosisSekarang);
            if (penyakit && strstr(penyakit, penyakitCari)) {
                printUserRow(&userSet->users[i], penyakit);
                found = true;
            }
        }
    }
    if (!found) {
        printf("Tidak ditemukan pasien dengan penyakit \"%s\".\n", penyakitCari);
    }
}


void cariDokterById(UserSet *userSet, int id) {
    for (int i = 0; i < userSet->jumlahUser; i++) {
        if (userSet->users[i].id == id && userSet->users[i].role == DOKTER) {
            printUserTableHeader();
            printUserRow(&userSet->users[i], "-");
            return;
        }
    }
    printf("Dokter dengan ID %d tidak ditemukan.\n", id);
}


void cariDokterByName(UserSet *userSet, const char *name) {
    bool found = false;
    printUserTableHeader();
    for (int i = 0; i < userSet->jumlahUser; i++) {
        if (userSet->users[i].role == DOKTER &&
            strstr(userSet->users[i].username, name)) {
            printUserRow(&userSet->users[i], "-");
            found = true;
        }
    }
    if (!found) {
        printf("Tidak ditemukan dokter dengan nama \"%s\".\n", name);
    }
}

int getSemuaEntriAntrian(const Denah* denah, EntriAntrianCheckup antrian[], int maxEntries){
    if (denah == NULL || antrian == NULL || maxEntries <= 0) {
        return 0; // Invalid input
    }

    int count = 0;
    for (int i = 0; i < denah->jumlahRuangan; i++) {
        const Queue* queue = &denah->ruangan[i].antrianPasien;
        Node* current = queue->front;
        while (current != NULL) {
            if (count < maxEntries) {
                antrian[count++] = current->data;
            } else {
                printf("Warning: Maximum entries limit reached (%d). Some entries may not be included.\n", maxEntries);
                return count;
            }
            current = current->next;
        }
    }
    return count; 
}

const char* getPenyakitSekarang(int id, EntriAntrianCheckup *antrian, int antrianCount){
    const char* penyakitSekarang = NULL;
    for (int i = 0; i < antrianCount; i++) {
        if (antrian[i].idPasien == id && antrian[i].idPenyakit != ID_INVALID) {
            penyakitSekarang = getNamaPenyakit(antrian[i].idPenyakit);
            break;
        }
    }

    return penyakitSekarang ? penyakitSekarang : "-";
}

