#ifndef KRUSKAL_H
#define KRUSKAL_H

struct edgeHeapNode {
    int src;
    int dest;
    int weight;
};

struct edgeHeap{
    int capacity ;
    int size ;
    struct edgeHeapNode **array;
};

struct edgeHeapNode* newHeapNode(Edge * edge){
    struct edgeHeapNode* HeapNode =(struct edgeHeapNode*)malloc(sizeof(struct edgeHeapNode));
    HeapNode->src = edge->src;
    HeapNode->dest= edge->dest;
    HeapNode->weight = edge->weight;
    return HeapNode;
}

struct edgeHeap* createEdgeHeap(int capacity){
    struct edgeHeap* edgeHeap = (struct edgeHeap*)malloc(sizeof(struct edgeHeap));
    edgeHeap->capacity = capacity;
    edgeHeap->size = 0;
    edgeHeap->array = (struct edgeHeapNode **)malloc(capacity *sizeof(struct edgeHeapNode*));
    return edgeHeap;
}

void swapEdgeHeapNode(struct edgeHeapNode** a,struct edgeHeapNode** b);
void upheapify(struct edgeHeap* heap,int index);
void downheapify(struct edgeHeap* heap,int index,int size);
void heapSort(struct edgeHeap*, int n);
void insertEdge(struct edgeHeap* heap,Edge * edge);
void Makeset(int v,int* parent, int* rank);
int Find(int v, int* parent, int* rank);
void Union(int r1, int r2, int* parent, int* rank);

struct Queue {
    int front,rear;
    int size;
    int capacity;
    int* array;
};
 
struct Queue* createQueue(int capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
void BFS(MSTGraph* graph,int s,int t);
void Kruskal(Graph* graph,int s, int t);

#endif