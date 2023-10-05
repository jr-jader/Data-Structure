#include "libraries.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

/*Tratamento de retânculos que serão inseridos na àrvore yxx como info struct para retangulos com os parametros lidos pelo .geo*/

//Malloc da struct para retangulo
void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]);

void setRectFill(void* element, char colorFill[20]);
void setRectX(void* element, double x);
void setRectBorder(void* element, char colorBorder[20]);
void setRectY(void* element, double y);

//Getters para retangulos
char* getRectBorder(void* element);
char* getRectFill(void* element);
int getRectId(void* element);
double getRectY(void* element);
double getRectW(void* element);
double getRectX(void* element);
double getRectH(void* element);


bool checkRect(void* element, double x1, double y1, double x2, double y2);

#endif