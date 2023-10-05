#include "libraries.h"

#ifndef INFO_H
#define INFO_H

typedef void* StructInfo;
typedef void* ElementInfo;

StructInfo newInfo(char type, void* info);

char getInfoType(StructInfo node);
ElementInfo getInfoFromInfo(StructInfo node);

void freeInfo(StructInfo node);

#endif