#include "yxxtree.h"
#include "info.h"
#include "libraries.h"
#include "queueCoord.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef void** CoordArr;
typedef void* Queue;

Queue newQueue(int size);

bool isFull(Queue queue);
bool isEmpty(Queue queue);

int getRear(Queue queue);
Coord getFirstCoord(Queue queue);
int getQueueSize(Queue queue);

void pol(FILE* pSvg, YxxTree tree, Queue queue, int i, double d, double e, char coLorBorder[20], char colorFill[20]);

void enqueue(Queue queue, double x, double y);

void dequeue(Queue queue, Coord coord);

bool freeAllCoord(Queue queue);
void freeQueue(Queue queue);

#endif