#include "list.h"
#include "queue.h"
#include "inp.h"
#include "svg.h"
#include "libraries.h"
#include "yxxtree.h"
#include "paths.h"

#ifndef QRY_H
#define QRY_H


//Criação de file pointer para .txt de relatório
FILE* newReport(AllPaths paths);

//Encerrar o .txt
void endReport(FILE* txt);

//finalizar o .svg
void endSvg(FILE* pfileSvg);

//leitura de consultas do .qry
void readQry(FILE* txt, YxxTree tree, AllPaths paths, PathsChecked pathsChecked);

#endif