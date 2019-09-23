#include <iostream>
#include <utility> //for std::pair and its helper functions
#include <vector>

int main() {
	std::pair<int, int> pair1 = std::make_pair(1, 3);
	std::cout << "first = " << pair1.first << std::endl;
	std::cout << "second = " << pair1.second << std::endl;
	
	std::vector<std::vector<std::pair<int, int>>> cliques;

}
