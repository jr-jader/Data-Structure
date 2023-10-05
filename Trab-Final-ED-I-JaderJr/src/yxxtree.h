#include "list.h"
#include "libraries.h"

#ifndef YXXTREE_H
#define YXXTREE_H

/*Manipulação da àrvore YXX YXXTRE é uma àrvore ternária que contem 3 ramificações (sd se, sm), coordenadas (y,x), A forma armazenada e um char auxiliar para facilidar a idd de cada forma*/
typedef void* Node;
typedef void* Info;
typedef void* YxxTree;

//Cria uma arvore YXX com o fator de degradação FD
YxxTree newYxxTree(double fd);

//Insere  informação dentro da info associada à ancora x e y na arvore tree, tomarnando indentificador para o nó que foi inserido
Node insertYxxT(YxxTree tree, Node node, double x, double y, Info info);

//Processa a info i, associando a um nó, cuja ancora é o ponto x e y. O aux aponta para o conjunto de dados que são compartilhado  entre as invocações dessa função
typedef void (*FvisitaNo)(Info i, double x, double y, void* aux);

//Retorna True se a info i está dentro do retangulo delimitada pelos pontos (x1, y1) e (x2,y2)
typedef bool (*FdentroDe)(Info i, double x1, double y1 , double x2, double y2);

//Retorna a aultura de um nó node
int getHeight(Node node);

//Retorna a info do nó node
Info getInfoYxxT(YxxTree tree, Node node);

//Rotorna True se x e y for considerado interno da info i
typedef bool (*FatingidoPor)(Info i, double x, double y);

//Percorre a árvore, invocando f em cada nó visitado e o apontador aux é parametro de invocação para f
void visitaLarguraYxxT(YxxTree tree, FvisitaNo f, void* aux);

//Retorna a raiz da arvore
Node getRoot(YxxTree tree);

//Percorre a àrvore em profundidade. invocando f em cada nó visitado e o apontador aux é parametro de invocação para f
void visitaProfundidadeYxxT(YxxTree tree, FvisitaNo f, void* aux);

//Retorna o nó da ancora que é o ponto x e y, aceitando uma discripancia entre o ponto e a ancora
Node getNodeYxxT(YxxTree tree, double x, double y, double epsilon);

//Remove o nó do node; caso, após a remoção o fator de degradação supere o limite definido na criação da arvore, ela é recriada sem os nós removidos
void removeNoYxxT(YxxTree tree, Node node);

//Retorna uma list dos nós cujas ancoras estão dentro da região determinada pelos pontos x1,y1 e x2,y2
List getNodesDentroRegiaoYxxT(YxxTree tree, double x1, double y1, double x2, double y2);

//Libera o espaço alocado para a árvore yxx
void freeTree(YxxTree tree);

#endif