#include "info.h"
#include "queue.h"
#include "libraries.h"
#include "yxxtree.h"

#ifndef INP_H
#define INP_H

void* newInp(int id, Queue queue, FILE* pTxt);
void fInp(Info i, double x, double y, void* aux);
Queue getInpQueue(void* inp);

#endif