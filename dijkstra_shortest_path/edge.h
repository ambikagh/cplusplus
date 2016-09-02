#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <climits>

#define MINIMUM_WAIT_TIME 4

class Vertex;

// ---------------------------------------------------------------------------
// Edge class: Represents the edge of a vertex
// Member variables: 
// Edge name -> represents adjacent vertex connected by the edge
// weight -> represents the cost factor
// Departure time table -> Consists of list of transit schedule information to
//           adjoining vertex joined by the edge. Each schedule info consists
//           of "Ship name" and "departure time"
//           Table is arranged in increasing order of time.
class Edge {
    struct departure_info {
        std::string ship_name;
        int dep_time;
        departure_info() :ship_name(""), dep_time(0) {};
        departure_info(std::string s, int t) :ship_name(s), dep_time(t) {};
    };
    Vertex* v;
    int weight;
    std::list<departure_info> dep_time_table;
public:
    Edge();
    Edge(Vertex *, int);
    //~Edge();
    void add(std::string, int );
    void insert_at(std::string, int);
    Vertex* get_vertex() const;
    int get_weight() const;
    int get_next_ship(int);
    void route_info(std::string &, int &, int);
};

#endif
