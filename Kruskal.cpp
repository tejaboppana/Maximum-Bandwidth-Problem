#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <math.h> 
#include <time.h>
#include <iomanip>
#include "graph_generation.h"
#include "Dijkstras.h"

using namespace std;

struct edgeHeapNode {                                           // Heap node which will be used by the heap for heap sorting, edges are stored here
    int src;
    int dest;
    int weight;
};

struct edgeHeap{                                              // Heap structure for the edges 
    int capacity ;
    int size ;
    struct edgeHeapNode **array;
};


struct Queue {                                                                      // Queue implementation for Breadth first search in the MST graph that we create from the edges 
    int front,rear;
    int size;
    int capacity;
    int* array;
};
 
struct Queue* create_queue(int capacity)                                            // Creating a queue 
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
 

int isFull(struct Queue* queue)                                         // check if the queue is full 
{
    return (queue->size== queue->capacity);
}
 

int isEmpty(struct Queue* queue)                            // check if the queue is empty 
{
    return (queue->size == 0);
}
 

void enqueue(struct Queue* queue, int item)                     // Add an element to the queue 
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear) + 1;//% queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
 
int dequeue(struct Queue* queue)                                // Remove the first element in the queue and return it 
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front) + 1;//% queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

struct edgeHeapNode* newEdgeHeapNode(Edge * edge){                                              // Function to create a new heap node
    struct edgeHeapNode* HeapNode =(struct edgeHeapNode*)malloc(sizeof(struct edgeHeapNode));
    HeapNode->src = edge->src;
    HeapNode->dest= edge->dest;
    HeapNode->weight = edge->weight;
    return HeapNode;
}

struct edgeHeap* create_edge_heap(int capacity){                                                  // Function to create a new max heap , which will be used for heap sort 
    struct edgeHeap* edgeHeap = (struct edgeHeap*)malloc(sizeof(struct edgeHeap));
    edgeHeap->capacity = capacity;
    edgeHeap->size = 0;
    edgeHeap->array = (struct edgeHeapNode **)malloc(capacity *sizeof(struct edgeHeapNode*));
    return edgeHeap;
}

