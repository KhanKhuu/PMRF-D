/**
  Header file for the file I/O functions used in PMRF-D. See io.cpp for implementations.
 */

#ifndef IO_H
#define IO_H

/**
 Writes the binary image data into the data vector. data is a 3-channel vector of vectors of the image data, with channels
 being the colors BGR in that order.
 
 @param img the OpenCV Mat object containing the image data
 @param data pointer to the vector<uint8_t> that stores the image data
*/
void transferMatDataToVector(cv::Mat *img, std::vector< std::vector<uint8_t> > *data);

/**
 Writes the denoised image data from the given vector to the given file path.

 @param img the OpenCV Mat object containing the image data
 @param fileName path to the output file in which to store the denoised image
 @param data pointer to the data vector that holds the denoised image data
*/
void writeImageToFile( cv::Mat *img, std::string fileName, std::vector< std::vector<uint8_t> > *data );

#endif
