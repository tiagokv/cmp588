# -*- coding: utf-8 -*-
"""
Created on Thu Jul  6 12:31:35 2017

@author: tiago
"""

import subprocess as sp
import pandas as pd
import sys

tsp_exec = { 'g':["berlin52.tsp", 
                    "brd14051.tsp", 
                    "d18512.tsp", 
                    "fnl4461.tsp", 
                    "pcb3038.tsp", 
                    "pr2392.tsp", 
                    "rl5915.tsp", 
                    "rl5934.tsp", 
                    "usa13509.tsp", 
                    "vm1748.tsp"],
             'p':["berlin52.tsp", 
                    "fnl4461.tsp", 
                    "pcb3038.tsp", 
                    "pr2392.tsp", 
                    "rl5915.tsp", 
                    "rl5934.tsp",  
                    "vm1748.tsp"]
#             'pg': ["berlin52.tsp", 
#                    "brd14051.tsp", 
#                    "d18512.tsp", 
#                    "fnl4461.tsp", 
#                    "pcb3038.tsp", 
#                    "pr2392.tsp", 
#                    "rl5915.tsp", 
#                    "rl5934.tsp", 
#                    "usa13509.tsp", 
#                    "vm1748.tsp"] 
}

data = pd.DataFrame(columns = ["mode", "file", "min_cost", "time"]);
                
for measure_mode, files in tsp_exec.items():
    print("Executing measure mode " + measure_mode)
    for file in files:
        print("Measuring file " + file)
        file_hdl = open("../" + file) 
        sub = sp.Popen(['./measure', measure_mode], stdout=sp.PIPE, stderr=sp.PIPE, stdin=file_hdl)
        output, error_output = sub.communicate()
        measure_col = error_output.decode("UTF-8").replace("\n","").split(" ")
        data.loc[data.shape[0]] = [measure_mode, file] + measure_col

print(data)
data.to_csv("./measures1.dat")


