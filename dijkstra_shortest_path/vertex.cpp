#include "vertex.h"

// constructor
Vertex::Vertex(std::string name) {
    vertex_name = name;
    node_color = WHITE;
    cost = INT_MAX;
    parent = nullptr;
}

// default constructor
Vertex::Vertex() {
    vertex_name = "";
    node_color = WHITE;
    cost = INT_MAX;
    parent = nullptr;
}


Vertex::~Vertex() {
    parent = nullptr;
}

// returns vertex name
std::string Vertex::get_vname() const {
    return vertex_name;
}

// sets vertex name 
void Vertex::set_vname(std::string v_name) {
    vertex_name = v_name;
}

// returns cost of the vertex
int Vertex::get_cost()const {
    return cost;
}

// returns a pointer to the parent vertex
Vertex* Vertex::get_parent()const {
    return parent;
}

// Add and edge to the edge list
void Vertex::add_edge(Edge e) {
    edge_list.push_back(e);
}

// If the edge exists between vertices A and B, edge object 
//  in vertex A corresponding to vertex B is returned
// For ex A---->B A.get_edge_info(B, edge) updates the 
//  edge information in "edge" object
void Vertex::get_edge_info(std::string edge_planet_name, Edge *e) {
    for (std::vector<Edge>::iterator it = edge_list.begin();
    it != edge_list.end(); it++) {
        if (it->get_vertex()->vertex_name == edge_planet_name) {
            *e = *it;
            return;
        }
    }
}

// Update the edge information in the adjacent vertex B, if B is 
//  already an edge from A
// Returns true if edge is already present and update is successful
//  otherwise returns false
bool Vertex::find_edge_nupdate(Vertex *v, std::string ship, int time) {
    for (std::vector<Edge>::iterator it = edge_list.begin();
    it != edge_list.end(); it++) {
        Vertex *temp_vertex = it->get_vertex();
        if (temp_vertex) {
            if (temp_vertex->vertex_name == v->vertex_name) {
                it->insert_at(ship, time);
                return true;
            }
        }
    }
    return false; // Edge not present
}

// operator < is responsible for the comparison of 2 objects
// This function is called when the comparison is performed in
//    priority queue
bool Vertex::operator<(const Vertex& right) const {
    if (cost < right.cost) return true;
    else return false;
}

// operator > is responsible for the comparison of 2 objects
// This function is called when the comparison is performed in
//    priority queue
bool Vertex::operator>(const Vertex& right) const {
    if (cost > right.cost) return true;
    else return false;
}

// Calculates the shortest path from node s in G(V, E) to all 
//  other nodes in G(V, E) and returns the longest path 
//  among the shortest
int Vertex::dijkstra_shortest(Vertex* &longest) {
    Heap<Vertex > prio_q;
    Vertex *source = this;

    source->node_color = GREY;
    source->cost = 0;
    source->parent = nullptr;
    prio_q.push(source);
    int max = 0;
    int edge_planet_cost = 0;
    while (!prio_q.is_empty()) {
        Vertex *temp_source = prio_q.pop();
        temp_source->node_color = BLACK;
        if (max < temp_source->cost) {
            max = temp_source->cost;
            longest = temp_source; // longest path amonth the shortest
        }
        // calculate the shortes path from "source" to all other nodes
        for (Edge edge : temp_source->edge_list) {
            Vertex *edge_planet = edge.get_vertex();
            edge_planet_cost = edge.get_next_ship(temp_source->cost);
            // Edges are visited for the first time, edge costs are 
            // updated and the edge is placed in priority queue
            if (edge_planet->node_color == WHITE) {
                edge_planet->cost = edge_planet_cost + edge.get_weight();
                edge_planet->parent = temp_source;
                edge_planet->node_color = GREY;
                prio_q.push(edge_planet);
                if (edge_planet->cost < 0) {
                    //std::cout << "less than 0" << std::endl;
                }
            }
            // Relax the cost of the vertex if shorter path from the 
            // source is discovered
            else if (edge_planet->node_color == GREY) {
                int new_distance = edge_planet_cost + edge.get_weight();
                if (edge_planet->cost > new_distance) {
                    edge_planet->cost = new_distance;
                    edge_planet->parent = temp_source;
                    if (edge_planet->cost < 0) {
                        //std::cout << "less than 0" << std::endl;
                    }
                }
            }
        }
    }
    return max;
}

// Resets the member variables to its initial value
void Vertex::reset_members() {
    node_color = WHITE;
    cost = INT_MAX;
    parent = nullptr;
}
