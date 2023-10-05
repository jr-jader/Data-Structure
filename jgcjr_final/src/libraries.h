#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef LIBRARIES_H
#define LIBRARIES_H

#define MAX_QUEUE 500

/*Bibliotecas utilizadas no projeto typedefs*/

//structs para auxiliar na verif. dos parametros
typedef void* PathsChecked;

//Structs com os parametros do argv, alguns podem ser modificados antes de serem armazenados para facilitar a manipulação 
typedef void* AllPaths;

#endif