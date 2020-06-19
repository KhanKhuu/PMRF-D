/**
  Implements Linear and Parallel (LAP) graph partitioning algorithm.
 */

#include <cstdint>
#include <iostream> //for debugging
#include <utility>
#include <vector>
#include "LAP.hpp"
#include "remove_duplicates.hpp"

/**
  Adds the first neighborhood of the given element in the data vector to the cliques vector.
 
  @param data binary image data in its entirety
  @param clique a clique of image graph elements grouped together according to LAP
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
  @param index index of the current image pixel whose first neighborhood we are getting
 */
void getFirstNeighborhood (const std::vector<uint8_t> *data,
			     std::vector< std::pair< uint8_t, int > > *clique,
			     const int WIDTH,
			     const int HEIGHT,
			     const int index) {
	//store the current elements left neighbor (if it exists) in clique
	if (index % WIDTH) { //i % WIDTH is 0 on the left edges			
		clique->push_back (std::make_pair(data->at(index - 1), index - 1));
	}

	//store the current element's top neighbor (if it exists) in clique
	if (index >= WIDTH) { //top neighbor exists for every element after those in the first row
		clique->push_back (std::make_pair(data->at(index - WIDTH), index - WIDTH));
	}
	
	//store the current element's right neighbor (if it exists) in clique
	if ( (index % (WIDTH - 1) && index < (WIDTH * HEIGHT) - 1) || index == 0) { //i % (WIDTH - 1) is 0 for on the right edges
		clique->push_back(std::make_pair(data->at(index + 1), index + 1));
	}

	//store the current element's bottom neighbor (if it exists) in clique
	if (index < (WIDTH * (HEIGHT - 1))) { //bottom neighbor exists for every element before those in the last row
		clique->push_back(std::make_pair(data->at(index + WIDTH), index + WIDTH));
	}
}

/**
  Partitions the image graph into a group of cliques. Cliques are created according to the Linear and
  Parallel (LAP) algorithm developed by Mizrahi, Denil, and de Freitas.
 
  @param cliques cliques of the graph stored as pairs of values with their positions in the original data vector
  @param data the input image's binary data stored one-dimensionally
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
 */
void LAP (std::vector< std::vector< std::pair< uint8_t, int > > > *cliques, 
		      const std::vector<uint8_t> *data, 
		      const int WIDTH, 
		      const int HEIGHT) {
	// temp clique vector to store individual cliques as they are being generated
	// each clique is saved to the set of all cliques once generated
	std::vector< std::pair< uint8_t, int > > clique;

	for (int i = 0; i < HEIGHT * WIDTH; i++) {

		// store the current element in cliqe
		clique.push_back(std::make_pair(data->at(i), i));		
		
		// store the first neighborhood of the current element in clique
		getFirstNeighborhood (data, &clique, WIDTH, HEIGHT, i);

		// store the first neighborhood of the current element's left neighbor (if it exists) in clique
		if (i % WIDTH) { //i % WIDTH is 0 on the left edges
			getFirstNeighborhood (data, &clique, WIDTH, HEIGHT, i - 1);
		}

		// store the first neighborhood of the current element's top neighbor (if it exists) in clique
		if (i >= WIDTH) { // top neighbor exists for every element after those in the first row
			getFirstNeighborhood (data, &clique, WIDTH, HEIGHT, i - WIDTH);
		}

		// store the first neighborhood of the current element's right neighbor (if it exists) in clique
		if (i % (WIDTH - 1) || i == 0) { //i % (WIDTH - 1) is 0 for on the right edges
			getFirstNeighborhood (data, &clique, WIDTH, HEIGHT, i + 1);
		}

		// store the first neighborhood of the current element's bottom neighbor (if it exists) in clique
		if (i < WIDTH * (HEIGHT - 1)) { // bottom neighbor exists for every element before those in the last row
			getFirstNeighborhood (data, &clique, WIDTH, HEIGHT, i + WIDTH);
		}
		
		// remove all of the duplicate elements in the clique
		removeDuplicates(&clique);	
	
		// store the current clique in the set of all cliques
		cliques->push_back(clique);
	
		// now reset clique to prepare it to store the next clique
		clique.erase(clique.begin(), clique.end());
	}
}

