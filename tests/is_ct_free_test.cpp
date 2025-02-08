#include <iostream>
#include <fstream>

#include "graph.h"
#include "json.hpp"

using json = nlohmann::json;

template <typename T>
void check_result(const T &expected, const T &result)
{
    if (result != expected)
    {
        std::cerr << "FAIL\n";
        std::cout << "Expected: " << (expected) << ", Got: " << (result) << "\n";
        exit(100);
    }
    else
    {
        std::cout << "PASS\n";
    }
    std::cout << "\n";
}

Graph get_graph_from_json(const json test)
{
    std::vector<std::pair<int, int>> edges;
    std::set<int> nodes;
    for (const auto &edge : test["edges"])
    {
        edges.emplace_back(edge[0], edge[1]);
        nodes.insert((int)edge[0]);
        nodes.insert((int)edge[1]);
    }
    int path_len = 5;

    Graph g = Graph(path_len);

    for (const auto node : nodes)
    {
        g.add_node(node);
    }

    for (const auto &edge : edges)
    {
        g.add_edge(edge.first, edge.second);
    }
    return g;
}

void run_test_case(json test)
{
    std::cout << "Test: " << test["description"] << "\n";

    Graph g = get_graph_from_json(test);
    bool expected = test["expected"];
    int cycle_len = test["cycle_len"];

    bool result = g.is_ct_free(cycle_len);
    check_result(expected, result);
}

void run_tests(const std::string &file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cerr << "Failed to open test cases file: " << file_name << std::endl;
        return;
    }

    json test_cases;
    try
    {
        file >> test_cases; // Attempt to parse the file
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    for (const auto &test : test_cases)
    {
        run_test_case(test);
    }
}

int main()
{
    run_tests("./tests/cases/is_ct_free.json");
    return 0;
}