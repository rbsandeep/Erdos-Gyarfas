#include <iostream>

#include "graph.h"

Graph::Graph(int k) {
    // Constructor
    this->k = k;
}

std::set<int> Graph::get_neighbors(int node) {
    // Returns the neighbors of a node
    return nodes[node];
}

void Graph::add_node(int node) {
    // Adds a node to the graph
    nodes[node] = std::set<int>();
}

void Graph::add_edge(int node1, int node2) {
    // Adds an edge between two nodes
    nodes[node1].insert(node2);
    nodes[node2].insert(node1);
}

void Graph::remove_edge(int node1, int node2) {
    // Removes an edge between two nodes
    nodes[node1].erase(node2);
    nodes[node2].erase(node1);
}

void Graph::remove_node(int node) {
    // Removes a node from the graph
    for (auto neighbor : nodes[node]) {
        nodes[neighbor].erase(node);
    }
    nodes.erase(node);
}

bool Graph::is_there_cycle(std::vector<bool>& marked, int t, int vert, int start) {
    /* Returns true if there is a cycle with t remaining vertices (taken from vertices other than marked and vert), 
       starting from the vertex
       start and with the current vertex vert. */

    marked[vert] = true; // mark the current node

    if (t == 0) {
        if (nodes[vert].find(start) != nodes[vert].end()) {
            // there is cycle
            return true;
        }
        marked[vert] = false; // unmark the vertex for future considerations
        return false;
    }

    for (auto neighbor : nodes[vert]) {
        if (!marked[neighbor]) {
            if (is_there_cycle(marked, t - 1, neighbor, start)) {
                return true;
            }
        }
    }
    marked[vert] = false; // unmark the vertex for future considerations
    return false;
}

bool Graph::is_ct_free(int t) {
    /* Returns true if the graph has no cycle on k vertices as a subgraph. 
       Returns False otherwise. */

    std::vector<bool> marked(nodes.size(), false); // all nodes part of a cycle (that is being found) are marked
    for (auto node : nodes) {
        if (is_there_cycle(marked, t - 1, node.first, node.first)) {
            return false;
        }
    }
    return true;
}

bool Graph::is_there_ind_path(std::vector<bool>& marked, int t, int vert, int prev_vert) {
    /* Checks if the currently discovered induced path (containing marked vertices), 
       where the latest vertex part of the path is prev_vert,
       can be extended by including vert and then t remaining vertices, 
       to a longer induced path containing t more unmarked vertices.*/

    // checking whether vert has any edge to the marked vertices (other than prev_vert)
    for (int i = 0; i < (int)marked.size(); i++) {
        if (marked[i] && i != prev_vert) {
            if (nodes[vert].find(i) != nodes[vert].end()) {
                marked[vert] = false;
                return false; // the current list of marked vertices and vert does not form an induced path
            }
        }
    }
    marked[vert] = true; // vert is included in the path

    if (t == 0) {
        return true;
    }

    for (auto neighbor : nodes[vert]) {
        if (!marked[neighbor]) {
            if (is_there_ind_path(marked, t - 1, neighbor, vert)) {
                return true;
            }
        }
    }
    marked[vert] = false; // unmark for future considerations
    return false;
}


bool Graph::is_ind_pk_free() {
    /* Checks if the graph contains P_k as an induced subgraph, where k is this->k.*/
    
    int n = nodes.size();

    std::vector<bool> marked(n, false);
    // A path has two end points - so need to check whether a vertex is an end
    // point only for n-1 vertices.
    for (int i = 0; i < n-1; i++) {
        if (is_there_ind_path(marked, this->k - 1, i, -1)) {
            return false;
        }
    }

    return true;
}

int Graph::get_degree(int node) {
    return nodes[node].size();
}

int Graph::get_next_safe_neighbor(int cur_node, int latest_safe_neighbor) {
    /* Find a vertex next_safe_neighbor such that (cur_node, next_safe_neighbor) is not an edge
       in the graph and adding it does not create a forbidden cycle 
       and next_safe_neighbor > latest_safe_neighbor */

    for (int next_safe_neighbor = latest_safe_neighbor+1; next_safe_neighbor < (int)nodes.size(); next_safe_neighbor++) {
        if (next_safe_neighbor == cur_node || nodes[cur_node].find(next_safe_neighbor) != nodes[cur_node].end()) {
            continue; // (node, i) cannot be included
        }
        int t = 4;
        bool is_cycle_found = false;
        add_edge(cur_node, next_safe_neighbor);
        while (t <= (int) this->nodes.size()){
            if (is_ct_free(t)) {
                t *= 2;
            }
            else{
                is_cycle_found = true;
                break;
            }
        }
        remove_edge(cur_node, next_safe_neighbor);
        if (!is_cycle_found){
            return next_safe_neighbor;
        }
    }
    return -1;
}

int Graph::get_highest_incomplete_node() {
    // Get the highest labelled vertex which has degree less than 3

    int n = nodes.size();
    for (int i = n-1; i >= 0; i--) {
        if (get_degree(i) < 3) {
            return i;
        }
    }

    return -1;
}

void Graph::print_graph() {
    for (auto node : nodes) {
        std::cout << node.first << ": ";
        for (auto neighbor : node.second) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}

