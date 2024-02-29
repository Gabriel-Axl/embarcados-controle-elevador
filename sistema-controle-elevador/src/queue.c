#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        queue->items[i] = 0;  
    }
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isDuplicate(Queue* queue, int value) {
    if (queue->front == -1) {
        return 0; 
    }

    for (int i = queue->front; i <= queue->rear; i++) {
        if (queue->items[i] == value) {
            return 1; 
        }
    }
    return 0; 
}

void enqueueUnique(Queue* queue, int value) {
    if (queue->rear == MAX_SIZE - 1) {
        fprintf(stderr, "Erro: a fila está cheia\n");
        exit(EXIT_FAILURE);
    }

    if (!isDuplicate(queue, value)) {
        queue->rear++;
        queue->items[queue->rear] = value;
        if (queue->front == -1) {
            queue->front = 0;
        }
    } 
}

int dequeue(Queue* queue) {
    if (queue->front == -1) {
        return -1;
    }

    int value = queue->items[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }

    return value;
}

void displayQueue(Queue* queue) {
    if (queue->front == -1) {
        return;
    }
    printf("Fila: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n |");
}

int peek(Queue* queue) {
    if (queue->front == -1) {
        return -1;
    }
    return queue->items[queue->front];
}
