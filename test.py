import networkx as nx
import numpy as np

def read_adjacency_matrix(filename):
    """Reads an adjacency matrix from a file."""
    with open(filename, 'r') as file:
        matrix = []
        for line in file:
            matrix.append([int(x) for x in line.strip().split()])
        return np.array(matrix)

def are_graphs_isomorphic(matrix1, matrix2):
    """Checks if two graphs are isomorphic."""
    G1 = nx.from_numpy_array(matrix1)
    G2 = nx.from_numpy_array(matrix2)
    return nx.is_isomorphic(G1, G2)

# Load adjacency matrices from files
matrix1 = read_adjacency_matrix('markstrom.txt')
matrix2 = read_adjacency_matrix('test.txt')

# Check if graphs are isomorphic
if are_graphs_isomorphic(matrix1, matrix2):
    print("The graphs are isomorphic.")
else:
    print("The graphs are not isomorphic.")