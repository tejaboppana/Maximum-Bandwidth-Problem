#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "graph_generation.h"

// status value => Unseen = -1 , Fringe = 0, In-tree = 1 , 

using namespace std;

bool checkFringes(int *status, int V){          // Function to check if fringes exist 
    bool result = false;
    for (int f =0; f < V; f++){
        if (status[f] == 0){
            result = true;
            break;
        }
    }
    return result;
}

int maxFringe(int *bw,int *status,int V){       // function that fetches the fringe vertex with max bandwidth
    int max_bw = -1;
    int max = -1;
    for (int i = 0; i < V; i++){
        if(status[i] == 0 && bw[i] > max_bw){
            max_bw = bw[i];
            max = i;
        }
    }
    return max;
}

int minfunction(int a, int b){                   // Fucntion to fetch the minimum value 
    int min;
    if (a < b)
        min = a ;
    else
        min = b ;
    return min;
}
void Djikstras (Graph* graph,int s, int t){            //Main Djikstras algorithm implementation
    int status[graph->V];
    int dad[graph->V];
    int bw[graph->V];
    for (int j = 0 ; j < graph->V; j++){               // Initializing the arrays  
        status[j] = -1;                                // status -> array to store the status of the vertices (in-tree,fringe or unseen)
        dad[j] = -1;                                   // dad -> parent array which is helpful in prinitng the path 
        bw[j] = -1;                                    // Array that stores the bandwith values for each vertex 
    }

    status[s] = 1;                                     // Set the BW of the source vertex to 0
   // bw[s] = 0;

    for (vertexNode* itr = graph->array[s].head; itr !=NULL; itr = itr->next){        // check all the adjacent vertices and mark them as fringes and update the BW 
        status[itr->dest] = 0;
        dad[itr->dest] = s;
        bw[itr->dest] = itr-> weight;                                                 // BW is equal to the weight of the edges 
    }
    int count =0 ;
    while(checkFringes(status,graph->V)){                                               // Loop to check all the fringes if they exist 
        int max = maxFringe(bw,status,graph->V);                                        // Fetch the fringe with max Bandwidth 
        status[max] = 1;
        for (vertexNode* itr2 = graph->array[max].head; itr2 != NULL; itr2=itr2->next){   // Check the adjacent vertices of the max fringe 
            if (status[itr2->dest] == -1){                                                // Case where adjacent vertex is still unseen 
                status[itr2->dest] = 0 ;  
                bw[itr2->dest] =  minfunction(bw[max],itr2->weight) ;
                dad[itr2->dest] = max;                                          
            }
            else if ((status[itr2->dest] == 0 ) && (bw[itr2->dest] < minfunction(bw[max],itr2->weight) )){   //  Case where adjacent vertex is a fringe 
                bw[itr2->dest] = minfunction(bw[max],itr2->weight);
                dad[itr2->dest] = max;
            }
        }

    }   
    if (status[t] != 1){                                                                // If status value of destination is not in-tree , then no path exists 
        cout << "No Path exists between " << s <<" - " << t << endl;
    }
    else {
        cout << "Maximum Bandwidth is " << bw[t] << endl;                               // Print the maximum BW
        int x = t;
        cout << "Path is as below " << endl;                                            // Print the path 
        cout << x;
        while(x!=s){
            x = dad[x];
            cout << " <- " << x;
        }
        cout << endl;
    }
}