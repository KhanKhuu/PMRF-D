#ifndef ICM_HPP
#define ICM_HPP

/**
 Calculates the square of the difference between a given pixel intensity value and a
 prospective new value for that pixel. The sum of these quadratic terms for a given pixel
 and the pixels around it represents the image's energy that we are minimizing.

 @param p_val intensity value of the image at the given pixel
 @param x_val proposed new value for the pixel
*/
int quad(int p_val, int x_val);

/**
  Performs Iterative Conditional Modes denoising on the given vector of cliques.

  @param cliques the vector of cliques or partitions of the graph (see LAP implementation)
*/
void ICM(std::vector< std::vector< std::pair< uint8_t, int > > > *cliques); 

#endif //ICM_HPP
