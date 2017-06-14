# -*- coding: utf-8 -*-
"""
Created on Thu May 18 19:36:10 2017

@author: tiago
"""

# -*- coding: utf-8 -*-
"""
Created on Sun Apr 16 19:59:50 2017

@author: tiago


exec(open('analysis_heap.py').read())
"""

import pandas as pd
import matplotlib.pyplot as plt
import math

graphstyle = 'r-X'

def ff_fattest_path_dijkstra_binheaps(n, m, capacity):
    dijkstra = (n + m) * n.apply(lambda x: math.log(x, 2)) 
    return dijkstra * m * capacity.apply(lambda x: math.log(x, math.e))

def hopcroft_karp(n,m):
    return n.apply(lambda x: math.sqrt(x))*(n + m)

def analyze_ff(file, measure='Edges'):
    data = pd.read_csv(file, sep=' ')
    data['Raz'] = data['FFTime']/ff_fattest_path_dijkstra_binheaps(data['Vertices'], data['Edges'], data['Vertices'])
    print(data)
    """
    print(data_group)
    """
    data.plot(x=[measure],y=['Raz'], legend=False, grid=True, style=graphstyle)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel('Quantidade de Arestas')
    plt.show()

def analyze(file, measure='Edges'):
    data = pd.read_csv(file, sep=' ')
    data['Raz'] = data['HHTime']/hopcroft_karp(data['Vertices'], data['Edges'])
    print(data)
    """
    print(data_group)
    """
    data.plot(x=[measure],y=['Raz'], legend=False, grid=True, style=graphstyle)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel('Quantidade de Arestas')
    plt.show()

def compare_ff_hh(file, measure='Vertices'):
    data = pd.read_csv(file, sep=' ')
    data.rename(columns = {'HHTime': 'Hopcroft-Karp', 'FFTime': 'Ford-Fulkerson Fattest Path'}, inplace=True )
    data.plot(x=[measure], y=['Hopcroft-Karp', 'Ford-Fulkerson Fattest Path'], loglog = True , 
                                                   legend=True, grid=True)
    plt.ylabel('Tempo [$ms$]')
    plt.xlabel('Quantidade de Arestas')
    plt.show()

#analyze('measure_101_10000_15_26.dat')
#compare_ff_hh('measure_101_10000_15_26.dat')
#analyze_ff('measure_101_10000_15_26.dat')
analyze('measure_118_1000000_10_20.dat', 'Vertices')
compare_ff_hh('measure_118_1000000_10_20.dat', 'Vertices')
#analyze_ff('measure_118_1000000_10_20.dat', 'Vertices')
