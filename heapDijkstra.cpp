#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <math.h> 
#include "graph_generation.h"
#include "Dijkstras.h"

using namespace std;

struct MaxHeapNode                                      // Heap node structure  to store fringes in the max hap 
{
    int  v;
    int bw;
};

struct MaxHeap                                            // Max heap structure for fringes 
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for updating the bandwidth values of the fringes 
    int *pos;   
    struct MaxHeapNode **array;
};

struct MaxHeapNode* newMaxHeapNode(int v,int bw)                                    // Create a new heap nodes 
{
    struct MaxHeapNode* maxHeapNode =(struct MaxHeapNode*)malloc(sizeof(struct MaxHeapNode));
    maxHeapNode->v = v;
    maxHeapNode->bw = bw;
    return maxHeapNode;
}

struct MaxHeap* createMaxHeap(int capacity)                                          // Create new Max heap and inttialize it 
{
    struct MaxHeap* maxHeap = (struct MaxHeap*)malloc(sizeof(struct MaxHeap));
    maxHeap->pos = (int *)malloc(capacity * sizeof(int));
    for (int i =0; i<capacity;i++){
        maxHeap->pos[i] = -1;
    }
    maxHeap->size = 0;
    maxHeap->capacity = capacity;
    maxHeap->array = (struct MaxHeapNode **)malloc(capacity *sizeof(struct MaxHeapNode*));
    return maxHeap;
}

void swapMaxHeapNode(struct MaxHeapNode** a,struct MaxHeapNode** b)                // Swap the heap nodea , useful in heapify functions 
{
    struct MaxHeapNode* t = *a;
    *a = *b;
    *b = t;
}

int isEmpty(struct MaxHeap* maxHeap)         // check if max heap is empty 
{   
    return maxHeap->size == 0;
}

void downheapify(struct MaxHeap* heap,int index){               // heapify function used for heap sort 
  //  printf("In the start downheapify function\n");
    int largest, left, right;
    largest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
    if (left < heap->size && heap->array[left]->bw > heap->array[largest]->bw)
        largest = left;
    if (right < heap->size && heap->array[right]->bw > heap->array[largest]->bw)
        largest = right;      

    if (largest != index){
        MaxHeapNode* largestNode = heap->array[largest];
        MaxHeapNode* cur_Node = heap->array[index];

        heap->pos[largestNode->v] = index;
        heap->pos[cur_Node->v] = largest;

        swapMaxHeapNode(&heap->array[largest],&heap->array[index]);
        downheapify(heap,largest);
    }
   // printf("In the end downheapify function\n");

}

void upheapify(struct MaxHeap* heap,int index){                         // Used in updateFringeheap function when a fringe is revisited and its BW has to be changed
  //  printf("In the start upheapify function\n");
    int parent ;
    while(index > 0 ){
        parent = floor((index-1)/2);
        
        if (heap->array[index]->bw > heap->array[parent]->bw){
            heap->pos[heap->array[index]->v] = parent;
            heap->pos[heap->array[parent]->v] = index;
            swapMaxHeapNode(&heap->array[parent],&heap->array[index]);
            index = parent;
        }
        else {
            heap->pos[heap->array[index]->v] = index;
            break;
        }
    }
   // printf("In the end upheapify function\n");
}

void insertFringe(struct MaxHeap* heap, int v, int bw){             // Function to implement Fring insertion into the heap 
   // printf("In the start insertFringe function\n");
    struct MaxHeapNode* fringe = newMaxHeapNode(v,bw);
    heap->size++;
    heap->array[heap->size-1] = fringe;
    heap->pos[fringe->v] = heap->size-1;
    upheapify(heap,heap->size-1);
   // printf("In the end insertFringe function\n");
}

void updateFringeheap(struct MaxHeap* heap,int v,int bw){           // Update the BW of the fringe in the Maxheap , we use the pos array to find the index of the fringe in the heap array 
  //  printf("In the start updateFringe function\n");
    int req_index = heap->pos[v];
  //  printf("req_index: %d\n",req_index);
    heap->array[req_index]->bw = bw;
  //  printf("In the end updateFringe function\n");
    upheapify(heap,req_index);
    
}

