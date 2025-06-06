#include "../header/queueAntri.h"

//insialisasi queue antrien pasien di tiap ruangan
void initQueue(Queue* q){
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

//cek antri kosong
bool isQueueEmpty(const Queue* q){
    return (q->size == 0);
}

//penambahan pasien ke antrian
bool enqueue(Queue* q, itemType item){
    if (q == NULL) {
        return false;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return false;
    }

    newNode->data = item;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    return true;
}

//hapus pasien dari antrian
bool dequeue(Queue* q, itemType* item){
    if (isQueueEmpty(q) || item == NULL) {
        return false;
    }

    //Node* temp = q->front;
    *item = q->front->data;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    //free(temp);
    q->size--;
    return true;
}

//ambil pasien di depan antrian
bool peek(const Queue* q, itemType* item){
    if (isQueueEmpty(q)|| item == NULL) {
        return false;
    }
    *item = q->front->data;
    return true;
}


int getSize(const Queue* q){
    return q->size;
}

//ambil posisi pasien di antrian
int getPosisiPasien (const Queue* q, int idPasien){
    if (isQueueEmpty(q)) {
        return -1;
    }

    Node* current = q->front;
    int posisi = 1;

    while (current != NULL) {
        if (current->data.idPasien == idPasien) {
            return posisi;
        }
        current = current->next;
        posisi++;
    }

    return -1; // ID pasien tidak ditemukan
}

//hapus semua pasien di antrian
void clearQueue(Queue* q){
    if (q == NULL) {
        return;
    }

    itemType item;
    while (!isQueueEmpty(q)) {
        dequeue(q, &item);
    }
}
