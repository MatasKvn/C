#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initializeQueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}
void enqueue(queue *q, double data, int priority)
{
    node *newnode = malloc(sizeof(node));
    newnode->value = data;
    newnode->priority = priority;
    newnode->next = NULL;
    if (q->tail != NULL)
    {
        q->tail->next = newnode;
    }
    q->tail = newnode;
    if (q->head == NULL)
    {
        q->head = newnode;
    }
}
void enqueuePriority(queue *q, double data, int priority)
{
    node *newnode = malloc(sizeof(node));
    newnode->value = data;
    newnode->priority = priority;
    newnode->next = NULL;
    node *temp = q->head;
    node *next;

    if (q->head == NULL)
    {
        q->head = newnode;
        return;
    }
    if(newnode->priority > q->head->priority)
    {
        newnode->next = q->head;
        q->head = newnode;
        return;
    }

    while(temp != NULL)
    {
        // printf("Value: %.1lf, priority: %d\n", temp->value, temp->priority);
        if(temp->next != NULL && temp->next->priority < newnode->priority ){
            // printf("Here!!!\n");
            
            newnode->next = temp->next;
            temp->next = newnode;
            
            return;
        }
        if(temp->next == NULL){
            // printf("cia gal\n");
            
            temp->next = newnode;
            return;
        }
        temp = temp->next;
        
        // next = temp->next;
    }
}
double sumQueue(queue *q){
    node *temp=q->head;
    double sum = 0;
    while(temp != NULL)
    {
        sum += temp->value;
        temp = temp->next;
    }
    return sum;
}
int dequeue(queue *q)
{
    if(q->head == q->tail)
    {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
    }

    if (q->head == NULL)
    {
        printf("queue empty\n");
        return 0;
    }

    node *temp = q->head;
    int data = temp->value;

    q->head = q->head->next;

    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(temp);
    return data;
}
int isFull(queue *q)
{
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
    {
        free(newnode);
        return 1; // memory allocation failed, queue is full
    }
    free(newnode);
    return 0; // memory allocation success, queue is not full
}
int isEmpty(queue *q)
{
    return (q->head == NULL);
}
int checkFirst(queue *q)
{
    if (q->head == NULL)
    {
        printf("queue empty\n");
        return 0;
    }

    return q->head->value;
}
int countElements(queue *q)
{
    int count = 0;
    node *temp = q->head;
    while (temp != NULL)
    {
        ++count;
        temp = temp->next;
    }
    return count;
}
void printQueue(queue *q)
{
    node *temp=q->head;
    while(temp!=NULL)
    {
        printf("%.2lf\n",temp->value);
        temp = temp->next;
    }
}
void deleteQueue(queue *q)
{
    while (q->head != NULL)
    {
        node *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    q->tail = NULL;
}