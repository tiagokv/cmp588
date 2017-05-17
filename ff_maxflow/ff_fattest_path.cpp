
#include <iostream>

#include "DimacsReader.hpp"
#include "FordFulkersonFattestPath.hpp"

using namespace std;

int main(int argc, char **argv) {
    DimacsReader direader;

    size_t source, target;
    auto graph = direader.read_max_flow_graph(cin, source, target);

    FordFulkersonFattestPath fffat(*graph, source, target);

    cout << "The max flow from " << source << " to " << target << " is " << fffat.get_max_flow() << endl;
}