#include "line.h"
#include "txt.h"
#include "yxxtree.h"
#include "circle.h"
#include "rectangle.h"
#include "info.h"
#include "queue.h"

struct ternaryTree
{
    double degFactor;
    int size;
    struct treeNode* root;
};

struct treeNode
{
    double x, y;
    Info info;
    bool removed;
    struct treeNode* se, *sm, *sd;
};


YxxTree newYxxTree(double fd)
{
    struct ternaryTree* new = (struct ternaryTree*)malloc(sizeof(struct ternaryTree));
    new->degFactor = fd;
    new->size = 0;
    new->root = NULL;
    return new;
}

Node allocNewNode(double x, double y, Info info)
{
    struct treeNode* new = (struct treeNode*)malloc(sizeof(struct treeNode));
    new->x = x;
    new->y = y;
    new->info = info;
    new->removed = false;
    new->se = new->sm = new->sd = NULL;
    return new;
}

int getSize(YxxTree tree)
{
    struct ternaryTree* aux = tree;
    return aux->size;
}

double getFd(YxxTree tree)
{
    struct ternaryTree* aux = tree;
    return aux->degFactor;
}

Node insertYxxT(YxxTree tree, Node node, double x, double y, Info info)
{
    struct ternaryTree* auxTree = tree;
    if(!node){
        node = allocNewNode(x, y, info);
        if(getSize(tree) == 0){
            auxTree->root = node;
        }
        auxTree->size++;
        return node;
    }
    struct treeNode* aux = node;
    if(y < aux->y){
        aux->se = insertYxxT(tree, aux->se, x, y, info);
    }
    else if(x < aux->x){
        aux->sm = insertYxxT(tree, aux->sm, x, y, info);
    }
    else{
        aux->sd = insertYxxT(tree, aux->sd, x, y, info);
    }
    return node;
}

Node trasverseGetNode(Node node, double x, double y, double epsilon, Node requested)
{
    struct treeNode* aux = node;
    if(fabs(aux->x - x) < epsilon && fabs(aux->y - y) < epsilon){
        return node;
    }
    if(aux->se){
        requested = trasverseGetNode(aux->se, x, y, epsilon, requested);
    }
    if(aux->sm){
        requested = trasverseGetNode(aux->sm, x, y, epsilon, requested);
    }
    if(aux->sd){
        requested = trasverseGetNode(aux->sd, x, y, epsilon, requested);
    }
    return requested;
}

Node getNodeYxxT(YxxTree tree, double x, double y, double epsilon)
{
    Node node = getRoot(tree);
    node = trasverseGetNode(getRoot(tree), x, y, epsilon, node);
    return node;
}

Info getInfoFromNode(Node node)
{
    struct treeNode* aux = node;
    return aux->info;
}

Node getRoot(YxxTree tree)
{
    struct ternaryTree* aux = tree;
    return aux->root;
}

bool getStatus(Node node)
{
    struct treeNode* aux = node;
    return aux->removed;
}

int getHeight(Node node)
{
    int height;
    if(node){
        struct treeNode* aux = node;
        int seH = getHeight(aux->se);
        int smH = getHeight(aux->sm);
        int sdH = getHeight(aux->sd);
        if(seH > smH){
            height = seH + 1;
        }
        else{
            height = smH + 1;
        }
        if(sdH > height){
            height = sdH + 1;
        }
        return height;
    }
    return 0;
}

bool goSd(Node node, double x, double y)
{ 
    //Extensão da região abaixo e a direita do ponto
    struct treeNode* aux = node;
    if(y >= aux->y && x >= aux->x){
        return true;
    }
    return false;
}

bool goSm(Node node, double x, double y)
{ 
    //Extensão da região abaixo e à esquerda do ponto
    struct treeNode* aux = node;
    if(y >= aux->y && x <= aux->x){
        return true;
    }
    return false;
}

bool goSe(Node node, double y)
{ 
    //Extensão da região acima do ponto
    struct treeNode* aux = node;
    if(y <= aux->y){
        return true;
    }
    return false;
}

