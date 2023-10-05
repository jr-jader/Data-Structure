#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "libraries.h"
#include "yxxtree.h"
#include "list.h"


#ifndef SVG_H
#define SVG_H

/*Manipulação do SVG*/

//Criar file pointer para .svg
FILE* newSvg(char* pathOut, char* filenameGeo);

//Encerrar .svg
void closeSvg(FILE *svg);

void printTSvg(Info i, double x, double y, void *aux);

//Escrita do .sgv
void writeSvg(FILE* svg, YxxTree tree);

void updateDpsSvg(FILE* pSvg, YxxTree tree, List list, int i, double dx, double dy, char colorBorder[20], char colorFill[20]);
void updateUpsSvg(FILE* pSvg, List list, char colorBorder[20], char colorFill[20], double dx, double dy, int n);
void updateTSvg(Info i, double x, double y, void *aux);

#endif