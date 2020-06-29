/**
  Implements Linear and Parallel (LAP) graph partitioning algorithm.
 */

#include <cstdint>
#include <iostream> //for debugging
#include <utility>
#include <vector>
#include "../Model/AuxMRF.hpp"
#include "../Model/ThreadData.hpp"
#include "LAP.hpp"
#include "remove_duplicates.hpp"


bool isEven(const size_t num) {
    return (num % 2) == 0;
}

/**
  Stores a set of maximal cliques representing every node in the graph in auxMRFs. These will
  serve as the base elements from which we obtain the auxiliary MRFs
 
  @param auxMRFs graph partitions container
  @param data the image data
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
  @param THREAD_ID id of the current thread
  @param NUM_THREADS total number of threads running
 */
void getMaximalCliques(std::vector<AuxMRF> *auxMRFs,
                       const std::vector<uint8_t> *data,
                       const size_t WIDTH,
                       const size_t HEIGHT,
                       const size_t THREAD_ID,
                       const size_t NUM_THREADS) {
    
    if (isEven(HEIGHT)) {
        size_t CLIQUES_PER_THREAD = WIDTH * HEIGHT / 2 / NUM_THREADS;
        size_t START_ROW = (THREAD_ID * CLIQUES_PER_THREAD / WIDTH) * 2;
        size_t START_COL = (THREAD_ID * CLIQUES_PER_THREAD) % WIDTH;
        size_t END_ROW = START_ROW + ((START_COL + CLIQUES_PER_THREAD - 1) / WIDTH) * 2;
        size_t END_COL = (START_COL + CLIQUES_PER_THREAD - 1) % WIDTH;
        
        if (END_ROW > HEIGHT - 2) {
            END_ROW = HEIGHT - 2;
            END_COL = WIDTH - 1;
        }
        
        if (START_ROW != END_ROW) {
            
            size_t i = START_ROW;
            
            // get maximal cliques in the first row belonging to the thread
            for (size_t j = START_COL; j < WIDTH; ++j) {
                // top node in the maximal clique
                auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                // bottom node in the maximal clique
                auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                // temp vector to store the maximal clique
                AuxMRF maximalClique;
                // push the nodes into the maximal clique
                maximalClique.addBaseNode(top);
                maximalClique.addBaseNode(bottom);
                // push the maximal clique into the collection
                auxMRFs->push_back(maximalClique);
            }
            // go to the next row
            i+=2;
            // get maximal cliques in the (guaranteed) complete rows
            // between the first and last rows belonging to the thread
            for ( ; i < END_ROW; i+=2) {
                for (size_t j = 0; j < WIDTH; ++j) {
                    // top node in the maximal clique
                   auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                   // bottom node in the maximal clique
                   auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                   // temp vector to store the maximal clique
                   AuxMRF maximalClique;
                   // push the nodes into the maximal clique
                   maximalClique.addBaseNode(top);
                   maximalClique.addBaseNode(bottom);
                   // push the maximal clique into the collection
                   auxMRFs->push_back(maximalClique);
                }
            }
            // now i == END_ROW
            for (size_t j = 0; j <= END_COL; ++j) {
                // top node in the maximal clique
                auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                // bottom node in the maximal clique
                auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                // temp vector to store the maximal clique
                AuxMRF maximalClique;
                // push the nodes into the maximal clique
                maximalClique.addBaseNode(top);
                maximalClique.addBaseNode(bottom);
                // push the maximal clique into the collection
                auxMRFs->push_back(maximalClique);
            }
        } else {
            size_t i = START_ROW; // (which is the same as END_ROW)
            for (size_t j = START_COL; j <= END_COL; ++j) {
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
        size_t CLIQUES_PER_THREAD = WIDTH * HEIGHT / 2 / NUM_THREADS;
        size_t START_ROW = (THREAD_ID * CLIQUES_PER_THREAD * 2 / WIDTH);
        size_t START_COL = (THREAD_ID * CLIQUES_PER_THREAD * 2) % WIDTH;
        size_t END_ROW = START_ROW + ((START_COL + CLIQUES_PER_THREAD * 2 - 1) / WIDTH);
        size_t END_COL = (START_COL + CLIQUES_PER_THREAD * 2 - 1) % WIDTH;
        
        if (END_ROW > HEIGHT - 1) {
            END_ROW = HEIGHT - 1;
            END_COL = WIDTH - 1;
        }
        
        if (START_ROW != END_ROW) {
            size_t i = START_ROW;
            // get maximal cliques in the first row belonging to the thread
            for (size_t j = START_COL; j < WIDTH; j+=2) {
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
            ++i; // go to the next row
            // get maximal cliques in the (guaranteed) complete
            // rows between the thread's first and last rows
            for ( ; i < END_ROW; ++i) {
                for (size_t j = 0; j < WIDTH; ++j) {
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
            // now i == END_ROW
            // get maximal cliques in the last row belonging to the thread
            for (size_t j = 0; j <= END_COL; j+=2) {
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
        } else {
            size_t i = START_ROW; // (which is also equal to END_ROW)
            for (size_t j = 0; j <= END_COL; j+=2) {
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
        // nodes as maximal cliques and handle the overlap in the last row.
        // results in WIDTH * (HEIGHT + 1) / 2 maximal cliques
        size_t CLIQUES_PER_THREAD = WIDTH * (HEIGHT + 1) / 2 / NUM_THREADS;
        size_t START_ROW = std::min((THREAD_ID * CLIQUES_PER_THREAD / WIDTH) * 2, HEIGHT - 2);
        size_t START_COL = (THREAD_ID * CLIQUES_PER_THREAD) % WIDTH;
        size_t END_ROW = START_ROW + ((START_COL + CLIQUES_PER_THREAD - 1) / WIDTH) * 2;
        size_t END_COL = (START_COL + CLIQUES_PER_THREAD - 1) % WIDTH;
        
        if (END_ROW > HEIGHT - 2) {
            END_ROW = HEIGHT - 2;
            END_COL = WIDTH - 1;
        }
        
//        std::cout << "I'm Thread " << THREAD_ID << " and I've got row " << START_ROW << ", column " << START_COL <<  " through row " << END_ROW << ", column " << END_COL << std::endl;
                
        if (START_ROW != END_ROW) {
            size_t i = START_ROW;
            
            // get maximal cliques in the first row belonging to the thread
            for (size_t j = START_COL; j < WIDTH; ++j) {
                // top node in the maximal clique
                auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                // bottom node in the maximal clique
                auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                // temp vector to store the maximal clique
                AuxMRF maximalClique;
                // push the nodes into the maximal clique
                maximalClique.addBaseNode(top);
                maximalClique.addBaseNode(bottom);
                // push the maximal clique into the collection
                auxMRFs->push_back(maximalClique);
            }
            // go to the next row
            i+=2;
            // get maximal cliques in the (guaranteed) complete rows
            // between the first and last rows belonging to the thread
            for ( ; i < END_ROW; i+=2) {
                for (size_t j = 0; j < WIDTH; ++j) {
                    // top node in the maximal clique
                   auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                   // bottom node in the maximal clique
                   auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                   // temp vector to store the maximal clique
                   AuxMRF maximalClique;
                   // push the nodes into the maximal clique
                   maximalClique.addBaseNode(top);
                   maximalClique.addBaseNode(bottom);
                   // push the maximal clique into the collection
                   auxMRFs->push_back(maximalClique);
                }
            }
            // Now i == END_ROW or i == END_ROW + 1. Make sure i == END_ROW.
            i = END_ROW;
            for (size_t j = 0; j <= END_COL; ++j) {
                // top node in the maximal clique
                auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                // bottom node in the maximal clique
                auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
                // temp vector to store the maximal clique
                AuxMRF maximalClique;
                // push the nodes into the maximal clique
                maximalClique.addBaseNode(top);
                maximalClique.addBaseNode(bottom);
                // push the maximal clique into the collection
                auxMRFs->push_back(maximalClique);
            }
        } else {
            size_t i = START_ROW; // (which is the same as END_ROW)
            for (size_t j = START_COL; j <= END_COL; ++j) {
                // top node in the maximal clique
                auto top = Node(data->at(i * WIDTH + j), i * WIDTH + j);
                // bottom node in the maximal clique
                auto bottom = Node(data->at((i + 1) * WIDTH + j), (i + 1) * WIDTH + j);
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
                    const size_t WIDTH,
                    const size_t HEIGHT) {
    
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
 
  @param auxMRFs graph partitions container
  @param data the image data
  @param WIDTH width of the input image
  @param HEIGHT height of the input image
  @param THREAD_ID id of the current thread
  @param NUM_THREADS total number of threads running
 */
void LAP (std::vector<AuxMRF> *auxMRFs,
          const std::vector<uint8_t> *data,
          const size_t WIDTH,
          const size_t HEIGHT,
          const size_t THREAD_ID,
          const size_t NUM_THREADS) {
    
    // get the maximal cliques to create the auxiliary MRFs from
    getMaximalCliques(auxMRFs, data, WIDTH, HEIGHT, THREAD_ID, NUM_THREADS);
    
    // augment the cliques to get the distributable auxiliary MRFs
    augmentCliques(auxMRFs, data, WIDTH, HEIGHT);
}

