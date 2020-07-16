/**
  Implementations of file I/O functions used in PMRF-D.
 */

// OpenCV includes:
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

// Classic includes
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "io.hpp"
#include <iostream> // DEBUG


/**
  Writes the binary image data into the data vector. data is a 3-channel vector of vectors of the image data, with channels
  being the colors BGR in that order.
 
  @param img the OpenCV Mat object containing the image data
  @param data pointer to the vector< vector<uint8_t> > that stores the image data
 */
void transferMatDataToVector(cv::Mat *img, std::vector< std::vector<uint8_t> > *data) {
    for (size_t channel = 0; channel < img->channels(); ++channel) {
        for (size_t row = 0; row < img->rows; ++row) {
            for (size_t col = 0; col < img->cols; ++col) {
                data->at(channel).at(row*(img->cols) + col) = img->at<cv::Vec3b>(row, col)[channel];
            }
        }
    }
}

/**
 Writes the denoised image data from the given vector to the given file path.

 @param img the OpenCV Mat object containing the image data
 @param fileName path to the output file in which to store the denoised image
 @param data pointer to the data vector that holds the denoised image data
*/
void writeImageToFile( cv::Mat *img, std::string fileName, std::vector< std::vector<uint8_t> > *data ) {
    for (size_t channel = 0; channel < img->channels(); ++channel) {
        for (size_t row = 0; row < img->rows; ++row) {
            for (size_t col = 0; col < img->cols; ++col) {
                img->at<cv::Vec3b>(row, col)[channel] = data->at(channel).at(row*(img->cols) + col);
            }
        }
    }
    
    imwrite(fileName, *img);
}

