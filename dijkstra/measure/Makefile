CPPC=g++-4.8
CFLAGS=-Wall --std=c++11 -I../src/
DIJKS_DEP=../src/Graph.cpp ../src/Dijkstra.cpp

dijkstra: dijkstra_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@ -g

usa: usa_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@ -g

heap: heap_measure.cpp
	$(CPPC) $(CFLAGS) $< -o $@ -g