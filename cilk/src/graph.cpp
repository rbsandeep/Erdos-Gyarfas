#include <iostream>

#include "graph.h"

Graph::Graph(int k) {
    // Constructor
    this->k = k;
    this->n = 0;
}


Graph::Graph(Graph* g) {
    // Constructor
    k = g->k;
    n = g->n;
    nodes = g->nodes; 
}

void Graph::add_node(int node) {
    // Adds a node to the graph
    nodes[node] = std::set<int>();
    n++;
}

void Graph::add_edge(int node1, int node2) {
    // Adds an edge between two nodes
    nodes[node1].insert(node2);
    nodes[node2].insert(node1);
}

void Graph::remove_node(int node) {
    // Removes a node from the graph
    for (auto neighbor : nodes[node]) {
        nodes[neighbor].erase(node);
    }
    nodes.erase(node);
    n--;
}

void Graph::remove_edge(int node1, int node2) {
    // Removes an edge between two nodes
    nodes[node1].erase(node2);
    nodes[node2].erase(node1);
}

void Graph::add_edges(std::vector<int> hitlist) {
    /* Add edges of the kind {n-1, i} such that hitlist[i] = 1.
       It is assumed that hitlist has size exactly n-1.  */
    for(int i=0; i<n-1; i++) {
        if(hitlist[i] == 1) {
            nodes[n-1].insert(i);
            nodes[i].insert(n-1);
        }
    }   
}

void Graph::remove_edges(std::vector<int> hitlist) {
    /* Removes edges of the kind {n-1, i} such that hitlist[i] = 1.
       It is assumed that hitlist has size exactly n-1.  */
    for(int i=0; i<n-1; i++) {
        if(hitlist[i] == 1) {
            nodes[n-1].erase(i);
            nodes[i].erase(n-1);
        }
    }   
}

bool Graph::is_there_cycle(std::vector<bool>& marked, int t, int vert, int start) {
    /* Returns true if there is a cycle with t remaining vertices (taken from vertices other than marked and vert), 
       starting from the vertex start 
       and with the current vertex vert. */
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

bool Graph::is_ct_free_special(int t, int u, int v) {
    /* Returns true if the graph has no cycle on t vertices as a subgraph such that
       the edge {u,v} is part of the cycle. 
       Returns False otherwise. */

    std::vector<bool> marked(n, false); // all nodes part of a cycle (that is being found) are marked
    marked[u] = true;
    marked[v] = true;
    for (auto neighbor : nodes[v]) {
        if (neighbor != u) {
            if (is_there_cycle(marked, t - 3, neighbor, u)) {
                return false;
            }
        }
    }
    return true;
}


bool Graph::is_ct_free(int t) {
    /* Returns true if the graph has no cycle on k vertices as a subgraph. 
       Returns False otherwise. */

    std::vector<bool> marked(n, false); // all nodes part of a cycle (that is being found) are marked
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

bool Graph::has_forbidden_cycle() {
    /* Returns true if the graph has a cycle of length a power of 2.
       Returns false otherwise. */
    int t = 4;
    while(t <= 8) {
        if (!is_ct_free(t)) {
            return true;
        }
        t = t*2;
    }
    return false;
}

bool Graph::has_forbidden_cycle_having(int u, int v) {
    /* Returns true if the graph has a cycle of length a power of 2
       having the edge {u,v}.
       Returns false otherwise. */
    int t = 4;
    while(t <= 8) {
        if (!is_ct_free_special(t, u, v)) {
            return true;
        }
        t = t*2;
    }
    return false;
}


bool Graph::get_next_neighbors(std::vector<int>& cur_neighbors) {
    /* Get next set of potential neighbors of the vertex n-1.
       It just finds the next (to cur_neighbors) binary number (-1s ignored).
    */
    int i = 0;
    while (true) {
        if (i == n-1) {
            // cur_neighbors contains all 0s now (ignoring -1s).
            return false;
        }
        if (cur_neighbors[i] == -1) {
            // ignore -1s
            i++;
            continue;
        }
        if (cur_neighbors[i] == 1) {
            // all consecutive (from the start) 1s must be flipped
            cur_neighbors[i] = 0;
            i++;
            continue;
        }
        if (cur_neighbors[i] == 0) {
            // flip the first 0 and return
            cur_neighbors[i] = 1;
            return true;
        }
    }
}

void Graph::init_safe_neighbors(std::vector<int>& safe_neighbors) {
    /* Sets safe_neighbors[i] = -1, if adding the edge {n-1, i}
       creates a forbidden cycle. It is assumed that the current
       graph has no forbidden cycle.
    */
    for (int i=0; i<n-1; i++) {
        if (safe_neighbors[i] == 0) {
            add_edge(n-1, i);
            if (has_forbidden_cycle_having(n-1, i)) {
                safe_neighbors[i] = -1;
            }
            remove_edge(n-1, i);
        }
    }
} 

bool Graph::update_next_safe_neighbors(std::vector<int>& cur_safe_neighbors) {
    /* Finds the 'next' list of neighbors of the last node (with index n-1) such that adding them does not result in a forbidden cycle.
       cur_safe_neighbors contains the current list of safe neighobrs - cur_safe_neighbors[i] = -1 implies
       that {n-1, i} is an existing edge. Setting a entry to 1 implies the 
       corresponding edge is part of the next safe list of edges. It is assumed that the size of cur_safe_neighbors
       is exactly n-1. If the next set is found, then the corresponding edges are added and returns true.
       If no next set of potential neighbors are found, then return false. */
    while (get_next_neighbors(cur_safe_neighbors)) {
        add_edges(cur_safe_neighbors);
        if (!has_forbidden_cycle()) {
            return true;
        } 
        remove_edges(cur_safe_neighbors);
    }
    return false;
}

int Graph::get_highest_incomplete_node() {
    /* Get the highest labelled vertex which has degree less than 3,
       Returns -1, if the graph has minimum degree at least 3. */

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

