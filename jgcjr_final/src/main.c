#include "paths.h"
#include "qry.h"
#include "svg.h"
#include "yxxtree.h"
#include "libraries.h"
#include "argv.h"
#include "geo.h"


int main(int argc, char* argv[])
{
    void* paths = newPaths();
    void* pathsChecked = newPathsChecked();

    setArgv(argc, argv, paths, pathsChecked);

    if(!checkCheckedPaths(pathsChecked))
    {
        printf("Erro: faltando parametro(s) obrigatório(s)\n");
        //freeCheckedPaths(pathsChecked);
        //freePaths(paths);
        return 0;
    }
    
    YxxTree tree = getParametersGeo(paths);

    FILE* pGeoSvg = newSvg(getPathOut(paths), getFileGeo(paths));
    writeSvg(pGeoSvg, tree);
    closeSvg(pGeoSvg);

    if(getCheckedQry(pathsChecked))
    {
        FILE* pTxt = newReport(paths);
        readQry(pTxt, tree, paths, pathsChecked);
        endReport(pTxt);    
    }

    /* freeTree(tree);
    freeCheckedPaths(pathsChecked);
    freePaths(paths); */
}
