import os

os.system("g++ -std=c++11 dp_trans.cpp -o dp_trans")
output_folder = "solutions" 	

for i in range(1, 5):
	output_file = output_folder + "/solution_" + str(i) + ".txt"
	command = "./dp_trans " + str(i) + " " + output_file
	os.system(command)