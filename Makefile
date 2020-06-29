PMRF-D-exec: 
	clang++ -o run PMRF-D/PMRF-D.cpp Model/Node.cpp Utilities/io.cpp Utilities/LAP.cpp Model/AuxMRF.cpp ICM/ICM.cpp -std=c++11
