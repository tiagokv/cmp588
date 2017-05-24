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
from mpl_toolkits.mplot3d import Axes3D
import math

graphstyle = 'r-X'

def ff_fattest_path_dijkstra_binheaps(n, m, capacity):
    dijkstra = (n + m) * n.apply(lambda x: math.log(x, 2)) 
    return dijkstra * m * capacity.apply(lambda x: math.log(x, math.e))

def analyze_matching(file):
    data = pd.read_csv(file, sep=' ')
    data['n'] = pd.Series(data = [20000] * data.shape[0])
    data['d'] = data['Edges'] / (data['n']) - 2
    data.sort_values('d', inplace = True)
    data['Raz'] = data['Time']/ff_fattest_path_dijkstra_binheaps(data['Vertices'], data['Edges'], data['MaxFlow'])
    print(data)
    """
    print(data_group)
    """
    data.plot(x=['d'],y=['Raz'], legend=False, grid=True, style=graphstyle)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel('Grau dos Vértices')
    plt.show()

def analyze_mesh(file):
    data = pd.read_csv(file, sep=' ')
    data['r'] = pd.Series(data = [100] * data.shape[0])
    data['c'] = data['Edges'] / (3*data['r']) + 1
    data['c'] = data['c'].apply(lambda x: math.floor(x))
    data.sort_values('c', inplace = True)
    data['Raz'] = data['Time']/ff_fattest_path_dijkstra_binheaps(data['Vertices'], data['Edges'], data['MaxFlow'])
    print(data)
    """
    print(data_group)
    """
    data.plot(x=['c'],y=['Raz'], legend=False, grid=True, style=graphstyle)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel('Quantidade de Colunas')
    plt.show()

def analyze_expline(file):
    data = pd.read_csv(file, sep=' ')
    data['n'] = pd.Series(data = [500] * data.shape[0])
    data['m'] = pd.Series(data = [500] * data.shape[0])
    data['D'] = (data['Edges'] - 2 * data['m'])/ (data['n']*data['m'])
    data['D'] = data['D'].apply(lambda x: math.ceil(x))
    data.sort_values('D', inplace = True)
    data['Raz'] = data['Time']/ff_fattest_path_dijkstra_binheaps(data['Vertices'], data['Edges'], data['MaxFlow'])
    print(data)
    """
    print(data_group)
    """
    data.plot(x=['D'],y=['Raz'], legend=False, grid=True, style=graphstyle)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel('Grau dos Vértices')
    plt.show()

analyze_mesh('measure_mesh_fixed_r.dat')
analyze_matching('measure_matching_fixed_n.dat')
analyze_expline('measure_expline_fixed_n_m.dat')