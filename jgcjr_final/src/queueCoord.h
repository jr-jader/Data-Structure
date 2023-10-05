#include "libraries.h"

#ifndef QUEUECOORD_H
#define QUEUECOORD_H

typedef void* Coord;

Coord newCoord();

void insertCoord(Coord coord, double x, double y);

double getXCoord(Coord coord);
double getYCoord(Coord coord);

void freeCoord(Coord coord);

#endif