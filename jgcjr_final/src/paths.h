#include "libraries.h"

#ifndef PATHS_H
#define PATHS_H

/*Tratamento de parâmetros fornecidos no argv*/

//Aloc da struct com todos os parâmetros
void* newPaths();

//Debug: mostra todos os paths
void printPaths(AllPaths paths);

//Libera os espaços alocados pela struct dos paths e paths armazenados dentro da struct
void freePaths(AllPaths paths);

//Malloc dos parâmetros
void allocGivenPathIn(AllPaths paths, int size);
void allocPathIn(AllPaths paths, int size);
void allocGivenPathOut(AllPaths paths, int size);
void allocPathOut(AllPaths paths, int size);
void allocGivenFileGeo(AllPaths paths, int size);
void allocFileGeo(AllPaths paths, int size);
void allocGivenFileQry(AllPaths paths, int size);
void allocFileQry(AllPaths paths, int size);
void allocCatGeoQry(AllPaths paths, int size);

//Realoc. dinamica dos arquivos de leitura
void reallocGeo(AllPaths paths, int size);
void reallocQry(AllPaths paths, int size);

//Atribuir dados e nome passado pelos parametros
void setGivenPathIn(AllPaths paths, char* name);
void setPathIn(AllPaths paths, char* name);
void setGivenPathOut(AllPaths paths, char* name);
void setPathOut(AllPaths paths, char* name);
void setGivenFileGeo(AllPaths paths, char* name);
void setFileGeo(AllPaths paths, char* name);
void setGivenFileQry(AllPaths paths, char* name);
void setFileQry(AllPaths paths, char* name);
void setDegFactor(AllPaths paths, double number);
void setCatGeoQry(AllPaths paths, char* name);

//Verificar extensão dos arquivos de leitura passados como para metros
bool checkFileGeo(AllPaths paths);
bool checkFileQry(AllPaths paths);

//Remove a extensão do arquivo
void removeExt(char* srcArr, char* destArr, int start);

//Remove o path do arquivo deixando apenas nome.
void removeRelPath(char* srcArr, char* destArr);

//Verificar se há paths absolutos ou relativos nos nomes dos arquivos dos para metros
bool checkAbsPathIn(AllPaths paths);
bool checkRelPathIn(AllPaths paths);
bool checkAbsPathOut(AllPaths paths);
bool checkRelPathOut(AllPaths paths);
bool checkRelGeo(AllPaths paths);
bool checkRelQry(AllPaths paths);

//Funções para copiar que foram utilizadas em outras funções de set
void strcpyPathIn(AllPaths paths, char* builtPath);
void strcpyPathOut(AllPaths paths, char* builtPath);

//Contrução dos paths
void buildWholePathIn(AllPaths paths);
void buildPathIn(AllPaths paths, char* tempPathIn);
void buildWholePathOut(AllPaths paths);
void buildPathOut(AllPaths paths, char* tempPathOut);

//Getters para parametros com path relativo
char* getRelPathIn(AllPaths paths);
char* getRelPathOut(AllPaths paths);

//Getters para respectivos argumentos
char* getPathIn(AllPaths paths);
char* getPathOut(AllPaths paths);
char* getGivenGeo(AllPaths paths);
char* getFileGeo(AllPaths paths);
char* getGivenQry(AllPaths paths);
char* getFileQry(AllPaths paths);
char* getCatGeoQry(AllPaths paths);
double getDegFactor(AllPaths paths);

#endif