struct MaxHeapNode* maxFringe(struct MaxHeap* heap){                    // Return the fringe with the max BW i.e the first element in the heap array and update the heap 
  //  printf("In the start maxFringe function\n");
     if (isEmpty(heap)){
         return NULL;
     }
    struct MaxHeapNode* root = heap->array[0];
    struct MaxHeapNode* lastNode = heap->array[heap->size-1];
    heap->size-- ;
    heap->array[0] = lastNode;
    heap->pos[root->v] = -1;
    heap->pos[lastNode->v] = 0;
    downheapify(heap,0);
  //  printf("In the end maxFringe function\n");
    return root;
}
// status value => Unseen = -1 , Fringe = 0, In-tree = 1 , 
void Dijkstraheap(Graph* graph,int s, int t){                           // Implementation of Dijkstras algorithm but the fringe with max value is fetched from the max heap that is constantly updated 
    int status[graph->V];
    int dad[graph->V];
    int bw[graph->V];

    struct MaxHeap* fringeHeap = createMaxHeap(graph->V);               // Create a new MaxHeap to store fringes  
    for (int j = 0 ; j < graph->V; j++){                                // Initializing the arrays
        status[j] = -1;                                                 // status -> array to store the status of the vertices (in-tree,fringe or unseen)
        dad[j] = -1;                                                    // dad -> parent array which is helpful in prinitng the path
        bw[j] = -1;                                                     // Array that stores the bandwith values for each vertex 
    }

    status[s] = 1;                                                      // Set the status of the source vertex to be in-tree (1)

    for (vertexNode* itr = graph->array[s].head; itr !=NULL; itr = itr->next){          // check all the adjacent vertices and mark them as fringes and update the BW
        status[itr->dest] = 0;
        dad[itr->dest] = s;
        bw[itr->dest] = itr-> weight;                                                  // BW is equal to the weight of the edges 
        insertFringe(fringeHeap,itr->dest,bw[itr->dest]);                              // Once it is marked as fringe , add it to the max heap 
    }
   /* printf("Heap array is as below \n");
    for (int i =0; i < fringeHeap->size; i++){
        printf("%d - ",fringeHeap->array[i]->v);
    }*/
    while(!isEmpty(fringeHeap)){                                                       // Loop to check all the fringes if they exist , i.e check if the Maxheap is empty 
        struct MaxHeapNode* max_fringe = maxFringe(fringeHeap);                        // Fetch the fringe with max BW from the Max Heap
        int max = max_fringe->v;
        status[max] = 1;                                                                
        for (vertexNode* itr2 = graph->array[max].head; itr2 != NULL; itr2=itr2->next){         // Check the adjacent vertices of the max fringe 
            if (status[itr2->dest] == -1){                                                      // Case where adjacent vertex is still unseen 
                status[itr2->dest] = 0 ;            
                bw[itr2->dest] =  minfunction(bw[max],itr2->weight) ;
                dad[itr2->dest] = max; 
                insertFringe(fringeHeap,itr2->dest,bw[itr2->dest]);                             // Add the fringe to Maxheap             
            }
            else if ((status[itr2->dest] == 0 ) && (bw[itr2->dest] < minfunction(bw[max],itr2->weight))){          //  Case where adjacent vertex is a fringe 
                bw[itr2->dest] = minfunction(bw[max],itr2->weight);
                dad[itr2->dest] = max;
                updateFringeheap(fringeHeap,itr2->dest,bw[itr2->dest]);                                 // Update the BW value of the fringe in the Maxheap and heapify 
            }
        }

    }
    if (status[t] != 1){                                                        // If status value of destination is not in-tree , then no path exists
        cout << "No Path exists between " << s <<" - " << t << endl;
    }
    else {
        cout << "Maximum Bandwidth is " << bw[t] << endl;                       // Print the maximum BW
        int x = t;
        cout << "Path is as below " << endl;
        cout << x;  
        while(x!=s){                                                            // Print the path 
            x = dad[x]; 
            cout << " <- " << x;
        }
        cout << endl;
    }
}