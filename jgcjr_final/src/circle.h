#include "libraries.h"

#ifndef CIRCLE_H
#define CIRCLE_H

/*Tratamento de circulos que serão inseridos na àrvore yxx como informado struct especificada com os parâmetros lido no .geo*/

//Malloc da struct p/ circulos.
void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]);

void setCircleBorder(void* element, char colorBorder[20]);
void setCircleFill(void* element, char colorFill[20]);
void setCircleX(void* element, double x);
void setCircleY(void* element, double y);

//Getters para circulos.
char* getCircleBorder(void* element);
char* getCircleFill(void* element);
int getCircleId(void* element);
double getCircleX(void* element);
double getCircleY(void* element);
double getCircleR(void* element);

bool checkCircle(void* element, double x1, double y1, double x2, double y2);

#endif