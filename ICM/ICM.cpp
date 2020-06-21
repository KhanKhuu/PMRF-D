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
 
  @param pixelValue intensity value of the image at the given pixel
  @param proposedValue proposed new value for the pixel
 */
int quad(int pixelValue, int proposedValue) {
	return (pixelValue - proposedValue) * (pixelValue - proposedValue);
}

/**
  Performs Iterative Conditional Modes denoising on the given vector of auxiliary MRFs.

  @param auxMRFs graph partitions (use LAP for partitioning)
*/
void ICM(std::vector<AuxMRF> *auxMRFs) {
	
	int minEnergy;  // the lowest energy obtainable by changing the value
                    // of a pixel at a given position
	int energy;     // energy at a given pixel in the image
    uint8_t bestX;      // value for a pixel that results in the least energy
    const int LAMBDA = 0.5;   // weighting for the pairwise (smoothness) term
    const int PSI_MAX = 1; // truncates the pairwise term (psi_max = 1 -> Potts)
    
    for (auto &auxMRF: *auxMRFs) {
        for (auto &baseNode: auxMRF.getBaseNodes()) {
            minEnergy = std::numeric_limits<int>::max();
            bestX = 0;
            for (uint16_t x = 0; x < 256; ++x) {
                energy = LAMBDA * quad(baseNode.value, x);
                for (auto augmentingNode: auxMRF.getAugmentingNodes()) {
                    energy +=  std::min(quad(augmentingNode.value, x), PSI_MAX);
                }
                
                // save the parameter that results in minimum energy
                if (energy < minEnergy) {
                    minEnergy = energy;
                    bestX = x;
                }
            }
            baseNode.value = bestX;
        }
    }
}

