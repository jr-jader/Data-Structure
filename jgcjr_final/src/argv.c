#include "argv.h"

struct pathsChecked
{
    bool factorDeg, givenPathOut, givenPathIn, geoFile, pathIn, pathOut, qryFile;
}; 

void* newPathsChecked()
{
    struct pathsChecked* new = (struct pathsChecked*)malloc(sizeof(struct pathsChecked));
    return new;
}

void setPathsChecked(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    aux->givenPathIn = aux->pathIn = aux->givenPathOut = aux->pathOut = aux->geoFile = aux->qryFile = aux->factorDeg = false;
}

void freePathsChecked(PathsChecked pathsChecked)
{
    free(pathsChecked);
}

void setDegFactorTrue(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    aux->factorDeg = true;
}

void setPathInTrue(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    aux->pathIn = true;
}


void setFileGeoTrue(PathsChecked pathsChecked){
    struct pathsChecked* aux = pathsChecked;
    aux->geoFile = true;
}

void setPathOutTrue(PathsChecked pathsChecked){
    struct pathsChecked* aux = pathsChecked;
    aux->pathOut = true;
}


void setFileQryTrue(PathsChecked pathsChecked){
    struct pathsChecked* aux = pathsChecked;
    aux->qryFile = true;
}

void setGivenPathInTrue(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    aux->givenPathIn = true;
}

void setGivenPathOutTrue(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    aux->givenPathOut = true;
}

bool checkCheckedPaths(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    if(aux->pathIn && aux->givenPathOut && aux->pathOut && aux->geoFile){
        return true;
    }
    return false;
}

bool getCheckedGivenPathIn(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    return aux->givenPathIn;
}

bool getCheckedPathIn(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    return aux->pathIn;
}

bool getCheckedGeo(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    return aux->geoFile;
}

bool getCheckedQry(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    return aux->qryFile;
}

bool getCheckedDegFactor(PathsChecked pathsChecked)
{
    struct pathsChecked* aux = pathsChecked;
    return aux->factorDeg;
}

