#ifndef GRAPH_GENERATION_H
#define GRAPH_GENERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>

//extern long long edge_count ;  // keeps a count of number of edges in the graphs and each edge is assigned  a number , helps to check if edges are sorted in Kruskal 

struct vertexNode{
    int dest;
    int weight;
    vertexNode *next;
};

struct adjList {
    vertexNode *head ;
};

struct Edge {
    int src;
    int dest;
    int weight;
    int num;
    Edge* next;
};

struct Graph{
    int V;
    adjList *array;
    int edgeCount ;
    Edge* edgehead;
};

struct MSTGraph{
    int V;
    adjList *array;
};

void addMSTEdge(struct MSTGraph* graph,int dest, int source, int weight);
struct MSTGraph* createMSTGraph(int V);

struct vertexNode* addNewnode(int dest,int weight);
Edge * createEdge(int node1, int node2,int weight);

void addEdge(struct Graph* graph,int dest, int source, int weight);

struct Graph* createSparseGraph(int V);

struct Graph* createDenseGraph(int V);

void printGraph(struct Graph* graph, int type);
void printMSTGraph(struct MSTGraph* graph);

#endif