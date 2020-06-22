PMRF-D-exec: 
	clang++ -o run PMRF-D/PMRF-D.cpp Utilities/Node.cpp Utilities/io.cpp Utilities/LAP.cpp Utilities/AuxMRF.cpp ICM/ICM.cpp -std=c++11
