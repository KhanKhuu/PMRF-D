#include <cassert> //for debugging
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>
#include "ICM.hpp"

/**
  Calculates the square of the difference between a given pixel intensity value and a
  prospective new value for that pixel. The sum of these quadratic terms for a given pixel
  and the pixels around it represents the image's energy that we are minimizing.
 
  @param p_val intensity value of the image at the given pixel
  @param x_val proposed new value for the pixel
 */
int quad(int p_val, int x_val) {
	return (p_val - x_val) * (p_val - x_val);
}

/**
  Performs Iterative Conditional Modes denoising on the given vector of cliques.
 
  @param cliques the vector of cliques or partitions of the graph (see LAP implementation)
 */
void ICM(std::vector< std::vector< std::pair< uint8_t, int > > > *cliques) {
	
	int minEnergy;  // the lowest energy obtainable by changing the value
                    // of a pixel at a given position
	int energy;     // energy at a given pixel in the image
    int bestX;      // value for a pixel that results in the least energy
    const int LAMBDA = 0.5;   // weighting for the pairwise (smoothness) term
    const int PSI_MAX = 1; // truncates the pairwise term (psi_max = 1 -> Potts)

    // it_v: iterator over the given vector of vectors of pairs
	for (auto it_v = cliques->begin(); it_v != cliques->end(); ++it_v) {
        
        // user feedback
		std::cout << "Performing ICM on clique " << it_v - cliques->begin() << " of " << cliques->size() << std::endl;

        // it_p: iterator over the given vector of pairs
        // pairs contain pixel values as the first element and
        // position in the image as the second element
		for (auto it_p = it_v->begin(); it_p != it_v->end(); ++it_p) {
			
			minEnergy = std::numeric_limits<int>::max();
            bestX = 0;
			
            // calculate energy for each potential pixel value and store
            // the one that results in the least energy
			for (int x = 0; x < 256; x++) {
                energy = quad(it_p->first, x) + LAMBDA * (
					 std::min ( ((it_p - 2) > it_v->begin() ? quad((it_p - 2)->first, x) : 0), PSI_MAX ) +
				 	 std::min ( ((it_p - 1) > it_v->begin() ? quad((it_p - 1)->first, x) : 0), PSI_MAX ) +
					 std::min ( ((it_p + 1) < it_v->end() ? quad((it_p + 1)->first, x) : 0), PSI_MAX ) +
					 std::min ( ((it_p + 2) < it_v->end() ? quad((it_p + 2)->first, x) : 0), PSI_MAX )
                                                          );

				if (energy < minEnergy) {
					minEnergy = energy;
					bestX = x;
				}
			}
            // update the pixel value with the value that causes the least energy
            it_p->first = bestX;
		}			
	}			
}

