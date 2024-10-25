#include <iostream>
#include <chrono>


#include "graph.h"
#include "lib.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    auto start = high_resolution_clock::now();

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k = atoi(argv[1]);

    if (k < 3) {
        cout << "No counter example among P_k-free graphs" << endl;
        return 0;
    }

    validate_conjecture(k);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "time taken: "<< duration.count() << " microseconds" << endl;
    return 0;
}
