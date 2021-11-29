#include "graph_generation.h"
#include "Dijkstras.h"
#include "heapDijkstra.h"
#include "Kruskal.h"
#include <time.h>
#include <iomanip>
using namespace std;

void testSparseGraph(){
    srand(time(0));
    for (int i = 0;i < 5; i++){

        cout<< "**********CREATING SPARSE GRAPH NUMBER " <<i+1 << "***********" << endl;
        struct Graph* mygraph1 = createSparseGraph(5000);
        clock_t start, end;
        for (int j =0; j <5; j++){
            int x,y;
            x = rand()%5000 ;
            y = rand()%5000 ;
            cout << "PAIR - " << j+1 << endl << "SOURCE: " << x << " DESTINATION: " << y << "|" << endl ;
            cout << "Executing algorithms for this pair" <<endl ;
            cout << "----------EXECUTING NORMAL DijkstraS----------" << endl ;
            start = clock();
            Dijkstras(mygraph1,x,y);
            end = clock();
            double time_taken_Dijkstra = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by normal Dijkstra algorithm is : " << fixed << time_taken_Dijkstra << setprecision(5);
            cout << " sec " << endl;   

            cout << "----------EXECUTING HEAP DijkstraS----------" << endl ;
            start = clock();
            Dijkstraheap(mygraph1,x,y);
            end = clock();
            double time_taken_heap = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by heap Dijkstra algorithm is : " << fixed << time_taken_heap << setprecision(5);
            cout << " sec " << endl;  

            cout << "----------EXECUTING KRUSKALS----------" << endl ;
            start = clock();
            Kruskal(mygraph1,x,y);
            end = clock();
            double time_taken_kruskal = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by normal Kruskal algorithm is : " << fixed << time_taken_kruskal << setprecision(5);
            cout << " sec " << endl;  
        }
    }
}

void testDenseGraph(){
    srand(time(0));
    for (int i = 0;i < 5; i++){

        cout<< "**********CREATING DENSE GRAPH NUMBER " <<i+1 << "***********" << endl;
        struct Graph* mygraph1 = createDenseGraph(5000);
        clock_t start, end;
        for (int j =0; j <5; j++){
            int x,y;
            x = rand()%5000 ;
            y = rand()%5000 ;
            cout << "PAIR - " << j+1 << endl << "SOURCE: " << x << " DESTINATION: " << y << "|" << endl ;
            cout << "Executing algorithms for this pair" <<endl ;
            cout << "----------EXECUTING NORMAL DijkstraS----------" << endl ;
            start = clock();
            Dijkstras(mygraph1,x,y);
            end = clock();
            double time_taken_Dijkstra = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by normal Dijkstra algorithm is : " << fixed << time_taken_Dijkstra << setprecision(5);
            cout << " sec " << endl;   

            cout << "----------EXECUTING HEAP DijkstraS----------" << endl ;
            start = clock();
            Dijkstraheap(mygraph1,x,y);
            end = clock();
            double time_taken_heap = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by heap Dijkstra algorithm is : " << fixed << time_taken_heap << setprecision(5);
            cout << " sec " << endl;  

            cout << "----------EXECUTING KRUSKALS----------" << endl ;
            start = clock();
            Kruskal(mygraph1,x,y);
            end = clock();
            double time_taken_kruskal = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Time taken by normal Kruskal algorithm is : " << fixed << time_taken_kruskal << setprecision(5);
            cout << " sec " << endl;  
        }
    }
}

int main(){
    srand(time(0));
  //  cout<< "Creating Sparse Graph G1" << endl;
  //  struct Graph* mygraph1 = createSparseGraph(5000);
 //   clock_t start, end;
 //   printGraph(mygraph1,1); // 0 -> print adjacency list,  1 -> print edges 
  //  cout << "Number of edges = " << edge_count << "\n";
  /*  int x,y;
    x = rand()%10 ;
    y = rand()%5000 ;
    cout << "Source: " << x << " Destination: " << y << endl ;
    cout << "Executing algorithms for pair 1 in G1" << endl;
    start = clock();
    Dijkstras(mygraph1,x,y);
    end = clock();
    double time_taken_Dijkstra = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by normal Dijkstra algorithm is : " << fixed << time_taken_Dijkstra << setprecision(5);
    cout << " sec " << endl;   

    start = clock();
    Dijkstraheap(mygraph1,x,y);
    end = clock();
    double time_taken_heap = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by heap Dijkstra algorithm is : " << fixed << time_taken_heap << setprecision(5);
    cout << " sec " << endl;  

    start = clock();
    Kruskal(mygraph1,x,y);
    end = clock();
    double time_taken_kruskal = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by normal Kruskal algorithm is : " << fixed << time_taken_kruskal << setprecision(5);
    cout << " sec " << endl;  */
    
    cout << "************************ TEST FOR SPARSE GRAPHS *****************************" << endl << endl;
    testSparseGraph();
    cout << "*****************************************************************************" << endl << endl;
    cout << "************************ TEST FOR DENSE GRAPHS *****************************" << endl << endl;
    testDenseGraph();
    cout << "*****************************************************************************" << endl << endl; 
    
}