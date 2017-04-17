# -*- coding: utf-8 -*-
"""
Created on Sun Apr 16 19:59:50 2017

@author: tiago


exec(open('analysis_heap.py').read())
"""

import pandas as pd
import matplotlib.pyplot as plt
import math
import subprocess
import sys

graphstyle = 'r-X'

def analyze_push(file):
	data = pd.read_csv(file, sep=' ')
	print(data)
	data['2**i'] = data['i'].apply(lambda x: 2**x)
	data['T(i)'] = data['R*T(i)'] / data['R']
	data['Raz'] = (data['T(i)'] - data['T(i)'].shift(1))/(data['2**i']*data['i'])
	print(data)
	"""
	print(data_group)
	"""
	data.plot(x=['2**i'],y=['Raz'], legend=False, grid=True, style=graphstyle)
	plt.ylabel('Tempo Normalizado [$ms$]')
	plt.xlabel('Quantidade de Números')
	plt.show()

def analyze_update(file):
	data = pd.read_csv(file, sep=' ')
	data['2**i'] = data['i'].apply(lambda x: 2**x)
	data['T(i)'] = data['R*T(i)'] / data['R']
	data['Raz'] = data['T(i)']/(data['2**i']*data['i'])
	print(data)
	"""
	print(data_group)
	"""
	data.plot(x=['2**i'],y=['Raz'], legend=False, grid=True, style= graphstyle)
	plt.ylabel('Tempo Normalizado [$ms$]')
	plt.xlabel('Quantidade de Números')
	plt.show()

def analyze_delete(file):
	data = pd.read_csv(file, sep=' ')
	data['2**i'] = data['i'].apply(lambda x: 2**x)
	data['Raz'] = data['T(i)']/(data['2**i']*data['i'])
	print(data)
	"""
	print(data_group)
	"""
	data.plot(x=['2**i'],y=['Raz'], legend=False, grid=True, style= graphstyle)
	plt.ylabel('Tempo Normalizado [$ms$]')
	plt.xlabel('Quantidade de Números')
	plt.show()

prefix = 'heap_measure_'

subprocess.run(['make', 'heap'], check=True )
subprocess.run(['./heap', prefix ], check=True)

analyze_push(prefix + 'push')
analyze_update(prefix + 'update')
analyze_delete(prefix + 'delete')

