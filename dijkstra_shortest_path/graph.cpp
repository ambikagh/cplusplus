#include "graph.h"

Graph::Graph() {
}

Graph::~Graph() {
    for (int i = 0; i < NO_OF_PLANETS; i++) {
        delete hyperspacev[i];
        hyperspacev[i] = nullptr;
    }
}

// Read data from the hyperspace conduit file
void Graph::read_data(std::ifstream& datafile, int graph_data[][27], int rowsz, int colsz) {
    for (int i = 0; i < rowsz; i++) {
        for (int j = 0; j < colsz; j++) {
            datafile >> graph_data[i][j];
        }
    }
}

// create_nodelist: creates a map of string(vertex names) to integers(index)
//            this data is used to decide row and column corresponding to
//            vertices, this data is used to extract the graph constraint
//            information from the data file
void Graph::create_nodelist(map_str2int& node_list) {
    node_list["ALDERAAN"] = 0;
    node_list["BESPIN"] = 1;
    node_list["CORELLIA"] = 2;
    node_list["CORUSCANT"] = 3;
    node_list["DAGOBAH"] = 4;
    node_list["DANTOOINE"] = 5;
    node_list["ENDOR"] = 6;
    node_list["GAMORR"] = 7;
    node_list["HOTH"] = 8;
    node_list["SULLUST"] = 9;
    node_list["TATOOINE"] = 10;
    node_list["YAVIN"] = 11;
    node_list["BRENTAAL"] = 12;
    node_list["CHANDRILA"] = 13;
    node_list["CORULAG"] = 14;
    node_list["ESSELES"] = 15;
    node_list["RHINNAL"] = 16;
    node_list["RALLTIIR"] = 17;
    node_list["KASHYYYK"] = 18;
    node_list["MYRKR"] = 19;
    node_list["WAYLAND"] = 20;
    node_list["BAKURA"] = 21;
    node_list["CORPORATE SECTOR"] = 22;
    node_list["HAPES CLUSTER"] = 23;
    node_list["KESSEL"] = 24;
    node_list["MON CALAMARI"] = 25;
    node_list["YAGA MINOR"] = 26;
}

// read_records: Reads the routing structure from input routing file into 
//  records structure for later reference, 
//  graph is build from the records structure
bool Graph::read_records(records& r) {
    char data[256];
    std::cin.getline(data, 256);
    std::string s(data);
    int start = 0, end = 0;
    std::string reco_temp[5];
    int i = 0;
    while (data[end] != '\0' && i < 5) {
        while (data[end] != '\t') {
            end++;
        }
        reco_temp[i++] = s.substr(start, (end - start));
        while (data[end] == '\t')end++;
        start = end;
    }
    if (start == 0 && end == 0)
        return false; // Reading record from file is unsuccessful(empty line)
    r.ship = reco_temp[0];
    r.dep_planet = reco_temp[1];
    r.dep_time = std::stoi(reco_temp[2]);
    r.arr_planet = reco_temp[3];
    r.arr_time = std::stoi(reco_temp[4]);

    
    std::cout << r.ship << '\t' << r.dep_planet << '\t' << r.dep_time;
    std::cout << '\t' << r.arr_planet << '\t' << r.arr_time << std::endl;

    return true; // Reading record from file is successful
}

// Validates the route structure and determines its goodness
// REcord structure read from standard input is compared with the graph constraints 
//  to determine validity
void Graph::validata_reco(records& prev_reco, records& current_reco, int actual_travel_time) {
    int travel_time = current_reco.arr_time - current_reco.dep_time;

    // Check if the route is valid
    if (actual_travel_time == INT_MAX) { // not a valid route
        std::cerr << "There is no valid connection between ";
        std::cerr << current_reco.dep_planet << " and ";
        std::cerr << current_reco.arr_planet << std::endl;
        std::cerr << "Error: route is not valid" << std::endl;
        exit(1);
    }
    // check if travel time complies with the given constraints
    else if (travel_time != actual_travel_time) {
        std::cerr << "Travel time for " << current_reco.dep_planet;
        std::cerr << " and " << current_reco.arr_planet;
        std::cerr << " does not comply with given constraints" << std::endl;
        exit(1);
    }

    // handle the condition for last travel for ship n
    if (prev_reco.ship != "" && prev_reco.ship != current_reco.ship) {
        prev_reco.arr_planet = "";
        prev_reco.arr_time = 0;
    }
    else if (prev_reco.ship == current_reco.ship) {
        if ((current_reco.dep_time - prev_reco.arr_time) < 4) {
            std::cerr << "Ship has a mandatory wait time of 4 hrs at every stop" << std::endl;
            exit(1);
        }
    }

    // Validate if the ship leaves the same planet which it arrives at
    if (prev_reco.arr_planet != "" && prev_reco.arr_planet != current_reco.dep_planet) {
        std::cerr << "arrival planet and the departure planet differ";
        std::cerr << " arrival planet = " << prev_reco.arr_planet;
        std::cerr << " departure planet = " << current_reco.dep_planet << std::endl;
        exit(1);
    }
}

