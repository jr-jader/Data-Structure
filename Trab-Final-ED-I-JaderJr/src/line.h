#include "libraries.h"

#ifndef LINE_H
#define LINE_H

/*Tratamento de linhas que serão inseridas na árvore yxx como info struct especifica para linhas com os parametros lidos no .geo*/

//malloc da structi para linhas
void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]);

void setLineX1(void* element, double x);
void setLineY1(void* element, double y);
void setLineX2(void* element, double x);
void setLineY2(void* element, double y);
void setLineColor(void* element, char color[20]);

//Getters para linhas
int getLineId(void* element);
double getLineX1(void* element);
double getLineY1(void* element);
double getLineX2(void* element);
double getLineY2(void* element);
char* getLineBorder(void* element);

bool checkLine(void* element, double x1, double y1, double x2, double y2);

#endif