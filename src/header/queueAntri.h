#ifndef QUEUE_ANTRI_H
#define QUEUE_ANTRI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../header/auth.h"
#include "../header/dataCheckup.h"

typedef EntriAntrianCheckup itemType;

typedef struct node{
    itemType data;
    struct node* next;
} Node;

typedef struct queue{
    Node* front;
    Node* rear;
    int size;
    int nomorAntri;
} Queue;

void initQueue(Queue* q);
bool isQueueEmpty(const Queue* q);
bool enqueue(Queue* q, itemType item);
bool dequeue(Queue* q, itemType* item);
bool peek(const Queue* q, itemType* item);
int getSize(const Queue* q);
int getPosisiPasien (const Queue* q, int idPasien);
void clearQueue(Queue* q);


#endif // QUEUE_ANTRI_H