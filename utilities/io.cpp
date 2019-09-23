#include <fstream>
#include <string>
#include <vector>
#include "io.hpp"

void read_image_file_to_vector(std::string file_name, std::vector<uint8_t> *data) {
	std::fstream image_file_stream (file_name, std::ios::in | std::ios::binary);
	char bin_val;
	
	while ( image_file_stream.read( &bin_val, 1) ) {
		data->push_back(bin_val);
	}

	image_file_stream.close();
}

void write_data_vector_to_file( std::string file_name, std::vector<uint8_t> *data, const int WIDTH, const int HEIGHT ) {	
	std::fstream image_file_stream (file_name, std::ios::out | std::ios::binary);
	char* bin_val = new char [WIDTH * HEIGHT];
	std::copy( data->begin(), data->end(), bin_val );
	image_file_stream.write( bin_val, data->size() );
	image_file_stream.close();

	delete [] bin_val;
}

