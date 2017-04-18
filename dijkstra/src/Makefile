CPPC=clang++-3.5
CFLAGS=-Wall --std=c++11 -I. -I/home/tiagokv/boost
DIJKS_DEP=Graph.cpp Dijkstra.cpp

dijkstra: main.cpp Dijkstra.cpp Graph.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@ -g