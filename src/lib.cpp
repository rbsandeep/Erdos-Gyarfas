#include <vector>
#include <iostream>

#include "graph.h"

/* Let V be the set of vertices of graph. Let V' be V \ {cur_node}. 
   Finds whether there is a P_k-free counter-example (where k is graph->k) in which
   G[V'] is an induced subgraph. If found, prints it, and if not found, prints nothing. 
*/
void explore(Graph* graph, int cur_node, int latest_safe_neighbor) {
    
    int next_safe_neighbor = graph->get_next_safe_neighbor(cur_node, latest_safe_neighbor);
    while (next_safe_neighbor != -1) {
        // check whether adding each safe edge leads to a counter example
        graph->add_edge(cur_node, next_safe_neighbor);
        //std::cout << "added edge " << cur_node << " " << next_safe_neighbor << std::endl;
        explore(graph, cur_node, next_safe_neighbor);
        graph->remove_edge(cur_node, next_safe_neighbor);
        //std::cout << "removed edge " << cur_node << " " << next_safe_neighbor << std::endl;
        next_safe_neighbor = graph->get_next_safe_neighbor(cur_node, next_safe_neighbor);
    }

    if (!graph->is_ind_pk_free()) {
        //std::cout << "cannot be extended" << std::endl;
        return; // the graph has an induced P_k and no more internal edges can be added
    }

    if (graph->get_degree(cur_node) >= 3) {
        cur_node = graph->get_highest_incomplete_node();
        if (cur_node == -1) {
            graph->print_graph(); // Got a counter-example!
            exit(100);
        }
    }

    int new_node = graph->nodes.size();

    graph->add_node(new_node);
    //std::cout << "added node " << new_node << std::endl;
    graph->add_edge(cur_node, new_node);
    //std::cout << "added edge " << cur_node << " " << new_node << std::endl;
    explore(graph, new_node, -1);
    graph->remove_node(new_node);
    //std::cout << "removed node " << new_node << std::endl;
}

/* Validates Erdos-Gyarfas conjecture on graphs without any induced copies of P_k 
   (where k is graph->k) but having an induced P_{k-1}. Prints nothing if validated, prints 
   the counter-example otherwise. 
*/
void validate_conjecture(int k) {
    Graph* g = new Graph(k);

    for (int i = 0; i < k; i++) {
        g->add_node(i);
    }

    for (int i = 0; i < k - 1; i++) {
        g->add_edge(i, i + 1);
    }
    // Now g is a path on k vertices.
    explore(g, k - 1, -1);
}


