Para compilar dijkstra_measure e usa_measure, usar o seguinte comando abaixo:

clang++-3.5 -Wall --std=c++11 -I../src usa_measure.cpp ../src/Graph.cpp ../src/Dijkstra.cpp -o usa_measure

clang++-3.5 -Wall --std=c++11 -I../src dijkstra_measure.cpp ../src/Graph.cpp ../src/Dijkstra.cpp -o dijkstra_measure

Para executar o usa_measure, basta enviar, via stdin o arquivo DIMACS a ser analisado.

Para executar o dijkstra_measure, ver argumentos abaixo em ordem:
- 1: 'v' caso variar vértices e 'e' para arestas
- 2: Quantidade fixa de vértices ou arestas
- 3: Quantidade de repetições a serem feitas
- 4: Potencia de 2 da quantidade mínima a ser variada
- 5: Potência de 2 da quantidade até qual será variada