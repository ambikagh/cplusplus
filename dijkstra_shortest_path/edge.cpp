#include "edge.h"

Edge::Edge() {
    v = nullptr;
    weight = 0;
}

// contructor
Edge::Edge(Vertex *vd, int w) {
    v = vd;
    weight = w;
}

// Adds the route information at the end of list
void Edge::add(std::string shipname, int time) {
    departure_info temp;
    temp.ship_name = shipname;
    temp.dep_time = time;
    dep_time_table.push_back(temp);
}

// Adds the route information to table 
// Table is arranged in increasing order of departure time
void Edge::insert_at(std::string shipname, int time) {
    std::list<departure_info>::iterator it;
    departure_info temp;
    temp.ship_name = shipname;
    temp.dep_time = time;
    for (it = dep_time_table.begin(); it != dep_time_table.end(); it++) {
        if (it->dep_time < time) continue;
        else {
            dep_time_table.insert(it, temp);
            return;
        }
    }
    dep_time_table.push_back(temp);
}

// Return the pointer to the vertex associated with the edge
Vertex* Edge::get_vertex() const {
    return v;
}

// Return the weight of the edge
int Edge::get_weight() const {
    return weight;
}

// get dep_time for the next planet 
// There should be a minimum 4 hours before journey is resumed
int Edge::get_next_ship(int time) {
    std::list<departure_info>::iterator it;
    if (time == 0) { // For the first journey of the ship
        // return the next available ship
        return dep_time_table.begin()->dep_time;
    }
    // Check the next ship which leaves atleast 4 hours after the arrival
    for (it = dep_time_table.begin(); it != dep_time_table.end(); it++) {
        if ((it->dep_time - time) >= MINIMUM_WAIT_TIME) {
            return it->dep_time;
        }
    }
    // if there is no next ship leaveing the planet after "time"
    //  indicate the planet cannot be reached
    return INT_MAX;
}


void Edge::route_info(std::string &ship_name, int &dep_time, int arr_time) {
    if (this->v == nullptr) return;
    std::list<departure_info>::iterator it;
    if (arr_time == 0) {
        ship_name = dep_time_table.begin()->ship_name;
        dep_time = dep_time_table.begin()->dep_time;
        return;
    }
    for (it = dep_time_table.begin(); it != dep_time_table.end(); it++) {
        if ((it->dep_time - arr_time) >= 4) {
            ship_name = it->ship_name;
            dep_time = it->dep_time;
            return;
        }
    }
}