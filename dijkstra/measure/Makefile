CPPC=g++-4.8
CFLAGS=-Wall --std=c++11 -I../src/ -I/home/tiagokv/boost
DIJKS_DEP=../src/Graph.cpp ../src/Dijkstra.cpp

dijkstra: dijkstra_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@ -g

usa: usa_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@ -g

heap: heap_measure.cpp
	$(CPPC) $(CFLAGS) $< -o $@ -g

heap_vertex: heap_vertex_measure.cpp
	$(CPPC) $(CFLAGS) $< -o $@ -g