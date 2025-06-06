#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

#include "adt_list_obat.h"  // Header ADT List yang baru Anda buat
#include "adt_stack_obat.h"

#define MAX_USERS 100
#define MAX_LEN 50

typedef enum {
    MANAGER,
    DOKTER,
    PASIEN
} Role;

typedef struct {
    int id;
    char username[MAX_LEN];
    char password[MAX_LEN];
    Role role;
    int diagnosisSekarang; // ID diagnosis terakhir
    ListInventoryObat inventory_obat;  // Inventaris obat pasien
    StackPerutObat perut_pasien;

    //bonus atribut dokter
    int aura;
} User;

typedef struct {
    User users[MAX_USERS];
    int jumlahUser;
} UserSet;

extern User *current_user;

void initUserSet(UserSet *set);
User* registerUser(UserSet *set, char *username, char *password, Role role);
User* loginUser(UserSet *set, char *username, char *password);
bool logoutUser();
const char* roleToStr(Role role);
User* findUserById(const UserSet *set, int id);
User* findUserByUsername(const UserSet *set, char *username);
User* findUser(UserSet *set, const char *username);
void generateRLE(const char *username, char *rleCode);
void lupaPassword(UserSet *set);

#endif