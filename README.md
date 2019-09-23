TODO:

DONE: 1) Store the width and height from command line args\
DONE: 2) Read input image fstream into vector from command line arg\
DONE: 3) Break up the data vector into cliques with LAP, storing values and indices in vector<vector<std::pair>> (implement LAP)\
4) Distribute out evenly sets of vector<std::pair>'s (sub-vector<vector<std::pair>>'s)\
	Note: the pair will be (value, index)\
5) Process the subsets with ICM\
6) When done processing, write the modified values into char[SIZE] output_data at the indices\
7) Write the output_data into the output fstream\

