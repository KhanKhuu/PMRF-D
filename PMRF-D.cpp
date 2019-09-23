#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "utilities/io.hpp"
#include "utilities/LAP.hpp"

int main(int argc, const char** argv) {
	//store command line args
	std::string file_name = argv[1];
	const int WIDTH = atoi(argv[2]);
	const int HEIGHT = atoi(argv[3]);
	const int SIZE = WIDTH * HEIGHT;
	//the data vector
	std::vector<uint8_t> data;
	//the vector in which to store cliques resulting from the LAP algorithm 	
	std::vector<std::vector<std::pair<uint8_t, int>>> cliques;


	//check whether we have our proper command line arg inputs
	std::cout << "using file: " << file_name << " (" << WIDTH << " x " << HEIGHT << ")" << std::endl;
	
	//read the data from the file into vector<uint8_t> data
	read_image_file_to_vector(file_name, &data);

	//write the data back to the file for testin purposes
	write_data_vector_to_file("data/test_output.dat", &data, WIDTH, HEIGHT);

	//break data up into cliques according to the LAP algorithm
	LAP(&cliques, &data, WIDTH, HEIGHT);

	
}
