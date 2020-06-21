/**
  Implements Linear and Parallel (LAP) graph partitioning algorithm.
 */

#include <cstdint>
#include <iostream> //for debugging
#include <utility>
#include <vector>
#include "AuxMRF.hpp"
#include "LAP.hpp"
#include "remove_duplicates.hpp"

bool isEven(const int num) {
    return num % 2 == 0;
}

/**
  Stores a set of maximal cliques representing every node in the graph in auxMRFs. These will
  serve as the base elements from which we obtain the auxiliary MRFs
 
  @param auxMRFs graph partitions container
  @param data the image data
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
 */
void getMaximalCliques(std::vector<AuxMRF> *auxMRFs,
                       const std::vector<uint8_t> *data,
                       const int WIDTH,
                       const int HEIGHT) {
        
        // Break up the graph in such a way that we eliminate overlap.
        // If either HEIGHT or WIDTH is even, there will be no overlap.
        // If not, then the last node will have to take in some neighbor
        // that is also in another clique in order to get a maximal clique.
        // We will track this by marking its position as -1 to maintain
        // determinism.
        if (isEven(HEIGHT)) {
            // get vertically adjacent pairs of pixels as maximal cliques
            for (size_t i = 0; i < HEIGHT; i+=2) {
                for (size_t j = 0; j < WIDTH; ++j) {
                    // top node in the maximal clique
                    auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                    // bottom node in the maximal clique
                    auto bottom = Node(data->at((i + 1) * WIDTH + j), i * WIDTH + j + 1);
                    // temp vector to store the maximal clique
                    AuxMRF maximalClique;
                    // push the nodes into the maximal clique
                    maximalClique.addBaseNode(top);
                    maximalClique.addBaseNode(bottom);
                    // push the maximal clique into the collection
                    auxMRFs->push_back(maximalClique);
                }
            }
        } else if (isEven(WIDTH)) {
            // get horizontally adjacent pairs of nodes as maximal cliques
            for (size_t i = 0; i < HEIGHT; i++) {
                for (size_t j = 0; j < WIDTH; j+=2) {
                    // left node in the maximal clique
                    auto left = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                    // bottom node in the maximal clique
                    auto right = Node(data->at(i * WIDTH + j + 1), i * WIDTH + j + 1);
                    // temp vector to store the maximal clique
                    AuxMRF maximalClique;
                    // push the nodes into the maximal clique
                    maximalClique.addBaseNode(left);
                    maximalClique.addBaseNode(right);
                    // push the maximal clique into the collection
                    auxMRFs->push_back(maximalClique);
                }
            }
        } else {
            // neither width nor height even, so we will get vertically adjacent
            // nodes as maximal cliques and handle the overlap in the last row
            
            // get vertically adjacent pairs of pixels as maximal cliques
            // up until the second to last row
            for (size_t i = 0; i < HEIGHT; i+=2) {
                for (size_t j = 0; j < WIDTH; ++j) {
                    // top node in the maximal clique
                    auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                    // bottom node in the maximal clique
                    auto bottom = Node(data->at((i + 1) * WIDTH + j), i * WIDTH + j + 1);
                    // temp vector to store the maximal clique
                    AuxMRF maximalClique;
                    // push the nodes into the maximal clique
                    maximalClique.addBaseNode(top);
                    maximalClique.addBaseNode(bottom);
                    // push the maximal clique into the collection
                    auxMRFs->push_back(maximalClique);
                }
            }
            // handle the last row by including the second to last row again
            for (size_t i = 0; i < WIDTH; ++i) {
                auto top = Node(data->at((HEIGHT - 2) * WIDTH + i), (HEIGHT - 2) * WIDTH + i);
                auto bottom = Node(data->at((HEIGHT - 1) * WIDTH + i), (HEIGHT - 1) * WIDTH + i);
                // temp vector to store the maximal clique
                AuxMRF maximalClique;
                // push the nodes into the maximal clique
                maximalClique.addBaseNode(top);
                maximalClique.addBaseNode(bottom);
                // push the maximal clique into the collection
                auxMRFs->push_back(maximalClique);
            }
        }
}

/**
  Completes the Linear and Parallel algorithm by adding any node with a neighbor in the maximal
  clique stored in auxMRFs to the maximal clique.
 
  @param auxMRFs graph partitons container
  @param data the image data
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
 */
void augmentCliques(std::vector<AuxMRF> *auxMRFs,
                    const std::vector<uint8_t> *data,
                    const int WIDTH,
                    const int HEIGHT) {
    
    for (auto &auxMRF: *auxMRFs) {
        for (auto baseNode: auxMRF.getBaseNodes()) {
            
            // add the base node's left neighbor to the augmented clique
            // i % WIDTH is 0 on the left edges
            if (baseNode.position % WIDTH != 0) {
                auto augmentingNode = Node(data->at(baseNode.position - 1), baseNode.position - 1);
                auxMRF.addAugmentingNode(augmentingNode);
            }
            
            // add the base node's top neighbor to the augmented clique
            if (baseNode.position >= WIDTH) { //top neighbor exists for every element after those in the first row
                auto augmentingNode = Node(data->at(baseNode.position - WIDTH), baseNode.position - WIDTH);
                auxMRF.addAugmentingNode(augmentingNode);
            }

            // add the base node's right neighbor to the augmented clique
            // i % (WIDTH - 1) is 0 for nodes on the right edges
            if ( ( ( (baseNode.position + 1) % WIDTH ) != 0) || ( baseNode.position == 0 ) ) {
                auto augmentingNode = Node(data->at(baseNode.position + 1), baseNode.position + 1);
                auxMRF.addAugmentingNode(augmentingNode);
            }
            
            // Add the base node's bottom neighbor to the augmented clique.
            // Bottom neighbor exists for every element before those in the
            // last row.
            if (baseNode.position < (WIDTH * (HEIGHT - 1))) {
                auto augmentingNode = Node(data->at(baseNode.position + WIDTH), baseNode.position + WIDTH);
                auxMRF.addAugmentingNode(augmentingNode);
            }
        }
    }
}

/**
  Partitions the image graph into a group of auxiliary MRFs. Auxiliary MRFs are created according to the
  Linear and Parallel (LAP) algorithm developed by Mizrahi, Denil, and de Freitas.
 
  @param auxMRFs graph partitons container
  @param data the image data
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
 */
void LAP (std::vector<AuxMRF> *auxMRFs,
          const std::vector<uint8_t> *data,
          const int WIDTH,
          const int HEIGHT) {
        
    // get the maximal cliques to create the auxiliary MRFs from
    getMaximalCliques(auxMRFs, data, WIDTH, HEIGHT);
    
    // augment the cliques to get the distributable auxiliary MRFs
    augmentCliques(auxMRFs, data, WIDTH, HEIGHT);
}

