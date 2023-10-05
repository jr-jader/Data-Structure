#include "paths.h"
#include "libraries.h"


#ifndef ARGV_H
#define ARGV_H


/*Tratamento de Checkers dos parâmetros do argv*/

//Alocação da struct com valores Booleanos dos parâmetros
void* newPathsChecked();

//Inicia os Valores Booleanos 
void setPathsChecked(PathsChecked pathsChecked);

//Libera o espaço alocado para a Struct com valores booleanos
void freePathsChecked(PathsChecked pathsChecked);

//Atribui True ao valor referente ao parâmetro passado
void setFileGeoTrue(PathsChecked pathsChecked);
void setFileQryTrue(PathsChecked pathsChecked);
void setGivenPathInTrue(PathsChecked pathsChecked);
void setPathOutTrue(PathsChecked pathsChecked);
void setDegFactorTrue(PathsChecked pathsChecked);
void setPathInTrue(PathsChecked pathsChecked);
void setGivenPathOutTrue(PathsChecked pathsChecked);

//Checa os valores da passagem de parâmetros
bool getCheckedQry(PathsChecked pathsChecked);
bool getCheckedDegFactor(PathsChecked pathsChecked);
bool checkCheckedPaths(PathsChecked pathsChecked);
bool getCheckedGivenPathIn(PathsChecked pathsChecked);
bool getCheckedPathIn(PathsChecked pathsChecked);
bool getCheckedGeo(PathsChecked pathsChecked);

//Leitura e Armazenamento dos nomes dos Paths e Arquivos
void setArgv(int argc, char** argv, void* paths, PathsChecked pathsChecked);

#endif