/**
  Header file for the Linear and Parallel (LAP) graph partitioning algorithm.
 */

#ifndef LAP_HPP
#define LAP_HPP

/**
 Adds the first neighborhood of the given element in the data vector to the cliques vector.

 @param data binary image data in its entirety
 @param clique a clique of image graph elements grouped together according to LAP
 @param WIDTH width of the input image
 @param HEIGHT height of the input image
 @param index index of the current image pixel whose first neighborhood we are getting
*/
void get_first_neighborhood (const std::vector<uint8_t> *data, 
			     std::vector<std::pair< uint8_t, int > > *clique,
			     const int WIDTH,
			     const int HEIGHT,
			     const int index);

/**
 Partitions the image graph into a group of cliques. Cliques are created according to the Linear and
 Parallel (LAP) algorithm developed by Mizrahi, Denil, and de Freitas.

 @param cliques cliques of the graph stored as pairs of values with their positions in the original data vector
 @param data the input image's binary data stored one-dimensionally
 @param WIDTH width of the input image
 @param HEIGHT height of the input image
*/
void LAP (std::vector<std::vector< std::pair< uint8_t, int > > > *cliques, 
		      const std::vector<uint8_t> *data, 
		      const int WIDTH, 
		      const int HEIGHT); 

#endif //LAP_HPP
