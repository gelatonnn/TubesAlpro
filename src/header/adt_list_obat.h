#ifndef ADT_LIST_OBAT_H
#define ADT_LIST_OBAT_H

#include <stdbool.h>

// Item yang disimpan dalam list inventory
typedef struct {
    int obat_id;
} ItemObatPasien;

// Node untuk linked list inventory
typedef struct NodeObatInventory {
    ItemObatPasien data;
    struct NodeObatInventory* next;
} NodeObatInventory;

// Struktur ADT List untuk inventory
typedef struct {
    NodeObatInventory* head;
    int count;
} ListInventoryObat;

// Fungsi-fungsi ADT List
void initListInventory(ListInventoryObat* list);
bool isListInventoryEmpty(const ListInventoryObat* list);
void insertLastListInventory(ListInventoryObat* list, ItemObatPasien item);
// Mengembalikan true jika berhasil, dan item yang dihapus disimpan di 'deleted_item'
// Menghapus berdasarkan indeks (0-based)
bool deleteAtListInventory(ListInventoryObat* list, int index, ItemObatPasien* deleted_item);
// Fungsi untuk menampilkan list (membutuhkan akses ke daftar obat global untuk nama)
// Kita akan implementasikan ini di fitur_obat_pasien.c agar bisa akses getNamaObat
// void displayListInventory(const ListInventoryObat* list);
int getCountListInventory(const ListInventoryObat* list);
// Mendapatkan item berdasarkan indeks tanpa menghapus (untuk pemilihan)
bool getItemAtListInventory(const ListInventoryObat* list, int index, ItemObatPasien* item_found);


#endif // ADT_LIST_OBAT_H