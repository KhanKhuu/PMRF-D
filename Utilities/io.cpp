/**
  Implementations of file I/O functions used in PMRF-D.
 */

#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "io.hpp"
#include <iostream> // DEBUG

/**
  Reads the binary image data into the vector one byte at a time.
 
  @param fileName the path/name of the binary file containing the image data
  @param data pointer to the vector<uint8_t> that stores the image data
 */
void readImageFileToVector(std::string fileName, std::vector<uint8_t> *data) {
	std::fstream imageFileStream (fileName, std::ios::in | std::ios::binary);
    if (!imageFileStream.is_open()) {
        throw std::invalid_argument("file " + fileName + " not found");
    }
	char binVal;
    
    // read image data into the vector one byte at a time
    while ( !imageFileStream.eof()) {
        imageFileStream.read( &binVal, 1);
		data->push_back(binVal);
	}

	imageFileStream.close();
}

/**
  Copies the denoised image data from the given vector to the given file path.
 
  @param fileName path to the output file in which to store the denoised image
  @param data pointer to the data vector that holds the denoised image data
  @param WIDTH width in bytes of the output image
  @param HEIGHT height in bytes of the output image
 */
void writeDataVectorToFile( std::string fileName, std::vector<uint8_t> *data, const int WIDTH, const int HEIGHT ) {
	std::fstream image_file_stream (fileName, std::ios::out | std::ios::binary);
    char* binValArray = new char [WIDTH * HEIGHT];
	std::copy( data->begin(), data->end(), binValArray );
	image_file_stream.write( binValArray, data->size() );
	image_file_stream.close();

	delete [] binValArray;
}

