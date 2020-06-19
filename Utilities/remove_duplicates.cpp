/**
  Implementation of the remove duplicates function.
*/

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>
#include "remove_duplicates.hpp"

/**
  Removes duplicate elements in the binary image data vector.
 
  @param data vector<uint8_t> that stores the binary image data
 */
void removeDuplicates(std::vector< std::pair< uint8_t, int > > *data) {
	auto end = data->end();

	for (auto it = data->begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}
	data->erase(end, data->end());
}

