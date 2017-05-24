import subprocess
import os
import sys

if "build" not in list(os.listdir(".")):
	print("project was not build")
	sys.exit(1)

if "new_washington" not in list(os.listdir("./build")):
	subprocess.check_output(["gcc", "-O3", "new_washington.c", "-o", "build/new_washington"])
	if "new_washington" not in list(os.listdir("./build")):
		print("compilation error for new_washington graph generator")
		sys.exit(1)

exec_file = "./build/new_washington"
dir_path = "./measure/data/"

weight = str(1000)
print("Generating mesh data...")
r = str(100)

print("fixed r = " + r)
for c in range(100,1200, 100):
	file_name = "mesh_fixed_r_100_" + str(c) + ".gr"
	if os.path.isfile(dir_path + file_name) == False:  
		subprocess.check_output([exec_file, "1", r, str(c), weight, dir_path + file_name])
	else:
		print(dir_path + file_name + " already exists, not overwriting")

print("Generating matching data...")

n = str(20000)
print("fixed n = " + n)

for d in range(10,21):
	file_name = "matching_fixed_n_" + n + "_" + str(d) + ".gr"
	if os.path.isfile(dir_path + file_name) == False:
		subprocess.check_output([exec_file, "4", n, str(d), weight, dir_path + file_name])
	else:
		print(dir_path + file_name + " already exists, not overwriting")

print("Generating exponential line...")

n = str(500)
m = n
print("fixed n = " + n + " m = " + m)

for d in range(5,16):
	file_name = "expline_fixed_n_m_" + n + "_" + m + "_" + str(d) + ".gr"
	if os.path.isfile(dir_path + file_name) == False:
		subprocess.check_output([exec_file, "7", n, m, str(d), weight, dir_path + file_name])
	else:
		print(dir_path + file_name + " already exists, not overwriting")