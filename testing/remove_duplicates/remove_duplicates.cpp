#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

// void remove_duplicates(std::vector<std::pair<uint8_t, int>> &data) {
// 	std::unordered_set<std::pair<uint8_t, int>> set;
// 	auto end = std::remove_if(data.begin(), data.end(), [&set](std::pair<uint8_t, int> const  &p) {
// 							 	   return !set.insert(p).second;
// 							      });
// 	data.erase(end, data.end());
// }

void remove_duplicates(std::vector<std::pair<uint8_t, int>> *data) {
	auto end = data->end();

	for (auto it = data->begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	data->erase(end, data->end());
}

int main() {
	std::vector<std::pair<uint8_t, int>> data;
	data.push_back(std::make_pair(10, 15));
	data.push_back(std::make_pair(85, 14));
	data.push_back(std::make_pair(48, 5));
	data.push_back(std::make_pair(16, 16));
	data.push_back(std::make_pair(18, 25));
	data.push_back(std::make_pair(16, 16));
	data.push_back(std::make_pair(10, 15));
	data.push_back(std::make_pair(25, 17));

	for (std::pair<uint8_t, int> p: data) {
		std::cout << "first: " << int(p.first) << ", second: " << p.second << std::endl;
	}
	
	remove_duplicates(&data);

	for (std::pair<uint8_t, int> p: data) {
		std::cout << "first: " << int(p.first) << ", second: " << p.second << std::endl;
	}
}
