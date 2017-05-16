#ifndef DIMACS_READER_HPP
#define DIMACS_READER_HPP

#include <iostream>
#include <string>
#include <memory>

#include "Graph.hpp"
#include "ResidualGraph.hpp"

class DimacsReader{
    public:
        std::shared_ptr<ResidualGraph> read_max_flow_graph(std::string filepath, size_t& source, size_t& target);
        std::shared_ptr<ResidualGraph> read_max_flow_graph(std::istream& in, size_t& source, size_t& target);

        std::shared_ptr<Graph> read_graph(std::string filepath);
        std::shared_ptr<Graph> read_graph(std::istream& in);
};

#endif