void Graph::build_graph(std::ifstream& conduit_file) {

    map_str2vertex hyperspace;
    // build node map: map of node name to an integer value
    // which is used to read graph information from the conduit file
    map_str2int nodelist;
    create_nodelist(nodelist);

    // Read the conduit file for the constraints on the graph
    int g_data[NO_OF_PLANETS][NO_OF_PLANETS];
    read_data(conduit_file, g_data, NO_OF_PLANETS, NO_OF_PLANETS);

    records prev_rec;

    while (!std::cin.eof()) {
        char ch = std::cin.get();
        if (ch == '#') { // ignore the line if it starts with #
            char dummy[128];
            std::cin.getline(dummy, 128);
            continue;
        }
        // if character is not '#' read the line from beginning
        std::cin.unget();

        records record_structure;
        if (!read_records(record_structure))continue;

        int row = nodelist[record_structure.dep_planet];
        int col = nodelist[record_structure.arr_planet];

        // check if the records read from the input file is valid
        validata_reco(prev_rec, record_structure, g_data[row][col]);

        // if vertex is already present in the map  
        // add the new edge to vertex
        // otherwise add the vertex to the map
        Vertex *temp = hyperspace[record_structure.dep_planet];
        // Check if destination planet is already present
        Vertex *destination_p = hyperspace[record_structure.arr_planet];
        if (!destination_p) {
            destination_p = new Vertex(record_structure.arr_planet);
            if (!destination_p) {
                std::cerr << "Error: memory allocation failed" << std::endl;
            }
            hyperspace[record_structure.arr_planet] = destination_p;
            hyperspacev.push_back(destination_p);
        }
        if (!temp) {// Vertex absent, create vertex
            temp = new Vertex(record_structure.dep_planet);
            if (!temp) {
                std::cerr << "Error: Memory could not be allocated" << std::endl;
            }
            // Create edge information
            Edge e(destination_p, (record_structure.arr_time - record_structure.dep_time));
            e.insert_at(record_structure.ship, record_structure.dep_time);
            temp->add_edge(e); // add edge to the vertex
            hyperspacev.push_back(temp);
        }
        else {
            // find edge and update the time table, if edge is not found create edge and add to the vertex
            if (!temp->find_edge_nupdate(hyperspace[record_structure.arr_planet], record_structure.ship, record_structure.dep_time)) {
                Edge e(destination_p, (record_structure.arr_time - record_structure.dep_time));
                e.insert_at(record_structure.ship, record_structure.dep_time);
                temp->add_edge(e);
            }
        }
        hyperspace[record_structure.dep_planet] = temp;
        prev_rec = record_structure;
    }
}

// longest_shortest_path: calculatest the longest shortest path from 
//      every node in the graph and returns the longest of all
int Graph::longest_shortest_path() {
    int max = 0;
    Vertex *longest;
    for (Vertex* v : hyperspacev) {
        int short_path = v->dijkstra_shortest(longest);
        if (short_path > max) {
            max = short_path;
            // Create the longest itinerary from the calculated longest path
            longest_itinerary(longest);
        }
        // Check whether all vertexes can be reached fron any vertex
        for (Vertex *vx : hyperspacev) {
            if (vx->get_cost() == INT_MAX) {
                std::cout << vx->get_vname() << " is not reachable" << std::endl;
                exit(1);
            }
        }        
        // reset vertices before calculating shortest path from the next planet
        reset_vertices();
    }
    return max; // returns the longest shortest path in graph
}

// Longest path information obtained from Dijkstra's algorith is used to 
//  prepare the itinerary 
// All the vertices lying in the longest path can be accessed by "longest"
// vertex pointer
// Longest contains destination vertex of the longest path, all other nodes
//       can be accessed using back pointer(which points to previous vertex
//       in the path
void Graph::longest_itinerary(Vertex *&longest) {
    // clear the longest route vector
    if (longest_route.size()) {
        longest_route.clear();
    }
    std::vector<Vertex *> stack_v;
    Vertex *temp_v = longest;
    while (temp_v) {
        stack_v.push_back(temp_v);
        temp_v = temp_v->get_parent();
    }
    int length = stack_v.size();
    // prev_planet is used to access the vertices in longest
    //  path in reverse order
    Vertex *prev_planet = stack_v[--length];
    while (--length >= 0) {
        // current_planet represents the parent vertex of the prev_planet
        Vertex *curr_planet = stack_v[length];
        // Get edge information of the current planet
        Edge edge_curr;
        prev_planet->get_edge_info(curr_planet->get_vname(), &edge_curr);
        records the_route;
        the_route.dep_planet = prev_planet->get_vname();
        the_route.arr_planet = curr_planet->get_vname();
        edge_curr.route_info(the_route.ship, the_route.dep_time, prev_planet->get_cost());
        the_route.arr_time = curr_planet->get_cost();
        longest_route.push_back(the_route);
        prev_planet = curr_planet;
    }
}

// Restore status of all the vertices to its initial value
void Graph::reset_vertices() {
    for (Vertex* v : hyperspacev) {
        v->reset_members();
    }
}

// output_longest_route: outputs the longest shortest path for 
//      the graph to output file
void Graph::output_longest_route() {
    std::ofstream outfile("itinerary.txt");
    if (!outfile) {
        std::cerr << "File could not be created for writing";
    }
    std::vector<records>::iterator it;
    std::cout << std::endl << std::endl;
    outfile << "longest shortest path for the hyperspace is " << std::endl;
    for (it = longest_route.begin(); it != longest_route.end(); it++) {
        outfile << it->ship << "\t" << it->dep_planet << "\t";
        outfile << it->dep_time << "\t" << it->arr_planet << "\t";
        outfile << it->arr_time << "\n";
    }
}
