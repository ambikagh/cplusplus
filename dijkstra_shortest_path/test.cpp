#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

// ---------------------------------------------------------------------------
// This program builds the graph from record structure read from standard input
// As and when record structure is read from std input it is also validated 
//   using the "datafile" as a reference(file is accepted as command line
//   argument) 
// Dijkstra's algorithm is used to calculate shortest path from each node to 
//   every other node, and the longest among them is the required
//   longest shortest path

int main(int argc, char *argv[]) {
    
    Graph g;

    if (argc < 2) {
        std::cerr << "enter at least 1 argument" << std::endl;
    }
    std::ifstream datafile(argv[1], ios_base::in);
    if (!datafile) {
        std::cerr << "Could not open data file for reading" << std::endl;
    }
    // build the graph from record file and validate it with the datafile
    g.build_graph(datafile);
    // calculate the longest shortest path in graph
    int sp = g.longest_shortest_path();
    cout << "longest path in graph is " << sp << endl;
    // output the itinerary of longest shortest path 
    g.output_longest_route();
    return 0;
}

