#include "../header/adt_list_obat.h"
#include <stdio.h>
#include <stdlib.h>

void initListInventory(ListInventoryObat* list) {
    if (list == NULL) return;
    list->head = NULL;
    list->count = 0;
}


bool isListInventoryEmpty(const ListInventoryObat* list) {
    if (list == NULL) return true;
    return list->head == NULL;
}

void insertLastListInventory(ListInventoryObat* list, ItemObatPasien item) {
    if (list == NULL) return;

    NodeObatInventory* newNode = (NodeObatInventory*)malloc(sizeof(NodeObatInventory));
    if (newNode == NULL) {
        perror("Gagal alokasi memori untuk node inventory baru");
        return;
    }
    newNode->data = item;
    newNode->next = NULL;

    if (isListInventoryEmpty(list)) {
        list->head = newNode;
    } else {
        NodeObatInventory* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

bool deleteAtListInventory(ListInventoryObat* list, int index, ItemObatPasien* deleted_item) {
    if (list == NULL || deleted_item == NULL || isListInventoryEmpty(list) || index < 0 || index >= list->count) {
        return false;
    }

    NodeObatInventory* temp = NULL;
    NodeObatInventory* current = list->head;

    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        for (int i = 0; i < index - 1; i++) {
            if (current->next == NULL) return false; // Seharusnya tidak terjadi jika index valid
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }

    *deleted_item = temp->data;
    free(temp);
    list->count--;
    return true;
}

int getCountListInventory(const ListInventoryObat* list) {
    if (list == NULL) return 0;
    return list->count;
}

bool getItemAtListInventory(const ListInventoryObat* list, int index, ItemObatPasien* item_found) {
    if (list == NULL || item_found == NULL || isListInventoryEmpty(list) || index < 0 || index >= list->count) {
        return false;
    }
    NodeObatInventory* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    *item_found = current->data;
    return true;
}