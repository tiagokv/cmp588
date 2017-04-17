# -*- coding: utf-8 -*-
"""
Spyder Editor

Este é um arquivo de script temporário.
"""

import pandas as pd
import matplotlib.pyplot as plt
import math

#data = pd.read_csv('manual_dka_vert_2', sep=' ')
data = pd.read_clipboard(sep=' ')
print(data)
data['Raz'] = data['R*T(i)']/((data['V'] + data['E'])*data['V'].apply(lambda x: math.log2(x)))
data_group = data.groupby(by=['i']).mean()
"""
print(data_group)
"""
data_group.plot(x=['V'],y=['Raz'], grid=True, style='r-X')
plt.grid(True)
plt.show()

