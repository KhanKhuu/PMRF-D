/**
 The structure that contains the data to pass to functions called with pthread_create.
*/

#ifndef ThreadData_hpp
#define ThreadData_hpp

#include <stdio.h>
#include <vector>
#include "AuxMRF.hpp"

struct ThreadData {
    size_t THREAD_ID;
    size_t NUM_THREADS;
    std::vector<uint8_t> *data;
    std::vector<AuxMRF> *auxMRFs;
    size_t WIDTH;
    size_t HEIGHT;
};

#endif /* ThreadData_hpp */
