#include "libraries.h"

#ifndef TXT_H
#define TXT_H

/*Tratamento de textos que serão inseridos na àrvore yxx como info struct para textos com os parametros lidos no .geo*/

//Malloc da struct para texto
void* newTxt(int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]);

void setTxtBorder(void* element, char colorBorder[20]);
void setTxtFill(void* element, char colorFill[20]);
void setTxtX(void* element, double x);
void setTxtY(void* element, double y);

//Getters para textos
char* getTxtBorder(void* element);
char* getTxtFill(void* element);
char getA(void* element);
char* getTxt(void* element);
int getTxtId(void* element);
double getTxtX(void* element);
double getTxtY(void* element);


bool checkTxt(void* element, double x1, double y1, double x2, double y2);

#endif