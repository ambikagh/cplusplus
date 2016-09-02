#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include "edge.h"
#include "heap.h"

// ---------------------------------------------------------------------------
// Vertex class:
// represents Vertex in graph
// Member variables: 
//     vertex_name
//     cost: cost associated with the vertex
//     color: denotes the visited status
enum color { WHITE, GREY, BLACK };

class Vertex {
    std::string vertex_name; 
    color node_color; // node color to keep track of visited status
    int cost; // cost from source vertex
    // represents the previous planet in the shortest path
    Vertex *parent; 
    // List of edge to the vertex
    std::vector<Edge> edge_list;
public:
    Vertex();
    Vertex(std::string);
    ~Vertex();
    std::string get_vname() const;
    int get_cost()const;
    void set_vname(std::string);
    void add_edge(Edge);
    bool find_edge_nupdate(Vertex *, std::string, int);
    bool operator<(const Vertex&) const;
    bool operator>(const Vertex&) const;
    int dijkstra_shortest(Vertex*&); // calculate shortest path 
    void reset_members(); // Resets the member variables to its initial value
    Vertex* get_parent()const;
    void get_edge_info(std::string, Edge*);
};

#endif