#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>

using namespace std;
static long long edge_count = 0;                            // variable to keep track of the number of edges 
static long long int seed = 2000;                           // seed value for the rand() function

struct vertexNode{                                          // Vertex structure for the adjacency list , destination, weight and the next pointer 
    int dest;   
    int weight;
    vertexNode *next;
};

struct adjList {                                            // Adjacency list structure consisting of array of vertices 
    vertexNode *head ;
};

struct Edge {                                               // Edge structure for the graph , useful in Kruskal algorithm -> source, destination, weight and next pointer 
    int src;
    int dest;
    int weight;
    int num;
    Edge* next;
};

struct Graph{                                               // Actual graph structure -> Number of vertices, array of linked list (adjList), linked list of edges 
    int V;
    adjList *array;
    int edgeCount ;
    Edge* edgehead;
};

struct MSTGraph{                                            // Graph structure for creating Maximum Spanning tree , does not need edges for this 
    int V;
    adjList *array;
};

struct vertexNode* addNewnode(int dest, int weight){                                          // Function to create a new vertex node 
    struct vertexNode* newNode = (struct vertexNode*)malloc(sizeof(struct vertexNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
Edge * createEdge(int node1, int node2, int weight){                                    // Function to create a new edge node 
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->src = node1;
    newEdge->dest = node2;
    newEdge->weight = weight;
    newEdge->num = 0;
    newEdge->next = NULL;
    return newEdge;
}

void addEdge(struct Graph* graph,int dest, int source){                     // Function to add an edge , this updates both the adjacency list and the edge strcuture 
    graph->edgeCount++; 
    srand((graph->edgeCount)*rand()*(seed)*(seed));
    seed++;
   int wt = rand()%10000+1 ;
  //int wt = weight;
  //  cout << endl << "Weight = " << wt ;
   // cout << endl; 
    struct vertexNode* newNode1 = addNewnode(dest,wt);
    newNode1->next = graph->array[source].head;
    graph->array[source].head = newNode1;

    struct vertexNode* newNode2 = addNewnode(source,wt);
    newNode2->next = graph->array[dest].head;
    graph->array[dest].head = newNode2;


    struct Edge* newEdge = createEdge(source,dest,wt);
    edge_count++;
    newEdge->num = edge_count; 
    newEdge->next = graph->edgehead ;
    graph->edgehead = newEdge;      
}

void addMSTEdge(struct MSTGraph* graph,int dest, int source, int weight){           // Adding edges for MST graph (used in Kruskal)
    struct vertexNode* newNode3 = addNewnode(dest,weight);
    newNode3->next = graph->array[source].head;
    graph->array[source].head = newNode3;

    struct vertexNode* newNode4 = addNewnode(source,weight);
    newNode4->next = graph->array[dest].head;
    graph->array[dest].head = newNode4;
}

struct MSTGraph* createMSTGraph(int V){                                                   // Function to create MST graph 
    struct MSTGraph* newGraph = (struct MSTGraph*)malloc(sizeof(struct MSTGraph));
    newGraph-> V = V;
    newGraph->array = (struct adjList*)malloc(V*sizeof(struct adjList));
    for(int i =0;i<V;i++){
        newGraph->array[i].head = NULL;
    }
    return newGraph;
}

struct Graph* createSparseGraph(int V){                                             // Function to create a sparse graph with average degree of 6 
    struct Graph* newGraph = (struct Graph*)malloc(sizeof(struct Graph));
    newGraph-> V = V;
    newGraph->edgeCount = 0;
    newGraph->array = (struct adjList*)malloc(V*sizeof(struct adjList));
    for(int i =0;i<V;i++){
        newGraph->array[i].head = NULL;
    }
    newGraph->edgehead = NULL;
 /*   addEdge(newGraph,0,4,4);
    addEdge(newGraph,0,3,2);
    addEdge(newGraph,0,1,3);
    addEdge(newGraph,0,2,2);
    addEdge(newGraph,4,3,1);
    addEdge(newGraph,1,3,4); */
   for (int i = 0; i < V; i++){                                                 // Adding edges to all the adjacent vertices and creating a cycle so that the graph is connected 
        srand((i+1)*rand()*rand()*(seed));
        seed++;
        addEdge(newGraph,i%V,(i+1)%V);
    }
        std::random_device rd1;
        std::default_random_engine generator1;
        std::poisson_distribution<int> distribution1(6);                        // Poisson distribution makes sure that the average degree is 6 when adding edges 
   // int count=0;
    for (int j =0; j < V; j++){
        int degree = 0;        
        int flag;
        degree = distribution1(generator1);                                     // This is where the number of edges for each vertex is decided and overall average is 6 
     /*   if (j == 30){
            cout << "Degree value -> " <<  degree << endl;
        }*/
        
       for (int k = 0; k < degree; k++){
            srand((k+1)*rand()*rand()*(seed++));
            int x = (int)rand()%(V-1)+1;  
            flag = 0;         
            if ((j!=x) && (newGraph->array[j].head == NULL)){          // check for self loops and also if the vertex has no edges create one without checking any further
                srand((k+1)*rand()*rand()*(seed++));
                addEdge(newGraph,j,x);
            }
            else {
                for (vertexNode* itr = newGraph->array[j].head ; itr!=NULL ; itr = itr->next ){        // check if an edge already exists 
                    if (j==x || itr->dest == x){
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0){                                                                 
                    srand((k+1)*rand()*rand()*seed++);
                    addEdge(newGraph,j,x);
                }
                else{
                    continue;
                }
            }
        }
       // cout << "Edge Count for 2930 -> " << count << endl;
    }
    
    return newGraph;
}

struct Graph* createDenseGraph(int V){                                                // Function create a dense graph where each vertex is adjacent to about 20% of the other vertices 
    struct Graph* newGraph2 = (struct Graph*)malloc(sizeof(struct Graph));
    newGraph2-> V = V;
    newGraph2->array = (struct adjList*)malloc(V*sizeof(struct adjList));
    for(int i =0;i<V;i++){
        newGraph2->array[i].head = NULL;
    }
  /*  newGraph->edgehead = NULL;
    addEdge(newGraph,0,4,4);
    addEdge(newGraph,0,3,2);
    addEdge(newGraph,0,1,3);
    addEdge(newGraph,0,2,2);
    addEdge(newGraph,4,3,1);
    addEdge(newGraph,1,3,4); */

    for (int i = 0; i < V; i++){                                        // Adding edges to all the adjacent vertices and creating a cycle so that the graph is connected 
        srand((i+1)*rand()*rand()*(seed));
        seed++;
        addEdge(newGraph2,i%V,(i+1)%V);
    }        
    std::random_device rd;
    std::default_random_engine generator (rd());
    std::poisson_distribution<int> distribution(1000);                  // Poisson distribution makes sure that the average degree is 6 when adding edges
    for (int j =0; j < V; j++){
        int degree = 0;
        int flag;
        degree = distribution(generator);                               // This is where the number of edges for each vertex is decided and overall average is 1000 (because total number of vertices is 5000)
     //   cout << "Degree value -> " <<  degree << endl;
        for (int k = 0; k < degree; k++){
            srand((k+1)*rand()*rand()*(seed));
            seed++;
            int x = rand()%(V-1)+1;  
            flag = 0;         
            if ((j!=x) && (newGraph2->array[j].head == NULL)){          // check for self loops and also if the vertex has no edges create one without checking any further
                srand((k+1)*rand()*rand()*(seed++));
                addEdge(newGraph2,j,x);
            }
            else {
                for (vertexNode* itr = newGraph2->array[j].head ; itr!=NULL ; itr = itr->next ){        // check if an edge already exists 
                    if ((j==x) || (itr->dest == x)){
                        flag = 1;
                        break;
                    }
                }
           //     cout<< "Flag value -> " << flag << endl;
                if (flag == 0){
                    srand((k+1)*rand()*rand()*(seed));
                    seed++;
                    addEdge(newGraph2,j,x);
                }
                else{
                    continue;
                }
            }
        }
        
    }
    return newGraph2;
}

void printGraph(struct Graph* graph, int type)                                          // Function to print the graph , if type = 0 we print adjacency list and if type =1 we print list of edges 
{   if (type == 0){ 
        for (int v = 0; v < graph->V; ++v)
        {
            struct vertexNode* node_itr = graph->array[v].head;
            cout << "\nAdjacency list of vertex " << v << " head";
            while (node_itr)
            {
                cout << "-> " << node_itr->dest << " (" << node_itr->weight << ")";
                node_itr = node_itr->next;
            }
            cout<<"\n";
        }
    }
    else{

       for (Edge* itr = graph->edgehead ; itr!=NULL; itr = itr->next){
           cout << "(" << itr->src << ", " << itr->dest << ", " << itr->weight << ")"<< " ";
       }
       cout << "\n";
    }
}

void printMSTGraph(struct MSTGraph* graph)                                              // Function to print MST graph 
{  
        for (int v = 0; v < graph->V; ++v)
        {
            struct vertexNode* node_itr = graph->array[v].head;
            cout << "\nAdjacency list of vertex " << v << " head";
            while (node_itr)
            {
                cout << "-> " << node_itr->dest << " (" << node_itr->weight << ")";
                node_itr = node_itr->next;
            }
            cout<<"\n";
        }

}

