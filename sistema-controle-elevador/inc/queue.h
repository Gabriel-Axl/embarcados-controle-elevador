#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 11

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

Queue* createQueue();
int isDuplicate(Queue* queue, int value);
void enqueueUnique(Queue* queue, int value);
int dequeue(Queue* queue);
void displayQueue(Queue* queue);
int peek(Queue* queue) ;
#endif /* QUEUE_H */