void swapEdgeHeapNode(struct edgeHeapNode** a,struct edgeHeapNode** b)                             // Function to swap heap nodes
{
    struct edgeHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void upheapify(struct edgeHeap* heap,int index){                                                    // Function used to form a max heap , when you add an element to the heap , but this is not used here since heapify is being done as a part of heap sort 

    int parent ;
    while(index > 0 ){
        parent = floor((index-1)/2);
      //  printf("Parent weight == %d, Index weight = %d\n",heap->array[parent]->weight,heap->array[index]->weight);
        if (heap->array[index]->weight > heap->array[parent]->weight){
       //     printf("In the swap loop\n");
            swapEdgeHeapNode(&heap->array[parent],&heap->array[index]);
            index = parent;
        }
        else {
            break;
        }
    }
}

void downheapify(struct edgeHeap* heap,int index,int size){                                 // This is the function that is used to heapify (parent is always greater than the child in the heap)
    //printf("In the start downheapify function\n");
    int largest, left, right;
    largest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
    if (left < size && heap->array[left]->weight > heap->array[largest]->weight)
        largest = left;
    if (right < size && heap->array[right]->weight > heap->array[largest]->weight)
        largest = right;      

    if (largest != index){
        swapEdgeHeapNode(&heap->array[largest],&heap->array[index]);
        downheapify(heap,largest,size);
    }
   // printf("In the end downheapify function\n");
}

void insertEdge(struct edgeHeap* heap,Edge * edge) {                                    // Function to add an edge to the heap array 

    struct edgeHeapNode* heapNode = newEdgeHeapNode(edge);
    heap->size++;
    heap->array[heap->size-1] = heapNode;
 
}

void heapSort(struct edgeHeap* heap, int n){                                           // Function to heap sort 
    for (int i = n/2 -1 ; i >=0 ; i--){                                                // This first heapifies the heap and converts it into a max heap 
        downheapify(heap,i,n);
    }                                        
    for (int i = n - 1; i > 0; i--) {
        swapEdgeHeapNode(&heap->array[0], &heap->array[i]);                            // then we perform heap sort by swapping the root element with the last element in the array 
        downheapify(heap,0,i);
    }
}

void Makeset(int v,int* parent, int* rank){                                     // Makeset function used in the Kruskal algorithm to initialize the parent and rank arrays 
    parent[v]=-1;
    rank[v] = 0;
}

int Find(int v, int* parent, int* rank, int n){                                        // Find function which finds the parent of an element and is used in Kruskal Algorithm 
    int w = v;
    struct Queue* findQueue = create_queue(n);
    while(parent[w]!=-1){
        enqueue(findQueue,w);
        w = parent[w];    
    }
    while(!isEmpty(findQueue)){
        int x = dequeue(findQueue);
        parent[x] = w;
    }
    return w;
}

void Union(int r1, int r2, int* parent, int* rank){                             // Union function that merges two sets depending on the rank , this is again used in Kruskal algorithm 

    if (rank[r1] > rank[r2])
        parent[r2] = r1;
    else if(rank[r1] < rank[r2])
        parent[r1] = r2;
    else{
        parent[r1] = r2;
        rank[r2]+=1;
    }

}

void BFS(MSTGraph* graph,int s,int t){                                  // Function to perform breadth first search to find the shortest path between 2 nodes from the MST graph 
    int visited[graph->V];    // 0 -> not visited , 1 -> visited 
    int dad[graph->V];        // Used to keep track of path 
    int bw[graph->V];         // BW array 
    for (int i =0; i < graph->V;i++){                                   // Initialize the status (visisted) array , dad array (parent) and the bw array , here bw is between only 2 adjacent vertices . Max BW of the path will be the minimum BW across the path. 
        visited[i]=0;                                                   
        dad[i]=-1;
        bw[i] = INT_MAX;
    }
    struct Queue* vertexQueue = create_queue(graph->V);                 // Push the source vertex to the queue  
    int destination = -1;
    visited[s] = 1;                                                     // Mark it as visited
    enqueue(vertexQueue,s);                                                  
    while(!isEmpty(vertexQueue)){                                                       // Check if the queue is empty and while keeps running till its empty
        int x = dequeue(vertexQueue);                                                   // Dequeue the elements from the queue 
        for (vertexNode* itr = graph->array[x].head; itr!=NULL ; itr = itr->next){      // Check the adjacent vertices for the node 
            if (visited[itr->dest]!=1){ 
                visited[itr->dest] = 1;                                                 // If they are unvisited then mark them as visited 
                enqueue(vertexQueue,itr->dest);                                         // Push the vertex to the queue 
                bw[itr->dest] = itr->weight;                                            // Update the BW
                dad[itr->dest] = x;                                                     // Update the parent for the vertex 
            }
            if(itr->dest == t){                                                         // If this vertex that we come across is the destination then break from the while loop 
                destination = t;
                break;
            }
        }
        if (destination == t){                                                          
            break;  
        }
    }
    //t: int l = 2;
    if (visited[t]!=1){                                                             // If the status of t is still not visisted then there exists no path between s and t 
        cout << "No Path exists between " << s <<" - " << t << endl ;
    }
    else {                                                                          //  Print the max BW value by taking the min weight across the shortest path in MST 
        int x =t;
        int b = bw[t];
        while(x!=s){
             b = minfunction(b,bw[dad[x]]) ;
            x =dad[x];
        }
        cout << "Maximum Bandwidth is " << b << endl;
        x = t;
        cout << "Path is as below " << endl;                                // print the path using the dad array
        cout << x;
        while(x!=s){
            x = dad[x];
            cout << " <- " << x;
        }
        cout << endl;
    }

}
void Kruskal(Graph* graph,int s, int t){                                      // Kruskal Algorithm function 
    struct edgeHeap* edge_heap = create_edge_heap(graph->edgeCount);          // Create a new heap to store the edges 
    struct MSTGraph* mst_graph = createMSTGraph(graph->V);                    // Create new graph that will have the maximum spanning tree 
    struct Edge* head = graph->edgehead;                                      // This is the head pointer to the linked list of edges from the main graph 
    for (Edge* itr = head; itr != NULL; itr=itr->next){                       // Add each edge into the heap created previously 
        insertEdge(edge_heap,itr);
    }
    heapSort(edge_heap,graph->edgeCount);                                   // Perform heapsort on the heap (Maxheap) created , it will sort the edge in increasing order 
    int * parent = (int *)malloc(graph->V*sizeof(int));                     // Parent array to keep track of parent in the UFM operations 
    int * rank = (int *)malloc(graph->V*sizeof(int));                       // Rank array to keep track of the rank of the vertex in UFM operation 
    for (int i=0;i<graph->V;i++){                                           // Run Makeset on each vertex in the graph 
        Makeset(i,parent,rank);
    }
    int k=graph->edgeCount-1, e=0;                                          // We need to add edges from the heap from the last one since the last edge in the array has the maximum weight 
    while(k >= 0 && e < graph->V-1 ){
        struct edgeHeapNode * currentNode = edge_heap->array[k];            // Fetching the edge from the sorted heap 
        int r1 = Find(currentNode->src,parent,rank,graph->V);                        // find operation gives the parent 
        int r2 = Find(currentNode->dest,parent,rank,graph->V);                       
        if (r1 != r2){                                                      // If parents are not equal add the edge to the MST graph and also perform an union operation 
            addMSTEdge(mst_graph,currentNode->dest,currentNode->src,currentNode->weight);
            Union(r1,r2,parent,rank);
            e++;
        }
        k--;
    }
   // printMSTGraph(mst_graph);
    BFS(mst_graph,s,t);                                                     // After the MST graph is created perform BFS , in this function the path and the max BW are also printed 
   // queuetest();
}