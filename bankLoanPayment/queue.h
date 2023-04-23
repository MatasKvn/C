#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct node
{
    int priority;
    double value;
    struct node *next;
} node;
typedef struct queue
{
    node *head;
    node *tail;

} queue;

void initializeQueue(queue *q);
void enqueue(queue *q, double data, int priority);
void enqueuePriority(queue *q, double data, int priority);
double sumQueue(queue *q);
int dequeue(queue *q);
int isFull(queue *q);
int isEmpty(queue *q);
int checkFirst(queue *q);
int countElements(queue *q);
void printQueue(queue *q);
void deleteQueue(queue *q);

#endif