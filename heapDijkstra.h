#ifndef HEAPDIJKSTRA_H
#define HEAPDIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "graph_generation.h"

struct MaxHeapNode
{
    int  v;
    int bw;
};

struct MaxHeap
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for updating the bandwidth values of the fringes 
    int *pos;   
    struct vertexNode **array;
};


struct MaxHeapNode* newMaxHeapNode(int v,int bw);
struct MaxHeap* createMaxHeap(int capacity);
void swapMaxHeapNode(struct MaxHeapNode** a,struct MaxHeapNode** b);
int isEmpty(struct MaxHeap* maxHeap);
void downheapify(struct MaxHeap* heap,int index);
void upheapify(struct MaxHeap* heap,int index);
void insertFringe(struct MaxHeap* heap, int v, int bw);
void updateFringeheap(struct MaxHeap* heap,int v,int bw);
struct MaxHeapNode* maxFringe(struct Maxheap* heap);
void Dijkstraheap(Graph* graph,int s, int t);

#endif