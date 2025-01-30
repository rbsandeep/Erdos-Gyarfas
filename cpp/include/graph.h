#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <set>
#include <vector>

class Graph
{
private:
    bool is_there_cycle(std::vector<bool> &marked, int n, int vert, int start);
    bool is_there_ind_path(std::vector<bool> &marked, int n, int vert, int start);
    bool is_ct_free_special(int t, int u, int v);
    bool has_forbidden_cycle_having(int u, int v);

public:
    std::unordered_map<int, std::set<int>> nodes;
    int k;
    int n;

    Graph(int k);
    std::set<int> get_neighbors(int node);
    void add_node(int node);
    void add_edge(int node1, int node2);
    void add_edges(std::vector<int> hitlist);
    void add_edges(int node, std::vector<int> hitlist);
    void remove_edge(int node1, int node2);
    void remove_edges(std::vector<int> nodelist);
    void remove_node(int node);
    bool is_ct_free(int t);
    bool is_ind_pk_free();
    void print_graph();
    void add_log_for_add_edges(const std::vector<int> safe_heighbors);
    void add_log_for_remove_edges(const std::vector<int> safe_heighbors);

    int get_degree(int node);
    bool update_next_safe_neighbors(std::vector<int> &cur_safe_neighbors);
    int get_highest_incomplete_node();
    bool has_forbidden_cycle();
    bool get_next_neighbors(std::vector<int> &cur_neighbors);
    void init_safe_neighbors(std::vector<int> &safe_neighbors);
};

#endif // GRAPH_H
