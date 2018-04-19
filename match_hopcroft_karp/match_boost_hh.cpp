#include <iostream>
#include <cassert>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace boost;
 
// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,undirectedS>::vertex_descriptor Node;
typedef adjacency_list_traits<vecS,vecS,undirectedS>::edge_descriptor Edge;
 
// information stored in vertices
struct VertexInformation {
  Node mate; // partner or graph_traits<Graph>::null_vertex()
};
// information stored in edges
struct EdgeInformation {};
 
// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS,vecS,undirectedS,VertexInformation,EdgeInformation> Graph;
 
int main(int argc, char *argv[]) {
 
  // (1) generate random bi-partite graph
  Graph g;

  string line="", dummy;
  while (line.substr(0,6) != "p edge")
    getline(cin,line);
  
  // (1) get nodes and edges
  stringstream linestr;
  linestr.str(line);
    size_t number_vertices, number_edges;
  linestr >> dummy >> dummy >> number_vertices >> number_edges;
  
  for(size_t i = 0; i < number_vertices; i++)
    add_vertex(g);

  unsigned i=0;
  while (i < number_edges) {
    getline(cin,line);
    if (line.substr(0,2) == "e ") {
      stringstream arc(line);
      unsigned u, v;
      char ac;
      arc >> ac >> u >> v;
      add_edge(u-1, v-1, g);
      i++;
    }
  }
 
  // (2) get maximum matching
  edmonds_maximum_cardinality_matching(g, get(&VertexInformation::mate,g));
  unsigned card = 0;
  graph_traits<Graph>::vertex_iterator vb, ve;
  for ( tie(vb, ve)=vertices(g); vb != ve; vb++)
    if (g[*vb].mate != graph_traits<Graph>::null_vertex())
      card++;
  
  cerr << "The cardinality of a maximum matching is " << card/2 << "." << endl;
}