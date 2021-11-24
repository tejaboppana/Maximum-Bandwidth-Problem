#include "graph_generation.h"
#include "Djikstras.h"
#include "heapDjikstra.h"
#include "Kruskal.h"
#include <time.h>
#include <iomanip>
using namespace std;

int main(){
    srand(time(0));
    struct Graph* mygraph1 = createSparseGraph(5000);
    clock_t start, end;
   //printGraph(mygraph1,0); // 0 -> print adjacency list,  1 -> print edges 
  //  cout << "Number of edges = " << edge_count << "\n";
    int x,y;
  //  srand(time(0));
  //  x = rand()%5000 ;
  //  y = rand()%5000 ;
  //  cout << "x: " << x << " y: " << y << endl ;
    
    start = clock();
    Djikstras(mygraph1,1,4000);
    end = clock();
    double time_taken_djikstra = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by normal Djikstra algorithm is : " << fixed << time_taken_djikstra << setprecision(5);
    cout << " sec " << endl;   

    start = clock();
    Djikstraheap(mygraph1,1,4000);
    end = clock();
    double time_taken_heap = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by heap Djikstra algorithm is : " << fixed << time_taken_heap << setprecision(5);
    cout << " sec " << endl;  

    start = clock();
    Kruskal(mygraph1,1,4000);
    end = clock();
    double time_taken_kruskal = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by normal Kruskal algorithm is : " << fixed << time_taken_kruskal << setprecision(5);
    cout << " sec " << endl;  

}