void setArgv(int argc, char** argv, void* paths, PathsChecked pathsChecked)
{
    int i = 1;

    setPathsChecked(pathsChecked);

    while(i < argc){ 
        if(strcmp(argv[i],"-e") == 0)
        { 
            //Path para diretório Base de Entrada
            i++;
            allocGivenPathIn(paths, strlen(argv[i]) + 1);
            setGivenPathIn(paths, argv[i]);
            setGivenPathInTrue(pathsChecked);
            if(checkRelPathIn(paths))
            { 
                //Se o caminho fornecido tem um caminho relativo
                char* tempPathIn = getRelPathIn(paths);
                buildPathIn(paths, tempPathIn);
            }
            else if(checkAbsPathIn(paths))
            { 
                //Se o caminho fornecido tem caminhi absoluto
                allocPathIn(paths, strlen(argv[i]) + 1);
                setPathIn(paths, argv[i]);
            }
            setPathInTrue(pathsChecked);
        }
        else if(strcmp(argv[i], "-o") == 0)
        { 
            //Path para diretorio base de saída
            i++;
            allocGivenPathOut(paths, strlen(argv[i]) + 1);
            setGivenPathOut(paths, argv[i]);
            setGivenPathOutTrue(pathsChecked);
            if(checkRelPathOut(paths))
            {
                 //Se o caminho fornecido tem caminho relativo
                char* tempPathOut = getRelPathOut(paths);
                buildPathOut(paths, tempPathOut);
            }
            else if(checkAbsPathOut(paths))
            { 
                //Se o caminho fornecido tem caminho absoluto
                allocPathOut(paths, strlen(argv[i]) + 1);
                setPathOut(paths, argv[i]);
            }
            else{
                buildWholePathOut(paths);    
            }
            setPathOutTrue(pathsChecked);
        }
        else if(strcmp(argv[i], "-f") == 0)
        { 
            //Nome do arquivo geo sobe o diretório Base de Entrada
            i++;
            allocGivenFileGeo(paths, strlen(argv[i]) + 1);
            setGivenFileGeo(paths, argv[i]);
            char* auxGeo = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(auxGeo, argv[i]);
            char* tempGeo = calloc(strlen(argv[i]) + 1, sizeof(char));
            if(checkRelGeo(paths)){
                char* geoArr = calloc(strlen(auxGeo) + 1, sizeof(char));
                int begin = 0;
                if(auxGeo[0] == '.' || auxGeo[0] == '/'){
                    begin++;
                    if(auxGeo[1] == '/'){
                        begin++;
                    }
                }
                removeExt(auxGeo, geoArr, begin);
                removeRelPath(geoArr, tempGeo);
                reallocGeo(paths, strlen(geoArr) + 1);
                setGivenFileGeo(paths, geoArr);
                free(geoArr);
            }
            else{
                strcpy(tempGeo, argv[i]);
                removeExt(tempGeo, tempGeo, 0);
                reallocGeo(paths, strlen(tempGeo) + 1);
                setGivenFileGeo(paths, tempGeo);
            }
            allocFileGeo(paths, strlen(tempGeo) + 1);
            setFileGeo(paths, tempGeo);
            setFileGeoTrue(pathsChecked);
            free(tempGeo);
            free(auxGeo);
        }
        else if(strcmp(argv[i], "-q") == 0)
        { 
            //Nome do arquivo qry sob o diretório Base de Entrada
            i++;
            allocGivenFileQry(paths, strlen(argv[i]) + 1);
            setGivenFileQry(paths, argv[i]);
            char* auxQry = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(auxQry, argv[i]);
            char* tempQry = calloc(strlen(argv[i]) + 1, sizeof(char));
            if(checkRelQry(paths))
            { 
                //Se o arquivo geo Fornecido tem caminho relativo
                char* qryArr = calloc(strlen(auxQry) + 1, sizeof(char));
                int begin = 0;
                if(auxQry[0] == '.' || auxQry[0] == '/')
                {
                     //Remover coisas do caminho relativo
                    begin++;
                    if(auxQry[1] == '/'){
                        begin++;
                    }
                }
                removeExt(auxQry, qryArr, begin);
                removeRelPath(qryArr, tempQry);
                reallocQry(paths, strlen(qryArr) + 1);
                setGivenFileQry(paths, qryArr);
                free(qryArr);
            }
            else{
                strcpy(tempQry, argv[i]);
                removeExt(tempQry, tempQry, 0);
                reallocQry(paths, strlen(tempQry) + 1);
                setGivenFileQry(paths, tempQry);
            }
            allocFileQry(paths, strlen(tempQry) + 1);
            setFileQry(paths, tempQry);
            setFileQryTrue(pathsChecked);
            free(tempQry);
            free(auxQry);
        }
        else if(strcmp(argv[i], "-fd") == 0){
            i++;
            double number;
            sscanf(argv[i], "%lf", &number);
            setDegFactor(paths, number);
            setDegFactorTrue(pathsChecked);
        }
        i++;
    }
    
    if(!getCheckedGivenPathIn(pathsChecked)){
        allocGivenPathIn(paths, 1);
        setGivenPathIn(paths, "");
    }
    if(!getCheckedPathIn(pathsChecked)){
        buildWholePathIn(paths);
        setPathInTrue(pathsChecked);
    }
    if(getCheckedGeo(pathsChecked) && getCheckedQry(pathsChecked)){
        char tempCat[50];
        strcpy(tempCat, getFileGeo(paths));
        strcat(tempCat, "-");
        strcat(tempCat, getFileQry(paths));
        allocCatGeoQry(paths, strlen(tempCat) + 1);
        setCatGeoQry(paths, tempCat);
    }
    if(!getCheckedDegFactor(pathsChecked)){
        setDegFactor(paths, 0.5);
        setDegFactorTrue(pathsChecked);
    }
}