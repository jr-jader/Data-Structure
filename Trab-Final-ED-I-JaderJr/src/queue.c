#include "queue.h"

struct queue
{
    int front, rear, size;
    CoordArr coord;
};

Queue newQueue(int size)
{
    struct queue* new = (struct queue*)malloc(sizeof(struct queue));
    new->front = new->rear =  0;
    new->size = size + 1; //Fila sempre tem um lugar livre restante
    new->coord = malloc(sizeof(void*) * size);
    return new;
}

bool isFull(Queue queue)
{
    struct queue* aux = queue;
    if((aux->rear + 1) % aux->size == aux->front){
        return true;
    }
    return false;
}

bool isEmpty(Queue queue)
{
    struct queue* aux = queue;
    if(aux->front == aux->rear){
        return true;
    }
    return false;
}

int getRear(Queue queue)
{
    struct queue* aux = queue;
    return aux->rear;
}

Coord getFirstCoord(Queue queue)
{
    struct queue* aux = queue;
    return aux->coord[aux->front + 1];
}

Coord getCoordAtPos(Queue queue, int position)
{
    struct queue* aux = queue;
    return aux->coord[position];
}

int getQueueSize(Queue queue)
{
    struct queue* aux = queue;
    return abs(aux->rear - aux->front);
}

void enqueue(Queue queue, double x, double y)
{
    if(isFull(queue)){
        printf("\nErro: impossivel adicionar elemento, fila circular estatica cheia\n");
        return;
    }
    struct queue* aux = queue;
    aux->rear++;
    Coord coord = newCoord();
    insertCoord(coord, x, y);
    if(aux->rear > aux->size)
    { 
        //Já chegou ao fim da fila, mas é circular e resta espaço
        aux->rear = 0;
        aux->coord[aux->rear] = coord;
    }
    else{
        aux->coord[aux->rear] = coord;  
    }
}

void dequeue(Queue queue, Coord coord)
{
    if(isEmpty(queue)){
        printf("\nErro ao remover elemento: fila circular estatica vazia\n");
        return;
    }
    struct queue* aux = queue;
    freeCoord(coord);
    aux->front++;
}

void drawPolLines(FILE* pSvg, int sides, double d, double e, char color[20], double minX, double maxX, double minY, double maxY)
{
    int numberLines = (maxY - minY) / d;
    for(int i = 1; i <= numberLines; i++){
        double x1 = minX;
        double y1 = minY + i * d;
        double x2 = maxX;
        double y2 = y1;
        fprintf(pSvg, "\n\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:%s; stroke-width:%.2lf\"/>", x1, y1, x2, y2, color, e);
    }
}

void pol(FILE* pSvg, YxxTree tree, Queue queue, int i, double d, double e, char colorBorder[20], char colorFill[20])
{
    if(isEmpty(queue)){
        printf("Erro: impossivel desenhar o polígono, fila circular estática vazia\n");
        return;
    }
    fprintf(pSvg, "\n\t<polygon points=\"");
    Node root = getRoot(tree);
    Info element;
    StructInfo infoNode;
    struct queue* aux = queue;
    Coord coord;
    int sides = 0;
    double x, y, minX, maxX, minY, maxY, x1, y1, x2, y2;
    minX = maxX = minY = maxY = 0;
    for(int j = aux->front + 1; j <= aux->rear; j++){
        coord = getCoordAtPos(queue, j);
        x = getXCoord(coord);
        y = getYCoord(coord);
        if(x < minX){
            minX = x;
        }
        if(x > maxX){
            maxX = x;
        }
        if(y < minY){
            minY = y;
        }
        if(y > maxY){
            maxY = y;
        }
        fprintf(pSvg, "%lf,%lf ", x, y);
        sides++;
        if(sides > 2){
            x1 = x2;
            y1 = y2;
            x2 = x;
            y2 = y;
            element = newLine(i, x1, y1, x2, y2, colorBorder);
            infoNode = newInfo('l', element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
            i++;
        }
        else if(sides == 2){
            x2 = x;
            y2 = y;
            element = newLine(i, x1, y1, x2, y2, colorBorder);
            infoNode = newInfo('l', element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
            i++;
        }
        else{
            x1 = x;
            y1 = y;
        }
    }
    fprintf(pSvg, "\" style=\"fill-opacity: 0; stroke: %s\"/>", colorBorder);
    drawPolLines(pSvg, sides, d, e, colorFill, minX, maxX, minY, maxY);
}

bool freeAllCoord(Queue queue){
    struct queue* aux = queue;
    void* coord;
    if(isEmpty(queue) == 0){
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coord = getFirstCoord(queue);
            freeCoord(coord);
            aux->front++;
        } while(aux->front != aux->rear);
        aux->front = aux->rear = 0;
        return true;
    }
    return false;
}

void freeQueue(Queue queue){
    struct queue* aux = queue;
    if(!isEmpty(queue)){
        struct queue* aux = queue;
        Coord coord;
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coord = getFirstCoord(queue);
            freeCoord(coord);
            aux->front++;
        } while(aux->front != aux->rear);
    }
    free(aux->coord);
    free(aux);
}