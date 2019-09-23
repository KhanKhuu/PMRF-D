#include <iostream>
#include "clamp.hpp"

int main() {
	std::cout << "100 clamped to low 0 and high 200: " << clamp(100, 0, 200) << std::endl;
	std::cout << "100 clamped to low 0 and high 50: "  << clamp(100, 0, 50) << std::endl;
	std::cout << "100 clamped to low 150 and high 200: " << clamp(100, 150, 200) << std::endl;
	std::cout << "100 clamped to low 200 & high 0 (testing high < low error case): " << clamp(100, 200, 0) << std::endl;
	std::cout << "end main." << std::endl;
}
