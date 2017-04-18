# -*- coding: utf-8 -*-
"""
Spyder Editor

Este é um arquivo de script temporário.
"""

import pandas as pd
import matplotlib.pyplot as plt
import math
import subprocess

graphstyle = 'r-X'

def analyze(file, xlabel, xfield):
    data = pd.read_csv(file, sep=' ')
    print(data)
    data['T(i)'] = data['R*T(i)']/data['R']
    data['Raz'] = data['T(i)']/((data['V'] + data['E'])*data['V'].apply(lambda x: math.log2(x)))
    #data['Raz'] = data['T(i)']/data['V'].apply(lambda x: x**2)
    data_group = data.groupby(by=['i']).mean()
    """
    print(data_group)
    """
    data_group.plot(x=[xfield],y=['Raz'], legend=False, grid=True, style= graphstyle)
    plt.grid(True)
    plt.ylabel('Tempo Normalizado [$ms$]')
    plt.xlabel(xlabel)
    plt.show()

#subprocess.run(['./dijkstra', 'e ' ], check=True)

analyze("dka_edges", "Quantidade de arestas", "E")
analyze("dka_vertexes", "Quantidade de vértices", "V")