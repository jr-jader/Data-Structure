#include "queueCoord.h"

struct Coord{
    double x, y;
};

Coord newCoord()
{
    struct Coord* new = (struct Coord*)malloc(sizeof(struct Coord));
    return new;
}

void insertCoord(Coord coord, double x, double y)
{
    struct Coord* aux = coord;
    aux->x = x;
    aux->y = y;
}

double getXCoord(Coord coord)
{
    struct Coord* aux = coord;
    return aux->x;
}

double getYCoord(Coord coord)
{
    struct Coord* aux = coord;
    return aux->y;
}

void freeCoord(Coord coord)
{
    struct Coord* aux = coord;
    free(aux);
}