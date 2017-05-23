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

def analyze_push(file):
    data = pd.read_csv(file, sep=' ')
    # Dijkstra 
    data['Raz'] = data['Time']/((data['Vertices'] + data['Edges']) * data['Vertices'].apply(lambda x: math.log(x, 2)) *
                                data['Edges'] * data['TotalCapacity'].apply(lambda x: math.log(x, math.e)))
    print(data)
    """
    print(data_group)
    """
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    #data.plot(x=['2**i'],y=['Raz'], legend=False, grid=True, style=graphstyle)
    ax.plot(data['Edges'], data['Vertices'], data['Raz'])
    #plt.ylabel('Tempo Normalizado [$ms$]')
    #plt.xlabel('Quantidade de Números')
    plt.show()

analyze_push('measure_mesh.dat')
