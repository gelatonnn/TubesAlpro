#include "../header/adt_stack_obat.h"
#include <stdio.h>
#include <stdlib.h>

void initStackPerut(StackPerutObat* stack) {
    if (stack == NULL) return;
    stack->top = NULL;
    stack->count = 0;
}

bool isStackPerutEmpty(const StackPerutObat* stack) {
    if (stack == NULL) return true;
    return stack->top == NULL;
}

void pushStackPerut(StackPerutObat* stack, ItemObatPasien item) {
    if (stack == NULL) return;

    NodeObatPerut* newNode = (NodeObatPerut*)malloc(sizeof(NodeObatPerut));
    if (newNode == NULL) {
        perror("Gagal alokasi memori untuk node perut baru");
        return;
    }
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

bool popStackPerut(StackPerutObat* stack, ItemObatPasien* popped_item) {
    if (stack == NULL || popped_item == NULL || isStackPerutEmpty(stack)) {
        return false;
    }

    NodeObatPerut* temp = stack->top;
    *popped_item = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->count--;
    return true;
}

int getCountStackPerut(const StackPerutObat* stack) {
    if (stack == NULL) return 0;
    return stack->count;
}