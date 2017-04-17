CPPC=clang++-3.5
CFLAGS=-Wall --std=c++11 -I../src/
DIJKS_DEP=../src/Graph.cpp ../src/Dijkstra.cpp

dijkstra: dijkstra_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@

usa: usa_measure.cpp
	$(CPPC) $(CFLAGS) $(DIJKS_DEP) $< -o $@

heap: heap_measure.cpp
	$(CPPC) $(CFLAGS) $< -o $@ -g