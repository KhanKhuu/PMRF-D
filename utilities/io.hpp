#ifndef IO_H
#define IO_H

void read_image_file_to_vector(std::string file_name, std::vector<uint8_t> *data);
void write_data_vector_to_file( std::string file_name, std::vector<uint8_t> *data, const int WIDTH, const int HEIGHT );

#endif
