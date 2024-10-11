#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <set>
#include<vector>

class Graph {
private:
    bool is_there_cycle(std::vector<bool>& marked, int n, int vert, int start);
    bool is_there_ind_path(std::vector<bool>& marked, int n, int vert, int start);

public:
    std::unordered_map<int, std::set<int>> nodes;
    int k;

    Graph(int k);
    Graph(Graph *g);
    std::set<int> get_neighbors(int node);
    void add_node(int node);
    void add_edge(int node1, int node2);
    void remove_edge(int node1, int node2);
    void remove_node(int node);
    bool is_ct_free(int t);
    bool is_ind_pk_free();
    void print_graph();

    int get_degree(int node);
    int get_next_safe_neighbor(int cur_node, int latest_safe_neighbor);
    int get_highest_incomplete_node();
};

#endif // GRAPH_H
