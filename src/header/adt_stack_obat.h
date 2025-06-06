#ifndef ADT_STACK_OBAT_H
#define ADT_STACK_OBAT_H

#include "adt_list_obat.h" // Untuk ItemObatPasien

// Node untuk linked list stack "perut"
typedef struct NodeObatPerut {
    ItemObatPasien data;
    struct NodeObatPerut* next;
} NodeObatPerut;

// Struktur ADT Stack untuk "perut"
typedef struct {
    NodeObatPerut* top;
    int count;
} StackPerutObat;

// Fungsi-fungsi ADT Stack
void initStackPerut(StackPerutObat* stack);
bool isStackPerutEmpty(const StackPerutObat* stack);
void pushStackPerut(StackPerutObat* stack, ItemObatPasien item);
bool popStackPerut(StackPerutObat* stack, ItemObatPasien* popped_item);
// bool peekStackPerut(const StackPerutObat* stack, ItemObatPasien* top_item); // Jika diperlukan
int getCountStackPerut(const StackPerutObat* stack);

#endif // ADT_STACK_OBAT_H