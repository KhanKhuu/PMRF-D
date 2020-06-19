/**
  Header file for the file I/O functions used in PMRF-D. See io.cpp for implementations.
 */

#ifndef IO_H
#define IO_H

/**
 Reads the binary image data into the vector one byte at a time.

 @param fileName the path/name of the binary file containing the image data
 @param data pointer to the vector<uint8_t> that stores the image data
*/
void readImageFileToVector(std::string fileName, std::vector<uint8_t> *data);
/**
 Copies the denoised image data from the given vector to the given file path.

 @param fileName path to the output file in which to store the denoised image
 @param data pointer to the data vector that holds the denoised image data
 @param WIDTH width in bytes of the output image
 @param HEIGHT height in bytes of the output image
*/
void writeDataVectorToFile( std::string fileName, std::vector<uint8_t> *data, const int WIDTH, const int HEIGHT );

#endif
