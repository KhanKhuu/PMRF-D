#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../ICM/ICM.hpp"
#include "../Utilities/io.hpp"
#include "../Utilities/LAP.hpp"

void reconstruct_image(std::vector< std::vector< std::pair< uint8_t, int > > > *cliques, std::vector<uint8_t> *data) {
	for (std::vector< std::pair< uint8_t, int > > v: *cliques) {
		for (std::pair<uint8_t, int> p: v) {
			data->at(p.second) = p.first;
		}
	}      		       
}

int main(int argc, const char** argv) {
    
    // check for proper usage and return if not
    if (argc < 4) {
        std::cout << "Usage: ./PMRF-D inputImageFile.dat width height" << std::endl;
        return 1;
    }
    
	// store command line args
	std::string file_name = argv[1];
	const int WIDTH = atoi(argv[2]);
	const int HEIGHT = atoi(argv[3]);
    
	// the data vector that will hold the binary image data
	std::vector<uint8_t> data;
    
	// the vector in which to store auxiliary MRFs resulting from the LAP
    // algorithm.
    // Note: this vector stores pairs of the values of pixels (pair->first) with
    // their postions (pair->second)
	std::vector< std::vector< std::pair< uint8_t, int > > > auxMRFs;

    // user feedback
	std::cout << "using file: " << file_name << " (" << WIDTH << " x " << HEIGHT << ")" << std::endl;
	
	// read the data from the file into vector<uint8_t> data
	readImageFileToVector(file_name, &data);

	//write the data back to the file for testing purposes
	writeDataVectorToFile("Output/test_output.dat", &data, WIDTH, HEIGHT);
    
	//break data up into cliques according to the LAP algorithm
	LAP(&auxMRFs, &data, WIDTH, HEIGHT);

	//perform ICM on the cliques	
	std::vector< std::vector< std::pair< uint8_t, int > > > auxMRFs_before_ICM = auxMRFs;
	ICM(&auxMRFs);
	if (auxMRFs_before_ICM == auxMRFs) {
		std::cout << "(DEBUG): No change after running ICM." << std::endl;
	}

	//rebuild the image with the new, denoised pixel values produced by ICM
	reconstruct_image(&auxMRFs, &data);

	writeDataVectorToFile("Output/PMRF-D_output.dat", &data, WIDTH, HEIGHT);
}
