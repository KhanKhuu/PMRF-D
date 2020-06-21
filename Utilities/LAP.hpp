/**
  Header file for the Linear and Parallel (LAP) graph partitioning algorithm.
 */

#ifndef LAP_HPP
#define LAP_HPP

/**
 Partitions the image graph into a group of cliques. Cliques are created according to the Linear and
 Parallel (LAP) algorithm developed by Mizrahi, Denil, and de Freitas.

 @param auxMRFs cliques of the graph stored as pairs of values with their positions in the original data vector
 @param data the input image's binary data stored one-dimensionally
 @param WIDTH width of the input image
 @param HEIGHT height of the input image
*/
void LAP (std::vector<AuxMRF> *auxMRFs,
		      const std::vector<uint8_t> *data, 
		      const int WIDTH, 
		      const int HEIGHT); 

#endif //LAP_HPP