bool checkInsideArea(Info i, double x1, double y1, double x2, double y2)
{
    bool checker;
    if(getInfoType(i) == 'c'){
        checker = checkCircle(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 'r'){
        checker = checkRect(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 'l'){
        checker = checkLine(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 't'){
        checker = checkTxt(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    return checker;
}

void trasverseSearch(YxxTree tree, Node node, List list, int depth, double x1, double y1, double x2, double y2)
{
    struct treeNode* auxNode = node;
    if(auxNode->se){
        if(goSe(auxNode, y1)){
            trasverseSearch(tree, auxNode->se, list, depth, x1, y1, x2, y2);
        }
    }
    if(auxNode->sm){
        if(goSm(auxNode, x1, y2)){
            trasverseSearch(tree, auxNode->sm, list, depth, x1, y1, x2, y2);
        }
    }
    if(auxNode->sd){
        if(goSd(auxNode, x2, y2)){
            trasverseSearch(tree, auxNode->sd, list, depth, x1, y1, x2, y2);
        }
    }
    if(checkInsideArea(auxNode->info, x1, y1, x2, y2)){
        insertList(list, getInfoFromNode(node));
    }
}

List getNodesDentroRegiaoYxxT(YxxTree tree, double x1, double y1, double x2, double y2)
{
    List list = newList();
    trasverseSearch(tree, getRoot(tree), list, 0, x1, y1, x2, y2);
    return list;
}

void trasverseYxxT(Node node, FvisitaNo f, void* aux, int depth)
{
    if(!node){
        return;
    }
    struct treeNode* nodeAux = node;
    trasverseYxxT(nodeAux->se, f, aux, depth);
    trasverseYxxT(nodeAux->sm, f, aux, depth + 1);
    trasverseYxxT(nodeAux->sd, f, aux, depth + 1);
    Info info = getInfoFromNode(node);
    f(info, nodeAux->x, nodeAux->y, aux);
}

void visitaProfundidadeYxxT(YxxTree tree, FvisitaNo f, void* aux)
{
    trasverseYxxT(getRoot(tree), f, aux, 0);
}

void printLvl(Info i, double x, double y, void* aux)
{
    FILE* pTxt = aux;
    fprintf(pTxt, "x: %lf y: %lf ", x, y);
    if(getStatus(i)){
        fprintf(pTxt, "REMOVIDA");
    }
    fprintf(pTxt, "\n");
}

void trasverseLvlYxxTree(Node node, FvisitaNo f, void* aux, int level)
{
    if(!node){
        return;
    }
    struct treeNode* nodeAux = node;
    if(level == 1){
        f(node, nodeAux->x, nodeAux->y, aux);
    }
    else if(level > 1){
        trasverseLvlYxxTree(nodeAux->se, f, aux, level - 1);
        trasverseLvlYxxTree(nodeAux->sm, f, aux, level - 1);
        trasverseLvlYxxTree(nodeAux->sd, f, aux, level - 1);
    }
}

void visitaLarguraYxxT(YxxTree tree, FvisitaNo f, void* aux)
{
    f = printLvl;
    trasverseLvlYxxTree(getRoot(tree), f, aux, getHeight(getRoot(tree)));
}

int compare(void* a, void* b)
{
    return(*(double*)a - *(double*)b);
}

void reorganizeTreeNodes(Info i, double x, double y, void* aux){
    if(getRear(aux) == 97)
    {
        //qsort(aux, 97, sizeof(void*), compare);
        freeQueue(aux);
        aux = newQueue(97);
        enqueue(aux, x, y);
    }
}


int getRmvTotal(Node node, int depth, int total)
{
    if(!node){
        return total;
    }
    struct treeNode* nodeAux = node;
    total = getRmvTotal(nodeAux->se, depth, total);
    total = getRmvTotal(nodeAux->sm, depth + 1, total);
    total = getRmvTotal(nodeAux->sd, depth + 1, total);
    if(getStatus(node)){
        total++;
    }
    return total;
}

void freeOldTree(Node node, int depth)
{
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    freeOldTree(aux->se, depth);
    freeOldTree(aux->sm, depth + 1);
    freeOldTree(aux->sd, depth + 1);
    free(node);
}

void rebuildTreeNodes(YxxTree tree, Node node){
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    if(!getStatus(node)){
        Node root = getRoot(tree);
        root = insertYxxT(tree, root, aux->x, aux->y, aux->info);
    }
    rebuildTreeNodes(tree, aux->se);
    rebuildTreeNodes(tree, aux->sm);
    rebuildTreeNodes(tree, aux->sd);
}

void rebuildTree(YxxTree tree)
{
    struct ternaryTree* aux = tree;
    Node oldRoot = aux->root;
    aux->root = NULL;
    aux->size = 0;
    rebuildTreeNodes(tree, oldRoot);
    freeOldTree(oldRoot, 0);
}

void removeNoYxxT(YxxTree tree, Node node)
{
    struct treeNode* aux = node;
    aux->removed = true;
    int totalRmv = getRmvTotal(getRoot(tree), 0, 0);
    int totalNodes = getSize(tree);
    if((double)totalRmv / totalNodes > getFd(tree)){
        rebuildTree(tree);
    }
}

void printTreeNodes(Node node, int depth)
{
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    printTreeNodes(aux->se, depth);
    printTreeNodes(aux->sm, depth + 1);
    printTreeNodes(aux->sd, depth + 1);
    printf("(%lf, %lf)", aux->x, aux->y);
}

void printTree(YxxTree tree)
{
    printf("\n===TREE===\n");
    printTreeNodes(getRoot(tree), 0);
}

void freeTree(YxxTree tree)
{
    freeTreeNodes(getRoot(tree));
    free(tree);
}

void freeTreeNodes(Node node)
{ 
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    freeTreeNodes(aux->se);
    freeTreeNodes(aux->sm);
    freeTreeNodes(aux->sd);
    freeInfo(aux->info);
    free(aux);
}
