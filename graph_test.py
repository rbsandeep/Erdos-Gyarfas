import networkx as nx
import numpy as np
from networkx.algorithms import isomorphism


def load_adjacency_matrix(file_path):
    matrix = []
    with open(file_path, 'r') as f:
        for line in f.readlines():
            row = [int(x) for x in line.split()]
            matrix.append(row)
    if not matrix:
        return []
    assert len(matrix) == 0 or len(matrix) == len(matrix[0])
    return np.array(matrix)


def read_and_save_adj_matrix(input_file: str, output_file: str):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    edges = []
    nodes = set()
    for line in lines:
        u, v = map(int, line.split())
        edges.append((u, v))
        nodes.add(u)
        nodes.add(v)

    nodes = sorted(nodes)
    node_index = {node: i for i, node in enumerate(nodes)}

    n = len(nodes)
    adj_matrix = np.zeros((n, n), dtype=int)

    for u, v in edges:
        i, j = node_index[u], node_index[v]
        adj_matrix[i][j] = 1
        adj_matrix[j][i] = 1

    np.savetxt(output_file, adj_matrix, fmt='%d')


def count_cycles_of_length(adj_matrix, cycle_length):
    G = nx.from_numpy_array(adj_matrix)
    print(f"Graph: Nodes: {len(G)}, Edges: {len(G.edges())}")
    count = 0
    for cycle in nx.simple_cycles(nx.DiGraph(G)):
        if len(cycle) == cycle_length:
            count += len(cycle) == cycle_length
    return count


def check_cycles(file_path):
    adjacency_matrix = load_adjacency_matrix(file_path)
    num_4_cycles = count_cycles_of_length(adjacency_matrix, 4)
    print(f"Number of 4-cycles: {num_4_cycles}")
    num_8_cycles = count_cycles_of_length(adjacency_matrix, 8)
    print(f"Number of 8-cycles: {num_8_cycles}")
    num_16_cycles = count_cycles_of_length(adjacency_matrix, 16)
    print(f"Number of 16-cycles: {num_16_cycles}")


def is_isomorphic(g1, g2):
    gm = isomorphism.GraphMatcher(g1, g2)
    return gm.is_isomorphic()

# read_and_save_adj_matrix('./possible.txt', "./temp.txt")
# check_cycles('./temp.txt')


G0 = nx.from_numpy_array(load_adjacency_matrix("./special/markstroem.txt"))
G1 = nx.from_numpy_array(load_adjacency_matrix(
    "./special/24-node-cubic-no-4-8-cycles-p18-free.1.txt"))
G2 = nx.from_numpy_array(load_adjacency_matrix(
    "./special/24-node-cubic-no-4-8-cycles-p18-free.2.txt"))
G3 = nx.from_numpy_array(load_adjacency_matrix(
    "./special/24-node-cubic-no-4-8-cycles-p18-free.3.txt"))

GTest = nx.from_numpy_array(load_adjacency_matrix("./temp.txt"))


print("GTest: Nodes: {}, Edges: {}", len(GTest), len(GTest.edges()))
if is_isomorphic(G0, GTest):
    print("Target is Isomorphic to Markstroem Graph")
if is_isomorphic(G1, GTest):
    print("Target is Isomorphic to G1")
if is_isomorphic(G2, GTest):
    print("Target is Isomorphic to G2")
if is_isomorphic(G3, GTest):
    print("Target is Isomorphic to G3")
