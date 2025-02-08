#include <vector>
#include <iostream>

#include "graph.h"


/* Let V = {0,1,...,n-1} be the set of vertices of graph.
   Let V' = {0,1,2,...,n-2} (i.e., V \ {n-1}).
   The vertex n has exactly one neighbor, which is anchor_node, in V. 
   Finds whether there is a P_k-free counter-example (where k is graph->k) 
   in which G[V'] is an induced subgraph and G[V] is a subgraph 
   (i.e., we are free to add new edges between n-1 and V').
   If such a graph is found, then it is printed. 
*/
void explore(Graph* graph, int anchor_node) {
    std::vector<int> safe_neighbors(graph->n-1, 0);
    safe_neighbors[anchor_node] = -1; // {n-1, anchor_node} is already an edge
    graph->init_safe_neighbors(safe_neighbors);
    bool success = true;
    while (success) {
        if (graph->is_ind_pk_free()) {
            int next_anchor_node = graph->get_highest_incomplete_node();
            if (next_anchor_node == -1) {
                graph->print_graph(); // Got a counter-example!
                exit(100);
            }
            int new_node = graph->n;
            graph->add_node(new_node);
            std::cout << "N " << new_node << "\n";
            graph->add_edge(new_node, next_anchor_node);
            std::cout << "E " << new_node << " " <<next_anchor_node << "\n";
            explore(graph, next_anchor_node);
            graph->remove_node(new_node);
            std::cout << "n " << new_node << "\n";
        } 
        graph->remove_edges(safe_neighbors);
        graph->add_log_for_remove_edges(safe_neighbors);
        success = graph->update_next_safe_neighbors(safe_neighbors);
        if(success){
            graph->add_log_for_add_edges(safe_neighbors);
        }
    }
}

/* Validates Erdos-Gyarfas conjecture on graphs without any induced copies of P_k 
   (where k is graph->k) but having an induced P_{k-1}. Prints a counter-example,
   if the conjecture is false.
*/
void validate_conjecture(int k) {
    Graph* g = new Graph(k);
    std::cout << "k = " << k << "\n";
    for (int i = 0; i < k; i++) {
        g->add_node(i);
        std::cout << "N " << i << "\n";
    }
    for (int i = 0; i < k - 1; i++) {
        g->add_edge(i, i+1);
        std::cout << "E " << i << " " << i + 1 << "\n";
    }
    // Now g is a path on k vertices.
    explore(g, k-2); // k-2 to is the anchor node to which the last node (k-1) is attached. 
}


