#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>
#include "remove_duplicates.hpp"

void remove_duplicates(std::vector<std::pair<uint8_t, int>> *data) {
	auto end = data->end();

	for (auto it = data->begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}
	data->erase(end, data->end());
}

