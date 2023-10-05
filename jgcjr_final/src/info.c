#include "info.h"

struct info{
    char type;
    void* info;
};

StructInfo newInfo(char type, void* info)
{
    struct info* new = (struct info*)malloc(sizeof(struct info));
    new->type = type;
    new->info = info;
    return new;
} 

char getInfoType(StructInfo node)
{
    struct info* aux = node;
    return aux->type;
}

ElementInfo getInfoFromInfo(StructInfo node)
{
    struct info* aux = node;
    return aux->info;
}

void freeInfo(StructInfo node)
{
    struct info* aux = node;
    free(aux->info);
    free(node);
}