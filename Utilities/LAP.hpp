/**
  Header file for the Linear and Parallel (LAP) graph partitioning algorithm.
 */

#ifndef LAP_HPP
#define LAP_HPP

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
          const size_t NUM_THREADS);

#endif //LAP_HPP
