#include <cassert> //for debugging
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>
#include "ICM.hpp"

int quad(int p_val, int x_val) {
	return (p_val - x_val) * (p_val - x_val);
}

void ICM(std::vector<std::vector<std::pair<uint8_t, int>>> *cliques) {
	
	int min_energy;
	int energy;

	for (auto it_v = cliques->begin(); it_v != cliques->end(); ++it_v) {
		std::cout << "Performing ICM on clique " << it_v - cliques->begin() << " of " << cliques->size() << std::endl;
		for (auto it_p = it_v->begin(); it_p != it_v->end(); ++it_p) {
			
			min_energy = std::numeric_limits<int>::max();
			
			for (int x = 0; x < 256; x++) {
		       		energy = quad(it_p->first, x) +
					 ((it_p - 2) > it_v->begin() ? quad((it_p - 2)->first, x) : 0) +
				 	 ((it_p - 1) > it_v->begin() ? quad((it_p - 1)->first, x) : 0) +
					 ((it_p + 1) < it_v->end() ? quad((it_p + 1)->first, x) : 0) +
					 ((it_p + 2) < it_v->end() ? quad((it_p + 2)->first, x) : 0) ;

				if (energy < min_energy) {
					min_energy = energy;
					it_p->first = x;
				}
			}

		}			
	}			
}

