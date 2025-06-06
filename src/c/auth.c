#include <stdio.h>
#include <string.h>
#include "../header/auth.h" 

User *current_user = NULL;

void initUserSet(UserSet *set) {
    set->jumlahUser = 1;
    set->users[0].id = 1;
    strcpy(set->users[0].username, "admin");
    strcpy(set->users[0].password, "admin123");
    set->users[0].role = MANAGER;
    initListInventory(&(set->users[0].inventory_obat));
    initStackPerut(&(set->users[0].perut_pasien));
}

User* registerUser(UserSet *set, char *username, char *password, Role role) {
    for (int i = 0; i < set->jumlahUser; i++) {
        if (strcmp(set->users[i].username, username) == 0) {
            printf("Username %s sudah terdaftar.\n", username);
            return NULL;
        }
    }

    if (set->jumlahUser >= MAX_USERS) {
        printf("User limit reached.\n");
        return NULL;
    }

    int newId = set->jumlahUser + 1;
    User *newUser = &set->users[set->jumlahUser++];
    newUser->id = newId;
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->role = role;

    // --- INISIALISASI FIELD BARU ---
    initListInventory(&(newUser->inventory_obat));
    initStackPerut(&(newUser->perut_pasien));
    newUser->diagnosisSekarang = -1;

    printf("Registrasi berhasil untuk %s.\n", username);
    return newUser;

    if (newUser->role == DOKTER) {
        newUser->aura = 0; //init aura dotker
    }
}

User* loginUser(UserSet *set, char *username, char *password) {
    User *user_found = findUserByUsername(set, username);
    if (user_found == NULL) {
        printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", username);
        return NULL;
    }

    for (int i = 0; i < set->jumlahUser; i++) {
        if (strcmp(set->users[i].username, username) == 0 &&
            strcmp(set->users[i].password, password) == 0) {
            current_user = &set->users[i];
            printf("Login berhasil. Halo, %s!\n", username);
            if (current_user->role == MANAGER) {
                printf("Selamat pagi Manager %s!\n\n", current_user->username);
            } else if (current_user->role == DOKTER) {
                printf("Selamat pagi Dokter %s!\n\n", current_user->username);
            } else if (current_user->role == PASIEN) {
                printf("Selamat pagi Pasien %s! Ada keluhan apa?\n\n", current_user->username);
            }
            return current_user;
        }
    }
    printf("Login gagal. Username atau password salah.\n");
    return NULL;
}

bool logoutUser() {
    printf(">>> LOGOUT\n");
    if (current_user) {
        printf("Logout berhasil. Sampai jumpa, %s!\n", current_user->username);
        current_user = NULL;
        return true;
    }
    printf("Belum login.\n");
    return false;
}

const char* roleToStr(Role role) {
    switch (role) {
        case MANAGER: return "MANAGER";
        case DOKTER: return "DOKTER";
        case PASIEN: return "PASIEN";
        default: return "UNKNOWN";
    }
}

User* findUserById(const UserSet *set, int id){
    if (set == NULL) {
        return NULL;
    }

    for (int i = 0; i < set->jumlahUser; i++) {
        if (set->users[i].id == id) {
            return (User*)&set->users[i];
        }
    }
    return NULL;
}

User* findUserByUsername(const UserSet *set, char *username){
    if (set == NULL) {
        return NULL;
    }

    for (int i = 0; i < set->jumlahUser; i++) {
        if (strcmp(set->users[i].username, username) == 0) {
            return (User*)&set->users[i];
        }
    }
    return NULL;
}

User* findUser(UserSet *set, const char *username) {
    for (int i = 0; i < set->jumlahUser; i++) {
        if (strcmp(set->users[i].username, username) == 0) {
            return &set->users[i];
        }
    }
    return NULL;
}

void generateRLE(const char *username, char *rleCode) {
    int len = strlen(username);
    int count = 1;
    int rleIndex = 0;

    for (int i = 1; i <= len; i++) {
        if (username[i] == username[i - 1] && i < len) {
            count++;
        } else {
            if (count > 1) {
                rleIndex += sprintf(rleCode + rleIndex, "%d", count);
            }
            rleIndex += sprintf(rleCode + rleIndex, "%c", username[i - 1]);
            count = 1;
        }
    }
    rleCode[rleIndex] = '\0';
}

void lupaPassword(UserSet *set) {
    char username[MAX_LEN];
    char rleCode[MAX_LEN * 2];
    char newPassword[MAX_LEN];

    printf(">>> LUPA_PASSWORD\n");
    printf("Username: ");
    scanf("%s", username);

    User *user = findUser(set, username);
    if (user == NULL) {
        printf("Username tidak terdaftar!\n");
        return;
    }

    printf("Kode Unik: ");
    scanf("%s", rleCode);

    char correctRle[MAX_LEN * 2];
    generateRLE(user->username, correctRle);

    if (strcmp(rleCode, correctRle) != 0) {
        printf("Kode unik salah!\n");
        return;
    }

    printf("Halo %s %s, silakan daftarkan ulang password anda!\n", roleToStr(user->role), user->username);
    printf("Password Baru: ");
    scanf("%s", newPassword);

    strcpy(user->password, newPassword);
    printf("Password berhasil diubah!\n");
}