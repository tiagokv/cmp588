# -*- coding: utf-8 -*-
"""
Created on Sun Apr 16 19:59:50 2017

@author: tiago
"""

import pandas as pd
import matplotlib.pyplot as plt
import math

#data = pd.read_csv('manual_dka_vert_2', sep=' ')
data = pd.read_clipboard(sep=' ')
print(data)
data['2**i'] = data['i'].apply(lambda x: 2**x)
data['Raz2'] = data['R*T(i)']/(data['2**i']*data['i'].apply(lambda x: math.log2(x-1)))
data['Raz'] = data['R*T(i)']/(data['2**i']*data['i'])
print(data)
"""
print(data_group)
"""
data.plot(x=['2**i'],y=['Raz', 'Raz2'], grid=True, style='r-X')
plt.grid(True)
plt.show()

