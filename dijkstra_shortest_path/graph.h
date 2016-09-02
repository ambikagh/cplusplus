#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <climits>
#include "vertex.h"

#define NO_OF_PLANETS 27

// ---------------------------------------------------------------------------
// Graph Class:
// Builds a Graph structure by reading data from standard inputs, and
//    calculates longest shortest path in the graph
// Uses edge list to build the edges
// Member hyperspacev:
//        list of Vertex pointers present in graph
//        longest_route:
//        Holds the longest route in the graph, contains relevant informatio
//        about the vertices that fall in the longest path
// Member functions:
// read_data: Reads graph data from the conduit file and stores the 
//            data in an 2 D array(row = column = #of Vertices
// create_nodelist: creates a map of string(vertex names) to integers(index)
//            this data is used to decide row and column corresponding to
//            vertices
// read_records: Reads the routing structure from input routing file into 
//  records structure for later reference
// validate_reco: validates the routing structure for complainace with 
//            data file
// reset_vertices: Resets all the vertices to its initial state after
//        shortest path to all nodes are calculated from a source node
// build_graph: builds the graph according to routing structure and 
//              validates the graph according to the constraints 
// longest_shortest_path: calculatest the longest shortest path from 
//      every node in the graph and returns the longest of all
// output_longest_route: outputs the longest shortest path for 
//      the graph to a file

class Graph {
    //friend std::istream& operator>>(istream& )
    typedef std::map<std::string, Vertex*> map_str2vertex;
    typedef std::map<std::string, int> map_str2int; 
    std::vector<Vertex *> hyperspacev;    
    struct records {
        std::string ship;
        std::string dep_planet;
        int dep_time;
        std::string arr_planet;
        int arr_time;
        records() :ship(""), dep_planet(""), dep_time(0), arr_planet(""), arr_time(0) {};
    };    
    std::vector<records> longest_route;
    void read_data(std::ifstream&, int g_data[][27],int, int);
    void create_nodelist(map_str2int&);
    bool read_records(records&);
    void validata_reco(records&, records&, int);
    void reset_vertices();
public:
    Graph();
    ~Graph();
    void build_graph(std::ifstream& );
    int longest_shortest_path();   
    void longest_itinerary(Vertex *&);
    void output_longest_route();
};

#endif


