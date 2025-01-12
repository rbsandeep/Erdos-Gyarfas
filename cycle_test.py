import networkx as nx
import numpy as np


def load_adjacency_matrix( file_path ):
    matrix = []
    with open( file_path, 'r' ) as f:
        for line in f.readlines():
            row = [int(x) for x in line.split()]
            matrix.append(row)
    if not matrix:
        return []
    assert len(matrix)==0 or len(matrix) == len(matrix[0])
    return np.array(matrix)

def count_cycles_of_length(adj_matrix, cycle_length):
    G = nx.from_numpy_array(adj_matrix)
    count = 0
    for cycle in nx.simple_cycles(nx.DiGraph(G)):
        if len(cycle) == cycle_length:
            print([v+1 for v in cycle])
            count += len(cycle) == cycle_length
    return count

def main(file_path):
    adjacency_matrix = load_adjacency_matrix(file_path)
    num_4_cycles = count_cycles_of_length(adjacency_matrix, 4)
    print(f"Number of 4-cycles: {num_4_cycles}")
    num_8_cycles = count_cycles_of_length(adjacency_matrix, 8)
    print(f"Number of 8-cycles: {num_8_cycles}")
    num_16_cycles = count_cycles_of_length(adjacency_matrix, 16)
    print(f"Number of 16-cycles: {num_16_cycles}")

main( './temp.txt' )